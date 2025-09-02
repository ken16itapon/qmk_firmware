#pragma once

#include QMK_KEYBOARD_H

// 最大修飾キー数
#define MAX_MOD_KEYS 4

// key_state_t構造体の定義
typedef struct key_state {
  bool is_pressed;  // pressed と mods_active を統合
  uint16_t pressed_time;
  uint16_t released_time;
  bool code_sent;
  bool rapid_press;
  bool repeat_active;
  bool other_key_pressed;  // 他のキーが押されたフラグ

  // キー関連情報
  uint16_t keycode;                 // このキーのキーコード
  uint16_t mod_keys[MAX_MOD_KEYS];  // このキーに対応する修飾キー（配列）
  uint8_t mod_count;                // 実際に使用する修飾キーの数
} key_state_t;

// 変数宣言
extern uint16_t all_keys_released_time;
extern key_state_t lower_state;
extern key_state_t raise_state;
extern key_state_t cc_bspc_state;
extern key_state_t c_ent_state;
extern key_state_t s_spc_state;
extern key_state_t cs_tab_state;
extern key_state_t henkan_state;
extern key_state_t mhenkan_state;

// 関数宣言
void initialize_key_states(void);
void set_other_key_pressed(void);
void reset_key_pressed(void);
void other_key_pressed_except(key_state_t *target);
void reset_rapid_press(void);
void reset_rapid_press_except(key_state_t *target);
void reset_code_sent(void);
void reset_code_sent_except(key_state_t *target);
void reset_pressed_except(key_state_t *target);
void reset_other_key_pressed(void);
bool all_keys_released(void);
bool get_mods_active(void);
void clean_all_mods_key(void);
bool is_modifier(uint16_t keycode);
void register_mods_for_key(key_state_t *key_state);
void unregister_mods_for_key(key_state_t *key_state);
