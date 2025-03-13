#include QMK_KEYBOARD_H
#include "tap_dance_funcs.h"

// 状態管理用の静的変数
static bool mods_active = false;

// タップダンス終了時の処理
void cstab_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      register_code(KC_TAB);
    } else {
      mods_active = true;
      register_code(KC_LCTL);
      register_code(KC_LSFT);
    }
  } else if (state->count == 2) {
    register_code(KC_ESC);
  }
}

// タップダンスリセット時の処理
void cstab_reset(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      unregister_code(KC_TAB);
    }
  } else if (state->count == 2) {
    unregister_code(KC_ESC);
  }

  if (mods_active) {
    unregister_code(KC_LCTL);
    unregister_code(KC_LSFT);
    mods_active = false;
  }
}

// タップダンス配列の定義 - 重要: tap_dance_actions[] の形式を守る
tap_dance_action_t tap_dance_actions[] = {
    // 基本形式: ACTION_TAP_DANCE_FN_ADVANCED を使用
    [TD_CSTAB] =
        ACTION_TAP_DANCE_FN_ADVANCED(NULL, cstab_finished, cstab_reset)};
