# OS別キーマッピング改修 実装計画書

## 1. 改修概要

本改修では、特殊キーごとにOS別の動作を定義できるようにするため、以下の実装を行います：
- 新しいデータ構造の導入
- 既存のkey_state_t構造体の改修
- OS別設定テーブルの実装
- キーハンドリング処理の更新

## 2. データ構造設計

### 2.1 新規データ構造

```c
// special_keys_config.h (新規ファイル)

#pragma once
#include QMK_KEYBOARD_H

// OS別キー設定構造体
typedef struct {
    uint16_t mod_keys[MAX_MOD_KEYS];  // 長押し時の修飾キー配列
    uint8_t mod_count;                 // 修飾キー数
    uint16_t tap_key;                  // タップ時のキーコード
} os_key_config_t;

// 特殊キー設定構造体（全OS分）
typedef struct {
    os_key_config_t macos;    // macOS用設定
    os_key_config_t windows;  // Windows用設定
    os_key_config_t linux;    // Linux用設定
} special_key_config_t;

// 特殊キー識別子
typedef enum {
    SK_HENKAN = 0,
    SK_MHENKAN,
    SK_C_BSPC,
    SK_CC_BSPC,
    SK_C_SPC,
    SK_C_ENT,
    SK_CS_TAB,
    SK_LOWER,
    SK_RAISE,
    SK_COUNT  // 特殊キー総数
} special_key_id_t;
```

### 2.2 既存構造体の改修

```c
// state_manager.h（改修）

typedef struct key_state {
    // 既存フィールド（変更なし）
    bool is_pressed;
    uint16_t pressed_time;
    uint16_t released_time;
    bool code_sent;
    bool rapid_press;
    bool repeat_active;
    bool other_key_pressed;
    
    // 改修：OS依存を排除
    special_key_id_t key_id;  // 特殊キー識別子（新規）
    // 削除: uint16_t keycode;
    // 削除: uint16_t mod_keys[MAX_MOD_KEYS];
    // 削除: uint8_t mod_count;
} key_state_t;
```

## 3. 設定テーブルの実装

### 3.1 特殊キー設定テーブル

