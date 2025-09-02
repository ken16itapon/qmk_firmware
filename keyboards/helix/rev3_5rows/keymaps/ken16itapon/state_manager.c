#include QMK_KEYBOARD_H
#include "state_manager.h"

#include "keymap.h"
#include "os_specific.h"

// 状態管理変数の定義
key_state_t lower_state = {0};
key_state_t raise_state = {0};
key_state_t cc_bspc_state = {0};
key_state_t s_bspc_state = {0};
key_state_t c_ent_state = {0};
key_state_t cs_tab_state = {0};
key_state_t henkan_state = {0};
key_state_t mhenkan_state = {0};

uint16_t all_keys_released_time = 0;

// キー状態の初期化
void initialize_key_states(void) {
  // HENKANキー（KANAとして動作、macOS: かな切替）
  henkan_state.keycode = KC_LNG1;  // macOS用のかなキー
  henkan_state.mod_keys[0] = KC_RSFT;
  henkan_state.mod_count = 1;

  // MHENKANキー（EISUとして動作、macOS: 英数切替）
  mhenkan_state.keycode = KC_LNG2;  // macOS用の英数キー
  mhenkan_state.mod_keys[0] = KC_LALT;
  mhenkan_state.mod_count = 1;

  // CC_BSPCキー
  cc_bspc_state.keycode = KC_BSPC;
  cc_bspc_state.mod_keys[0] = KC_LCTL;
  cc_bspc_state.mod_count = 1;

  // S_BSPCキー
  s_bspc_state.keycode = KC_BSPC;
  s_bspc_state.mod_keys[0] = KC_LSFT;
  s_bspc_state.mod_count = 1;

  // C_ENTキー
  c_ent_state.keycode = KC_ENT;
  c_ent_state.mod_keys[0] = KC_LCTL;
  c_ent_state.mod_count = 1;

  // LOWERキー
  lower_state.keycode = KC_BSPC;
  lower_state.mod_count = 0;  // 修飾キーなし

  // RAISEキー
  raise_state.keycode = KC_SPC;
  raise_state.mod_count = 0;  // 修飾キーなし

  // CS_TABキー
  cs_tab_state.keycode = KC_TAB;
  cs_tab_state.mod_keys[0] = KC_LGUI;
  cs_tab_state.mod_keys[1] = KC_LSFT;
  cs_tab_state.mod_count = 2;
}

// キーに関連付けられた全ての修飾キーを登録
void register_mods_for_key(key_state_t *key_state) {
  for (uint8_t i = 0; i < key_state->mod_count; i++) {
    register_code(key_state->mod_keys[i]);
  }
}

// キーに関連付けられた全ての修飾キーを解除
void unregister_mods_for_key(key_state_t *key_state) {
  for (uint8_t i = 0; i < key_state->mod_count; i++) {
    unregister_code(key_state->mod_keys[i]);
  }
}

// 指定したキー以外のフラグをセットする
void other_key_pressed_except(key_state_t *target) {
  if (target != &lower_state) lower_state.other_key_pressed = true;
  if (target != &raise_state) raise_state.other_key_pressed = true;
  if (target != &cc_bspc_state) cc_bspc_state.other_key_pressed = true;
  if (target != &s_bspc_state) s_bspc_state.other_key_pressed = true;
  if (target != &henkan_state) henkan_state.other_key_pressed = true;
  if (target != &mhenkan_state) mhenkan_state.other_key_pressed = true;
  if (target != &cs_tab_state) cs_tab_state.other_key_pressed = true;
}

// 全てのキーのother_key_pressedフラグをtrueにする
void set_other_key_pressed(void) {
  lower_state.other_key_pressed = true;
  raise_state.other_key_pressed = true;
  cc_bspc_state.other_key_pressed = true;
  s_bspc_state.other_key_pressed = true;
  henkan_state.other_key_pressed = true;
  mhenkan_state.other_key_pressed = true;
  cs_tab_state.other_key_pressed = true;
}

// 全てのキーのis_pressedフラグをfalseにする
void reset_key_pressed(void) {
  lower_state.is_pressed = false;
  raise_state.is_pressed = false;
  cc_bspc_state.is_pressed = false;
  s_bspc_state.is_pressed = false;
  henkan_state.is_pressed = false;
  mhenkan_state.is_pressed = false;
  cs_tab_state.is_pressed = false;
}

