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

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#include "naginata.h"
#include "process_tap_dance.h"
#include "raw_hid.h"
#include "twpair_on_jis.h"

#define USE_MANUAL_OS_DETECTION  // 手動OS検出を有効化

// OSの状態を管理する変数
#ifdef OS_DETECTION_ENABLE
#include "os_detection.h"
// 現在のOS状態
static os_variant_t current_os_mode = OS_UNSURE;

// OSの種類を取得する関数
os_variant_t get_current_os(void) {
  if (current_os_mode == OS_UNSURE) {
    return detected_host_os();
  }
  return current_os_mode;
}
#else
// 自前のOS定義（OS_DETECTION_ENABLEがない場合のみ）
typedef enum {
  OS_AUTO = 0,  // OS検出機能に任せる
  OS_WINDOWS,   // Windows強制モード
  OS_MACOS,     // macOS強制モード
  OS_LINUX      // Linux強制モード
} keyboard_os_t;

// 現在のOS状態（OS_DETECTION_ENABLEがない場合のみ定義）
static keyboard_os_t current_os_mode = OS_AUTO;

// OSの種類を取得する関数
keyboard_os_t get_current_os(void) { return current_os_mode; }
#endif

// OS用のグローバル変数を定義
#ifdef OS_DETECTION_ENABLE
static os_variant_t global_os_cache;
#define GET_OS() (global_os_cache = get_current_os())
#else
static keyboard_os_t global_os_cache;
#define GET_OS() (global_os_cache = get_current_os())
#endif

NGKEYS naginata_keys;

// タップダンスのインデックス定義
enum {
  TD_CSTAB = 0,
};

// clang-format off
// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE = 0,
    _NAGINATA,
    _LOWER,
    _RAISE,
    _ADJUST,
    _10KEY
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    MHENKAN = NG_SAFE_RANGE,
    HENKAN,
    LOWER,
    RAISE,
    ADJUST,
// OS切り替え
    AUTO_MODE,
    MAC_MODE,
    WIN_MODE,
    LINUX_MODE,
// OS独立定義 OS-agnostic definition
    C_SPACE,
    CS_TAB,
    C_BSPC,
    OA_LCTL,
    OA_LWIN,
    OA_RALT,

    OS_DISP
};
// clang-format on

#define S_ENTER SFT_T(KC_ENT)
// #define C_SPACE CTL_T(KC_SPACE)
#define CS_TAB TD(TD_CSTAB)  // 既存のCS_TABマクロを上書き
// #define C_BSPC CTL_T(KC_BSPC)
#define S_ESC SFT_T(KC_ESC)
#define COPILOT LSG(KC_F23)
#define POWER KC_KB_POWER
#define S_CAPS LSFT(KC_CAPS)
#define TENKEY TG(_10KEY)

// OSによって修飾キーを変更
#define MC_LCTL KC_LCMD
#define MC_LWIN KC_LOPT
#define MC_LALT KC_LCTL
#define MC_RCTL KC_RCMD
#define MC_RWIN KC_ROPT
#define MC_RALT KC_RCTL

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_ex2(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       CS_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G, COPILOT,     TENKEY,    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
       C_BSPC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D, XXXXXXX,     KC_EQL,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
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
      QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,MAC_MODE,   WIN_MODE, XXXXXXX, XXXXXXX,   POWER, XXXXXXX, XXXXXXX,  S_CAPS,
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
      OA_LCTL, KC_PDOT,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, _______,    _______, KC_PDOT,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, KC_PSLS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_P0,   KC_P1,   KC_P2,   KC_P3, KC_PPLS,                        KC_P0,   KC_P1,   KC_P2,   KC_P3, KC_PPLS, KC_PAST,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          OA_LWIN,   MO(1),  KC_SPC,     KC_ENT,   MO(2), OA_RALT
                                      //`--------------------------'  `--------------------------'

  )
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
    [1] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
    [2] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
    [3] =
        {
            ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
            ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
            ENCODER_CCW_CW(RM_VALD, RM_VALU),
            ENCODER_CCW_CW(KC_RGHT, KC_LEFT),
        },
};
#endif

void matrix_init_user(void) {
  // 薙刀式

  set_naginata(_NAGINATA);
  // 薙刀式
}

// 状態管理の構造体を拡張
static struct {
  bool pressed;
  uint16_t pressed_time;
  uint16_t released_time;
  bool bspc_active;
  bool backspace_sent;
  bool rapid_press;
  bool mods_active;  // 修飾キーの状態管理を追加
} lower_state = {0};

