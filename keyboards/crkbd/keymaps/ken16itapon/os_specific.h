#pragma once
#include QMK_KEYBOARD_H  // 最初に基本QMKヘッダー
#include "keymap.h"      // カスタムキーコード、レイヤー定義
#include "keymap_japanese.h"

// 前方宣言だけで済ませる（keymap.hからのインクルードを避ける）
enum custom_keycodes;

// OSによって修飾キーを変更
#define MC_LCTL KC_LCMD  // Command
#define MC_LWIN KC_LOPT  // Option
#define MC_LALT KC_LCTL  // Control
#define MC_RCTL KC_RCMD
#define MC_RWIN KC_ROPT
#define MC_RALT KC_RCTL

// 変換/無変換キーの定義
#define MC_HENKAN KC_LNG1   // macOSでの変換キー
#define MC_MHENKAN KC_LNG2  // macOSでの無変換キー
#define KC_HENKAN KC_INT4   // WindowsでのIME有効化
#define KC_MHENKAN KC_INT5  // WindowsでのIME無効化

#ifdef OS_DETECTION_ENABLE
typedef os_variant_t keyboard_os_t;
#define OS_AUTO OS_UNSURE
#define OS_UNKNOWN OS_UNSURE + 1
// 自前のOS定義
typedef enum {
  OS_AUTO = 0,  // OS検出機能に任せる
  OS_WINDOWS,   // Windows強制モード
  OS_MACOS,     // macOS強制モード
  OS_LINUX,     // Linux強制モード
  OS_UNKNOWN
} keyboard_os_t;
#endif

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

// set_os_mode関数の宣言を修正
void set_os_mode(keyboard_os_t os);
