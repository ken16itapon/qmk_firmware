#include QMK_KEYBOARD_H
#include "state_manager.h"
#include "special_keys_config.h"

#include "keymap.h"
#include "os_specific.h"

// 状態管理変数の定義
key_state_t lower_state = {0};
key_state_t raise_state = {0};
key_state_t c_bspc_state = {0};
key_state_t cc_bspc_state = {0};
// key_state_t c_spc_state = {0};
key_state_t c_ent_state = {0};
key_state_t cs_tab_state = {0};
key_state_t henkan_state = {0};
key_state_t mhenkan_state = {0};

uint16_t all_keys_released_time = 0;

// キー状態の初期化（改修版）
void initialize_key_states(void) {
  // 各キー状態に特殊キーIDを設定
  henkan_state.key_id = SK_HENKAN;
  mhenkan_state.key_id = SK_MHENKAN;
  c_bspc_state.key_id = SK_C_BSPC;
  cc_bspc_state.key_id = SK_CC_BSPC;
  // c_spc_state.key_id = SK_C_SPC;
  c_ent_state.key_id = SK_C_ENT;
  cs_tab_state.key_id = SK_CS_TAB;
  lower_state.key_id = SK_LOWER;
  raise_state.key_id = SK_RAISE;
  
  // 互換性のため、現在のOS設定を初期値として設定
  const os_key_config_t* config;
  
  // HENKANキー
  config = get_os_key_config(SK_HENKAN);
  if (config) {
    henkan_state.keycode = config->tap_key;
    memcpy(henkan_state.mod_keys, config->mod_keys, sizeof(uint16_t) * config->mod_count);
    henkan_state.mod_count = config->mod_count;
  }
  
  // MHENKANキー
  config = get_os_key_config(SK_MHENKAN);
  if (config) {
    mhenkan_state.keycode = config->tap_key;
    memcpy(mhenkan_state.mod_keys, config->mod_keys, sizeof(uint16_t) * config->mod_count);
    mhenkan_state.mod_count = config->mod_count;
  }
  
  // その他のキーも同様に初期化（簡略化のため省略）
}

// キーに関連付けられた全ての修飾キーを登録
void register_mods_for_key(key_state_t *key_state) {
  // OS別設定から修飾キーを取得して登録
  const os_key_config_t* config = get_os_key_config(key_state->key_id);
  if (config && config->mod_count > 0) {
    for (uint8_t i = 0; i < config->mod_count; i++) {
      // 修飾キーは既に正しいOS用のキーコードが設定されているため、直接登録
      register_code(config->mod_keys[i]);
    }
  }
}

// キーに関連付けられた全ての修飾キーを解除
void unregister_mods_for_key(key_state_t *key_state) {
  // OS別設定から修飾キーを取得して解除
  const os_key_config_t* config = get_os_key_config(key_state->key_id);
  if (config && config->mod_count > 0) {
    for (uint8_t i = 0; i < config->mod_count; i++) {
      // 修飾キーは既に正しいOS用のキーコードが設定されているため、直接解除
      unregister_code(config->mod_keys[i]);
    }
  }
}

// 指定したキー以外のフラグをセットする
void other_key_pressed_except(key_state_t *target) {
  if (target != &lower_state) lower_state.other_key_pressed = true;
  if (target != &raise_state) raise_state.other_key_pressed = true;
  if (target != &c_bspc_state) c_bspc_state.other_key_pressed = true;
  if (target != &cc_bspc_state) cc_bspc_state.other_key_pressed = true;
  // if (target != &c_spc_state) c_spc_state.other_key_pressed = true;
  if (target != &c_ent_state) c_ent_state.other_key_pressed = true;
  if (target != &henkan_state) henkan_state.other_key_pressed = true;
  if (target != &mhenkan_state) mhenkan_state.other_key_pressed = true;
  if (target != &cs_tab_state) cs_tab_state.other_key_pressed = true;
}

// 全てのキーのother_key_pressedフラグをtrueにする
void set_other_key_pressed(void) {
  lower_state.other_key_pressed = true;
  raise_state.other_key_pressed = true;
  c_bspc_state.other_key_pressed = true;
  cc_bspc_state.other_key_pressed = true;
  // c_spc_state.other_key_pressed = true;
  c_ent_state.other_key_pressed = true;
  henkan_state.other_key_pressed = true;
  mhenkan_state.other_key_pressed = true;
  cs_tab_state.other_key_pressed = true;
}

// 全てのキーのis_pressedフラグをfalse`にする
void reset_key_pressed(void) {
  lower_state.is_pressed = false;
  raise_state.is_pressed = false;
  c_bspc_state.is_pressed = false;
  cc_bspc_state.is_pressed = false;
  // c_spc_state.is_pressed = false;
  c_ent_state.is_pressed = false;
  henkan_state.is_pressed = false;
  mhenkan_state.is_pressed = false;
  cs_tab_state.is_pressed = false;
}

