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

#include QMK_KEYBOARD_H
#include "keymap.h"
#include "key_handlers.h"
#include "state_manager.h"

// clang-format off

// ============================================================
// キーマップ定義
// ============================================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Bkspc │Ins│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │Del│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter  │Hom│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │Shift │ ↑ │   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
     * │Ctrl│Win │Alt │        Space           │Alt│Fn │Fn2│ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
     */
    [_BASE] = LAYOUT_ansi_67(
        KC_ESC,       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_INS,
        KC_TAB,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
        KC_CAPS,      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,           KC_HOME,
        KC_LSFT,               KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT, KC_UP,
        KC_LCTL,      KC_LGUI, KC_LALT,                            KC_SPC,                              KC_RALT,  LOWER,    RAISE,    KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /*
     * LOWER Layer - 記号、Fキー、メディアコントロール
     */
    [_LOWER] = LAYOUT_ansi_67(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_DEL,           _______,
        _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,  _______,            _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______, KC_PGUP,
        _______, _______, _______,                            _______,                            _______,  _______,  ADJUST,   KC_HOME, KC_PGDN, KC_END
    ),

    /*
     * RAISE Layer - ナビゲーション、数値入力
     */
    [_RAISE] = LAYOUT_ansi_67(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_UNDS,  KC_PLUS,  _______,          _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     _______,  _______,  _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______, _______,
        _______, _______, _______,                            _______,                            _______,  ADJUST,   _______,  _______, _______, _______
    ),

    /*
     * ADJUST Layer - RGB制御、設定
     */
    [_ADJUST] = LAYOUT_ansi_67(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        RM_TOGG, RM_NEXT, RM_VALU, RM_HUEU, RM_SATU, RM_SPDU, _______, _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, RM_PREV, RM_VALD, RM_HUED, RM_SATD, RM_SPDD, _______, _______, _______, _______, _______,  _______,            _______,          _______,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______,  _______,            _______, _______,
        _______, _______, _______,                            _______,                            _______,  _______,  _______,  _______, _______, _______
    ),

    /*
     * SPECIAL Layer - カスタム機能テスト用
     */
    [_SPECIAL] = LAYOUT_ansi_67(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, KC_MACRO_1, KC_MACRO_2, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        KC_DOUBLE_TAP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,            _______, _______,
        _______, _______, _______,                            _______,                            _______,  _______,  _______,  _______, _______, _______
    )
};

// clang-format on

// ============================================================
// 初期化処理
// ============================================================
void keyboard_post_init_user(void) {
    // 状態管理の初期化
    initialize_key_states();
}

// ============================================================
// キー入力処理のエントリーポイント
// ============================================================
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // key_handlers.c に処理を委譲
    return handle_custom_keys(keycode, record);
}

// ============================================================
// マトリックススキャン時の処理
// ============================================================
void matrix_scan_user(void) {
    // タイマーベースの処理
    check_tapping_timeout();
}

// ============================================================
// レイヤー切替時の処理
// ============================================================
layer_state_t layer_state_set_user(layer_state_t state) {
    // レイヤー変更時の副作用をここに記述
    on_layer_change(get_highest_layer(state));
    return state;
}
