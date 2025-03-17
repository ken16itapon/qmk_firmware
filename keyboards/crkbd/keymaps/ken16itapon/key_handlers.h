#pragma once

#include QMK_KEYBOARD_H
#include "state_manager.h"  // key_state_t型を使うために必要

// 変数宣言（実際の定義はstate_manager.cで行う）
extern key_state_t lower_state;
extern key_state_t raise_state;
extern key_state_t c_bspc_state;
extern key_state_t c_spc_state;
extern key_state_t cs_tab_state;
extern key_state_t henkan_state;
extern key_state_t mhenkan_state;

// キー共通の処理関数
void handle_key_press_init(uint16_t keycode);

// キー処理関数
bool handle_tap_key(bool pressed, uint16_t pressed_time,
                    uint16_t *released_time, bool *code_sent, bool *rapid_press,
                    bool *repeat_active, bool *mod_key_pressed,
                    bool other_pressed, uint16_t keycode, uint16_t mod_key,
                    uint16_t record_time);

void handle_advanced_repeat(bool is_pressed, uint16_t pressed_time,
                            uint16_t released_time, bool *active_flag,
                            bool *code_sent, bool *rapid_press_flag,
                            bool other_key_pressed, uint16_t keycode,
                            uint16_t mod_key);

// 個別キーハンドラー関数
bool handle_lower_key(keyrecord_t *record);
bool handle_raise_key(keyrecord_t *record);
bool handle_c_spc_key(keyrecord_t *record);
bool handle_c_bspc_key(keyrecord_t *record);
bool handle_henkan_key(keyrecord_t *record);
bool handle_mhenkan_key(keyrecord_t *record);

// 修飾キー処理
bool handle_modifier_key(bool pressed, uint16_t keycode);
void apply_active_mods(uint16_t keycode);

// キー状態設定関数 - これらを追加
void other_key_pressed_except(key_state_t *target);
void set_other_key_pressed(void);

// ユーティリティ関数
void register_os_specific_key(uint16_t keycode);
void unregister_os_specific_key(uint16_t keycode);
void tap_os_specific_key(uint16_t keycode);
