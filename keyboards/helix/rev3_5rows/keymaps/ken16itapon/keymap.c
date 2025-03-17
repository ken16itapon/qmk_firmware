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
#include "quantum.h"
#include "split_debug.h" // 追加

// Unicode モード定数の修正
// #define UNICODE_MODE_WINCOMPOSE UC_WIN
// #define UNICODE_MODE_MACOS UC_MAC
// #define UNICODE_MODE_LINUX UC_LNX

// 未定義定数の追加
#define NG_CLR SAFE_RANGE
#define NGSW_WIN (NG_CLR + 1)
#define NGSW_MAC (NG_CLR + 2)
#define NGSW_LNX (NG_CLR + 3)
#define NG_MLV (NG_CLR + 4)
#define NG_SHOS (NG_CLR + 5)
#define NG_TAYO (NG_CLR + 6)
#define NG_KOTI (NG_CLR + 7)

NGKEYS naginata_keys;

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE = 0,
    _NAGINATA,
    _LOWER,
    _RAISE,
    _ADJUST,
    _10KEY //,
    //   _COLEMAK,
    //  _QWERTY
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { MHENKAN = NG_SAFE_RANGE, HENKAN, LOWER, RAISE, ADJUST };

#define S_ENTER SFT_T(KC_ENT)
#define C_SPACE CTL_T(KC_SPACE)
// #define CS_TAB  TD(TD_CSTAB)  // 既存のCS_TABマクロを上書き
#define C   _BSPC  CTL_T(KC_BSPC)
#define S_ESC   SFT_T(KC_ESC)
#define COPILOT LSG(KC_F23)
#define POWER   KC_KB_POWER
#define COLEMAK DF(_COLEMAK)
#define QWERTY  DF(_QWERTY)
#define S_CAPS  LSFT(KC_CAPS)
#define TENKEY  TG(_10KEY)


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        // ,-----------------------------------------------------.                 ,-----------------------------------------------------.
              KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
        // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
              CS_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_EQL,
        // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
              C_BSPC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
        // |--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+--------|
             KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, _______,  TENKEY,    KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_BSLS,
        // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
             XXXXXXX, XXXXXXX, KC_LCTL, KC_LGUI, MHENKAN,   LOWER, C_SPACE, S_ENTER,   RAISE,  HENKAN, KC_RALT, KC_RSFT, XXXXXXX, XXXXXXX
        // `-----------------------------------------------------------------------------------------------------------------------------'
        ),

    [_NAGINATA] = LAYOUT(
        // ,-----------------------------------------------------.                 ,-----------------------------------------------------.
             _______,    NG_1,    NG_2,    NG_3,    NG_4,    NG_5,                   _______, _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
             _______,    NG_Q,    NG_W,    NG_E,    NG_R,    NG_T,                      NG_Y,    NG_U,    NG_I,    NG_O,    NG_P,   NG_X1,
        // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
             _______,    NG_A,    NG_S,    NG_D,    NG_F,    NG_G,                      NG_H,    NG_J,    NG_K,    NG_L, NG_SCLN,  C_BSPC,
        // |--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+--------|
             _______,    NG_Z,    NG_X,    NG_C,    NG_V,    NG_B, _______, _______,    NG_N,    NG_M, NG_COMM,  NG_DOT, NG_SLSH, _______,
        // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        // `-----------------------------------------------------------------------------------------------------------------------------'
        ),

    [_LOWER] = LAYOUT(
        // ,-----------------------------------------------------.                 ,-----------------------------------------------------.
             _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_PLUS,
        // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
             _______, KC_HOME,  KC_END,   KC_UP,  KC_DEL, KC_PGUP,                   _______, _______, _______, KC_LPRN, KC_RPRN,  KC_EQL,
        // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
             _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT,KC_PGDN,                   _______, _______, _______, KC_LCBR, KC_RCBR, _______,
        // |--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______,
        // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        // `-----------------------------------------------------------------------------------------------------------------------------'
        ),
    [_RAISE] = LAYOUT(
        // ,-----------------------------------------------------.                 ,-----------------------------------------------------.
             _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_UNDS,
        // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
             _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS,
        // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
             _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
        // |--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        // `-----------------------------------------------------------------------------------------------------------------------------'
        ),
    [_ADJUST] = LAYOUT(
        // ,-----------------------------------------------------.                 ,-----------------------------------------------------.
             QK_BOOT, _______, _______, _______, _______,  QK_RBT,                     POWER, _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,  S_CAPS,
        // |--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS,  KC_INS,  KC_DEL, KC_CAPS,
        // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
        // `-----------------------------------------------------------------------------------------------------------------------------'
        ),
    [_10KEY] = LAYOUT(
        // ,-----------------------------------------------------.                 ,-----------------------------------------------------.
             _______, _______, _______, _______, _______, _______,                   _______,  KC_NUM, _______, _______, KC_PSLS, _______,
        // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______,                     KC_F2,   KC_P7,   KC_P8,   KC_P9, KC_PAST, _______,
        // |--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______,                     KC_F4,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, _______,
        // |--------+--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_P1,   KC_P2,   KC_P3, KC_PPLS, _______,
        // |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
             _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_P0, KC_PDOT, KC_PCMM, KC_PEQL, KC_PENT
        // `-----------------------------------------------------------------------------------------------------------------------------'
        ) //,
    /*
     */
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_COLEMAK] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN),    ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_LOWER] =  { ENCODER_CCW_CW(KC_PGUP, KC_PGDN),  ENCODER_CCW_CW(KC_HOME, KC_END)  },
    [_RAISE] =  { ENCODER_CCW_CW(UG_VALD, UG_VALU),  ENCODER_CCW_CW(UG_SPDD, UG_SPDU)  },
    [_ADJUST] = { ENCODER_CCW_CW(UG_PREV, UG_NEXT), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif

void matrix_init_user(void) {
    // 薙刀式

    set_naginata(_NAGINATA);
    // 薙刀式
}

static bool     raise_pressed        = false;
static uint16_t raise_pressed_time   = 0;
static bool     henkan_pressed       = false;
static uint16_t henkan_pressed_time  = 0;
static bool     mhenkan_pressed      = false;
static uint16_t mhenkan_pressed_time = 0;

// LOWERキー状態管理用構造体
static struct {
    bool     pressed;
    uint16_t pressed_time;
    uint16_t released_time;
    bool     other_key_pressed;
    bool     bspc_active;
    bool     backspace_sent;
    bool     rapid_press;
} lower_state = {0};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    monitor_keyboard_state(keycode, record); // キー入力のモニタリング
#endif

    // 他のキー押下検出
    if (record->event.pressed && keycode != LOWER) {
        lower_state.pressed           = false;
        lower_state.other_key_pressed = true;
        lower_state.backspace_sent    = false;
        lower_state.rapid_press       = false;
    }

    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                if (timer_elapsed(lower_state.released_time) < TAPPING_TERM) {
                    lower_state.rapid_press = true; // 連打
                } else {
                    lower_state.rapid_press = false; // 連打リセット
                }

                lower_state.pressed           = true;
                lower_state.pressed_time      = record->event.time;
                lower_state.other_key_pressed = false;
                lower_state.bspc_active       = false;

                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                // 単打判定（他のキーが押されていない && TAPPING_TERM以内）
                if (timer_elapsed(lower_state.pressed_time) < TAPPING_TERM && !lower_state.other_key_pressed && !lower_state.rapid_press) { // 連打でない場合のみBSPC発行
                    register_code(KC_BSPC);
                    unregister_code(KC_BSPC);
                    lower_state.backspace_sent = true;
                    lower_state.released_time  = record->event.time;
                }

                if (lower_state.bspc_active) {
                    unregister_code(KC_BSPC);
                    lower_state.bspc_active = false;
                    lower_state.backspace_sent = false;
                }

                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
                lower_state.pressed = false;
            }
            return false;

        case RAISE:
            if (record->event.pressed) {
                raise_pressed      = true;
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
                mhenkan_pressed      = true;
                mhenkan_pressed_time = record->event.time;
            } else {
                if (mhenkan_pressed && (TIMER_DIFF_16(record->event.time, mhenkan_pressed_time) < TAPPING_TERM)) {
                    // tap_code(KC_LANGUAGE_2);      // Mac用
                    tap_code(KC_INTERNATIONAL_5); // Windows用
                    naginata_off();
                }
                // 必ず ALT を解除する
                unregister_code(KC_LALT);
                mhenkan_pressed = false;
            }
            return false;
            break;

        case HENKAN:
            if (record->event.pressed) {
                henkan_pressed      = true;
                henkan_pressed_time = record->event.time;
            } else {
                if (henkan_pressed && (TIMER_DIFF_16(record->event.time, henkan_pressed_time) < TAPPING_TERM)) {
                    // tap_code(
                    // KC_LANGUAGE_1);      // Mac用
                    tap_code(KC_INTERNATIONAL_4); // Windows用
                    naginata_on();
                }
                // 必ず GUI modifier を解除する
                unregister_code(KC_LGUI);
                henkan_pressed = false;
            }
            return false;
            break;

        default:
            if (henkan_pressed) {
                register_code(KC_LGUI);
                register_code(keycode);
                unregister_code(keycode);
                unregister_code(KC_LGUI);
                henkan_pressed = false;
                return false;
            } else if (mhenkan_pressed) {
                register_code(KC_LALT);
                register_code(keycode);
                unregister_code(keycode);
                unregister_code(KC_LALT);
                mhenkan_pressed = false;
                return false;
            }
            break;
    }
    return true;
}

