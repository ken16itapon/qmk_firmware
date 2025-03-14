#pragma once

#include QMK_KEYBOARD_H

#include "key_handlers.h"  // その後に関数定義
#include "keymap_japanese.h"

#include "os_specific.h"
#include "state_manager.h"  // 先に型定義
#include "twpair_on_jis.h"
#include "naginata.h"

// カスタムキーコード定義
enum custom_keycodes {
  MHENKAN = NG_SAFE_RANGE,
  HENKAN,
  LOWER,
  RAISE,
  ADJUST,
  AUTO_MODE,
  MAC_MODE,
  WIN_MODE,
  LINUX_MODE,
  OS_DISP,
  OA_LCTL,
  OA_LWIN,
  OA_RALT,
  C_SPC,
  C_BSPC
};

// レイヤー定義
enum layers { _BASE = 0, _NAGINATA, _LOWER, _RAISE, _ADJUST, _10KEY };

#define S_ENTER SFT_T(KC_ENT)

#define S_ESC SFT_T(KC_ESC)
#define COPILOT LSG(KC_F23)
#define POWER KC_KB_POWER
#define S_CAPS LSFT(KC_CAPS)
#define TENKEY TG(_10KEY)

// 関数宣言
bool process_record_user(uint16_t keycode, keyrecord_t *record);
void matrix_scan_user(void);
layer_state_t layer_state_set_user(layer_state_t state);
void keyboard_post_init_user(void);
