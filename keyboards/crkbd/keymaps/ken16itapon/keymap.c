/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#include "naginata.h"
#include "twpair_on_jis.h"
#include "raw_hid.h"
#include "process_tap_dance.h"

NGKEYS naginata_keys;

// タップダンスのインデックス定義
enum {
    TD_CSTAB = 0,
};

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _BASE = 0,
  _NAGINATA,
  _LOWER,
  _RAISE,
  _ADJUST,
  _10KEY,
  _COLEMAK,
  _QWERTY
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  MHENKAN = NG_SAFE_RANGE,
  HENKAN,
  LOWER,
  RAISE,
  ADJUST
};

#define S_ENTER SFT_T(KC_ENT)
#define C_SPACE CTL_T(KC_SPACE)
#define CS_TAB  TD(TD_CSTAB)  // 既存のCS_TABマクロを上書き
#define C_BSPC  CTL_T(KC_BSPC)
#define S_ESC   SFT_T(KC_ESC)
#define COPILOT LSG(KC_F23)
#define POWER   KC_KB_POWER
#define COLEMAK DF(_COLEMAK)
#define QWERTY  DF(_QWERTY)
#define S_CAPS  LSFT(KC_CAPS)
#define TENKEY  TG(_10KEY)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       CS_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,  TENKEY,     TENKEY,    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
       C_BSPC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D, COPILOT,     KC_EQL,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        S_ESC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MHENKAN,   LOWER, C_SPACE,    S_ENTER,   RAISE,  HENKAN
                                      //`--------------------------'  `--------------------------'

  ),

    [_NAGINATA] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    NG_Q,    NG_W,    NG_E,    NG_R,    NG_T, _______,    _______,    NG_Y,    NG_U,    NG_I,    NG_O,    NG_P,   NG_X1,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,    NG_A,    NG_S,    NG_D,    NG_F,    NG_G, _______,    _______,    NG_H,    NG_J,    NG_K,    NG_L, NG_SCLN, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,    NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,                         NG_N,    NG_M, NG_COMM,  NG_DOT, NG_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'

  ),


    [_LOWER] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_GRAVE, KC_HOME,  KC_END,   KC_UP,  KC_DEL, KC_PGUP, _______,    _______, _______, _______, _______, KC_LPRN, KC_RPRN, KC_PLUS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, KC_LEFT, KC_DOWN,KC_RIGHT, KC_PGDN, _______,    _______, _______, _______, _______, KC_LCBR, KC_RCBR,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F11,  KC_F12, _______, KC_LBRC, KC_RBRC, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_RAISE] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, _______,    _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, _______,    _______,   KC_6,     KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                       KC_F11,  KC_F12, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_ADJUST] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, _______, _______, _______, _______, _______, _______,    _______,   POWER, _______, _______, _______, _______,  S_CAPS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, _______, _______, _______,    _______, COLEMAK,  QWERTY, _______, _______, _______, KC_CAPS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RM_NEXT, RM_HUED, RM_SATD, RM_VALD, _______, _______,                      KC_PSCR, KC_SCRL, KC_PAUS,  KC_INS,  KC_DEL, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

      [_10KEY] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,   KC_P7,   KC_P8,   KC_P9,    KC_P, KC_BSPC, _______,    _______, KC_COMM,   KC_P7,   KC_P8,   KC_P9,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_PDOT,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, _______,    _______, KC_PDOT,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, KC_PSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_P0,   KC_P1,   KC_P2,   KC_P3, KC_PPLS,                        KC_P0,   KC_P1,   KC_P2,   KC_P3, KC_PPLS, KC_PAST,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_SPC,     KC_ENT,   MO(2), KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

    [_COLEMAK] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       CS_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,        ,           ,    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
       C_BSPC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D, COPILOT,     KC_EQL,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        S_ESC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MHENKAN,   LOWER, C_SPACE,    S_ENTER,   RAISE,  HENKAN
                                      //`--------------------------'  `--------------------------'

  ),

    [_QWERTY] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       CS_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        ,           ,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
       C_BSPC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, COPILOT,     KC_EQL,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+--------+--------|
        S_ESC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MHENKAN,   LOWER, C_SPACE,    S_ENTER,   RAISE,  HENKAN
                                      //`--------------------------'  `--------------------------'

  )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
  [3] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(RM_VALD, RM_VALU), ENCODER_CCW_CW(KC_RGHT, KC_LEFT), },
};
#endif

void matrix_init_user(void) {
  // 薙刀式

  set_naginata(_NAGINATA);
  // 薙刀式
}


static bool raise_pressed = false;
static uint16_t raise_pressed_time = 0;
static bool henkan_pressed = false;
static uint16_t henkan_pressed_time = 0;
static bool mhenkan_pressed = false;
static uint16_t mhenkan_pressed_time = 0;

