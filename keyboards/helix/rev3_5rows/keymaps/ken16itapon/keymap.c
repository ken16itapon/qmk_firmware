 /* Copyright 2020 yushakobo
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
#include "keymap_japanese.h"
#include "naginata.h"
#include "twpair_on_jis.h"
#include "raw_hid.h"
#include "process_tap_dance.h"

NGKEYS naginata_keys;

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _BASE = 0,
  _NAGINATA,
  _LOWER,
  _RAISE,
  _ADJUST,
  _10KEY//,
//   _COLEMAK,
//   _QWERTY
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
// #define CS_TAB  TD(TD_CSTAB)  // 既存のCS_TABマクロを上書き
#define C_BSPC  CTL_T(KC_BSPC)
#define S_ESC   SFT_T(KC_ESC)
#define COPILOT LSG(KC_F23)
#define POWER   KC_KB_POWER
#define COLEMAK DF(_COLEMAK)
#define QWERTY  DF(_QWERTY)
#define S_CAPS  LSFT(KC_CAPS)
#define TENKEY  TG(_10KEY)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT(
 // ,-----------------------------------------------------.                 ,-----------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
 // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
       KC_GRV,    KC_1,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_EQL,
 // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
       CS_TAB,    KC_Q,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
 // |--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+--------|
       C_BSPC,    KC_A,    KC_X,    KC_C,    KC_V,    KC_B, COPILOT,  TENKEY,    KC_K,    KC_M,  C_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
 // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     KC_LSHFT,    KC_Z, KC_LALT, KC_LGUI,    EISU,   LOWER, KC_BSPC,    R_ENT,   RAISE,G(KANA), KC_RGUI, KC_RALT, KC_BSLS, KC_RGHT
 // `-----------------------------------------------------------------------------------------------------------------------------'
   ),

  [_LOWER] = LAYOUT(
 // ,-----------------------------------------------------.                 ,-----------------------------------------------------.
      _______, _______,   _______,   _______,   _______,   _______,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
 // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
      _______,   _______,  KC_END,   KC_UP,    KC_P, KC_PGUP,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_EQL,
 // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
      _______, KC_HOME, KC_LEFT, KC_DOWN,KC_RIGHT, KC_PGDN,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
 // |--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+--------|
      _______,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, COPILOT,  TENKEY,    KC_K,    KC_M,  C_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
 // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______,  KC_ESC, KC_LALT, KC_LGUI,    EISU,   LOWER, KC_BSPC,    R_ENT,   RAISE,G(KANA), KC_RGUI, KC_RALT, KC_BSLS, KC_RGHT
 // `-----------------------------------------------------------------------------------------------------------------------------'
   ),
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
      KC_TILD, _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
      _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT,KC_PGDN,                     KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
       KC_F11, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LPRN, KC_RPRN, KC_F12,  _______, _______, KC_HOME, KC_END,  _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   `  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  \   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |  F12 |  F6  |  F7  |  F8  |  F9  |  F10 |      |      |  F12 |      |      |PageDn|PageUp|      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT(
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_BSPC,
      KC_GRV,  S(KC_1), S(KC_2), S(KC_3),    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
       KC_F12, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, _______, KC_F12,  _______, _______, KC_PGDN, KC_PGUP, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|EEPRST|      |      |             |      |      |      |      |      |  Del |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      | Mac  |             | Win  |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT(
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
      _______, QK_BOOT, RGBRST,  EE_CLR,  _______, _______,                   _______, _______, _______, _______, _______, KC_DEL,
      _______, _______, _______, _______, _______, AG_NORM,                   AG_SWAP, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, UG_TOGG, UG_HUEU, UG_SATU, UG_VALU,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, UG_NEXT, UG_HUED, UG_SATD, UG_VALD
      ),
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Adjust| Esc  | Alt  | GUI  | EISU |Lower |Space |Space |Raise | KANA | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
      ADJUST,  KC_ESC,  KC_LALT, KC_LGUI, EISU,    LOWER,   KC_SPC,  KC_SPC,  RAISE,   KANA,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN),    ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_LOWER] =  { ENCODER_CCW_CW(KC_PGUP, KC_PGDN),  ENCODER_CCW_CW(KC_HOME, KC_END)  },
    [_RAISE] =  { ENCODER_CCW_CW(UG_VALD, UG_VALU),  ENCODER_CCW_CW(UG_SPDD, UG_SPDU)  },
    [_ADJUST] = { ENCODER_CCW_CW(UG_PREV, UG_NEXT), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif

void matrix_init_user(void) {
  // ???

  set_naginata(_NAGINATA);
  // ???
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
static bool backspace_sent = false;  // ???BSPC?????????????
static bool other_key_pressed = false;  // ??

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed &&  (keycode != LOWER)) {
        other_key_pressed = true;
    }
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                lower_pressed = true;
                lower_pressed_time = record->event.time;
                // LOWER??????????????
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
}