```c
// special_keys_config.c (新規ファイル)

#include "special_keys_config.h"

// グローバル設定テーブル
const special_key_config_t special_key_configs[SK_COUNT] = {
    // SK_HENKAN - 変換キー
    [SK_HENKAN] = {
        .macos = {
            .mod_keys = {KC_RCMD},
            .mod_count = 1,
            .tap_key = MC_HENKAN
        },
        .windows = {
            .mod_keys = {KC_RWIN},
            .mod_count = 1,
            .tap_key = WC_HENKAN
        },
        .linux = {
            .mod_keys = {KC_RWIN},
            .mod_count = 1,
            .tap_key = KC_HENKAN
        }
    },
    
    // SK_MHENKAN - 無変換キー
    [SK_MHENKAN] = {
        .macos = {
            .mod_keys = {KC_LCMD},
            .mod_count = 1,
            .tap_key = MC_MHENKAN
        },
        .windows = {
            .mod_keys = {KC_LWIN},
            .mod_count = 1,
            .tap_key = WC_MHENKAN
        },
        .linux = {
            .mod_keys = {KC_LWIN},
            .mod_count = 1,
            .tap_key = KC_MHENKAN
        }
    },
    
    // SK_C_BSPC - Ctrl/Cmd + Backspace
    [SK_C_BSPC] = {
        .macos = {
            .mod_keys = {KC_RCMD},
            .mod_count = 1,
            .tap_key = KC_BSPC
        },
        .windows = {
            .mod_keys = {KC_RSFT},
            .mod_count = 1,
            .tap_key = KC_BSPC
        },
        .linux = {
            .mod_keys = {KC_RSFT},
            .mod_count = 1,
            .tap_key = KC_BSPC
        }
    },
    
    // SK_CC_BSPC - Ctrl + Backspace（別パターン）
    [SK_CC_BSPC] = {
        .macos = {
            .mod_keys = {KC_LCTL},
            .mod_count = 1,
            .tap_key = KC_BSPC
        },
        .windows = {
            .mod_keys = {KC_LCTL},
            .mod_count = 1,
            .tap_key = KC_BSPC
        },
        .linux = {
            .mod_keys = {KC_LCTL},
            .mod_count = 1,
            .tap_key = KC_BSPC
        }
    },
    
    // SK_C_SPC - Ctrl/Cmd + Space
    [SK_C_SPC] = {
        .macos = {
            .mod_keys = {KC_RCMD},
            .mod_count = 1,
            .tap_key = KC_SPC
        },
        .windows = {
            .mod_keys = {KC_RSFT},
            .mod_count = 1,
            .tap_key = KC_SPC
        },
        .linux = {
            .mod_keys = {KC_RSFT},
            .mod_count = 1,
            .tap_key = KC_SPC
        }
    },
    
    // SK_C_ENT - Ctrl/Cmd + Enter
    [SK_C_ENT] = {
        .macos = {
            .mod_keys = {KC_RCMD},
            .mod_count = 1,
            .tap_key = KC_ENT
        },
        .windows = {
            .mod_keys = {KC_RCTL},
            .mod_count = 1,
            .tap_key = KC_ENT
        },
        .linux = {
            .mod_keys = {KC_RCTL},
            .mod_count = 1,
            .tap_key = KC_ENT
        }
    },
    
    // SK_CS_TAB - Ctrl/Cmd + Shift + Tab（複数修飾キーの例）
    [SK_CS_TAB] = {
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
    },
    
    // SK_LOWER - レイヤー切り替え + タップ
    [SK_LOWER] = {
        .macos = {
            .mod_keys = {},
            .mod_count = 0,
            .tap_key = KC_BSPC
        },
        .windows = {
            .mod_keys = {},
            .mod_count = 0,
            .tap_key = KC_BSPC
        },
        .linux = {
            .mod_keys = {},
            .mod_count = 0,
            .tap_key = KC_BSPC
        }
    },
    
    // SK_RAISE - レイヤー切り替え + タップ
    [SK_RAISE] = {
        .macos = {
            .mod_keys = {},
            .mod_count = 0,
            .tap_key = KC_SPC
        },
        .windows = {
            .mod_keys = {},
            .mod_count = 0,
            .tap_key = KC_SPC
        },
        .linux = {
            .mod_keys = {},
            .mod_count = 0,
            .tap_key = KC_SPC
        }
    }
};

// OS別設定取得関数
const os_key_config_t* get_os_key_config(special_key_id_t key_id) {
    if (key_id >= SK_COUNT) {
        return NULL;
    }
    
    keyboard_os_t current_os = get_current_os();
    const special_key_config_t* config = &special_key_configs[key_id];
    
    switch (current_os) {
        case OS_MACOS:
            return &config->macos;
        case OS_WINDOWS:
            return &config->windows;
        case OS_LINUX:
            return &config->linux;
        default:
            return &config->windows;  // デフォルトはWindows設定
    }
}
```

## 4. 既存ファイルの改修内容

### 4.1 state_manager.c の改修

```c
// state_manager.c（改修）

#include "special_keys_config.h"

// グローバル変数の初期化を変更
key_state_t henkan_state = {.key_id = SK_HENKAN};
key_state_t mhenkan_state = {.key_id = SK_MHENKAN};
key_state_t c_bspc_state = {.key_id = SK_C_BSPC};
key_state_t cc_bspc_state = {.key_id = SK_CC_BSPC};
key_state_t c_spc_state = {.key_id = SK_C_SPC};
key_state_t c_ent_state = {.key_id = SK_C_ENT};
key_state_t cs_tab_state = {.key_id = SK_CS_TAB};
key_state_t lower_state = {.key_id = SK_LOWER};
key_state_t raise_state = {.key_id = SK_RAISE};

// initialize_key_states関数を削除（不要になる）

// 新規：修飾キー登録関数（OS対応版）
void register_mods_for_key_os(key_state_t* key_state) {
    const os_key_config_t* config = get_os_key_config(key_state->key_id);
    if (config && config->mod_count > 0) {
        for (uint8_t i = 0; i < config->mod_count; i++) {
            register_code(config->mod_keys[i]);
        }
    }
}

// 新規：修飾キー解除関数（OS対応版）
void unregister_mods_for_key_os(key_state_t* key_state) {
    const os_key_config_t* config = get_os_key_config(key_state->key_id);
    if (config && config->mod_count > 0) {
        for (uint8_t i = 0; i < config->mod_count; i++) {
            unregister_code(config->mod_keys[i]);
        }
    }
}
```

