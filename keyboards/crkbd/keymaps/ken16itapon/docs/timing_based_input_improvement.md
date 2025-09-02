# 薙刀式キーボードにおけるタイミングベース入力判定の改善提案

## 概要
本ドキュメントでは、crkbd/rev4_1/standard:ken16itaponキーマップにおける2つの入力判定の改善案を提案します。

1. **薙刀式の同時打ち判定**：キーの押下時間の重なり率による判定
2. **修飾キーの誤入力防止**：Mod-Tapキーの意図しない修飾を防ぐ仕組み

---

## 1. 薙刀式の同時打ち判定改善

### 現状の問題点
- 現在の実装では、2つのキーが一瞬でも同時に押されていれば同時打ちと判定される
- ビットマスク（`keycomb`）による即座の判定
- 個人の打鍵速度の差を考慮できない

### 提案する解決策：時間重なり率による判定

#### 基本概念
2つのキーの押下時間の重なりが、短い方のキーの押下時間に対して一定の割合（例：50%）以上の場合に同時打ちと判定する。

#### 必要なデータ構造

```c
// キーの押下情報を記録する構造体
typedef struct {
    uint16_t keycode;      // キーコード
    uint16_t press_time;   // 押された時刻（ミリ秒）
    uint16_t release_time; // 離された時刻（ミリ秒）
    bool     is_pressed;   // 現在押されているか
} key_timing_t;

// 設定可能なパラメータ
typedef struct {
    uint8_t  overlap_threshold_percent; // 重なり率の閾値（%）
    uint16_t min_overlap_time_ms;      // 最小重なり時間（ミリ秒）
    uint16_t max_wait_time_ms;         // 判定待機の最大時間
} naginata_timing_config_t;
```

#### 重なり率計算アルゴリズム

```c
uint8_t calculate_overlap_percent(key_timing_t *key1, key_timing_t *key2) {
    // 重なり時間を計算
    uint16_t overlap_start = MAX(key1->press_time, key2->press_time);
    uint16_t overlap_end = MIN(key1->release_time, key2->release_time);
    
    if (overlap_start >= overlap_end) return 0; // 重なりなし
    
    uint16_t overlap_duration = overlap_end - overlap_start;
    
    // 各キーの押下時間
    uint16_t key1_duration = key1->release_time - key1->press_time;
    uint16_t key2_duration = key2->release_time - key2->press_time;
    
    // 短い方のキーの押下時間に対する重なり率を計算
    uint16_t shorter_duration = MIN(key1_duration, key2_duration);
    
    return (overlap_duration * 100) / shorter_duration;
}
```

#### 推奨パラメータ設定

```c
#define NAGINATA_OVERLAP_THRESHOLD 50  // 50%以上の重なりで同時打ち
#define NAGINATA_MIN_OVERLAP_MS 20     // 最小20ms重なり必要
#define NAGINATA_MAX_WAIT_MS 100        // 最大100ms待機
```

### 実装による効果
- より自然な同時打ち判定
- 個人の打鍵速度に合わせた調整が可能
- 誤判定の減少

### 考慮事項
- メモリ使用量の増加（タイミング情報の保存）
- 判定の遅延（最大待機時間分）
- CPUリソースの使用増加

---

## 2. 修飾キー（Mod-Tap）の誤入力防止

### 現状の問題点
- `SFT_T(KC_SPC)`のようなMod-Tapキーで、スペース→ハイフンを素早く打つと、意図せず「_」（アンダースコア）が入力される
- QMKのデフォルトでは、修飾キーが押されている間は即座に修飾が有効になる
- タイピング速度が速い場合に特に問題となる

### 提案する解決策：スマート修飾判定

#### 基本概念
修飾キーと通常キーの重なり時間が一定以上の場合のみ、修飾を適用する。

#### 必要なデータ構造

```c
// 修飾キーのタイミング情報
typedef struct {
    uint16_t keycode;
    uint16_t press_time;
    uint16_t release_time;
    bool is_active;
    bool is_mod_tap;  // Mod-Tapキーかどうか
} mod_timing_t;

// 通常キーのタイミング情報
typedef struct {
    uint16_t keycode;
    uint16_t press_time;
    bool needs_modifier;  // 修飾が必要かどうかの判定結果
    uint8_t mods_applied; // 適用された修飾キー
} key_timing_t;

// 設定パラメータ
typedef struct {
    uint16_t min_overlap_ms;      // 最小重なり時間（デフォルト: 30ms）
    uint8_t  overlap_percent;     // 重なり率の閾値（デフォルト: 40%）
    bool     enable_smart_shift;  // スマートシフト機能の有効/無効
} smart_mod_config_t;
```

