#include QMK_KEYBOARD_H  // 最初に基本QMKヘッダー
#include "keymap.h"      // カスタムキーコード、レイヤー定義
// その他の依存関係
#include "keymap_japanese.h"  // 日本語キーボード定義
#include "os_specific.h"

// 現在のOS状態 - すでにMacOSがデフォルト
static keyboard_os_t current_os_mode = OS_AUTO;

// グローバル変数の定義
keyboard_os_t global_os_cache = OS_MACOS;  // デフォルトでmacOSに設定;

// OSの種類を取得する関数
keyboard_os_t get_current_os(void) {
#ifdef OS_DETECTION_ENABLE
  if (current_os_mode == OS_UNSURE) {
    return detected_host_os();
  }
#endif
  return current_os_mode;
}

// 元のキーコードとOSの種類から、適切なキーコードに変換する関数
uint16_t get_os_specific_keycode(uint16_t keycode) {
  GET_OS();

  // 基本キーはOS関係なく同じなので、修飾キーのみ変換
  switch (keycode) {
    // 左側修飾キー
    case KC_LCTL:
      return (global_os_cache == OS_MACOS) ? MC_LCTL : KC_LCTL;
    case KC_LGUI:  // GUI/Win/Commandキー
      return (global_os_cache == OS_MACOS) ? MC_LWIN : KC_LGUI;
    case KC_LALT:
      return (global_os_cache == OS_MACOS) ? MC_LALT : KC_LALT;

    // 右側修飾キー
    case KC_RCTL:
      return (global_os_cache == OS_MACOS) ? MC_RCTL : KC_RCTL;
    case KC_RGUI:  // GUI/Win/Commandキー
      return (global_os_cache == OS_MACOS) ? MC_RWIN : KC_RGUI;
    case KC_RALT:
      return (global_os_cache == OS_MACOS) ? MC_RALT : KC_RALT;

    // 修飾キーのビットマスク（直接mods用）
    case MOD_LCTL:
      return (global_os_cache == OS_MACOS) ? MOD_BIT(MC_LCTL)
                                           : MOD_BIT(KC_LCTL);
    case MOD_LGUI:
      return (global_os_cache == OS_MACOS) ? MOD_BIT(MC_LWIN)
                                           : MOD_BIT(KC_LGUI);
    case MOD_LALT:
      return (global_os_cache == OS_MACOS) ? MOD_BIT(MC_LALT)
                                           : MOD_BIT(KC_LALT);
    case MOD_RCTL:
      return (global_os_cache == OS_MACOS) ? MOD_BIT(MC_RCTL)
                                           : MOD_BIT(KC_RCTL);
    case MOD_RGUI:
      return (global_os_cache == OS_MACOS) ? MOD_BIT(MC_RWIN)
                                           : MOD_BIT(KC_RGUI);
    case MOD_RALT:
      return (global_os_cache == OS_MACOS) ? MOD_BIT(MC_RALT)
                                           : MOD_BIT(KC_RALT);

    // IME関連キー
    case KC_HENKAN:  // IME有効化
      return (global_os_cache == OS_MACOS) ? MC_HENKAN : KC_HENKAN;
    case KC_MHENKAN:  // IME無効化
      return (global_os_cache == OS_MACOS) ? MC_MHENKAN : KC_MHENKAN;

    // その他のキーは変換せずそのまま返す
    default:
      return keycode;
  }
}

// キーコードに対応するモディファイアビットを取得
uint8_t get_os_specific_mod_bit(uint16_t keycode) {
  GET_OS();

  switch (keycode) {
    case KC_LCTL:
      return (global_os_cache == OS_MACOS) ? MOD_BIT(MC_LCTL)
                                           : MOD_BIT(KC_LCTL);
    case KC_LGUI:
      return (global_os_cache == OS_MACOS) ? MOD_BIT(MC_LWIN)
                                           : MOD_BIT(KC_LGUI);
    case KC_LALT:
      return (global_os_cache == OS_MACOS) ? MOD_BIT(MC_LALT)
                                           : MOD_BIT(KC_LALT);
    case KC_RCTL:
      return (global_os_cache == OS_MACOS) ? MOD_BIT(MC_RCTL)
                                           : MOD_BIT(KC_RCTL);
    case KC_RGUI:
      return (global_os_cache == OS_MACOS) ? MOD_BIT(MC_RWIN)
                                           : MOD_BIT(KC_RGUI);
    case KC_RALT:
      return (global_os_cache == OS_MACOS) ? MOD_BIT(MC_RALT)
                                           : MOD_BIT(KC_RALT);
    default:
      return 0;
  }
}

