#pragma once

#include QMK_KEYBOARD_H

// key_state_t構造体の定義
typedef struct {
  bool pressed;
  uint16_t pressed_time;
  uint16_t released_time;
  bool code_sent;
  bool rapid_press;
  bool repeat_active;
  bool mods_active;
  bool other_key_pressed;  // 他のキーが押されたフラグ
} key_state_t;

// other_key_pressed_t構造体定義
typedef struct {
  bool lower;
  bool raise;
  bool any;  // 何らかのキーが押されているかのフラグ
} other_key_pressed_t;

// 変数宣言
extern other_key_pressed_t other_key_pressed;
extern uint16_t all_keys_released_time;
extern key_state_t lower_state;
extern key_state_t raise_state;
extern key_state_t c_bspc_state;
extern key_state_t c_spc_state;
extern key_state_t cs_tab_state;
extern key_state_t henkan_state;
extern key_state_t mhenkan_state;

// 関数宣言
void set_other_key_pressed(void);
void reset_key_pressed(void);
void other_key_pressed_except(key_state_t *target);
void reset_rapid_press(void);
void reset_rapid_press_except(key_state_t *target);
void reset_code_sent(void);
void reset_code_sent_except(key_state_t *target);
void reset_pressed_except(key_state_t *target);

// 以下の関数宣言を追加
void reset_other_key_pressed(void);
bool all_keys_released(void);
bool get_mods_active(void);
void clean_all_mods_key(void);

// キーコードがモディファイアかどうか
bool is_modifier(uint16_t keycode);
