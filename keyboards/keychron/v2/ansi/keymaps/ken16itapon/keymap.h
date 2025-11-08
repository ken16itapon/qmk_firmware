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

#pragma once

#include QMK_KEYBOARD_H

// ============================================================
// カスタムキーコード定義
// ============================================================
enum custom_keycodes {
    // QMKの安全な範囲から開始
    KC_MY_CUSTOM = SAFE_RANGE,
    KC_DOUBLE_TAP,      // ダブルタップ検出キー
    KC_HOLD_ACTION,     // ホールド時に特殊動作
    KC_COMBO_KEY,       // コンボキー
    KC_MACRO_1,         // カスタムマクロ1
    KC_MACRO_2,         // カスタムマクロ2
    OS_SWITCH,          // OS切替
    
    // ここに追加のカスタムキーを定義
};

// ============================================================
// レイヤー定義
// ============================================================
enum layers {
    _BASE = 0,          // ベースレイヤー
    _LOWER,             // 下位レイヤー（記号、Fキー等）
    _RAISE,             // 上位レイヤー（ナビゲーション等）
    _ADJUST,            // 調整レイヤー（RGB、設定等）
    _SPECIAL,           // 特殊機能レイヤー
};

// ============================================================
// レイヤー切替マクロ
// ============================================================
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define ADJUST  MO(_ADJUST)
#define SPECIAL MO(_SPECIAL)

// ============================================================
// 便利なショートカットマクロ
// ============================================================
#define KC_CTAB LCTL(KC_TAB)        // Ctrl+Tab
#define KC_STAB LSFT(KC_TAB)        // Shift+Tab
#define KC_WTAB LGUI(KC_TAB)        // Win+Tab (Task View)
#define KC_WEXP LGUI(KC_E)          // Win+E (Explorer)

// Mac用ショートカット
#define KC_MCPY LGUI(KC_C)          // Cmd+C
#define KC_MPST LGUI(KC_V)          // Cmd+V
#define KC_MCUT LGUI(KC_X)          // Cmd+X
#define KC_MUND LGUI(KC_Z)          // Cmd+Z
#define KC_MRED LGUI(LSFT(KC_Z))    // Cmd+Shift+Z

// Windows用ショートカット
#define KC_WCPY LCTL(KC_C)          // Ctrl+C
#define KC_WPST LCTL(KC_V)          // Ctrl+V
#define KC_WCUT LCTL(KC_X)          // Ctrl+X
#define KC_WUND LCTL(KC_Z)          // Ctrl+Z
#define KC_WRED LCTL(KC_Y)          // Ctrl+Y

// ============================================================
// 関数宣言（他のファイルから使用）
// ============================================================
bool process_record_user(uint16_t keycode, keyrecord_t *record);
void matrix_scan_user(void);
layer_state_t layer_state_set_user(layer_state_t state);
void keyboard_post_init_user(void);
