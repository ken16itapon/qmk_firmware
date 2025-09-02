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
#include "keymap.h"


// Layer names and custom keycodes are defined in keymap.h

// LOWER and RAISE are now handled as custom keycodes with advanced features

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK] = LAYOUT(
    //,-----------------------------------------------------.                 ,-----------------------------------------------------.
         KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
         KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  KC_EQL,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
        CC_BSPC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                      KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  OS_MEH,TG(_PAD),    KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_BSLS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        _______, _______, KC_LALT, KC_LGUI,    EISU,   LOWER,   C_ENT,  S_BSPC,   RAISE,    KANA, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT
    //`-----------------------------------------------------------------------------------------------------------------------------'
    ),

    [_NAGINATA] = LAYOUT(
    //,-----------------------------------------------------.                 ,-----------------------------------------------------.
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
        _______,    NG_Q,    NG_W,    NG_E,    NG_R,    NG_T,                      NG_Y,    NG_U,    NG_I,    NG_O,    NG_P,   NG_X1,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
        _______,    NG_A,    NG_S,    NG_D,    NG_F,    NG_G,                      NG_H,    NG_J,    NG_K,    NG_L, NG_SCLN, _______,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        _______,    NG_Z,    NG_X,    NG_C,    NG_V,    NG_B, _______, _______,    NG_N,    NG_M, NG_COMM,  NG_DOT, NG_SLSH, _______,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    //`-----------------------------------------------------------------------------------------------------------------------------'
    ),

    [_LOWER] = LAYOUT(
    //,-----------------------------------------------------.                 ,-----------------------------------------------------.
        _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
       KC_GRAVE, KC_HOME,  KC_END,   KC_UP,  KC_DEL, KC_PGUP,                   _______, _______, _______, KC_LCBR, KC_RCBR,  KC_F12,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
        _______, _______, KC_LEFT, KC_DOWN,KC_RIGHT, KC_PGDN,                   _______, _______, _______, KC_LBRC, KC_RBRC, _______,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LABK, KC_RABK, _______,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    //`-----------------------------------------------------------------------------------------------------------------------------'
    ),

    [_RAISE] = LAYOUT(
    //,-----------------------------------------------------.                 ,-----------------------------------------------------.
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
        KC_TILD, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______,  KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
        _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_CAPS,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, _______, _______,  KC_F12, _______, _______, KC_PGDN, KC_PGUP, _______,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    //`-----------------------------------------------------------------------------------------------------------------------------'
    ),

    [_PAD] = LAYOUT(
    //,-----------------------------------------------------.                 ,-----------------------------------------------------.
         KC_NUM, KC_LPRN, KC_RPRN, KC_PERC, KC_CIRC, KC_BSPC,                    KC_NUM, KC_LPRN, KC_RPRN, KC_PERC, KC_CIRC, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
        C(KC_C),   KC_P7,   KC_P8,   KC_P9,   KC_LT,   KC_GT,                   C(KC_C),   KC_P7,   KC_P8,   KC_P9,   KC_LT,   KC_GT,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
        C(KC_X),   KC_P4,   KC_P5,   KC_P6, KC_PAST, KC_PSLS,                   C(KC_X),   KC_P4,   KC_P5,   KC_P6, KC_PAST, KC_PSLS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        C(KC_V),   KC_P1,   KC_P2,   KC_P3, KC_PPLS, KC_PMNS, _______, _______, C(KC_V),   KC_P1,   KC_P2,   KC_P3, KC_PPLS, KC_PMNS,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        _______,   KC_P0, KC_PCMM, KC_PDOT, KC_PEQL, KC_PENT, _______, _______, _______,   KC_P0, KC_PCMM, KC_PDOT, KC_PEQL, KC_PENT
    //`-----------------------------------------------------------------------------------------------------------------------------'
    ),

    [_ADJUST] = LAYOUT(
    //,-----------------------------------------------------.                 ,-----------------------------------------------------.
        QK_BOOT, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
        _______, _______,  RGBRST,  EE_CLR, _______, _______,                   _______, _______, _______, _______, _______,  KC_DEL,
    //|--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, AG_NORM,                   AG_SWAP, _______, _______, _______, _______, _______,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, UG_TOGG, UG_HUEU, UG_SATU, UG_VALU,
    //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, UG_NEXT, UG_HUED, UG_SATD, UG_VALD
    //`-----------------------------------------------------------------------------------------------------------------------------'
    )

};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_COLEMAK] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN),    ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_LOWER] =  { ENCODER_CCW_CW(KC_PGUP, KC_PGDN),  ENCODER_CCW_CW(KC_HOME, KC_END)  },
    [_RAISE] =  { ENCODER_CCW_CW(UG_VALD, UG_VALU),  ENCODER_CCW_CW(UG_SPDD, UG_SPDU)  },
    [_PAD] =  { ENCODER_CCW_CW(UG_VALD, UG_VALU),  ENCODER_CCW_CW(UG_SPDD, UG_SPDU)  },
    [_ADJUST] = { ENCODER_CCW_CW(UG_PREV, UG_NEXT), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },};
