#pragma once
#include QMK_KEYBOARD_H

// 最大修飾キー数
#ifndef MAX_MOD_KEYS
#define MAX_MOD_KEYS 4
#endif

// OS別キー設定構造体
typedef struct {
    uint16_t mod_keys[MAX_MOD_KEYS];  // 長押し時の修飾キー配列
    uint8_t mod_count;                 // 修飾キー数
    uint16_t tap_key;                  // タップ時のキーコード
} os_key_config_t;

// 特殊キー設定構造体（全OS分）
typedef struct {
    os_key_config_t macos;    // macOS用設定
    os_key_config_t windows;  // Windows用設定
    os_key_config_t linux;    // Linux用設定
} special_key_config_t;

// 特殊キー識別子
typedef enum {
    SK_HENKAN = 0,  // 変換キー
    SK_MHENKAN,     // 無変換キー
    SK_C_BSPC,      // Ctrl/Cmd + Backspace
    SK_CC_BSPC,     // Ctrl + Backspace（別パターン）
    SK_C_SPC,       // Ctrl/Cmd + Space
    SK_C_ENT,       // Ctrl/Cmd + Enter
    SK_CS_TAB,      // Ctrl/Cmd + Shift + Tab
    SK_LOWER,       // Lower レイヤー + タップ
    SK_RAISE,       // Raise レイヤー + タップ
    SK_COUNT        // 特殊キー総数
} special_key_id_t;

// グローバル設定テーブル（外部参照）
extern const special_key_config_t special_key_configs[SK_COUNT];

// 前方宣言
struct key_state;

// 関数プロトタイプ
const os_key_config_t* get_os_key_config(special_key_id_t key_id);
void register_mods_for_key_os(struct key_state* key_state);
void unregister_mods_for_key_os(struct key_state* key_state);