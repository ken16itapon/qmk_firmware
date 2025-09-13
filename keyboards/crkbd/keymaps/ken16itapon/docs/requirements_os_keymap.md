# キーボードファームウェア OS別キーマッピング改修 要件定義書

## 1. 概要

### 1.1 背景
現在のファームウェアでは、OSごとのキーコード変換が単純な1対1マッピングで実装されており、特殊キーごとの柔軟な動作定義ができない。これを改修し、特殊キー毎にOSごとの修飾キーとタップ時のキー動作を個別に定義できるようにする。

### 1.2 目的
- 特殊キーごとにOS別の動作を柔軟に定義できるようにする
- 修飾キーの組み合わせ（複数キー）をサポートする
- コードの保守性と拡張性を向上させる

## 2. 対象範囲

### 2.1 対象となる特殊キー
以下の既存特殊キーを対象とする（新規追加は現時点では予定なし）：
- HENKAN（変換）
- MHENKAN（無変換）
- C_SPC（Ctrl/Cmd + Space）
- C_BSPC（Ctrl/Cmd + Backspace）
- CC_BSPC（Ctrl/Cmd + Backspace別パターン）
- C_ENT（Ctrl/Cmd + Enter）
- CS_TAB（Ctrl/Cmd + Shift + Tab）
- LOWER（レイヤー切り替え + タップ機能）
- RAISE（レイヤー切り替え + タップ機能）

### 2.2 対象OS
- macOS
- Windows
- Linux

## 3. 機能要件

### 3.1 特殊キー定義機能
各特殊キーに対して、OSごとに以下を定義できること：
- **長押し時の修飾キー**: 最大4個の修飾キーの組み合わせ
- **タップ時のキーコード**: 単一のキーコード

### 3.2 OS別動作定義
#### 3.2.1 データ構造
```c
// OS別キー設定
typedef struct {
    uint16_t mod_keys[MAX_MOD_KEYS];  // 修飾キー配列（最大4個）
    uint8_t mod_count;                 // 実際の修飾キー数
    uint16_t tap_key;                  // タップ時のキーコード
} os_key_config_t;

// 特殊キー設定（全OS分）
typedef struct {
    os_key_config_t macos;    // macOS用設定
    os_key_config_t windows;  // Windows用設定
    os_key_config_t linux;    // Linux用設定
} special_key_config_t;
```

#### 3.2.2 設定例
```c
// C_SPCキーの設定例
special_key_config_t c_spc_config = {
    .macos = {
        .mod_keys = {KC_LCMD},
        .mod_count = 1,
        .tap_key = KC_SPC
    },
    .windows = {
        .mod_keys = {KC_LCTL},
        .mod_count = 1,
        .tap_key = KC_SPC
    },
    .linux = {
        .mod_keys = {KC_LCTL},
        .mod_count = 1,
        .tap_key = KC_SPC
    }
};

// CS_TABキーの設定例（複数修飾キー）
special_key_config_t cs_tab_config = {
    .macos = {
        .mod_keys = {KC_LCMD, KC_LSFT},
        .mod_count = 2,
        .tap_key = KC_TAB
    },
    .windows = {
        .mod_keys = {KC_LCTL, KC_LSFT},
        .mod_count = 2,
        .tap_key = KC_TAB
    },
    .linux = {
        .mod_keys = {KC_LCTL, KC_LSFT},
        .mod_count = 2,
        .tap_key = KC_TAB
    }
};
```

### 3.3 設定管理
- コンパイル時の静的定義とする（config.hまたは専用の設定ファイルで定義）
- 実行時の変更は不要（EEPROMへの保存は実装しない）

## 4. 非機能要件

### 4.1 パフォーマンス
- キー処理のレスポンスに影響を与えないこと
- メモリ使用量の増加を最小限に抑えること

### 4.2 互換性
- 既存のキーハンドリング処理フローを可能な限り維持すること
- 既存の`key_state_t`構造体を拡張する形で実装すること

### 4.3 保守性
- 設定の追加・変更が容易であること
- コードの可読性を維持すること
- テスタビリティを考慮した設計とすること

## 5. 実装方針

### 5.1 構造体の拡張
既存の`key_state_t`構造体を以下のように拡張する：

```c
typedef struct key_state {
    // 既存フィールド
    bool is_pressed;
    uint16_t pressed_time;
    uint16_t released_time;
    bool code_sent;
    bool rapid_press;
    bool repeat_active;
    bool other_key_pressed;
    
    // 削除または置換
    // uint16_t keycode;                 // OS固有変換後のキーコード
    // uint16_t mod_keys[MAX_MOD_KEYS];  // 修飾キー配列
    // uint8_t mod_count;                 // 修飾キー数
    
    // 新規追加
    special_key_config_t* config;        // OS別設定へのポインタ
} key_state_t;
```

### 5.2 キー処理フロー

#### 5.2.1 特殊キー単独押下時の処理
1. 特殊キー押下時：`is_pressed`フラグをセット（修飾キーは登録しない）
2. タイマー開始
3. TAPPING_TERM内に離された場合：タップキーを送信
4. TAPPING_TERMを超えて保持された場合：修飾キーとして機能

#### 5.2.2 特殊キー＋通常キーの処理（期待される動作）
1. **特殊キー押下**
   - `handle_xxx_key()`が呼ばれる
   - `is_pressed`フラグが立つ
   - 修飾キーは**まだ登録しない**（`register_mods_for_key`はコメントアウト）
   
