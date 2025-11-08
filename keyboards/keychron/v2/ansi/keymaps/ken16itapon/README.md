# Ken16itapon Keymap for Keychron V2 ANSI

Keychron V2 ANSI用のカスタムキーマップテンプレートです。
モジュール分割構造により、保守性・拡張性の高い実装を実現しています。

## 特徴

- **モジュール分割**: 機能ごとにファイルを分割し、保守性向上
- **カスタムキー機能**: ダブルタップ、ホールドアクション、マクロ等
- **OS切替対応**: Mac/Windows/Linux環境に対応
- **5レイヤー構成**: Base、Lower、Raise、Adjust、Special
- **拡張可能**: 新機能追加が容易な設計

## ファイル構成

```
ken16itapon/
├── keymap.h           # カスタムキーコード・レイヤー定義
├── keymap.c           # メインキーマップ定義
├── key_handlers.h     # キー処理関数宣言
├── key_handlers.c     # キー処理ロジック実装
├── state_manager.h    # 状態管理型定義
├── state_manager.c    # 状態管理実装
├── config.h           # キーマップ固有設定
├── rules.mk           # 機能有効化設定
└── README.md          # このファイル
```

## レイヤー構成

### Layer 0: BASE
標準的なQWERTY配列

### Layer 1: LOWER
- Fキー（F1～F12）
- メディアコントロール（再生、音量等）
- ナビゲーションキー（矢印キー）

### Layer 2: RAISE
- 数字入力
- 記号入力
- 追加のナビゲーション

### Layer 3: ADJUST
- RGB制御（トグル、明るさ、色相等）
- Nキーロールオーバートグル
- リセット（QK_BOOT）

### Layer 4: SPECIAL
- カスタム機能テスト用
- マクロキー
- 特殊動作キー

## カスタムキー機能

### KC_DOUBLE_TAP
- **シングルタップ**: ESCキー
- **ダブルタップ**: "Double Tap!"文字列送信

### KC_HOLD_ACTION
- **タップ**: Aキー
- **ホールド**: Ctrl+A

### KC_COMBO_KEY
- 他のキーとの組み合わせで動作するコンボキー

### KC_MACRO_1 / KC_MACRO_2
- **MACRO_1**: メールアドレス入力 "hello@example.com"
- **MACRO_2**: コピー→貼り付けマクロ（OS別対応）

### OS_SWITCH
- OS切替（Mac → Windows → Linux → Mac）

## ビルド方法

```bash
# Keychron V2 ANSI用にコンパイル
qmk compile -kb keychron/v2/ansi -km ken16itapon

# または
make keychron/v2/ansi:ken16itapon
```

## フラッシュ方法

```bash
# DFUモードでフラッシュ
qmk flash -kb keychron/v2/ansi -km ken16itapon

# または
make keychron/v2/ansi:ken16itapon:flash
```

## カスタマイズ方法

### 1. キー配列を変更する

**keymap.c** を編集:
```c
[_BASE] = LAYOUT_ansi_67(
    KC_ESC,  KC_1,  KC_2,  ...,  // ← キーコードを変更
    ...
),
```

### 2. カスタムキーを追加する

**keymap.h** にキーコード追加:
```c
enum custom_keycodes {
    KC_MY_NEW_KEY = SAFE_RANGE,
    ...
};
```

**key_handlers.c** に処理を追加:
```c
case KC_MY_NEW_KEY:
    if (record->event.pressed) {
        // キー押下時の処理
    }
    return false;
```

### 3. マクロを変更する

**key_handlers.c** の `handle_macro_key()` を編集:
```c
case KC_MACRO_1:
    SEND_STRING("your_custom_text");
    break;
```

### 4. タップ判定時間を変更する

**config.h** を編集:
```c
#define TAPPING_TERM 200  // ミリ秒（デフォルト: 200）
```

### 5. 機能の有効/無効化

**rules.mk** を編集:
```make
COMBO_ENABLE = yes       # コンボ機能を有効化
TAP_DANCE_ENABLE = yes   # タップダンスを有効化
```

## OS別動作

### Mac
- Cmd+C/V/X/Z でコピー/貼り付け/切り取り/アンドゥ

### Windows/Linux
- Ctrl+C/V/X/Z でコピー/貼り付け/切り取り/アンドゥ

OS切替は `OS_SWITCH` キーで切り替え可能（デフォルトはMac）

## トラブルシューティング

### ファームウェアサイズが大きすぎる場合

1. **rules.mk** で不要な機能を無効化:
```make
CONSOLE_ENABLE = no
MOUSEKEY_ENABLE = no
```

2. **config.h** でRGB設定を削減:
```c
// RGB_MATRIX_KEYPRESSES をコメントアウト
```

3. LTO有効化（既にON）:
```make
LTO_ENABLE = yes
```

### キーが反応しない

1. `key_handlers.c` の `handle_custom_keys()` で `return true;` になっているか確認
2. デバッグコンソールを有効化して動作確認:
```make
CONSOLE_ENABLE = yes
```

### タップ/ホールド判定がうまくいかない

**config.h** の設定を調整:
```c
#define TAPPING_TERM 200        // 判定時間を増減
#define PERMISSIVE_HOLD         // コメントアウト/追加で動作変更
```

## 参考資料

- [QMK公式ドキュメント](https://docs.qmk.fm/)
- [Keychron V2ページ](https://www.keychron.com/products/keychron-v2)
- [カスタムキーマップガイド](../../CUSTOM_KEYMAP_GUIDE.md)
- [アーキテクチャ解説](../../ARCHITECTURE.md)

## ライセンス

GPL v2 or later

## 作成者

Ken16itapon

## 更新履歴

- 2024-XX-XX: 初版作成