// matrix_scan_user関数内
void matrix_scan_user(void) {
#ifdef CONSOLE_ENABLE
    monitor_split_status(); // スプリット状態のモニタリング
#endif

    // BSPCリピート開始条件
    if (lower_state.pressed && lower_state.backspace_sent && !lower_state.bspc_active && !lower_state.other_key_pressed && (timer_elapsed(lower_state.released_time) < TAPPING_TERM)) {
        lower_state.bspc_active = true;
        register_code(KC_BSPC);
        lower_state.backspace_sent = false;
    }

    // リピート終了条件
    if ((!lower_state.pressed && lower_state.bspc_active) || lower_state.other_key_pressed) {
        unregister_code(KC_BSPC);
        lower_state.bspc_active = false;
    }
}

void keyboard_post_init_user(void) {
#    ifdef CONSOLE_ENABLE
    keyboard_post_init_debug(); // デバッグ初期化
#    endif

    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(HSV_GREEN);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t current_layer = get_highest_layer(state);

    // LED色の設定
    switch (current_layer) {
        case _BASE:
            rgb_matrix_sethsv(HSV_GREEN);
            break;
        case _NAGINATA:
            rgb_matrix_sethsv(HSV_ORANGE);
            break;
        case _10KEY:
            rgb_matrix_sethsv(HSV_BLUE);
            break;
        case _LOWER:
            rgb_matrix_sethsv(HSV_PURPLE);
            break;
        case _RAISE:
            rgb_matrix_sethsv(HSV_RED);
            break;
        case _ADJUST:
            rgb_matrix_sethsv(HSV_YELLOW);
            break;
    }
    return state;
}

