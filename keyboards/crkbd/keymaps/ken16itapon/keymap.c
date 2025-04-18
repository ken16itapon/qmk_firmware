/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
This program is distributed in the hope that it will be useful,
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H  // 最初に基本QMKヘッダー
#include "keymap.h"      // カスタムキーコード、レイヤー定義

#include "key_handlers.h"
#include "os_specific.h"    // OS関連の関数を使うために追加
#include "state_manager.h"  // is_modifier関数を使うために追加

enum {
  TD_CSTAB = 0,
};
#define CS_TAB TD(TD_CSTAB)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       CS_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G, COPILOT,     TENKEY,    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
       C_BSPC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D, XXXXXXX,     KC_EQL,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MHENKAN,   LOWER,   C_SPC,    S_ENTER,   RAISE,  HENKAN
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
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, _______,    _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                       KC_F11,  KC_F12, SC_BACK,  SC_FWD, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_ADJUST] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,MAC_MODE,   WIN_MODE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  S_CAPS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX, OS_DISP,  AUTO_MODE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                      KC_PSCR, KC_SCRL, KC_PAUS,  KC_INS,  KC_DEL, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
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
                                          KC_LWIN,   MO(1),  KC_SPC,     KC_ENT,   MO(2), KC_RALT
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
// clang-format on

void matrix_init_user(void) {
  // 薙刀式
  set_naginata(_NAGINATA);

  // EEPROMから設定を読み込む
  uint32_t user_config = eeconfig_read_user();
  global_os_cache = (uint8_t)(user_config & 0xFF);

  // 不正な値の場合はデフォルトに
  if (global_os_cache > OS_UNKNOWN) {
    global_os_cache = OS_AUTO;
  }
}

// matrix_scan_user関数内
void matrix_scan_user(void) {
  // 各キーの状態を処理 - 簡略化された呼び出し
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
  handle_advanced_repeat(&c_spc_state);
  handle_advanced_repeat(&c_bspc_state);
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

// CS_TAB キーのタップダンス処理
void cstab_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      // 単体タップ: TAB
      register_code(KC_TAB);
    } else {
      // 長押し: CTRL+SHIFT
      cs_tab_state.is_pressed = true;
      // 修飾キー関数を使用して複数の修飾キーを登録
      register_mods_for_key(&cs_tab_state);
    }
  } else if (state->count == 2) {
    // ダブルタップ: ESC
    register_code(KC_ESC);
  }
}

void cstab_reset(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      unregister_code(KC_TAB);
    } else if (cs_tab_state.is_pressed) {
      // 修飾キー関数を使用して複数の修飾キーを解除
      unregister_mods_for_key(&cs_tab_state);
      cs_tab_state.is_pressed = false;
    }
  } else if (state->count == 2) {
    unregister_code(KC_ESC);
  }

  // 安全のため、必ず状態をリセット
  if (cs_tab_state.is_pressed) {
    cs_tab_state.is_pressed = false;
    // 修飾キー関数を使用
    unregister_mods_for_key(&cs_tab_state);
  }
}

// タップダンス配列の定義
tap_dance_action_t tap_dance_actions[] = {
    [TD_CSTAB] = {.fn =
                      {
                          NULL,
                          cstab_finished,
                          cstab_reset,
                      }},
};

// keyboard_post_init_user関数を修正
void keyboard_post_init_user(void) {
  // EEPROMから前回の設定を読み込む
  keyboard_os_t saved_os = (keyboard_os_t)eeconfig_read_user();

  // 有効な値であれば適用、無効ならデフォルト(MACOS)を設定
  if (saved_os >= OS_AUTO && saved_os <= OS_LINUX) {
    set_os_mode(saved_os);
  } else {
    set_os_mode(OS_MACOS);  // デフォルトはMacOS
  }

  // キー状態の初期化を追加
  initialize_key_states();

  // 薙刀式の初期化など、他の初期化処理
  naginata_clear();
  naginata_off();

  // RGB初期化
  rgb_matrix_enable();
  rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
  rgb_matrix_sethsv(HSV_GREEN);

  // 最大輝度を設定（LEDが多すぎると電力不足になることがある）
  rgb_matrix_set_speed(128);            // 中程度の速度
  rgb_matrix_set_color_all(0, 255, 0);  // 緑色に設定（全LEDを点灯）
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
      clean_all_mods_key();
      reset_rapid_press();
      set_other_key_pressed();
      rgb_matrix_sethsv(HSV_YELLOW);
      break;
  }
  return state;
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

    // OS切替キーの処理
    case MAC_MODE:
      if (record->event.pressed) {
        set_os_mode(OS_MACOS);
        // 設定保存や状態リセットが必要な場合はここに追加
      }
      return false;

    case WIN_MODE:
      if (record->event.pressed) {
        set_os_mode(OS_WINDOWS);
        // 設定保存や状態リセットが必要な場合はここに追加
      }
      return false;

    case OS_DISP:
      if (record->event.pressed) {
        return handle_os_display();
      }
      return false;

    case MHENKAN:
      return handle_mhenkan_key(record);

    case HENKAN:
      return handle_henkan_key(record);

    case C_SPC:
      return handle_c_spc_key(record);

    case C_BSPC:
      return handle_c_bspc_key(record);

    case SC_BACK:
      tap_os_specific_key(SC_BACK);
      return false;

    case SC_FWD:
        tap_os_specific_key(SC_FWD);
        return false;

    default:
      reset_code_sent();
      set_other_key_pressed();
      if (record->event.pressed && !is_modifier(keycode) &&
          !get_mods_active()) {
        apply_active_mods();
      }
  }

  if (!twpair_on_jis(keycode, record)) return false;

  if (!process_naginata(keycode, record)) return true;

  return true;
}
