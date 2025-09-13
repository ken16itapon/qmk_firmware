#pragma once
#include QMK_KEYBOARD_H
#include <stdbool.h>

// OS種別の定義
typedef enum {
    OS_TYPE_AUTO = 0,      // 自動検出
    OS_TYPE_MACOS,         // macOS
    OS_TYPE_WINDOWS,       // Windows  
    OS_TYPE_LINUX,         // Linux
    OS_TYPE_IOS,           // iOS/iPadOS
    OS_TYPE_ANDROID,       // Android
    OS_TYPE_CHROMEOS,      // ChromeOS
    OS_TYPE_UNKNOWN        // 不明
} os_type_t;

// macOSのバージョン
typedef enum {
    MACOS_UNKNOWN = 0,
    MACOS_MONTEREY,        // 12.x
    MACOS_VENTURA,         // 13.x
    MACOS_SONOMA,          // 14.x
    MACOS_SEQUOIA          // 15.x
} macos_version_t;

// Windowsのバージョン
typedef enum {
    WINDOWS_UNKNOWN = 0,
    WINDOWS_10,
    WINDOWS_11
} windows_version_t;

// IMEの種類
typedef enum {
    IME_NONE = 0,
    IME_MACOS_JIS,         // macOS日本語入力
    IME_MACOS_US,          // macOS USキーボード
    IME_WINDOWS_MS,        // Windows MS-IME
    IME_WINDOWS_GOOGLE,    // Windows Google日本語入力
    IME_WINDOWS_ATOK,      // Windows ATOK
    IME_LINUX_FCITX,       // Linux Fcitx
    IME_LINUX_IBUS,        // Linux IBus
    IME_LINUX_UIM          // Linux uim
} ime_type_t;

// キーボードレイアウト
typedef enum {
    LAYOUT_US = 0,         // USレイアウト
    LAYOUT_JIS,            // JISレイアウト
    LAYOUT_UK,             // UKレイアウト
    LAYOUT_DE,             // ドイツ語レイアウト
    LAYOUT_FR              // フランス語レイアウト
} keyboard_layout_t;

// 修飾キーマッピング設定
typedef struct {
    uint16_t ctrl_key;     // Ctrlキーの実際のキーコード
    uint16_t cmd_key;      // Cmd/Winキーの実際のキーコード
    uint16_t alt_key;      // Alt/Optionキーの実際のキーコード
    uint16_t fn_key;       // Fnキーの実際のキーコード
    bool swap_cmd_ctrl;    // Cmd/Ctrlを入れ替えるか
    bool swap_alt_cmd;     // Alt/Cmdを入れ替えるか
} modifier_mapping_t;

// IME制御設定
typedef struct {
    uint16_t ime_on_key;   // IMEオンのキーコード
    uint16_t ime_off_key;  // IMEオフのキーコード
    uint16_t ime_toggle_key; // IME切り替えキー
    uint16_t ime_henkan_key;   // 変換キー
    uint16_t ime_muhenkan_key; // 無変換キー
    uint16_t ime_kana_key;     // かなキー
    uint16_t ime_eisu_key;     // 英数キー
    bool use_ime_state_led;    // IME状態をLEDで表示
    bool auto_ime_off_on_layer; // レイヤー切り替え時に自動IMEオフ
} ime_control_t;

// ショートカット設定
typedef struct {
    uint16_t copy_keys[3];     // コピー
    uint16_t paste_keys[3];    // ペースト
    uint16_t cut_keys[3];      // カット
    uint16_t undo_keys[3];     // アンドゥ
    uint16_t redo_keys[3];     // リドゥ
    uint16_t find_keys[3];     // 検索
    uint16_t replace_keys[3];  // 置換
    uint16_t select_all_keys[3]; // 全選択
} shortcut_mapping_t;

// アプリケーション固有設定
typedef struct {
    const char* app_name;      // アプリケーション名
    modifier_mapping_t modifiers; // 修飾キー設定
    shortcut_mapping_t shortcuts; // ショートカット設定
    bool active;               // この設定が有効か
} app_specific_config_t;

