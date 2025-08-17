#pragma once

#include QMK_KEYBOARD_H

#include "key_handlers.h"
#include "keymap_japanese.h"
#include "state_manager.h"
// 条件付きインクルード
#ifdef NAGINATA_ENABLE
  #include "naginata.h"
#else
  // NAGINATAが無効の場合のダミー定義
  #define NG_SAFE_RANGE SAFE_RANGE
  #define set_naginata(x)
  #define naginata_on()
  #define naginata_off()
  #define naginata_clear()
  #define process_naginata(keycode, record) true
  #define NG_Q KC_NO
  #define NG_W KC_NO
  #define NG_E KC_NO
  #define NG_R KC_NO
  #define NG_T KC_NO
  #define NG_Y KC_NO
  #define NG_U KC_NO
  #define NG_I KC_NO
  #define NG_O KC_NO
  #define NG_P KC_NO
  #define NG_X1 KC_NO
  #define NG_A KC_NO
  #define NG_S KC_NO
  #define NG_D KC_NO
  #define NG_F KC_NO
  #define NG_G KC_NO
  #define NG_H KC_NO
  #define NG_J KC_NO
  #define NG_K KC_NO
  #define NG_L KC_NO
  #define NG_SCLN KC_NO
  #define NG_Z KC_NO
  #define NG_X KC_NO
  #define NG_C KC_NO
  #define NG_V KC_NO
  #define NG_B KC_NO
  #define NG_N KC_NO
  #define NG_M KC_NO
  #define NG_COMM KC_NO
  #define NG_DOT KC_NO
  #define NG_SLSH KC_NO
#endif

// twpair_on_jisの定義（Windows用）
#ifdef TARGET_OS_WINDOWS
  bool twpair_on_jis(uint16_t keycode, keyrecord_t *record);
#else
  #define twpair_on_jis(keycode, record) true
#endif

// カスタムキーコード定義
enum custom_keycodes {
  EISU = NG_SAFE_RANGE,  // MHENKAN相当（英数）
  KANA,                   // HENKAN相当（かな）
  LOWER,
  RAISE,
  C_SPC,                  // Ctrl+Space（IME切り替え用）
  C_BSPC,                 // Ctrl+Backspace
  ADJUST,
  RGBRST                  // RGB設定リセット
};

// エイリアス定義（crkbdとの互換性のため）
#define MHENKAN EISU
#define HENKAN KANA
#define CC_LCTL KC_LCTL

// レイヤー定義（既存のものを維持）
enum layers { 
  _COLEMAK = 0,
  _NAGINATA,
  _LOWER,
  _RAISE,
  _PAD,
  _ADJUST
};

// 関数宣言
bool process_record_user(uint16_t keycode, keyrecord_t *record);
void matrix_scan_user(void);
layer_state_t layer_state_set_user(layer_state_t state);
void keyboard_post_init_user(void);
void matrix_init_user(void);