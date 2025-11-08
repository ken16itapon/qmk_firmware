# 独自キーマップに特殊機能を実装する構成ガイド

## 推奨構成パターン

Keychron V2（および一般的なQMKキーボード）で独自の特殊機能を実装する場合、以下の構成を推奨します。

---

## 基本構成：モジュール分割型

### ディレクトリ構造

```
keyboards/keychron/v2/ansi/keymaps/your_keymap/
├── keymap.c           # メインキーマップ定義
├── keymap.h           # カスタムキーコード・レイヤー定義
├── config.h           # キーマップ固有の設定
├── rules.mk           # 機能有効化設定
├── key_handlers.c     # キー処理ロジック（特殊機能）
├── key_handlers.h     # ハンドラー関数宣言
├── state_manager.c    # 状態管理（複雑な状態を持つ場合）
├── state_manager.h    # 状態管理の型定義
└── README.md          # キーマップドキュメント
```

**参考例**: `keyboards/crkbd/keymaps/ken16itapon/` がこの構成を採用しています。

---

## 各ファイルの役割と実装例

### 1. keymap.h - カスタムキーコードとレイヤー定義

**役割**: カスタムキーコード、レイヤー、マクロ定義を一元管理

```c
#pragma once

#include QMK_KEYBOARD_H

// カスタムキーコード定義
enum custom_keycodes {
    // QMKの安全な範囲から開始
    KC_MY_CUSTOM = SAFE_RANGE,
    KC_DOUBLE_TAP,      // ダブルタップ検出キー
    KC_HOLD_ACTION,     // ホールド時に特殊動作
    KC_COMBO_KEY,       // コンボキー
    KC_MACRO_1,         // カスタムマクロ
    OS_SWITCH,          // OS切替
};

// レイヤー定義
enum layers {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
    _SPECIAL,
};

// マクロ定義
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define ADJUST  MO(_ADJUST)

// 便利なショートカット
#define KC_CTAB LCTL(KC_TAB)
#define KC_STAB LSFT(KC_TAB)

// 関数宣言（他のファイルから使用）
bool process_record_user(uint16_t keycode, keyrecord_t *record);
void matrix_scan_user(void);
layer_state_t layer_state_set_user(layer_state_t state);
```

---

### 2. keymap.c - キーマップ本体

**役割**: レイアウト定義とエントリーポイント関数

```c
#include "keymap.h"
#include "key_handlers.h"
#include "state_manager.h"

// キーマップ定義
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ansi_67(
        KC_ESC,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_INS,
        KC_TAB,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
        KC_DOUBLE_TAP,KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,           KC_HOME,
        KC_LSFT,               KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT, KC_UP,
        KC_LCTL,      KC_LWIN, KC_LALT,                            KC_SPC,                             KC_RALT,  LOWER,    RAISE,    KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_LOWER] = LAYOUT_ansi_67(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______, _______,
        _______, _______, _______,                            _______,                            _______,  _______,  _______,  _______, _______, _______
    ),

    // ... 他のレイヤー
};

// 初期化処理
void keyboard_post_init_user(void) {
    // 状態管理の初期化
    initialize_key_states();
}

// キー入力処理のエントリーポイント
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // key_handlers.c に処理を委譲
    return handle_custom_keys(keycode, record);
}

// マトリックススキャン時の処理
void matrix_scan_user(void) {
    // タイマーベースの処理をここに記述
    check_tapping_timeout();
}

// レイヤー切替時の処理
layer_state_t layer_state_set_user(layer_state_t state) {
    // レイヤー変更時の副作用をここに記述
    on_layer_change(get_highest_layer(state));
    return state;
}
```

---

### 3. key_handlers.h - キーハンドラーのインターフェース

**役割**: キー処理関数の宣言と状態変数のextern宣言

```c
#pragma once

#include QMK_KEYBOARD_H
#include "state_manager.h"

// キー処理のメイン関数
bool handle_custom_keys(uint16_t keycode, keyrecord_t *record);

// 個別キーハンドラー
bool handle_double_tap_key(keyrecord_t *record);
bool handle_hold_action_key(keyrecord_t *record);
bool handle_combo_key(keyrecord_t *record);
bool handle_macro_key(uint16_t keycode, keyrecord_t *record);

// ユーティリティ関数
void check_tapping_timeout(void);
bool is_key_within_tapping_term(key_state_t *state);
void send_custom_sequence(const uint16_t *sequence, uint8_t length);
```

---

### 4. key_handlers.c - キー処理ロジック本体

**役割**: 特殊機能の実装