static bool lower_pressed = false;
static uint16_t lower_pressed_time = 0;
static bool bspc_active = false;
static bool backspace_sent = false;  // 最初のBSPCが送信されたかどうかを追跡
static bool other_key_pressed = false;  // 追加

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed &&  (keycode != LOWER)) {
        other_key_pressed = true;
    }
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                lower_pressed = true;
                lower_pressed_time = record->event.time;
                // LOWERを押したタイミングでリセット
                other_key_pressed = false;

                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);

            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);

                if (lower_pressed && !bspc_active && !other_key_pressed &&
                    (TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM)) {
                    register_code(KC_BSPC);
                    unregister_code(KC_BSPC);
                    backspace_sent = true;
                } else {
                    // Do nothing if the key was held for too long
                    backspace_sent = false;
                }

                if (bspc_active) {
                    unregister_code(KC_BSPC);
                    bspc_active = false;
                    backspace_sent = false;
                }

                lower_pressed = false;

            }
            return false;
            break;

        case RAISE:
            if (record->event.pressed) {
                raise_pressed = true;
                raise_pressed_time = record->event.time;

                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);

                if (raise_pressed && (TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM)) {
                    register_code(KC_SPC);
                    unregister_code(KC_SPC);
                }
                raise_pressed = false;
            }
            return false;
            break;

        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;

        case MHENKAN:
            if (record->event.pressed) {
                mhenkan_pressed = true;
                mhenkan_pressed_time = record->event.time;

            } else {
                if (mhenkan_pressed && (TIMER_DIFF_16(record->event.time, mhenkan_pressed_time) < TAPPING_TERM)) {
                    tap_code(KC_LANGUAGE_2); // Mac
                    tap_code(KC_INTERNATIONAL_5); // Win

                    naginata_off();
                }
                mhenkan_pressed = false;
            }
            return true;
            break;

        case HENKAN:
            if (record->event.pressed) {
                henkan_pressed = true;
                henkan_pressed_time = record->event.time;
            } else {
                if (henkan_pressed && (TIMER_DIFF_16(record->event.time, henkan_pressed_time) < TAPPING_TERM)) {
                    tap_code(KC_LANGUAGE_1); // Mac
                    tap_code(KC_INTERNATIONAL_4); // Win

                    naginata_on();
                    henkan_pressed = false;
                } else {
                    // Do nothing if the key was held for too long
                    henkan_pressed = false;
                }
            }
            return true;
            break;

        default:
            if (henkan_pressed) {
                register_code(keycode);
                register_code(KC_LGUI);
                unregister_code(KC_LGUI);
                unregister_code(keycode);
                henkan_pressed = false;
                return true;
            } else if (mhenkan_pressed) {
                register_code(KC_LALT);
                register_code(keycode);
                unregister_code(keycode);
                unregister_code(KC_LALT);
                mhenkan_pressed = false;
                return true;
            }
    }



    if (!twpair_on_jis(keycode, record))
        return false;

    // 薙刀式
    if (!process_naginata(keycode, record))
        return true;
    // 薙刀式

    return true;

}

// matrix_scan_user関数内
void matrix_scan_user(void) {
    // 既に一度BSPCが送信されていて、かつTAPPING_TERMを超えて押されている場合にリピート開始
    if (lower_pressed && backspace_sent && !bspc_active &&
        !other_key_pressed && (timer_elapsed(lower_pressed_time) >= TAPPING_TERM)) {
        register_code(KC_BSPC);
        bspc_active = true;
    }
}

// HIDレポートのハンドリング
void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length < 1) return;

    switch(data[0]) {
        case 0x01:  // IME状態更新
            if (data[1]) {
                naginata_on();
            } else {
                naginata_off();
            }
            break;
    }
}

// 状態管理用の静的変数を追加
static bool mods_active = false;

// タップダンス終了時の処理
void cstab_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            // 単体タップ: TAB
            register_code(KC_TAB);
        } else {
            // 他のキーと同時押し: CTRL+SHIFT
            mods_active = true;
            register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
        }
    } else if (state->count == 2) {
        // ダブルタップ: ESC
        register_code(KC_ESC);
    }
}

// タップダンスリセット時の処理
void cstab_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            unregister_code(KC_TAB);
        } else if (mods_active) {
            unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
            mods_active = false;
        }
    } else if (state->count == 2) {
        unregister_code(KC_ESC);
    }
    // 安全のため、必ず修飾キーをクリア
    if (mods_active) {
        unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
        mods_active = false;
    }
}

// タップダンス配列の定義
tap_dance_action_t tap_dance_actions[] = {
    [TD_CSTAB] = {
        .fn = {
            NULL,
            cstab_finished,
            cstab_reset,
        }
    },
};

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(HSV_GREEN);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BASE:
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv(HSV_GREEN);    // 基本: 緑
            break;
        case _NAGINATA:
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv(HSV_ORANGE);   // 薙刀式: オレンジ
            break;
        case _10KEY:
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv(HSV_BLUE);     // テンキー: 青
            break;
        case _LOWER:
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv(HSV_PURPLE);   // LOWER: 紫
            break;
        case _RAISE:
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv(HSV_RED);      // RAISE: 赤
            break;
        case _ADJUST:
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv(HSV_YELLOW);      // RAISE: 黄
            break;

    }
    return state;
}