### 4.2 key_handlers.c の改修（実際の実装）

```c
// key_handlers.c（実装済み）

// handle_tap_key関数 - OS別設定からタップキーを取得
bool handle_tap_key(key_state_t *state, uint16_t record_time) {
    // タッピング判定
    if (!state->is_pressed && !state->other_key_pressed && 
        timer_elapsed(state->pressed_time) < TAPPING_TERM &&
        state->pressed_time != 0) {
        
        // 短いタップ - 複数回押しを無視
        if (state->code_sent && timer_elapsed(state->released_time) < 10) {
            return false;
        }
        
        // タップキーを送信（OS別設定から取得）
        const os_key_config_t* config = get_os_key_config(state->key_id);
        if (config) {
            tap_os_specific_key(config->tap_key);
            state->code_sent = true;
        }
    }
    
    // リピート処理（必要な場合）
    if (state->repeat_active) {
        const os_key_config_t* config = get_os_key_config(state->key_id);
        if (config) {
            unregister_os_specific_key(config->tap_key);
        }
        state->repeat_active = false;
        state->code_sent = false;
    }
    
    state->is_pressed = false;
    state->released_time = record_time;
    return false;
}

// 特殊キーハンドラー（修飾キー登録をコメントアウト）
bool handle_henkan_key(keyrecord_t *record) {
    if (record->event.pressed) {
        henkan_state.is_pressed = true;
        henkan_state.pressed_time = record->event.time;
        
        // 修飾キーを登録しない（apply_active_modsで処理）
        // register_mods_for_key(&henkan_state);
        
        other_key_pressed_except(&henkan_state);
        return false;
    } else {
        henkan_state.is_pressed = false;
        unregister_mods_for_key(&henkan_state);
        bool result = handle_tap_key(&henkan_state, record->event.time);
        
        if (henkan_state.code_sent) {
            naginata_on();
        }
        return result;
    }
}

// apply_active_mods関数 - 押されている特殊キーの修飾キーを登録
void apply_active_mods(void) {
    if (henkan_state.is_pressed) {
        register_mods_for_key(&henkan_state);
    }
    if (mhenkan_state.is_pressed) {
        register_mods_for_key(&mhenkan_state);
    }
    if(c_bspc_state.is_pressed) {
        register_mods_for_key(&c_bspc_state);
    }
    if(cc_bspc_state.is_pressed) {
        register_mods_for_key(&cc_bspc_state);
    }
    if (c_spc_state.is_pressed) {
        register_mods_for_key(&c_spc_state);
    }
    if (c_ent_state.is_pressed) {
        register_mods_for_key(&c_ent_state);
    }
    if (cs_tab_state.is_pressed) {
        register_mods_for_key(&cs_tab_state);
    }
}
```

### 4.3 os_specific.c の改修

```c
// os_specific.c（改修）

// get_os_specific_keycode関数を簡略化
uint16_t get_os_specific_keycode(uint16_t keycode) {
    // 通常のキーコード変換のみ残す（特殊キーは別処理）
    keyboard_os_t current_os = get_current_os();
    
    if (current_os == OS_MACOS) {
        // macOS用の基本修飾キー変換
        switch (keycode) {
            case KC_LCTL: return KC_LCMD;
            case KC_LWIN: return KC_LOPT;
            case KC_LALT: return KC_LCTL;
            case KC_RCTL: return KC_RCMD;
            case KC_RWIN: return KC_ROPT;
            case KC_RALT: return KC_RCTL;
            default: return keycode;
        }
    }
    
    return keycode;
}

// register_os_specific_key、unregister_os_specific_key、tap_os_specific_key は削除または簡略化
// （特殊キーは新しい仕組みで処理するため）
```

## 5. 実装手順

### Phase 1: データ構造の実装（1日目）
1. `special_keys_config.h`を作成
2. 構造体定義とenum定義を実装
3. コンパイルエラーがないことを確認