static struct {
  bool pressed;
  uint16_t pressed_time;
  uint16_t released_time;
  bool spc_active;
  bool space_sent;
  bool rapid_press;
  bool mods_active;  // 修飾キーの状態管理を追加
} raise_state = {0};

// henkan/mhenkanの状態管理を構造体化
static struct {
  bool henkan_pressed;
  uint16_t henkan_pressed_time;
  bool mhenkan_pressed;
  uint16_t mhenkan_pressed_time;
  bool mods_active;  // 修飾キーの状態管理
} ime_state = {0};

static struct {
  uint16_t pressed_time;
  uint16_t released_time; // リリース時間を追加
  bool bspc_active;       // リピート状態フラグ
  bool backspace_sent;    // バックスペースが送信されたフラグ
  bool pressed;           // キーが押されているかフラグ
} c_bspc_state = {0};

static struct {
  uint16_t pressed_time;
} c_space_state = {0};

static struct {
  bool lower;
  bool raise;
  bool any;
} other_key_pressed = {0};

void other_key_pressed_except(bool *except) {
  if (&other_key_pressed.lower != except) {
    other_key_pressed.lower = true;
    other_key_pressed.any = true;
  }
  if (&other_key_pressed.raise != except) {
    other_key_pressed.raise = true;
    other_key_pressed.any = true;
  }
}

void reset_other_key_pressed(void) {
  other_key_pressed.lower = false;
  other_key_pressed.raise = false;
  other_key_pressed.any = false;
}

void set_other_key_pressed(void) {
  other_key_pressed.lower = true;
  other_key_pressed.raise = true;
  other_key_pressed.any = true;
}

bool all_keys_released(void) {
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    // matrix_get_row() はその行のビットマップを返す
    if (matrix_get_row(row)) {
      return false;
    }
  }
  return true;
}

static uint16_t all_keys_released_time;