2. **通常キー押下**
   - `process_record_user()`のdefaultケースで処理
   - `get_mods_active()`がtrueを返す（特殊キーのis_pressedがtrue）
   - `apply_active_mods()`が呼ばれる
   - `apply_active_mods()`内で押されている特殊キーに対して`register_mods_for_key()`を実行
   - OS別設定から修飾キーを取得して登録
   - 通常キーが処理される
   
3. **結果**
   - 修飾キー＋通常キーが出力される

#### 5.2.3 修飾キー適用メカニズム
```c
// keymap.c内の通常キー処理
if (record->event.pressed && !is_modifier(keycode) && 
    get_mods_active()) {  // 特殊キーが押されている場合
  apply_active_mods();    // 修飾キーを適用
}

// apply_active_mods()の実装
void apply_active_mods(void) {
  if (henkan_state.is_pressed) {
    register_mods_for_key(&henkan_state);
  }
  // 他の特殊キーも同様にチェック
}

// register_mods_for_key()の実装
void register_mods_for_key(key_state_t *key_state) {
  const os_key_config_t* config = get_os_key_config(key_state->key_id);
  if (config && config->mod_count > 0) {
    for (uint8_t i = 0; i < config->mod_count; i++) {
      register_code(config->mod_keys[i]);  // 直接登録（追加変換なし）
    }
  }
}
```

### 5.3 ファイル構成
```
keyboards/crkbd/keymaps/ken16itapon/
├── key_handlers.c      # キーハンドリング処理（修正）
├── key_handlers.h      # ヘッダーファイル（修正）
├── state_manager.c     # 状態管理（修正）
├── state_manager.h     # ヘッダーファイル（修正）
├── os_specific.c       # OS固有処理（修正）
├── os_specific.h       # ヘッダーファイル（修正）
└── special_keys_config.h  # 特殊キー設定定義（新規）
```

## 6. テスト要件

### 6.1 単体テスト
- 各特殊キーのOS別動作確認
- 修飾キー組み合わせの動作確認
- タップ/長押し判定の動作確認

### 6.2 結合テスト
- 実機での各OS環境下での動作確認
  - macOS環境
  - Windows環境
  - Linux環境

## 7. 制約事項

### 7.1 技術的制約
- QMKファームウェアの制限内で実装すること
- ファームウェアサイズの制限を超えないこと

### 7.2 リソース制約
- メモリ使用量を最小限に抑えること
- CPU処理負荷を増やさないこと

## 8. リスクと対策

### 8.1 リスク
- 既存機能への影響
- メモリ使用量の増加
- 処理速度の低下

### 8.2 対策
- 段階的な実装とテスト
- プロファイリングによるパフォーマンス確認
- 既存コードのバックアップとバージョン管理

## 9. スケジュール（案）

1. **Phase 1**: データ構造の設計と定義（1日）
2. **Phase 2**: 設定管理機能の実装（2日）
3. **Phase 3**: キーハンドリング処理の改修（3日）
4. **Phase 4**: テストと修正（2日）
5. **Phase 5**: ドキュメント作成（1日）

## 10. 成果物

- 改修されたファームウェアコード
- 特殊キー設定ファイル
- テスト結果報告書
- 設定方法のドキュメント

## 11. 追加要件（実装時の指示事項）

### 11.1 ビルド環境
- **ターゲットマイコン**: RP2040（rev4_1用）
  - AVRではメモリ制限（28672バイト）を超えるため、RP2040搭載のrev4_1を使用すること
  - ビルドコマンド: `qmk compile -kb crkbd/rev4_1/standard -km ken16itapon`

### 11.2 レイアウトマクロ
- **使用レイアウト**: `LAYOUT_split_3x6_3_ex2`
  - rev4_1では追加キー（HYSPC、TENKEY、OS_MEH等）をサポートするため、標準の`LAYOUT_split_3x6_3`（42キー）ではなく、`LAYOUT_split_3x6_3_ex2`（46キー）を使用すること
  - 定義場所: `keyboards/crkbd/rev4_1/info.json`

### 11.3 実装上の注意事項
- **ヘッダー依存関係**: 循環参照を避けるため、`special_keys_config.h`で`struct key_state`の前方宣言を使用
- **文字列マクロ**: `SEND_STRING`マクロは初期化子で使用できないため、`send_string()`関数を使用
- **キーコード**: `KC_HENKAN`、`KC_MHENKAN`ではなく、`HENKAN`、`MHENKAN`を使用
- **修飾キー登録タイミング**: 
  - 特殊キー押下時には修飾キーを登録せず、`is_pressed`フラグのみセット
  - 通常キー押下時に`apply_active_mods()`経由で修飾キーを登録
  - これにより、特殊キー単独のタップ機能と、特殊キー＋通常キーの修飾機能が両立

### 11.4 重要な設計判断
- **`register_mods_for_key`のコメントアウト**: 特殊キー押下時の即座の修飾キー登録は行わない
- **`apply_active_mods`による遅延登録**: 通常キー押下時に初めて修飾キーを登録することで、タップ/ホールドの判定を適切に行う
- **OS別キーコードの直接登録**: `special_keys_config.c`で定義されたキーコードは既にOS用に設定済みのため、追加変換は不要

---

**作成日**: 2025-09-13  
**バージョン**: 1.1  
**更新日**: 2025-09-13  
**作成者**: プロジェクトマネージャー

**作成日**: 2025-09-13  
**バージョン**: 1.0  
**作成者**: プロジェクトマネージャー