// 指定したキー以外のis_pressedフラグをfalseにする
void reset_pressed_except(key_state_t *target) {
  if (target != &lower_state) lower_state.is_pressed = false;
  if (target != &raise_state) raise_state.is_pressed = false;
  if (target != &cc_bspc_state) cc_bspc_state.is_pressed = false;
  if (target != &s_bspc_state) s_bspc_state.is_pressed = false;
  if (target != &henkan_state) henkan_state.is_pressed = false;
  if (target != &mhenkan_state) mhenkan_state.is_pressed = false;
  if (target != &cs_tab_state) cs_tab_state.is_pressed = false;
}

// 全てのキーのrapid_pressフラグをfalseにする
void reset_rapid_press(void) {
  lower_state.rapid_press = false;
  raise_state.rapid_press = false;
  cc_bspc_state.rapid_press = false;
  s_bspc_state.rapid_press = false;
  henkan_state.rapid_press = false;
  mhenkan_state.rapid_press = false;
  cs_tab_state.rapid_press = false;
}

// 指定したキー以外のrapid_pressフラグをfalseにする
void reset_rapid_press_except(key_state_t *target) {
  if (target != &lower_state) lower_state.rapid_press = false;
  if (target != &raise_state) raise_state.rapid_press = false;
  if (target != &cc_bspc_state) cc_bspc_state.rapid_press = false;
  if (target != &s_bspc_state) s_bspc_state.rapid_press = false;
  if (target != &henkan_state) henkan_state.rapid_press = false;
  if (target != &mhenkan_state) mhenkan_state.rapid_press = false;
  if (target != &cs_tab_state) cs_tab_state.rapid_press = false;
}

// 全てのキーのcode_sentフラグをfalseにする
void reset_code_sent(void) {
  lower_state.code_sent = false;
  raise_state.code_sent = false;
  cc_bspc_state.code_sent = false;
  s_bspc_state.code_sent = false;
  henkan_state.code_sent = false;
  mhenkan_state.code_sent = false;
  cs_tab_state.code_sent = false;
}

// 指定したキー以外のcode_sentフラグをfalseにする
void reset_code_sent_except(key_state_t *target) {
  if (target != &lower_state) lower_state.code_sent = false;
  if (target != &raise_state) raise_state.code_sent = false;
  if (target != &cc_bspc_state) cc_bspc_state.code_sent = false;
  if (target != &s_bspc_state) s_bspc_state.code_sent = false;
  if (target != &henkan_state) henkan_state.code_sent = false;
  if (target != &mhenkan_state) mhenkan_state.code_sent = false;
  if (target != &cs_tab_state) cs_tab_state.code_sent = false;
}

// 全てのキーのother_key_pressedフラグをfalseにする
void reset_other_key_pressed(void) {
  lower_state.other_key_pressed = false;
  raise_state.other_key_pressed = false;
  cc_bspc_state.other_key_pressed = false;
  s_bspc_state.other_key_pressed = false;
  henkan_state.other_key_pressed = false;
  mhenkan_state.other_key_pressed = false;
  cs_tab_state.other_key_pressed = false;
}

// いずれかのキーがis_pressedかどうかを返す
bool get_mods_active(void) {
  return lower_state.is_pressed || raise_state.is_pressed ||
         s_bspc_state.is_pressed || cc_bspc_state.is_pressed ||
         henkan_state.is_pressed || mhenkan_state.is_pressed ||
         cs_tab_state.is_pressed;
}

/**
 * すべてのキー（修飾キー含む）が解放されているかどうかを確認
 * @return 全キーが解放されていればtrue
 */
bool all_keys_released(void) {
  // キーボードマトリクス全体をスキャン
  for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
    if (matrix_get_row(r) > 0) {
      return false;  // いずれかのキーがオン
    }
  }
  return true;  // すべてのキーがオフ
}

// 全ての修飾キーを解除する
void clean_all_mods_key(void) {
  // 各キーの修飾キーを解除
  unregister_mods_for_key(&henkan_state);
  unregister_mods_for_key(&mhenkan_state);
  unregister_mods_for_key(&cc_bspc_state);
  unregister_mods_for_key(&s_bspc_state);
  unregister_mods_for_key(&cs_tab_state);
}

// キーがモディファイアかどうかを返す
bool is_modifier(uint16_t keycode) {
  return IS_MODIFIER_KEYCODE(keycode);
}