// CTRLキーが現在押されているか確認するヘルパー関数
bool is_control_pressed(void) {
  GET_OS();
  switch (global_os_cache) {
    case OS_MACOS:  // MacOS
      return (get_mods() & MOD_BIT(MC_LCTL)) || (get_mods() & MOD_BIT(MC_RCTL));
    default:  // Windows/Linux
      return (get_mods() & MOD_BIT(KC_LCTL)) || (get_mods() & MOD_BIT(KC_RCTL));
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 全キー共通の前処理
  if (record->event.pressed) {

    // LOWERでもRAISEでもない通常キーが押された場合
    if (keycode != LOWER && keycode != RAISE) {
      set_other_key_pressed(); // 両方のフラグをセット
    } else if (keycode == LOWER) {
      set_other_key_pressed_exept(&other_key_pressed.lower);
    } else if (keycode == RAISE) {
      set_other_key_pressed_exept(&other_key_pressed.raise);
    }

  } else {
    if (all_keys_released()) {
      all_keys_released_time = record->event.time;
    }
  }

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        // 高速タイピング対応: キーの状態をリセット
        if (timer_elapsed(all_keys_released_time) < TAPPING_TERM) {
          reset_other_key_pressed();
        }

        if (timer_elapsed(lower_state.released_time) < TAPPING_TERM) {
          lower_state.rapid_press = true;  // 連打
        } else {
          lower_state.rapid_press = false;  // 連打リセット
        }

        lower_state.pressed = true;
        lower_state.pressed_time = record->event.time;
        other_key_pressed_except(&other_key_pressed.lower);
        lower_state.bspc_active = false;

        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        // 単打判定の修正: 高速タイピングでも単打を許容
        if (timer_elapsed(lower_state.pressed_time) < TAPPING_TERM &&
            !other_key_pressed.lower &&
            !lower_state.rapid_press) {  // 連打でない場合のみBSPC発行
          tap_code(KC_BSPC);
          lower_state.backspace_sent = true;
          lower_state.released_time = record->event.time;
        }

        if (lower_state.bspc_active) {
          unregister_code(KC_BSPC);
          lower_state.bspc_active = false;
          // lower_state.backspace_sent = false;
        }

        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        lower_state.pressed = false;
      }
      return false;

    case RAISE:
      if (record->event.pressed) {
        // 高速タイピング対応: キーの状態をリセット
        if (timer_elapsed(all_keys_released_time) < TAPPING_TERM) {
          reset_other_key_pressed();
        }

        if (timer_elapsed(raise_state.released_time) < TAPPING_TERM) {
          raise_state.rapid_press = true;  // 連打
        } else {
          raise_state.rapid_press = false;  // 連打リセット
        }

        raise_state.pressed = true;
        raise_state.pressed_time = record->event.time;
        other_key_pressed_except(&other_key_pressed.raise);
        raise_state.spc_active = false;

        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        // CTRLキーが押されている場合は、即座にSPACEも押下してCTRL+SPACEにする
        if (is_control_pressed()) {
          register_code(KC_SPACE);
        }
      } else {
        // 単打判定の修正: 高速タイピングでも単打を許容
        if (timer_elapsed(raise_state.pressed_time) < TAPPING_TERM &&
            !other_key_pressed.raise < TAPPING_TERM &&
            !raise_state.rapid_press) {  // 連打でない場合のみSPC発行
          // CTRLが押されていない場合のみスペース単打を発行
          if (!is_control_pressed()) {
            tap_code(KC_SPACE);
            raise_state.space_sent = true;
            raise_state.released_time = record->event.time;
          }
        }

        // CTRLが押されている場合はスペースキーを解放
        if (is_control_pressed()) {
          unregister_code(KC_SPACE);
        }

        if (raise_state.spc_active) {
          unregister_code(KC_SPC);
          raise_state.spc_active = false;
        }

        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        raise_state.pressed = false;
      }
      return false;

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
        ime_state.mods_active = true;
        ime_state.mhenkan_pressed = true;
        ime_state.mhenkan_pressed_time = record->event.time;

        // 修飾キーを登録（押したときに登録）
        GET_OS();
        switch (global_os_cache) {
          case OS_MACOS:  // MacOS
            register_mods(MOD_BIT(MC_LALT));
            break;
          default:  // Windows/Linux
            register_mods(MOD_BIT(KC_LALT));
            break;
        }
      } else {
        if (timer_elapsed(ime_state.mhenkan_pressed_time) < TAPPING_TERM &&
            !other_key_pressed.lower && !other_key_pressed.raise) {
          // 単打時の処理（他のキーが押されていない場合のみ）
          GET_OS();
          switch (global_os_cache) {
            case OS_MACOS:  // MacOS
              tap_code(KC_LANGUAGE_2);
              break;
            case OS_WINDOWS:  // Windows
              tap_code(KC_INTERNATIONAL_5);
              break;
            default:  // Linux
              tap_code(KC_INTERNATIONAL_5);
              break;
          }
          naginata_off();
        }

        // 修飾キーを解除
        ime_state.mhenkan_pressed = false;
        ime_state.mods_active = ime_state.henkan_pressed ? true : false;

        GET_OS();
        switch (global_os_cache) {
          case OS_MACOS:  // MacOS
            unregister_mods(MOD_BIT(MC_LALT));
            break;
          default:  // Windows/Linux
            unregister_mods(MOD_BIT(KC_LALT));
            break;
        }
      }
      return false;

    case HENKAN:
      if (record->event.pressed) {
        ime_state.mods_active = true;
        ime_state.henkan_pressed = true;
        ime_state.henkan_pressed_time = record->event.time;

        // 修飾キーを登録（押したときに登録）
        GET_OS();
        switch (global_os_cache) {
          case OS_MACOS:  // MacOS
            register_mods(MOD_BIT(MC_RWIN));
            break;
          default:  // Windows/Linux
            register_mods(MOD_BIT(KC_RWIN));
            break;
        }
      } else {
        if (timer_elapsed(ime_state.henkan_pressed_time) < TAPPING_TERM &&
        !other_key_pressed.lower && !other_key_pressed.raise) {
          GET_OS();
          switch (global_os_cache) {
            case OS_MACOS:  // MacOS
              tap_code(KC_LANGUAGE_1);
              break;
            case OS_WINDOWS:  // Windows
              tap_code(KC_INTERNATIONAL_4);
              break;
            default:  // Linux
              tap_code(KC_INTERNATIONAL_4);
              break;
          }
          naginata_on();
        }
        ime_state.henkan_pressed = false;
        ime_state.mods_active = ime_state.mhenkan_pressed ? true : false;

        GET_OS();
        switch (global_os_cache) {
          case OS_MACOS:  // MacOS
            unregister_mods(MOD_BIT(MC_LWIN));
            break;
          default:  // Windows/Linux
            unregister_mods(MOD_BIT(KC_LWIN));
            break;
        }
            // 修飾キーを解除
    ime_state.henkan_pressed = false;
    ime_state.mods_active = ime_state.mhenkan_pressed ? true : false;

    GET_OS();
    switch (global_os_cache) {
      case OS_MACOS:  // MacOS
        unregister_mods(MOD_BIT(MC_LWIN));
        break;
      default:  // Windows/Linux
        unregister_mods(MOD_BIT(KC_RWIN));
        break;
    }
      }
      return false;