#### 修飾判定アルゴリズム

```c
bool is_modifier_intentional(mod_timing_t *mod, uint16_t key_press_time) {
    uint16_t current_time = timer_read();
    
    // Mod-Tapキーの場合、タップとホールドを区別
    if (mod->is_mod_tap) {
        // タップの場合（素早く離された）
        if (!mod->is_active && 
            (mod->release_time - mod->press_time) < TAPPING_TERM) {
            return false;  // 修飾として扱わない
        }
    }
    
    // 重なり時間を計算
    uint16_t overlap_start = MAX(mod->press_time, key_press_time);
    uint16_t overlap_end = mod->is_active ? 
                          current_time : mod->release_time;
    
    if (overlap_start >= overlap_end) return false;
    
    uint16_t overlap_duration = overlap_end - overlap_start;
    
    // 最小重なり時間のチェック
    if (overlap_duration < config.min_overlap_ms) {
        return false;
    }
    
    // 修飾キーの押下時間に対する重なり率をチェック
    uint16_t mod_duration = mod->is_active ? 
        (current_time - mod->press_time) : 
        (mod->release_time - mod->press_time);
    
    uint8_t overlap_ratio = (overlap_duration * 100) / mod_duration;
    
    return overlap_ratio >= config.overlap_percent;
}
```

#### 推奨設定値

```c
#define SMART_MOD_ENABLE              // スマートモディファイア機能を有効化
#define SMART_MOD_MIN_OVERLAP_MS 30   // 最小重なり時間
#define SMART_MOD_OVERLAP_PERCENT 40  // 重なり率の閾値（%）
```

### ユーザータイプ別の推奨設定

| ユーザータイプ | MIN_OVERLAP_MS | OVERLAP_PERCENT | 説明 |
|--------------|----------------|-----------------|------|
| 高速タイピスト | 40-50ms | 45-50% | 誤修飾を強く防止 |
| 通常速度 | 30ms | 40% | バランス重視 |
| 初心者 | 20ms | 35% | 修飾を効きやすく |

### 実装による効果
- スペース→ハイフンの素早い入力で「-」が正しく入力される
- 意図的なシフト+ハイフンで「_」が確実に入力される
- 個人の打鍵速度に合わせた調整が可能

---

## 実装手順

### フェーズ1：基礎実装
1. タイミング記録用のデータ構造を追加
2. 時間計測機能の実装
3. 重なり率計算関数の実装

### フェーズ2：薙刀式への統合
1. `naginata_timing.h`と`naginata_timing.c`を作成
2. `process_naginata`関数を改修
3. 既存の即座判定モードとの切り替え機能を追加

### フェーズ3：修飾キー対応
1. `modifier_timing.h`と`modifier_timing.c`を作成
2. `process_record_user`関数を改修
3. Mod-Tapキーの特別処理を実装

### フェーズ4：デバッグと最適化
1. タイミング情報のログ出力機能
2. パラメータの実行時調整機能
3. メモリ使用量の最適化

---

## テスト項目

### 薙刀式の同時打ち
- [ ] 通常の同時打ちが正しく認識される
- [ ] 素早い連続入力が誤判定されない
- [ ] 重なり率の閾値調整が機能する
- [ ] タイムアウト処理が正しく動作する

### 修飾キーの判定
- [ ] SFT_T(KC_SPC)でスペース→ハイフンが「-」になる
- [ ] 意図的なシフト+ハイフンが「_」になる
- [ ] 他のMod-Tapキーでも同様に機能する
- [ ] 通常の修飾キーは影響を受けない

---

## 今後の拡張案

1. **学習機能**
   - ユーザーの打鍵パターンを学習
   - 自動的に閾値を調整

2. **視覚的フィードバック**
   - LEDで同時打ち判定状態を表示
   - デバッグモードでタイミング情報を可視化

3. **プリセット機能**
   - 複数の設定プリセットを保存
   - キーコンビネーションで切り替え

4. **統計情報**
   - 誤判定率の記録
   - 最適な設定値の提案

---

## まとめ

本提案では、時間的な重なりを考慮した2つの改善を提案しました：

1. **薙刀式の同時打ち判定**：重なり率による、より自然な判定
2. **修飾キーの誤入力防止**：意図しない修飾を防ぐスマート判定

これらの実装により、より快適で正確なタイピング体験が実現できると考えられます。実装の際は、段階的に機能を追加し、十分なテストを行うことが重要です。

パラメータは個人の打鍵特性に合わせて調整可能なため、ユーザーごとに最適な設定を見つけることができます。