#ifdef RGBLIGHT_ENABLE
// バックライトの色設定関数
void set_layer_backlight_color(uint8_t layer) {
    switch (layer) {
        case _BASE:
            rgblight_sethsv(85, 255, 255); // 緑色
            break;
        case _NAGINATA:
            rgblight_sethsv(32, 255, 255); // オレンジ色
            break;
        case _LOWER:
            rgblight_sethsv(128, 255, 255); // 紫色
            break;
        case _RAISE:
            rgblight_sethsv(0, 255, 255); // 赤色
            break;
        case _ADJUST:
            rgblight_sethsv(42, 255, 255); // 黄色
            break;
        case _10KEY:
            rgblight_sethsv(170, 255, 255); // 青色
            break;
        default:
            rgblight_sethsv(0, 0, 0); // バックライトをオフ
            break;
    }
}

// レイヤー切り替え時のバックライト設定
layer_state_t layer_state_set_user(layer_state_t state) {
    set_layer_backlight_color(biton32(state));
    return state;
}
#endif

#ifdef ENCODER_ENABLE
void keyboard_pre_init_user(void) {
    // エンコーダーのピン定義
    pin_t encoders_pad_a[]       = {GP16};
    pin_t encoders_pad_b[]       = {GP17};
    pin_t encoders_pad_a_right[] = {GP16};
    pin_t encoders_pad_b_right[] = {GP17};

    // ピンの初期化
    for (uint8_t i = 0; i < NUM_ENCODERS; i++) {
        setPinInputHigh(encoders_pad_a[i]);
        setPinInputHigh(encoders_pad_b[i]);
        setPinInputHigh(encoders_pad_a_right[i]);
        setPinInputHigh(encoders_pad_b_right[i]);
    }
}
#endif