// OS管理構造体
typedef struct {
    // 基本情報
    os_type_t current_os;
    os_type_t detected_os;
    bool auto_detect_enabled;
    
    // 詳細バージョン情報
    union {
        macos_version_t macos_version;
        windows_version_t windows_version;
        uint8_t linux_distro;  // Linux ディストリビューション識別子
    } version_info;
    
    // キーボード設定
    keyboard_layout_t keyboard_layout;
    
    // 修飾キーマッピング
    modifier_mapping_t modifiers;
    
    // IME制御
    ime_type_t ime_type;
    ime_control_t ime_control;
    bool ime_active;
    
    // ショートカット
    shortcut_mapping_t shortcuts;
    
    // アプリケーション固有設定（最大5個）
    app_specific_config_t app_configs[5];
    uint8_t active_app_config;
    
    // 状態フラグ
    bool initialized;
    bool settings_locked;     // 設定変更をロック
    uint32_t last_detection_time;
    
    // デバッグ情報
    bool debug_mode;
    uint8_t detection_confidence; // 検出精度（0-100%）
} os_manager_t;

// キーコード変換テーブル
typedef struct {
    uint16_t generic_key;     // 汎用キーコード
    uint16_t macos_key;       // macOS用キーコード
    uint16_t windows_key;     // Windows用キーコード
    uint16_t linux_key;       // Linux用キーコード
} keycode_translation_t;

// グローバルインスタンス
extern os_manager_t g_os_manager;

// 初期化・管理関数
void os_manager_init(void);
void os_manager_reset(void);
bool os_manager_load_from_eeprom(void);
bool os_manager_save_to_eeprom(void);

// OS検出・設定
os_type_t os_manager_detect_os(void);
void os_manager_set_os(os_type_t os);
void os_manager_set_auto_detect(bool enable);
os_type_t os_manager_get_current_os(void);

// バージョン検出
void os_manager_detect_version(void);
const char* os_manager_get_version_string(void);

// キーボードレイアウト
void os_manager_set_keyboard_layout(keyboard_layout_t layout);
keyboard_layout_t os_manager_get_keyboard_layout(void);

// 修飾キー管理
void os_manager_set_modifier_mapping(const modifier_mapping_t* mapping);
uint16_t os_manager_translate_modifier(uint16_t keycode);
void os_manager_apply_modifier_swap(void);

// IME制御
void os_manager_set_ime_type(ime_type_t ime);
void os_manager_configure_ime(const ime_control_t* config);
bool os_manager_ime_on(void);
bool os_manager_ime_off(void);
bool os_manager_ime_toggle(void);
bool os_manager_is_ime_active(void);

// キーコード変換
uint16_t os_manager_translate_keycode(uint16_t keycode);
uint16_t os_manager_get_os_specific_key(uint16_t generic_key);
void os_manager_register_key(uint16_t keycode);
void os_manager_unregister_key(uint16_t keycode);
void os_manager_tap_key(uint16_t keycode);

// ショートカット処理
bool os_manager_send_shortcut(uint8_t shortcut_id);
void os_manager_configure_shortcuts(const shortcut_mapping_t* shortcuts);

// アプリケーション固有設定
bool os_manager_add_app_config(const app_specific_config_t* config);
bool os_manager_activate_app_config(uint8_t index);
bool os_manager_deactivate_app_config(void);

// イベントハンドラ
bool os_manager_process_record(uint16_t keycode, keyrecord_t* record);
void os_manager_layer_change(layer_state_t layer_state);
void os_manager_matrix_scan(void);

// デバッグ・ユーティリティ
void os_manager_enable_debug(bool enable);
void os_manager_print_status(void);
const char* os_manager_get_os_name(os_type_t os);
const char* os_manager_get_ime_name(ime_type_t ime);

// LED表示
#ifdef RGB_MATRIX_ENABLE
void os_manager_update_led_indicator(void);
void os_manager_show_os_indicator(void);
#endif

// 互換性マクロ（既存コードとの互換性維持）
#define get_current_os() os_manager_get_current_os()
#define set_os_mode(os) os_manager_set_os(os)
#define register_os_specific_key(key) os_manager_register_key(key)
#define unregister_os_specific_key(key) os_manager_unregister_key(key)
#define tap_os_specific_key(key) os_manager_tap_key(key)