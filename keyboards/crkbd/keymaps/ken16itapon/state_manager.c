#include QMK_KEYBOARD_H
#include "state_manager.h"

#include "keymap.h"

// 状態管理変数の定義
key_state_t lower_state = {0};
key_state_t raise_state = {0};
key_state_t c_bspc_state = {0};
key_state_t c_spc_state = {0};
key_state_t cs_tab_state = {0};
key_state_t henkan_state = {0};
key_state_t mhenkan_state = {0};

// other_key_pressed変数の追加（この行が重要）
other_key_pressed_t other_key_pressed = {0};

uint16_t all_keys_released_time = 0;

// 指定したキー以外のフラグをセットする
void other_key_pressed_except(key_state_t *target) {
  if (target != &lower_state) lower_state.other_key_pressed = true;
  if (target != &raise_state) raise_state.other_key_pressed = true;
  if (target != &c_bspc_state) c_bspc_state.other_key_pressed = true;
  if (target != &c_spc_state) c_spc_state.other_key_pressed = true;
  if (target != &henkan_state) henkan_state.other_key_pressed = true;
  if (target != &mhenkan_state) mhenkan_state.other_key_pressed = true;
  if (target != &cs_tab_state) cs_tab_state.other_key_pressed = true;
}

// 指定したキー以外のフラグをセットする
void reset_pressed_except(key_state_t *target) {
  if (target != &lower_state) lower_state.pressed = false;
  if (target != &raise_state) raise_state.pressed = false;
  if (target != &c_bspc_state) c_bspc_state.pressed = false;
  if (target != &c_spc_state) c_spc_state.pressed = false;
  if (target != &henkan_state) henkan_state.pressed = false;
  if (target != &mhenkan_state) mhenkan_state.pressed = false;
  if (target != &cs_tab_state) cs_tab_state.pressed = false;
}

// キー押下フラグをリセット
void reset_other_key_pressed(void) {
  lower_state.other_key_pressed = false;
  raise_state.other_key_pressed = false;
  c_bspc_state.other_key_pressed = false;
  c_spc_state.other_key_pressed = false;
  henkan_state.other_key_pressed = false;
  mhenkan_state.other_key_pressed = false;
  cs_tab_state.other_key_pressed = false;
}

// すべてのキーが押されたフラグをセット
void set_other_key_pressed(void) {
  lower_state.other_key_pressed = true;
  raise_state.other_key_pressed = true;
  c_bspc_state.other_key_pressed = true;
  c_spc_state.other_key_pressed = true;
  henkan_state.other_key_pressed = true;
  mhenkan_state.other_key_pressed = true;
  cs_tab_state.other_key_pressed = true;
}

// すべてのキーのrapid_pressフラグをリセット
void reset_rapid_press(void) {
  lower_state.rapid_press = false;
  raise_state.rapid_press = false;
  c_bspc_state.rapid_press = false;
  c_spc_state.rapid_press = false;
}

// 指定したキー以外のrapid_pressをリセットする
void reset_rapid_press_except(key_state_t *target) {
  if (target != &lower_state) lower_state.rapid_press = false;
  if (target != &raise_state) raise_state.rapid_press = false;
  if (target != &c_bspc_state) c_bspc_state.rapid_press = false;
  if (target != &c_spc_state) c_spc_state.rapid_press = false;
}

// すべてのキーのcode_sentフラグをセット
void reset_code_sent(void) {
  lower_state.code_sent = true;
  raise_state.code_sent = true;
  c_bspc_state.code_sent = true;
  c_spc_state.code_sent = true;
}

// 指定したキー以外のcode_sentをリセットする
void reset_code_sent_except(key_state_t *target) {
  if (target != &lower_state) lower_state.code_sent = true;
  if (target != &raise_state) raise_state.code_sent = true;
  if (target != &c_bspc_state) c_bspc_state.code_sent = true;
  if (target != &c_spc_state) c_spc_state.code_sent = true;
}

// すべてのキーが離されているか確認（シンプル版）
bool all_keys_released(void) {
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
      if (matrix_is_on(row, col)) {
        return false;
      }
    }
  }
  return true;
}

// いずれかの修飾キーフラグがアクティブか確認
bool get_mods_active(void) {
  return lower_state.mods_active || raise_state.mods_active ||
         c_spc_state.mods_active || c_bspc_state.mods_active ||
         henkan_state.mods_active || mhenkan_state.mods_active;
}

// すべての修飾キーフラグをクリア
void clean_all_mods_key(void) {
  lower_state.mods_active = false;
  raise_state.mods_active = false;
  c_spc_state.mods_active = false;
  c_bspc_state.mods_active = false;
  henkan_state.mods_active = false;
  mhenkan_state.mods_active = false;

  // 物理的な修飾キーも解除
  unregister_mods(MOD_MASK_CTRL | MOD_MASK_SHIFT | MOD_MASK_ALT | MOD_MASK_GUI);
}

// キーコードがモディファイアかどうか
bool is_modifier(uint16_t keycode) {
  // 基本の修飾キーをチェック
  if (IS_MODIFIER_KEYCODE(keycode)) {
    return true;
  }

  // カスタム修飾キーもチェック
  switch (keycode) {
    case MHENKAN:
    case HENKAN:
    case OA_LCTL:
    case OA_LWIN:
    case OA_RALT:
      return true;
  }

  // どの条件にも一致しなければfalseを返す
  return false;
}