```c
#include "key_handlers.h"
#include "state_manager.h"

// タップ判定時間（ミリ秒）
#define TAPPING_TERM 200

// メインハンドラー
bool handle_custom_keys(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_DOUBLE_TAP:
            return handle_double_tap_key(record);
            
        case KC_HOLD_ACTION:
            return handle_hold_action_key(record);
            
        case KC_COMBO_KEY:
            return handle_combo_key(record);
            
        case KC_MACRO_1:
        case KC_MACRO_2:
            return handle_macro_key(keycode, record);
            
        case OS_SWITCH:
            if (record->event.pressed) {
                toggle_os_mode();
            }
            return false;
    }
    
    // その他のキーは通常処理
    return true;
}

// ダブルタップ検出
bool handle_double_tap_key(keyrecord_t *record) {
    static key_state_t tap_state = {0};
    
    if (record->event.pressed) {
        // 前回のリリースから短時間ならダブルタップ
        if (timer_elapsed(tap_state.released_time) < TAPPING_TERM) {
            // ダブルタップ動作
            SEND_STRING("Double Tap!");
            tap_state.released_time = 0; // リセット
            return false;
        }
        
        // 通常のタップ
        tap_code(KC_ESC);
        
    } else {
        // リリース時刻を記録
        tap_state.released_time = timer_read();
    }
    
    return false;
}

// ホールド時アクション
bool handle_hold_action_key(keyrecord_t *record) {
    static key_state_t hold_state = {0};
    
    if (record->event.pressed) {
        hold_state.is_pressed = true;
        hold_state.pressed_time = timer_read();
        
    } else {
        uint16_t hold_duration = timer_elapsed(hold_state.pressed_time);
        
        if (hold_duration < TAPPING_TERM) {
            // タップ動作
            tap_code(KC_A);
        } else {
            // ホールド動作（Ctrl+A）
            register_code(KC_LCTL);
            tap_code(KC_A);
            unregister_code(KC_LCTL);
        }
        
        hold_state.is_pressed = false;
    }
    
    return false;
}

// コンボキー（他のキーと組み合わせて動作）
bool handle_combo_key(keyrecord_t *record) {
    static bool combo_ready = false;
    
    if (record->event.pressed) {
        combo_ready = true;
        // 他のキーが押されるまで待機
        
    } else {
        if (combo_ready) {
            // タイムアウト or 単独押しなら通常動作
            tap_code(KC_SPC);
        }
        combo_ready = false;
    }
    
    return false;
}

// マクロ実行
bool handle_macro_key(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return false;
    }
    
    switch (keycode) {
        case KC_MACRO_1:
            SEND_STRING("hello@example.com");
            break;
            
        case KC_MACRO_2:
            // 複雑なマクロ
            register_code(KC_LCTL);
            tap_code(KC_C);
            unregister_code(KC_LCTL);
            wait_ms(100);
            register_code(KC_LCTL);
            tap_code(KC_V);
            unregister_code(KC_LCTL);
            break;
    }
    
    return false;
}

// タイムアウトチェック（matrix_scan_user から呼ばれる）
void check_tapping_timeout(void) {
    // ここでタイムアウト処理を実装
    // 例: ホールド状態のキーが一定時間経過したら修飾キー化
}
```

---

### 5. state_manager.h - 状態管理の型定義

**役割**: 複雑な状態を持つ機能の状態管理

```c
#pragma once

#include QMK_KEYBOARD_H

// キー状態構造体
typedef struct {
    bool is_pressed;           // 現在押下中か
    uint16_t pressed_time;     // 押下開始時刻
    uint16_t released_time;    // リリース時刻
    bool code_sent;            // キーコード送信済みか
    bool rapid_press;          // 連続押し判定
    bool other_key_pressed;    // 他のキーが押された
} key_state_t;

// OS モード
typedef enum {
    OS_MAC,
    OS_WINDOWS,
    OS_LINUX
} os_mode_t;

// グローバル状態
extern os_mode_t current_os;

// 初期化
void initialize_key_states(void);

// OS切替
void toggle_os_mode(void);
os_mode_t get_current_os(void);

// レイヤー変更通知
void on_layer_change(uint8_t layer);

// キー状態リセット
void reset_all_key_states(void);
```

---

### 6. state_manager.c - 状態管理の実装

**役割**: グローバル状態の管理