void register_os_specific_key(uint16_t keycode) {
  uint16_t os_keycode = get_os_specific_keycode(keycode);
  register_code(os_keycode);
}

void unregister_os_specific_key(uint16_t keycode) {
  uint16_t os_keycode = get_os_specific_keycode(keycode);
  unregister_code(os_keycode);
}

void tap_os_specific_key(uint16_t keycode) {
  uint16_t os_keycode = get_os_specific_keycode(keycode);
  tap_code(os_keycode);
}

void register_os_specific_mods(uint16_t keycode) {
  uint8_t mod_bit = get_os_specific_mod_bit(keycode);
  register_mods(mod_bit);
}

void unregister_os_specific_mods(uint16_t keycode) {
  uint8_t mod_bit = get_os_specific_mod_bit(keycode);
  unregister_mods(mod_bit);
}

// OS設定モード切り替え処理
bool handle_os_mode(uint16_t keycode, bool pressed) {
  // keymap.hで定義されたカスタムキーコードを使用
  if (!pressed) return false;

  GET_OS();

  switch (keycode) {
    case AUTO_MODE:
      global_os_cache = OS_AUTO;
      break;
    case MAC_MODE:
      global_os_cache = OS_MACOS;
      break;
    case WIN_MODE:
      global_os_cache = OS_WINDOWS;
      break;
    case LINUX_MODE:
      global_os_cache = OS_LINUX;
      break;
    default:
      return true;
  }

  // 設定を保存
  eeconfig_update_os_mode(global_os_cache);
  return false;
}

// EEPROMに設定を保存する関数
void eeconfig_update_os_mode(keyboard_os_t mode) {
  // EECONFIG_USERはuint32_t型のポインタだが、eeprom_update_byteはuint8_t型のポインタを期待
  // 正しいQMK APIを使用する
  eeconfig_update_user((uint32_t)mode);

  // デバッグ出力
  dprintf("Saving OS mode: %d\n", mode);
}

// EEPROMから読み込む関数
keyboard_os_t eeconfig_read_os_mode(void) {
  // QMK APIを使用して値を取得
  uint32_t val = eeconfig_read_user();

  // 8ビット値として扱う（キーボードOSタイプは列挙型で小さな値）
  uint8_t os_mode = (uint8_t)(val & 0xFF);

  // 有効範囲チェック - 明示的な値をチェック
  if (os_mode != OS_AUTO && os_mode != OS_WINDOWS && os_mode != OS_MACOS &&
      os_mode != OS_LINUX) {
    os_mode = OS_MACOS;  // デフォルトはMacOS
  }

  return (keyboard_os_t)os_mode;
}

// OSモードを設定する関数
void set_os_mode(keyboard_os_t os) {
  // モードを変更して保存
  global_os_cache = os;

  // EEPROMに保存して再起動後も保持
  eeconfig_update_os_mode(os);

  // デバッグ情報
  dprintf("OS Mode set to: %d\n", os);

// 状態表示LEDなど、必要であれば設定
#ifdef RGB_MATRIX_ENABLE
  switch (global_os_cache) {
    case OS_MACOS:
      rgb_matrix_sethsv(HSV_CYAN);  // macOS:青色
      break;
    case OS_WINDOWS:
      rgb_matrix_sethsv(HSV_PURPLE);  // Windows:紫色
      break;
    case OS_LINUX:
      rgb_matrix_sethsv(HSV_YELLOW);  // Linux:黄色
      break;
    case OS_AUTO:
    default:
      rgb_matrix_sethsv(HSV_GREEN);  // 自動検出:緑色
      break;
  }
#endif
}

// OS表示処理
bool handle_os_display(void) {
  // 現在のOSモードを取得
  GET_OS();

  // デバッグ出力
  dprintf("Current OS: %d\n", global_os_cache);

// RGBマトリックスでOS表示
#ifdef RGB_MATRIX_ENABLE
  switch (global_os_cache) {
    case OS_MACOS:
      rgb_matrix_sethsv(HSV_CYAN);  // macOS:青色
      break;
    case OS_WINDOWS:
      rgb_matrix_sethsv(HSV_PURPLE);  // Windows:紫色
      break;
    case OS_LINUX:
      rgb_matrix_sethsv(HSV_YELLOW);  // Linux:黄色
      break;
    case OS_AUTO:
    default:
      rgb_matrix_sethsv(HSV_GREEN);  // 自動検出:緑色
      break;
  }
#endif

  return false;  // キー処理を続けない
}
