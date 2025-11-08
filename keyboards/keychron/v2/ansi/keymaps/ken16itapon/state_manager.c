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

#include "state_manager.h"

// ============================================================
// グローバル変数定義
// ============================================================
os_mode_t current_os = OS_MAC;

// 各キーの状態
static key_state_t double_tap_state = {0};
static key_state_t hold_action_state = {0};
static key_state_t combo_state = {0};

// ============================================================
// 初期化
// ============================================================
void initialize_key_states(void) {
    // OS設定初期化（デフォルトはMac）
    current_os = OS_MAC;
    
    // キー状態初期化
    reset_all_key_states();
}

// ============================================================
// OS切替
// ============================================================
void toggle_os_mode(void) {
    current_os = (current_os + 1) % 3; // MAC → WIN → LINUX → MAC
    
    // OS変更時の処理
    switch (current_os) {
        case OS_MAC:
            // Mac用の設定
            // 例: RGB LEDを青色に
            break;
            
        case OS_WINDOWS:
            // Windows用の設定
            // 例: RGB LEDを緑色に
            break;
            
        case OS_LINUX:
            // Linux用の設定
            // 例: RGB LEDを赤色に
            break;
    }
}

os_mode_t get_current_os(void) {
    return current_os;
}

void set_os_mode(os_mode_t mode) {
    if (mode < OS_MAC || mode > OS_LINUX) {
        return;
    }
    current_os = mode;
}

// ============================================================
// レイヤー変更通知
// ============================================================
void on_layer_change(uint8_t layer) {
    // レイヤー変更時にキー状態をリセット
    reset_all_key_states();
    
    // レイヤー固有の処理
    switch (layer) {
        case 0: // _BASE
            // ベースレイヤーの初期化
            break;
            
        case 1: // _LOWER
            // LOWERレイヤーの初期化
            break;
            
        case 2: // _RAISE
            // RAISEレイヤーの初期化
            break;
            
        case 3: // _ADJUST
            // ADJUSTレイヤーの初期化
            break;
            
        case 4: // _SPECIAL
            // SPECIALレイヤーの初期化
            break;
    }
}

// ============================================================
// 全キー状態リセット
// ============================================================
void reset_all_key_states(void) {
    reset_key_state(&double_tap_state);
    reset_key_state(&hold_action_state);
    reset_key_state(&combo_state);
}

// ============================================================
// 個別キー状態リセット
// ============================================================
void reset_key_state(key_state_t *state) {
    state->is_pressed = false;
    state->pressed_time = 0;
    state->released_time = 0;
    state->code_sent = false;
    state->rapid_press = false;
    state->other_key_pressed = false;
}
