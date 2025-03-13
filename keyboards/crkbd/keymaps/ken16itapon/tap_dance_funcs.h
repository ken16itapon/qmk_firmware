#pragma once

#include QMK_KEYBOARD_H

// タップダンスのインデックス定義
enum {
  TD_CSTAB = 0,
};

// タップダンス用マクロ定義
#define CS_TAB TD(TD_CSTAB)

// 関数宣言
void cstab_finished(tap_dance_state_t *state, void *user_data);
void cstab_reset(tap_dance_state_t *state, void *user_data);

// 配列を外部宣言
extern tap_dance_action_t tap_dance_actions[];