```c
#include "state_manager.h"

// グローバル変数定義
os_mode_t current_os = OS_MAC;

// 各キーの状態
key_state_t double_tap_state = {0};
key_state_t hold_action_state = {0};

// 初期化
void initialize_key_states(void) {
    current_os = OS_MAC;
    // 他の初期化処理
}

// OS切替
void toggle_os_mode(void) {
    current_os = (current_os + 1) % 3; // MAC → WIN → LINUX → MAC
    
    // OS変更時の処理
    switch (current_os) {
        case OS_MAC:
            // Mac用の設定
            break;
        case OS_WINDOWS:
            // Windows用の設定
            break;
        case OS_LINUX:
            // Linux用の設定
            break;
    }
}

os_mode_t get_current_os(void) {
    return current_os;
}

// レイヤー変更通知
void on_layer_change(uint8_t layer) {
    // レイヤー変更時にキー状態をリセット
    reset_all_key_states();
    
    // レイヤー固有の処理
    switch (layer) {
        case _SPECIAL:
            // 特殊レイヤーの初期化
            break;
    }
}

// 全キー状態リセット
void reset_all_key_states(void) {
    double_tap_state = (key_state_t){0};
    hold_action_state = (key_state_t){0};
}
```

---

### 7. config.h - キーマップ固有の設定

**役割**: QMK機能のカスタマイズ

```c
#pragma once

// タップ判定時間（ミリ秒）
#define TAPPING_TERM 200

// タップ判定を厳密にする（他のキー押下時に即座にホールド判定）
#define PERMISSIVE_HOLD

// Mod-Tap時のタップ優先
#define IGNORE_MOD_TAP_INTERRUPT

// マウスキー設定
#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_DELAY 0
#    define MOUSEKEY_INTERVAL 16
#    define MOUSEKEY_MAX_SPEED 6
#    define MOUSEKEY_TIME_TO_MAX 40
#endif

// コンボ機能
#ifdef COMBO_ENABLE
#    define COMBO_COUNT 5
#    define COMBO_TERM 50
#endif

// デバッグ用
// #define DEBUG_MATRIX_SCAN_RATE
```

---

### 8. rules.mk - 機能有効化

**役割**: QMK機能の有効/無効化とファイルの追加

```make
# 基本機能
MOUSEKEY_ENABLE = yes       # マウスキー
EXTRAKEY_ENABLE = yes       # メディアキー
CONSOLE_ENABLE = no         # デバッグコンソール（サイズ削減のため無効）
COMMAND_ENABLE = no         # デバッグコマンド

# 拡張機能
COMBO_ENABLE = yes          # キーコンボ
TAP_DANCE_ENABLE = yes      # タップダンス
KEY_OVERRIDE_ENABLE = no    # キーオーバーライド

# 追加ソースファイル
SRC += key_handlers.c
SRC += state_manager.c

# OS検出機能（必要な場合）
# OS_DETECTION_ENABLE = yes

# ファームウェアサイズ削減（必要な場合）
LTO_ENABLE = yes            # Link Time Optimization
```

---

## 実装パターン別サンプル

### パターン1: タップ/ホールド判定

```c
bool handle_tap_hold_key(keyrecord_t *record) {
    static key_state_t state = {0};
    
    if (record->event.pressed) {
        state.is_pressed = true;
        state.pressed_time = timer_read();
        state.code_sent = false;
        
    } else {
        uint16_t elapsed = timer_elapsed(state.pressed_time);
        
        if (!state.code_sent) {
            if (elapsed < TAPPING_TERM && !state.other_key_pressed) {
                // タップ動作
                tap_code(KC_ESC);
            }
            // ホールド動作はmatrix_scan_userで処理
        }
        
        state.is_pressed = false;
        state.other_key_pressed = false;
    }
    
    return false;
}

// matrix_scan_user内で呼び出す
void check_hold_timeout(key_state_t *state) {
    if (state->is_pressed && !state->code_sent) {
        if (timer_elapsed(state->pressed_time) > TAPPING_TERM) {
            // ホールド動作
            register_code(KC_LCTL);
            state->code_sent = true;
        }
    }
}
```

---

### パターン2: 連打検出（リピート）

```c
void handle_advanced_repeat(key_state_t *state) {
    if (!state->is_pressed) return;
    
    uint16_t hold_time = timer_elapsed(state->pressed_time);
    
    // 最初の500msは待機
    if (hold_time < 500) return;
    
    // その後200ms間隔でリピート
    static uint16_t last_repeat_time = 0;
    if (timer_elapsed(last_repeat_time) > 200) {
        tap_code(KC_BSPC); // 例：バックスペース連打
        last_repeat_time = timer_read();
    }
}
```

---

### パターン3: キーシーケンス検出

