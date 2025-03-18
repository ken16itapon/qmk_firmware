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
  // OS_UNSUREではなく、OS_AUTO（CRKBD_OS_AUTO）を使用
  if (current_os_mode == OS_AUTO) {
// 自動検出モード
#ifdef OS_DETECTION_ENABLE
    // QMK組み込みの検出機能を使用
    os_variant_t detected = detected_host_os();
    switch (detected) {
      case OS_WINDOWS:
        return OS_WINDOWS;
      case OS_MACOS:
        return OS_MACOS;
      case OS_LINUX:
        return OS_LINUX;
      default:
        return OS_MACOS;  // デフォルトはMacOS
    }
#else
    // 検出機能が無効なら、デフォルトを返す
    return OS_MACOS;
#endif
  }

  // 明示的なモード設定
  return current_os_mode;
}

// 元のキーコードとOSの種類から、適切なキーコードに変換する関数
uint16_t get_os_specific_keycode(uint16_t keycode) {
  // 現在のOSを取得（グローバル変数への副作用を避けるため直接関数呼び出し）
  keyboard_os_t current_os = get_current_os();

  // 共通キー（CC_*）は直接対応するキーコードを返す
  switch (keycode) {
    case CC_LCTL:
      return KC_LCTL;
    case CC_LALT:
      return KC_LALT;
    case CC_LWIN:
      return KC_LGUI;
    case CC_RCTL:
      return KC_RCTL;
    case CC_RALT:
      return KC_RALT;
    case CC_RWIN:
      return KC_RGUI;
  }

  // OS固有のキーマッピング
  if (current_os == OS_MACOS) {
    // macOS用キーマッピング
    switch (keycode) {
      // 修飾キー
      case KC_LCTL:
        return KC_LCMD;  // Left Control -> Left Command
      case KC_LGUI:
        return KC_LOPT;  // Left GUI -> Left Option
      case KC_LALT:
        return KC_LCTL;  // Left Alt -> Left Control
      case KC_RCTL:
        return KC_RCMD;
      case KC_RGUI:
        return KC_ROPT;
      case KC_RALT:
        return KC_RCTL;

      // IME関連キー
      case HENKAN:
        return MC_HENKAN;  // 変換キー
      case MHENKAN:
        return MC_MHENKAN;  // 無変換キー

      default:
        return keycode;
    }
  } else {
    // Windows/Linuxなど他のOSのキーマッピング
    switch (keycode) {
      // IME関連キー（Windows固有のものがあれば追加）
      case HENKAN:
        return WC_HENKAN;  // 変換キー
      case MHENKAN:
        return WC_MHENKAN;  // 無変換キー

      default:
        return keycode;
    }
  }
}

// キーコードに対応するモディファイアビットを取
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

  uint8_t mods = get_mods();

  if (mods) {
    uint16_t mod_keycode = (mods << 8) | os_keycode;
    tap_code16(mod_keycode);
  } else {
    register_code(os_keycode);
    unregister_code(os_keycode);
  }
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


// OS固有の状態をリセット
void reset_os_specific_states(void) {
  // すべてのキー状態をリセット
  henkan_state.other_key_pressed = false;
  henkan_state.code_sent = false;
  henkan_state.repeat_active = false;

  mhenkan_state.other_key_pressed = false;
  mhenkan_state.code_sent = false;
  mhenkan_state.repeat_active = false;
}

// OSモードを設定する関数
void set_os_mode(keyboard_os_t os) {
  // 前に押されていたキーをすべて解除
  clean_all_mods_key();

  // キー状態をリセット
  reset_os_specific_states();

  // モードを変更して保存
  global_os_cache = os;
  current_os_mode = os;

  // EEPROMに保存（後で読み込めるように）
  eeconfig_update_os_mode(os);

  // デバッグ情報
  dprintf("OS Mode set to: %d\n", os);

// RGB LEDでフィードバック
#ifdef RGB_MATRIX_ENABLE
  switch (os) {
    case OS_MACOS:
      rgb_matrix_sethsv(HSV_CYAN);
      break;
    case OS_WINDOWS:
      rgb_matrix_sethsv(HSV_PURPLE);
      break;
    case OS_AUTO:
      rgb_matrix_sethsv(HSV_GREEN);
      break;
    default:
      break;
  }
#endif

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