#ifdef OS_DETECTION_ENABLE
    case AUTO_MODE:
      if (record->event.pressed) {
        current_os_mode = OS_UNSURE;  // OS_AUTOではなくOS_UNSUREを使用
        // 状態を永続化する場合はEEPROMに書き込み
        // eeconfig_update_user((uint32_t)current_os_mode);
        set_other_key_pressed();
      }
      return false;
#else
    case AUTO_MODE:
      if (record->event.pressed) {
        current_os_mode = OS_AUTO;  // 自前定義のOS_AUTOを使用
        // 状態を永続化する場合はEEPROMに書き込み
        // eeconfig_update_user((uint32_t)current_os_mode);
        set_other_key_pressed();
      }
      return false;
#endif

#ifdef OS_DETECTION_ENABLE
    case MAC_MODE:
      if (record->event.pressed) {
        current_os_mode = OS_MACOS;  // os_detection.hで定義されたOS_MACOS
        set_other_key_pressed();
      }
      return false;

    case WIN_MODE:
      if (record->event.pressed) {
        current_os_mode = OS_WINDOWS;  // os_detection.hで定義されたOS_WINDOWS
        set_other_key_pressed();
      }
      return false;
#else
    case MAC_MODE:
      if (record->event.pressed) {
        current_os_mode = OS_MACOS;  // 自前定義のOS_MACOSを使用
        set_other_key_pressed();
      }
      return false;

    case WIN_MODE:
      if (record->event.pressed) {
        current_os_mode = OS_WINDOWS;  // 自前定義のOS_WINDOWSを使用
        set_other_key_pressed();
      }
      return false;