```c
bool detect_sequence(uint16_t keycode) {
    static uint16_t sequence[4] = {KC_NO};
    static uint8_t seq_index = 0;
    
    // シーケンスに追加
    sequence[seq_index] = keycode;
    seq_index = (seq_index + 1) % 4;
    
    // 特定シーケンス検出（例：↑↑↓↓）
    if (sequence[0] == KC_UP && 
        sequence[1] == KC_UP && 
        sequence[2] == KC_DOWN && 
        sequence[3] == KC_DOWN) {
        
        SEND_STRING("Konami Code!");
        memset(sequence, 0, sizeof(sequence));
        seq_index = 0;
        return true;
    }
    
    return false;
}
```

---

### パターン4: OS別動作切替

```c
void send_os_specific_shortcut(void) {
    switch (get_current_os()) {
        case OS_MAC:
            // Cmd+C
            register_code(KC_LGUI);
            tap_code(KC_C);
            unregister_code(KC_LGUI);
            break;
            
        case OS_WINDOWS:
        case OS_LINUX:
            // Ctrl+C
            register_code(KC_LCTL);
            tap_code(KC_C);
            unregister_code(KC_LCTL);
            break;
    }
}
```

---

### パターン5: レイヤー依存動作

```c
bool handle_layer_dependent_key(keyrecord_t *record) {
    if (!record->event.pressed) return false;
    
    uint8_t layer = get_highest_layer(layer_state);
    
    switch (layer) {
        case _BASE:
            tap_code(KC_A);
            break;
            
        case _LOWER:
            tap_code(KC_F1);
            break;
            
        case _RAISE:
            SEND_STRING("Special");
            break;
    }
    
    return false;
}
```

---

## ベストプラクティス

### 1. ファイル分割の基準

| ファイルサイズ | 機能数 | 推奨 |
|-------------|-------|------|
| < 300行 | 1-3機能 | keymap.c に直接記述 |
| 300-800行 | 4-10機能 | key_handlers.c に分離 |
| > 800行 | 11+機能 | 機能別に複数ファイル分割 |

### 2. 命名規則

```c
// カスタムキーコード
KC_MY_CUSTOM      // プレフィックス KC_

// レイヤー
_BASE, _LOWER     // プレフィックス _（アンダースコア）

// 関数
handle_xxx_key()  // キーハンドラー
check_xxx()       // チェック関数
send_xxx()        // 送信関数
on_xxx()          // イベントハンドラー
```

### 3. デバッグ方法

```c
// config.h に追加
#define CONSOLE_ENABLE

// keymap.c 内で使用
#include "print.h"

void debug_key_state(key_state_t *state) {
    uprintf("pressed: %d, time: %u\n", 
            state->is_pressed, 
            state->pressed_time);
}
```

### 4. パフォーマンス考慮

```c
// ❌ 悪い例：毎回計算
void matrix_scan_user(void) {
    if (timer_elapsed(some_state.pressed_time) > 200) {
        // 処理
    }
}

// ✅ 良い例：必要な時だけ計算
void matrix_scan_user(void) {
    if (some_state.is_pressed && !some_state.code_sent) {
        if (timer_elapsed(some_state.pressed_time) > 200) {
            // 処理
            some_state.code_sent = true;
        }
    }
}
```

---

## 参考実装

### 実際の参考になるキーマップ

1. **crkbd/keymaps/ken16itapon** (本リポジトリ)
   - 複雑な状態管理
   - OS別動作
   - モジュール分割の好例

2. **QMK公式: planck/keymaps/default**
   - シンプルな実装
   - Mod-Tapの使い方

3. **QMK公式: ergodox_ez/keymaps/default**
   - 多レイヤー構成
   - マクロ活用

---

## まとめ

### 段階的な実装アプローチ

1. **Phase 1**: `keymap.c`に直接記述（プロトタイピング）
2. **Phase 2**: `key_handlers.c`に分離（機能が増えてきたら）
3. **Phase 3**: `state_manager.c`追加（状態管理が複雑になったら）
4. **Phase 4**: さらに機能別ファイル分割（大規模化したら）

### チェックリスト

- [ ] カスタムキーコードは`SAFE_RANGE`から始める
- [ ] レイヤー名は`_`プレフィックス
- [ ] `rules.mk`で必要な機能を有効化
- [ ] `config.h`でタップ判定時間等を設定
- [ ] タイマーベース処理は`matrix_scan_user`に
- [ ] 状態変数は構造体で管理
- [ ] デバッグ時は`CONSOLE_ENABLE`を活用
- [ ] ファームウェアサイズに注意（`LTO_ENABLE`で削減）

これらの構成を採用することで、保守性が高く拡張しやすいキーマップを作成できます。