#endif

void matrix_init_user(void) {
  // 薙刀式
  set_naginata(_NAGINATA);
}

void matrix_scan_user(void) {
  // 各キーの状態を処理
  if (timer_elapsed(henkan_state.pressed_time) > TAPPING_TERM &&
      henkan_state.is_pressed) {
    register_mods_for_key(&henkan_state);
  }
  handle_advanced_repeat(&henkan_state);
  if (timer_elapsed(mhenkan_state.pressed_time) > TAPPING_TERM &&
      mhenkan_state.is_pressed) {
    register_mods_for_key(&mhenkan_state);
  }
  handle_advanced_repeat(&mhenkan_state);
  handle_advanced_repeat(&cc_bspc_state);
  handle_advanced_repeat(&s_bspc_state);
  handle_advanced_repeat(&c_ent_state);
  handle_advanced_repeat(&lower_state);
  handle_advanced_repeat(&raise_state);

  // 既存の自動リセット処理
  if (all_keys_released() &&
      timer_elapsed(all_keys_released_time) > TAPPING_TERM * 2) {
    reset_key_pressed();
    reset_rapid_press();
    reset_other_key_pressed();
    reset_code_sent();
    clean_all_mods_key();
  }
}

void keyboard_post_init_user(void) {
  // キー状態の初期化
  initialize_key_states();

  // 薙刀式の初期化など、他の初期化処理
  naginata_clear();
  naginata_off();

  // RGB LEDの初期化
  #ifdef RGBLIGHT_ENABLE
    rgblight_enable();
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    // 初期色設定（OS別）
    #ifdef TARGET_OS_WINDOWS
      rgblight_sethsv_noeeprom(HSV_CYAN);    // Windows: シアン
    #else
      rgblight_sethsv_noeeprom(HSV_GREEN);   // Mac: 緑
    #endif
  #endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t current_layer = get_highest_layer(state);

  // ADJUST層の処理
  switch (current_layer) {
    case _ADJUST:
      clean_all_mods_key();
      reset_rapid_press();
      set_other_key_pressed();
      break;
  }

  // RGBライトでレイヤーを表示
  #ifdef RGBLIGHT_ENABLE
    switch (current_layer) {
      case _NAGINATA:
        rgblight_sethsv_noeeprom(HSV_ORANGE);  // 薙刀式: オレンジ
        break;
      case _LOWER:
        rgblight_sethsv_noeeprom(HSV_PURPLE);  // Lower: 紫
        break;
      case _RAISE:
        rgblight_sethsv_noeeprom(HSV_RED);     // Raise: 赤
        break;
      case _PAD:
        rgblight_sethsv_noeeprom(HSV_BLUE);    // Pad: 青
        break;
      case _ADJUST:
        rgblight_sethsv_noeeprom(HSV_YELLOW);  // Adjust: 黄色
        break;
      default:
        // ベースレイヤー（COLEMAK）: OS別の色
        #ifdef TARGET_OS_WINDOWS
          rgblight_sethsv_noeeprom(HSV_CYAN);    // Windows: シアン
        #else
          rgblight_sethsv_noeeprom(HSV_GREEN);   // Mac: 緑
        #endif
        break;
    }
  #endif

  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 全キー共通の前処理
  if (record->event.pressed) {
    handle_key_press_init(keycode);
  } else {
    if (all_keys_released()) {
      reset_key_pressed();
      all_keys_released_time = record->event.time;
    }
  }

  switch (keycode) {
    case LOWER:
      return handle_lower_key(record);

    case RAISE:
      return handle_raise_key(record);

    case EISU:  // MHENKAN相当
      return handle_mhenkan_key(record);

    case KANA:  // HENKAN相当
      return handle_henkan_key(record);

    case CC_BSPC:
      return handle_cc_bspc_key(record);

    case S_BSPC:
      return handle_s_bspc_key(record);

    case C_ENT:
      return handle_c_ent_key(record);

    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        clean_all_mods_key();
        reset_code_sent();
        reset_rapid_press();
        set_other_key_pressed();
      } else {
        layer_off(_ADJUST);
      }
      return false;

    // OS切替キーの処理（削除）

    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;

    default:
      reset_code_sent();
      set_other_key_pressed();
      if (record->event.pressed && !is_modifier(keycode) &&
          !get_mods_active()) {
        apply_active_mods();
      }
  }

  // Windows用JISキーボード処理
  #ifdef TARGET_OS_WINDOWS
    if (!twpair_on_jis(keycode, record)) return false;
  #endif

  // 薙刀式の処理
  if (!get_mods_active()) {
    if (!process_naginata(keycode, record)) return true;
  }

  return true;
}