#endif

    case C_SPACE:
      if (record->event.pressed) {
        c_space_state.pressed_time = record->event.time;
        GET_OS();
        switch (global_os_cache) {
          case OS_MACOS:  // MacOS
            register_mods(MOD_BIT(MC_LCTL));
            break;
          default:  // Windows/Linux
            register_mods(MOD_BIT(KC_LCTL));
            break;
        }
        set_other_key_pressed();
      } else {
        if (timer_elapsed(c_space_state.pressed_time) < TAPPING_TERM) {
          tap_code(KC_SPACE);
          set_other_key_pressed();
        } else {
          GET_OS();
          switch (global_os_cache) {
            case OS_MACOS:  // MacOS
              unregister_mods(MOD_BIT(MC_LCTL));
              break;
            default:  // Windows/Linux
              unregister_mods(MOD_BIT(KC_LCTL));
              break;
          }
        }
      }
      return false;

    case C_BSPC:
      if (record->event.pressed) {
        c_bspc_state.pressed = true;
        c_bspc_state.pressed_time = record->event.time;
        c_bspc_state.bspc_active = false;
        GET_OS();
        switch (global_os_cache) {
          case OS_MACOS:  // MacOS
            register_mods(MOD_BIT(MC_LCTL));
            break;
          default:  // Windows/Linux
            register_mods(MOD_BIT(KC_LCTL));
            break;
        }
        set_other_key_pressed();
        return false;
      } else {
        // キーを離した時の処理
        if (timer_elapsed(c_bspc_state.pressed_time) < TAPPING_TERM) {
          // タップした場合はバックスペース入力
          tap_code(KC_BSPC);
          c_bspc_state.backspace_sent = true;
          c_bspc_state.released_time = record->event.time;
        } else {
          // 長押しの場合は修飾キーを解除
          GET_OS();
          switch (global_os_cache) {
            case OS_MACOS:  // MacOS
              unregister_mods(MOD_BIT(MC_LCTL));
              break;
            default:  // Windows/Linux
              unregister_mods(MOD_BIT(KC_LCTL));
              break;
          }
        }
        c_bspc_state.pressed = false;
        return false;
      }

    case OA_LCTL:
      if (record->event.pressed) {
        GET_OS();
        switch (global_os_cache) {
          case OS_MACOS:  // MacOS
            register_mods(MOD_BIT(MC_LCTL));
            break;
          default:  // Windows/Linux
            register_mods(MOD_BIT(KC_LCTL));
            break;
        }
        set_other_key_pressed();
        return false;

      } else {
        GET_OS();
        switch (global_os_cache) {
          case OS_MACOS:  // MacOS
            unregister_mods(MOD_BIT(MC_LCTL));
            break;
          default:  // Windows/Linux
            unregister_mods(MOD_BIT(KC_LCTL));
            break;
        }
        return false;
      }

    case OA_LWIN:
      if (record->event.pressed) {
        GET_OS();
        switch (global_os_cache) {
          case OS_MACOS:  // MacOS
            register_mods(MOD_BIT(MC_LWIN));
            break;
          default:  // Windows/Linux
            register_mods(MOD_BIT(KC_LWIN));
            break;
        }
        set_other_key_pressed();
        return false;
      } else {
        GET_OS();
        switch (global_os_cache) {
          case OS_MACOS:  // MacOS
            unregister_mods(MOD_BIT(MC_LWIN));
            break;
          default:  // Windows/Linux
            unregister_mods(MOD_BIT(KC_LWIN));
            break;
        }
        return false;
      }

    case OA_RALT:

      if (record->event.pressed) {
        GET_OS();
        switch (global_os_cache) {
          case OS_MACOS:  // MacOS
            register_mods(MOD_BIT(MC_RALT));
            break;
          default:  // Windows/Linux
            register_mods(MOD_BIT(KC_RALT));
            break;
        }
        set_other_key_pressed();
        return false;
      } else {
        GET_OS();
        switch (global_os_cache) {
          case OS_MACOS:  // MacOS
            unregister_mods(MOD_BIT(MC_RALT));
            break;
          default:  // Windows/Linux
            unregister_mods(MOD_BIT(KC_RALT));
            break;
        }
        return false;
      }

    case OS_DISP:
      if (record->event.pressed) {
#ifdef OS_DETECTION_ENABLE
        GET_OS();
        switch (global_os_cache) {
          case OS_UNSURE:
            SEND_STRING("OS Mode: Auto Detect");
            break;
          case OS_LINUX:
            SEND_STRING("OS Mode: Linux");
            break;
          case OS_WINDOWS:
            SEND_STRING("OS Mode: Windows");
            break;
          case OS_MACOS:
            SEND_STRING("OS Mode: MacOS");
            break;
          default:
            SEND_STRING("OS Mode: Unknown");
            break;
        }
#else
        GET_OS();
        switch (global_os_cache) {
          case OS_AUTO:
            SEND_STRING("OS Mode: Auto");
            break;
          case OS_WINDOWS:
            SEND_STRING("OS Mode: Windows");
            break;
          case OS_MACOS:
            SEND_STRING("OS Mode: macOS");
            break;
          case OS_LINUX:
            SEND_STRING("OS Mode: Linux");
            break;
          default:
            SEND_STRING("OS Mode: Unknown");
            break;
        }
#endif
      }
      return false;

    default:
      if (record->event.pressed) {
        // 修飾キーの処理
        if (ime_state.mods_active) {
          if (ime_state.henkan_pressed) {
            register_mods(MOD_BIT(KC_RWIN));
            tap_code(keycode);
            unregister_mods(MOD_BIT(KC_RWIN));
          }
          if (ime_state.mhenkan_pressed) {
            register_mods(MOD_BIT(KC_LALT));
            tap_code(keycode);
            unregister_mods(MOD_BIT(KC_LALT));
          }

          set_other_key_pressed();
          return false;
        }
      }

      // 薙刀式とその他の処理
      if (!twpair_on_jis(keycode, record)) return false;
      if (!process_naginata(keycode, record)) return true;

      return true;
  }
}

