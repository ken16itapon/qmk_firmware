#pragma once
#include QMK_KEYBOARD_H
#include "keymap.h"
#include "keymap_japanese.h"

// 前方宣言
enum custom_keycodes;

// 変換/無変換キーの定義q
#define MC_HENKAN KC_LNG1    // macOSでのカナキー
#define MC_MHENKAN KC_LNG2   // macOSでの英数キー
#define WC_HENKAN KC_INT4   // WindowsでのIME有効化
#define WC_MHENKAN KC_INT5  // WindowsでのIME無効化

// 完全に独自のOS列挙型を定義（QMKとの衝突を避ける）
typedef enum {
  CRKBD_OS_AUTO = 0,
  CRKBD_OS_WINDOWS,
  CRKBD_OS_MACOS,
  CRKBD_OS_LINUX,
  CRKBD_OS_UNKNOWN
} keyboard_os_t;

// ユーザーコードの互換性のためのマクロ定義
#define OS_AUTO CRKBD_OS_AUTO
#define OS_WINDOWS CRKBD_OS_WINDOWS
#define OS_MACOS CRKBD_OS_MACOS
#define OS_LINUX CRKBD_OS_LINUX
#define OS_UNKNOWN CRKBD_OS_UNKNOWN

// アプリケーションコードでの使用のために、os_typeもkeyboard_os_tとして再定義
typedef keyboard_os_t os_type;

// OSの現在の設定を取得するマクロ
#define GET_OS() global_os_cache = get_current_os()

// グローバル変数宣言
extern keyboard_os_t global_os_cache;

// 関数宣言
keyboard_os_t get_current_os(void);
uint16_t get_os_specific_keycode(uint16_t keycode);
uint8_t get_os_specific_mod_bit(uint16_t keycode);
void register_os_specific_key(uint16_t keycode);
void unregister_os_specific_key(uint16_t keycode);
void tap_os_specific_key(uint16_t keycode);
void register_os_specific_mods(uint16_t keycode);
void unregister_os_specific_mods(uint16_t keycode);
bool handle_os_mode(uint16_t keycode, bool pressed);
bool handle_os_display(void);

// EEPROMに保存する関数（独自実装）
void eeconfig_update_os_mode(keyboard_os_t mode);

// set_os_mode関数の宣言
void set_os_mode(keyboard_os_t os);

// 状態リセット用関数の宣言
void clean_all_mods_key(void);
void reset_os_specific_states(void);