### Phase 2: 設定テーブルの実装（2日目）
1. `special_keys_config.c`を作成
2. 特殊キー設定テーブルを実装
3. `get_os_key_config()`関数を実装

### Phase 3: 既存ファイルの改修（3-4日目）
1. `state_manager.h`の構造体を改修
2. `state_manager.c`の初期化処理を改修
3. `key_handlers.c`の各ハンドラー関数を改修
4. `os_specific.c`を簡略化

### Phase 4: テストとデバッグ（5-6日目）
1. コンパイルテスト
2. 各OS環境での動作確認
3. 修飾キー組み合わせのテスト
4. タップ/長押し動作の確認

### Phase 5: 最適化と文書化（7日目）
1. コードの最適化
2. コメントの追加
3. 使用方法のドキュメント作成

## 6. 移行時の注意点

### 6.1 ビルド設定
- `rules.mk`に新規ファイルを追加：
  ```makefile
  SRC += special_keys_config.c
  ```

### 6.2 互換性の維持
- 既存のキーコード（HENKAN、MHENKAN等）は引き続き使用可能
- process_record_user()での呼び出し方法は変更なし

### 6.3 テスト項目
1. **基本動作テスト**
   - 各特殊キーのタップ動作
   - 各特殊キーの長押し動作
   - リピート機能

2. **OS別動作テスト**
   - macOSでの動作確認
   - Windowsでの動作確認
   - Linuxでの動作確認

3. **複合動作テスト**
   - 複数修飾キーの同時押し
   - レイヤー切り替えとの併用
   - 日本語入力との連携

## 7. サンプルコード（使用例）

### 7.1 設定のカスタマイズ例

```c
// ユーザーが設定を変更したい場合の例
// special_keys_config.c内で

// 例: C_SPCをmacOSではCmd+Shift+Spaceにしたい場合
[SK_C_SPC] = {
    .macos = {
        .mod_keys = {KC_RCMD, KC_RSFT},  // 複数修飾キー
        .mod_count = 2,
        .tap_key = KC_SPC
    },
    // ... 他のOS設定
}
```

### 7.2 新規特殊キーの追加例

```c
// 1. enumに追加（special_keys_config.h）
typedef enum {
    // ... 既存のキー
    SK_NEW_KEY,  // 新規追加
    SK_COUNT
} special_key_id_t;

// 2. 設定テーブルに追加（special_keys_config.c）
[SK_NEW_KEY] = {
    .macos = {
        .mod_keys = {KC_LCMD, KC_LOPT},
        .mod_count = 2,
        .tap_key = KC_ESC
    },
    // ... 他のOS設定
}

// 3. key_state変数を追加（state_manager.c）
key_state_t new_key_state = {.key_id = SK_NEW_KEY};
```

## 8. メモリ使用量の見積もり

### 8.1 データサイズ
- `os_key_config_t`: 11バイト（4*2 + 1 + 2）
- `special_key_config_t`: 33バイト（11 * 3）
- 全設定テーブル: 約297バイト（33 * 9）

### 8.2 既存構造体からの削減
- `key_state_t`から削除: 11バイト/インスタンス
- 9個のインスタンス: 99バイト削減

### 8.3 実質的な増加量
- 約200バイトの増加（許容範囲内）

## 9. リスクと対策

### 9.1 潜在的リスク
1. **メモリ不足**: ファームウェアサイズの増加
2. **処理速度低下**: 間接参照の増加
3. **デバッグの複雑化**: 設定の階層化

### 9.2 対策
1. **メモリ最適化**: const修飾子の使用、不要なコードの削除
2. **処理最適化**: キャッシュの活用、インライン関数の使用
3. **デバッグ支援**: デバッグ出力マクロの追加、設定確認関数の実装

## 10. 今後の拡張可能性

### 10.1 将来的な機能追加
- ユーザー定義可能な設定（EEPROM保存）
- 動的なOS切り替え
- アプリケーション別設定
- LED表示によるモード表示

### 10.2 拡張時の考慮事項
- 設定構造体の拡張性を確保
- 関数インターフェースの安定性
- 後方互換性の維持

---

**作成日**: 2025-09-13  
**バージョン**: 1.0  
**作成者**: 技術設計チーム