// 指定したキー以外のis_pressedフラグをfalseにする
void reset_pressed_except(key_state_t *target) {
  if (target != &lower_state) lower_state.is_pressed = false;
  if (target != &raise_state) raise_state.is_pressed = false;
  if (target != &c_bspc_state) c_bspc_state.is_pressed = false;
  if (target != &cc_bspc_state) cc_bspc_state.is_pressed = false;
  // if (target != &c_spc_state) c_spc_state.is_pressed = false;
  if (target != &c_ent_state) c_ent_state.is_pressed = false;
  if (target != &henkan_state) henkan_state.is_pressed = false;
  if (target != &mhenkan_state) mhenkan_state.is_pressed = false;
  if (target != &cs_tab_state) cs_tab_state.is_pressed = false;
}

// 全てのキーのrapid_pressフラグをfalseにする
void reset_rapid_press(void) {
  lower_state.rapid_press = false;
  raise_state.rapid_press = false;
  c_bspc_state.rapid_press = false;
  cc_bspc_state.rapid_press = false;
  // c_spc_state.rapid_press = false;
  c_ent_state.rapid_press = false;
  henkan_state.rapid_press = false;
  mhenkan_state.rapid_press = false;
  cs_tab_state.rapid_press = false;
}

// 指定したキー以外のrapid_pressフラグをfalseにする
void reset_rapid_press_except(key_state_t *target) {
  if (target != &lower_state) lower_state.rapid_press = false;
  if (target != &raise_state) raise_state.rapid_press = false;
  if (target != &c_bspc_state) c_bspc_state.rapid_press = false;
  if (target != &cc_bspc_state) cc_bspc_state.rapid_press = false;
  // if (target != &c_spc_state) c_spc_state.rapid_press = false;
  if (target != &c_ent_state) c_ent_state.rapid_press = false;
  if (target != &henkan_state) henkan_state.rapid_press = false;
  if (target != &mhenkan_state) mhenkan_state.rapid_press = false;
  if (target != &cs_tab_state) cs_tab_state.rapid_press = false;
}

// 全てのキーのcode_sentフラグをfalseにする
void reset_code_sent(void) {
  lower_state.code_sent = false;
  raise_state.code_sent = false;
  c_bspc_state.code_sent = false;
  cc_bspc_state.code_sent = false;
  // c_spc_state.code_sent = false;
  c_ent_state.code_sent = false;
  henkan_state.code_sent = false;
  mhenkan_state.code_sent = false;
  cs_tab_state.code_sent = false;
}

// 指定したキー以外のcode_sentフラグをfalseにする
void reset_code_sent_except(key_state_t *target) {
  if (target != &lower_state) lower_state.code_sent = false;
  if (target != &raise_state) raise_state.code_sent = false;
  if (target != &c_bspc_state) c_bspc_state.code_sent = false;
  if (target != &cc_bspc_state) cc_bspc_state.code_sent = false;
  // if (target != &c_spc_state) c_spc_state.code_sent = false;
  if (target != &c_ent_state) c_ent_state.code_sent = false;
  if (target != &henkan_state) henkan_state.code_sent = false;
  if (target != &mhenkan_state) mhenkan_state.code_sent = false;
  if (target != &cs_tab_state) cs_tab_state.code_sent = false;
}

// 全てのキーのother_key_pressedフラグをfalseにする
void reset_other_key_pressed(void) {
  lower_state.other_key_pressed = false;
  raise_state.other_key_pressed = false;
  c_bspc_state.other_key_pressed = false;
  cc_bspc_state.other_key_pressed = false;
  // c_spc_state.other_key_pressed = false;
  c_ent_state.other_key_pressed = false;
  henkan_state.other_key_pressed = false;
  mhenkan_state.other_key_pressed = false;
  cs_tab_state.other_key_pressed = false;
}

// いずれかのキーがis_pressedかどうかを返す
bool get_mods_active(void) {
  return lower_state.is_pressed || raise_state.is_pressed ||
         /* c_spc_state.is_pressed || */ c_bspc_state.is_pressed ||
         c_ent_state.is_pressed || cc_bspc_state.is_pressed ||
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
  unregister_mods_for_key(&c_bspc_state);
  unregister_mods_for_key(&cc_bspc_state);
  // unregister_mods_for_key(&c_spc_state);
  unregister_mods_for_key(&c_ent_state);
  unregister_mods_for_key(&cs_tab_state);
}

// キーがモディファイアかどうかを返す
bool is_modifier(uint16_t keycode) {
  return IS_MODIFIER_KEYCODE(keycode);
}
