#include "state_manager.h"
#include QMK_KEYBOARD_H  // 最初に基本QMKヘッダー
#include "keymap.h"      // カスタムキーコード、レイヤー定義
// その他の依存関係
#include "key_handlers.h"
// naginata.hはkeymap.hで条件付きインクルードされる

// タップと長押しの両方をサポートしたリピート処理
void handle_advanced_repeat(key_state_t *state) {
  // 既にアクティブな場合、処理しない
  if (state->repeat_active) {
    return;
  }

  // リピート開始条件判定
  if (!state->is_pressed || state->other_key_pressed || !state->code_sent ||
      !state->rapid_press || layer_state_is(_ADJUST) ||
      timer_elapsed(state->pressed_time) < TAPPING_TERM) {
    return;
  }

  // リピート開始条件を満たした - 修飾キーを解除してから通常キーを登録
  if (state->mod_count > 0) {
    unregister_mods_for_key(state);
  }

  state->code_sent = false;
  state->repeat_active = true;
  register_os_specific_key(state->keycode);
}

// キー押下時の初期化処理
void handle_key_press_init(uint16_t keycode) {
  if (keycode != HENKAN && henkan_state.is_pressed) {
    henkan_state.other_key_pressed = true;
  }
  if (keycode != MHENKAN && mhenkan_state.is_pressed) {
    mhenkan_state.other_key_pressed = true;
  }
  if (keycode != S_BSPC && s_bspc_state.is_pressed) {
    s_bspc_state.other_key_pressed = true;
  }
  if (keycode != CC_BSPC && cc_bspc_state.is_pressed) {
    cc_bspc_state.other_key_pressed = true;
  }
  if (keycode != C_ENT && c_ent_state.is_pressed) {
    c_ent_state.other_key_pressed = true;
  }
  if (keycode != LOWER && lower_state.is_pressed) {
    lower_state.other_key_pressed = true;
  }
  if (keycode != RAISE && raise_state.is_pressed) {
    raise_state.other_key_pressed = true;
  }
}

// 単打判定と対応キー送信処理 - 構造体へのポインタを使用
bool handle_tap_key(key_state_t *state, uint16_t record_time) {
  // 離した時の単打判定
  if (timer_elapsed(state->pressed_time) < TAPPING_TERM) {
    apply_active_mods();
    if (state->mod_count > 0) {
      unregister_mods_for_key(state);
    }

    // タップキーを送信
    tap_code(state->keycode);
    state->code_sent = true;
    state->released_time = record_time;
  }

  if (state->repeat_active) {
    unregister_code(state->keycode);
    state->repeat_active = false;
    state->code_sent = false;
  }

  // 状態をリセット
  state->is_pressed = false;
  state->released_time = record_time;

  return false;
}

// 修飾キー処理
bool handle_modifier_key(bool pressed, uint16_t keycode) {
  if (pressed) {
    register_code(keycode);
  } else {
    unregister_code(keycode);
  }
  return false;
}

// キーに対して有効な修飾キーを適用する
void apply_active_mods(void) {
  // 修飾キーを持つすべてのキー状態をチェック
  if (henkan_state.is_pressed) {
    register_mods_for_key(&henkan_state);
  }
  if (mhenkan_state.is_pressed) {
    register_mods_for_key(&mhenkan_state);
  }
  if (cc_bspc_state.is_pressed) {
    register_mods_for_key(&cc_bspc_state);
  }
  if (s_bspc_state.is_pressed) {
    register_mods_for_key(&s_bspc_state);
  }
  if (c_ent_state.is_pressed) {
    register_mods_for_key(&c_ent_state);
  }
  if (cs_tab_state.is_pressed) {
    register_mods_for_key(&cs_tab_state);
  }

  // 必要に応じてここで修飾キーをクリア
}

// LOWERキー処理
bool handle_lower_key(keyrecord_t *record) {
  if (record->event.pressed) {
    if (timer_elapsed(lower_state.released_time) < TAPPING_TERM) {
      lower_state.rapid_press = true;
    } else {
      lower_state.rapid_press = false;
    }

    lower_state.is_pressed = true;
    lower_state.pressed_time = record->event.time;

    layer_on(_LOWER);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
    if (layer_state_is(_ADJUST)) {
      lower_state.rapid_press = false;
    }
    return false;
  }

  // キーを離した時の処理
  lower_state.is_pressed = false;
  layer_off(_LOWER);
  update_tri_layer(_LOWER, _RAISE, _ADJUST);

  bool result = handle_tap_key(&lower_state, record->event.time);

  return result;  // 明示的にreturnを追加
}