// matrix_scan_user関数内
void matrix_scan_user(void) {
  // BSPCリピート開始条件
  if (lower_state.pressed && lower_state.backspace_sent &&
      !lower_state.bspc_active && !other_key_pressed.lower &&
      (timer_elapsed(lower_state.released_time) < TAPPING_TERM)) {
    lower_state.bspc_active = true;
    register_code(KC_BSPC);
    lower_state.backspace_sent = false;
  }

  // BSPCリピート終了条件
  if ((!lower_state.pressed && lower_state.bspc_active) ||
      other_key_pressed.lower) {
    unregister_code(KC_BSPC);
    lower_state.bspc_active = false;
  }

  // C_BSPCリピート開始条件 - ここに追加
  if (c_bspc_state.pressed && c_bspc_state.backspace_sent &&
      !c_bspc_state.bspc_active &&
      (timer_elapsed(c_bspc_state.released_time) < TAPPING_TERM)) {
    c_bspc_state.bspc_active = true;
    register_code(KC_BSPC);
    c_bspc_state.backspace_sent = false;
  }

  // C_BSPCリピート終了条件 - ここに追加
  if (!c_bspc_state.pressed && c_bspc_state.bspc_active) {
    unregister_code(KC_BSPC);
    c_bspc_state.bspc_active = false;
  }

  // SPCリピート開始条件
  if (raise_state.pressed && raise_state.space_sent &&
      !raise_state.spc_active && !other_key_pressed.raise &&
      (timer_elapsed(raise_state.released_time) < TAPPING_TERM)) {
    raise_state.spc_active = true;
    register_code(KC_SPC);
    raise_state.space_sent = false;
  }

  // SPCリピート終了条件
  if ((!raise_state.pressed && raise_state.spc_active) ||
      other_key_pressed.raise) {
    unregister_code(KC_SPC);
    raise_state.spc_active = false;
  }

  // 修飾キーのクリーンアップ
  if (all_keys_released() && (timer_elapsed(all_keys_released_time) > TAPPING_TERM)) {
    lower_state.pressed = false;
    raise_state.pressed = false;
    ime_state.henkan_pressed = false;
    ime_state.mhenkan_pressed = false;
    ime_state.mods_active = false;
    reset_other_key_pressed();

    // 修飾キーのクリーンアップ修正
    unregister_mods(MOD_BIT(KC_LALT));
    unregister_mods(MOD_BIT(KC_LWIN));
    unregister_mods(MOD_BIT(KC_LCTL));
    unregister_mods(MOD_BIT(KC_LSFT));
    unregister_mods(MOD_BIT(KC_RALT));
    unregister_mods(MOD_BIT(KC_RWIN));
    unregister_mods(MOD_BIT(KC_RCTL));
    unregister_mods(MOD_BIT(KC_RSFT));
  }
}

// HIDレポートのハンドリング
void raw_hid_receive(uint8_t *data, uint8_t length) {
  if (length < 1) return;

  switch (data[0]) {
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
      register_code(KC_TAB);
    } else {
      mods_active = true;
      GET_OS();
      switch (global_os_cache) {
        case OS_MACOS:  // MacOS
          register_mods(MOD_BIT(MC_LCTL) | MOD_BIT(KC_LSFT));
          break;
        default:  // Windows/Linux
          register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
          break;
      }
    }
  } else if (state->count == 2) {
    register_code(KC_ESC);
  }
}

// タップダンスリセット時の処理
void cstab_reset(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      unregister_code(KC_TAB);
    } else if (mods_active) {
      GET_OS();
      switch (global_os_cache) {
        case OS_MACOS:  // MacOS
          unregister_mods(MOD_BIT(MC_LCTL) | MOD_BIT(KC_LSFT));
          break;
        default:  // Windows/Linux
          unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
          break;
      }
      mods_active = false;
    }
  } else if (state->count == 2) {
    unregister_code(KC_ESC);
  }

  if (mods_active) {
    GET_OS();
    switch (global_os_cache) {
      case OS_MACOS:  // MacOS
        unregister_mods(MOD_BIT(MC_LCTL) | MOD_BIT(KC_LSFT));
        break;
      default:  // Windows/Linux
        unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT));
        break;
    }
    mods_active = false;
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
  // デバッグモードを有効化
  debug_enable = true;
  debug_matrix = true;

  // RGB初期化
  rgb_matrix_enable();
  rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
  rgb_matrix_sethsv(HSV_GREEN);

  // 最大輝度を設定（LEDが多すぎると電力不足になることがある）
  rgb_matrix_set_speed(128);  // 中程度の速度
  rgb_matrix_set_color_all(0, 255, 0);  // 緑色に設定（全LEDを点灯）

  // デバッグ情報の出力
  dprintf("RGB Matrix Status: %d\n", rgb_matrix_is_enabled());
  dprintf("LED Config: %d LEDs, Mode: %d\n", DRIVER_LED_TOTAL, rgb_matrix_get_mode());
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
