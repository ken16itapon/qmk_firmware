/* Copyright 2024 @ Ken16itapon
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "key_handlers.h"
#include "keymap.h"
#include "state_manager.h"

// ============================================================
// メインハンドラー
// ============================================================
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
            return handle_os_switch_key(record);
    }
    
    // その他のキーは通常処理
    return true;
}

// ============================================================
// ダブルタップ検出
// ============================================================
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
        
        // 通常のタップ（Escキー）
        tap_code(KC_ESC);
        
    } else {
        // リリース時刻を記録
        tap_state.released_time = timer_read();
    }
    
    return false;
}

// ============================================================
// ホールド時アクション
// ============================================================
bool handle_hold_action_key(keyrecord_t *record) {
    static key_state_t hold_state = {0};
    
    if (record->event.pressed) {
        hold_state.is_pressed = true;
        hold_state.pressed_time = timer_read();
        hold_state.code_sent = false;
        
    } else {
        uint16_t hold_duration = timer_elapsed(hold_state.pressed_time);
        
        if (!hold_state.code_sent) {
            if (hold_duration < TAPPING_TERM) {
                // タップ動作（Aキー）
                tap_code(KC_A);
            } else {
                // ホールド動作は既に送信済み
            }
        }
        
        hold_state.is_pressed = false;
    }
    
    return false;
}

// ============================================================
// コンボキー
// ============================================================
bool handle_combo_key(keyrecord_t *record) {
    static bool combo_ready = false;
    
    if (record->event.pressed) {
        combo_ready = true;
        // 他のキーが押されるまで待機
        
    } else {
        if (combo_ready) {
            // タイムアウト or 単独押しなら通常動作（スペース）
            tap_code(KC_SPC);
        }
        combo_ready = false;
    }
    
    return false;
}

// ============================================================
// マクロ実行
// ============================================================
bool handle_macro_key(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return false;
    }
    
    switch (keycode) {
        case KC_MACRO_1:
            // メールアドレス入力
            SEND_STRING("hello@example.com");
            break;
            
        case KC_MACRO_2:
            // コピー→貼り付けマクロ
            send_os_specific_key(KC_MCPY, KC_WCPY);
            wait_ms(100);
            send_os_specific_key(KC_MPST, KC_WPST);
            break;
    }
    
    return false;
}

// ============================================================
// OS切替
// ============================================================
bool handle_os_switch_key(keyrecord_t *record) {
    if (record->event.pressed) {
        toggle_os_mode();
        
        // OS切替通知（オプション）
        switch (get_current_os()) {
            case OS_MAC:
                SEND_STRING("Mac Mode");
                break;
            case OS_WINDOWS:
                SEND_STRING("Windows Mode");
                break;
            case OS_LINUX:
                SEND_STRING("Linux Mode");
                break;
        }
    }
    return false;
}

// ============================================================
// タイムアウトチェック
// ============================================================
void check_tapping_timeout(void) {
    // ここでホールド状態のタイムアウト処理を実装
    // 例：KC_HOLD_ACTIONのホールド動作
}

// ============================================================
// ユーティリティ: タップ判定時間内か
// ============================================================
bool is_key_within_tapping_term(key_state_t *state) {
    return timer_elapsed(state->pressed_time) < TAPPING_TERM;
}

// ============================================================
// ユーティリティ: キーシーケンス送信
// ============================================================
void send_custom_sequence(const uint16_t *sequence, uint8_t length) {
    for (uint8_t i = 0; i < length; i++) {
        tap_code(sequence[i]);
        wait_ms(10);
    }
}

// ============================================================
// ユーティリティ: OS別キー送信
// ============================================================
void send_os_specific_key(uint16_t mac_key, uint16_t win_key) {
    switch (get_current_os()) {
        case OS_MAC:
            tap_code16(mac_key);
            break;
        case OS_WINDOWS:
        case OS_LINUX:
            tap_code16(win_key);
            break;
    }
}