// RAISEキー処理
bool handle_raise_key(keyrecord_t *record) {
  if (record->event.pressed) {
    if (timer_elapsed(raise_state.released_time) < TAPPING_TERM) {
      raise_state.rapid_press = true;
    } else {
      raise_state.rapid_press = false;
    }

    raise_state.is_pressed = true;
    raise_state.pressed_time = record->event.time;

    layer_on(_RAISE);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
    if (layer_state_is(_ADJUST)) {
      raise_state.code_sent = true;
      raise_state.rapid_press = false;
    }
    return false;
  }

  // キーを離した時の処理
  raise_state.is_pressed = false;
  layer_off(_RAISE);
  update_tri_layer(_LOWER, _RAISE, _ADJUST);

  bool result = handle_tap_key(&raise_state, record->event.time);

  return result;  // 明示的にreturnを追加
}

bool handle_henkan_key(keyrecord_t *record) {
  if (record->event.pressed) {
    henkan_state.is_pressed = true;
    henkan_state.pressed_time = record->event.time;

    // 修飾キーを登録
    register_mods_for_key(&henkan_state);

    // 他のキーが押されていることを記録
    other_key_pressed_except(&henkan_state);

    return false;
  } else {
    // キー離し時の処理 - 簡略化された呼び出し
    henkan_state.is_pressed = false;
    unregister_mods_for_key(&henkan_state);
    bool result = handle_tap_key(&henkan_state, record->event.time);

    // タップ時の追加処理（薙刀式オン）
    if (henkan_state.code_sent) {
      naginata_on();
    }

    return result;
  }
}

bool handle_mhenkan_key(keyrecord_t *record) {
  if (record->event.pressed) {
    mhenkan_state.is_pressed = true;  // is_pressedのみ使用
    mhenkan_state.pressed_time = record->event.time;

    // 修飾キー関数を使用
    register_mods_for_key(&mhenkan_state);

    // 他のキーが押されていることを記録
    other_key_pressed_except(&mhenkan_state);

    return false;
  } else {
    // キー離し時の処理
    bool result = handle_tap_key(&mhenkan_state, record->event.time);

    // 状態リセット
    mhenkan_state.is_pressed = false;
    unregister_mods_for_key(&mhenkan_state);  // 修飾キー関数を使用

    // タップ時の追加処理（薙刀式オフ）
    if (mhenkan_state.code_sent) {
      naginata_off();
    }

    return result;
  }
}

bool handle_cc_bspc_key(keyrecord_t *record) {
  if (record->event.pressed) {
    cc_bspc_state.is_pressed = true;
    cc_bspc_state.pressed_time = record->event.time;

    register_mods_for_key(&cc_bspc_state);

    if (timer_elapsed(cc_bspc_state.released_time) < TAPPING_TERM) {
      cc_bspc_state.rapid_press = true;
    } else {
      cc_bspc_state.rapid_press = false;
    }

    other_key_pressed_except(&cc_bspc_state);

    return false;
  } else {
    return handle_tap_key(&cc_bspc_state, record->event.time);
  }
}

// S_BSPCキーを例にした処理
bool handle_s_bspc_key(keyrecord_t *record) {
  if (record->event.pressed) {
    // キー押下時の共通処理
    s_bspc_state.is_pressed = true;
    s_bspc_state.pressed_time = record->event.time;
    register_mods_for_key(&s_bspc_state);

    // 重要: rapid_press判定（前回のタップからの継続かどうか）
    if (timer_elapsed(s_bspc_state.released_time) < TAPPING_TERM) {
      s_bspc_state.rapid_press = true;
    } else {
      s_bspc_state.rapid_press = false;
    }

    // 他のキーが押されていることを記録
    other_key_pressed_except(&s_bspc_state);

    return false;
  } else {
    // キー離し時の処理
    bool result = handle_tap_key(&s_bspc_state, record->event.time);

    // 状態リセット
    s_bspc_state.is_pressed = false;
    unregister_mods_for_key(&s_bspc_state);

    return result;
  }
}

// C_ENTキーを例にした処理
bool handle_c_ent_key(keyrecord_t *record) {
  if (record->event.pressed) {
    // キー押下時の共通処理
    c_ent_state.is_pressed = true;
    c_ent_state.pressed_time = record->event.time;
    register_mods_for_key(&c_ent_state);

    // 重要: rapid_press判定（前回のタップからの継続かどうか）
    if (timer_elapsed(c_ent_state.released_time) < TAPPING_TERM) {
      c_ent_state.rapid_press = true;
    } else {
      c_ent_state.rapid_press = false;
    }

    // 他のキーが押されていることを記録
    other_key_pressed_except(&c_ent_state);

    return false;
  } else {
    // キー離し時の処理
    bool result = handle_tap_key(&c_ent_state, record->event.time);

    // 状態リセット
    c_ent_state.is_pressed = false;
    unregister_mods_for_key(&c_ent_state);

    return result;
  }
}
