#include QMK_KEYBOARD_H  // 最初に基本QMKヘッダー
#include "keymap.h"      // カスタムキーコード、レイヤー定義
// その他の依存関係
#include "key_handlers.h"
#include "naginata.h"

// タップと長押しの両方をサポートしたリピート処理
void handle_advanced_repeat(bool is_pressed, uint16_t pressed_time,
                            uint16_t released_time, bool *active_flag,
                            bool *code_sent, bool *rapid_press,
                            bool other_key_pressed, uint16_t keycode,
                            uint16_t mod_key) {
  // 既にアクティブな場合、単に状態を更新
  if (*active_flag) {
    if (!is_pressed) {
      unregister_code(keycode);
      *active_flag = false;
    }
    return;
  }

  // リピート開始条件判定（すべての条件を明示的にチェック）
  if (!is_pressed) return;              // キーが押されている
  if (!*code_sent) return;              // コードが送信済み
  if (*active_flag) return;             // リピートでない
  if (!*rapid_press) return;            // 連続タップされている
  if (layer_state_is(_ADJUST)) return;  // ADJUSTでない
  if (timer_elapsed(pressed_time) < TAPPING_TERM) return;  // 長押し

  // リピート開始条件を満たした - 修飾キーを解除してから通常キーを登録
  if (mod_key != KC_NO) {
    unregister_os_specific_key(mod_key);
  }

  *code_sent = false;
  *active_flag = true;
  register_code(keycode);
  return;
}

// キー押下時の初期化処理
void handle_key_press_init(uint16_t keycode) {
  switch (keycode) {
    case LOWER:
      reset_code_sent_except(&lower_state);
      other_key_pressed_except(&lower_state);
      break;
    case RAISE:
      reset_code_sent_except(&raise_state);
      other_key_pressed_except(&raise_state);
      break;
    case C_SPC:
      reset_code_sent_except(&c_spc_state);
      other_key_pressed_except(&c_spc_state);
      break;
    case C_BSPC:
      reset_code_sent_except(&c_bspc_state);
      other_key_pressed_except(&c_bspc_state);
      break;
    default:
      reset_code_sent();
      set_other_key_pressed();
      reset_rapid_press();
      break;
  }
}

// 単打判定と対応キー送信処理
bool handle_tap_key(bool pressed, uint16_t pressed_time,
                    uint16_t *released_time, bool *code_sent, bool *rapid_press,
                    bool *repeat_active, bool *mod_key_pressed,
                    bool other_pressed, uint16_t keycode, uint16_t mod_key,
                    uint16_t record_time) {
  if (pressed) {
    return false;
  }

  // 離した時の単打判定
  if (timer_elapsed(pressed_time) < TAPPING_TERM && !other_pressed) {
    if (mod_key != KC_NO) unregister_os_specific_key(mod_key);
    tap_code(keycode);
    *code_sent = true;
    *released_time = record_time;
    *mod_key_pressed = false;
    return false;
  }

  if (*repeat_active) {
    unregister_code(keycode);
    *repeat_active = false;
    *code_sent = false;
    return false;
  }

  *released_time = record_time;
  if (mod_key != KC_NO) unregister_os_specific_key(mod_key);
  *mod_key_pressed = false;
  return false;
}

// 修飾キー処理
bool handle_modifier_key(bool pressed, uint16_t keycode) {
  if (pressed) {
    register_os_specific_key(keycode);
  } else {
    unregister_os_specific_key(keycode);
  }
  return false;
}

// 複数の修飾キーを適用する関数
void apply_active_mods(uint16_t keycode) {
  if (henkan_state.mods_active) {
    register_os_specific_key(KC_RWIN);
  }
  if (mhenkan_state.mods_active) {
    register_os_specific_key(KC_LALT);
  }
  if (c_bspc_state.mods_active) {
    register_os_specific_key(KC_LCTL);
  }
  if (c_spc_state.mods_active) {
    register_os_specific_key(KC_RCTL);
  }
}

// LOWERキー処理
bool handle_lower_key(keyrecord_t *record) {
  if (record->event.pressed) {
    if (timer_elapsed(lower_state.released_time) < TAPPING_TERM) {
      lower_state.rapid_press = true;
    } else {
      lower_state.rapid_press = false;
    }

    lower_state.pressed = true;
    lower_state.pressed_time = record->event.time;
    lower_state.other_key_pressed = false;
    lower_state.mods_active = true;

    layer_on(_LOWER);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
    if (layer_state_is(_ADJUST)) {
      lower_state.rapid_press = false;
      lower_state.code_sent = true;
    }
    return false;
  }

  // キーを離した時の処理
  lower_state.pressed = false;
  layer_off(_LOWER);
  update_tri_layer(_LOWER, _RAISE, _ADJUST);

  bool result = handle_tap_key(
      false, lower_state.pressed_time, &lower_state.released_time,
      &lower_state.code_sent, &lower_state.rapid_press,
      &lower_state.repeat_active, &lower_state.mods_active,
      lower_state.other_key_pressed, KC_BSPC, KC_NO, record->event.time);

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

    raise_state.pressed = true;
    raise_state.pressed_time = record->event.time;
    raise_state.other_key_pressed = false;
    raise_state.mods_active = true;

    layer_on(_RAISE);
    update_tri_layer(_LOWER, _RAISE, _ADJUST);
    if (layer_state_is(_ADJUST)) {
      raise_state.code_sent = true;
      raise_state.rapid_press = false;
    }
    return false;
  }

  // キーを離した時の処理
  raise_state.pressed = false;
  layer_off(_RAISE);
  update_tri_layer(_LOWER, _RAISE, _ADJUST);

  bool result = handle_tap_key(
      false, raise_state.pressed_time, &raise_state.released_time,
      &raise_state.code_sent, &raise_state.rapid_press,
      &raise_state.repeat_active, &raise_state.mods_active,
      raise_state.other_key_pressed, KC_SPC, KC_NO, record->event.time);

  return result;  // 明示的にreturnを追加
}

bool handle_henkan_key(keyrecord_t *record) {
  if (record->event.pressed) {
    henkan_state.pressed = true;
    henkan_state.pressed_time = record->event.time;
    henkan_state.mods_active = true;

    // 他のキーが押されていることを記録
    other_key_pressed_except(&henkan_state);

    return false;
  } else {
    bool result = handle_tap_key(
        false, henkan_state.pressed_time, &henkan_state.released_time,
        &henkan_state.code_sent, &henkan_state.rapid_press,
        &henkan_state.repeat_active, &henkan_state.mods_active,
        henkan_state.other_key_pressed, KC_HENKAN, KC_RWIN, record->event.time);

    // 状態リセット
    henkan_state.pressed = false;
    unregister_os_specific_key(KC_RWIN);

    // タップ時の追加処理（薙刀式オン）
    if (henkan_state.code_sent) {
      naginata_on();
    }

    return result;
  }
}

bool handle_mhenkan_key(keyrecord_t *record) {
  if (record->event.pressed) {
    mhenkan_state.pressed = true;
    mhenkan_state.pressed_time = record->event.time;
    mhenkan_state.mods_active = true;

    // 他のキーが押されていることを記録
    //    other_key_pressed_except(&mhenkan_state);

    return false;
  } else {
    // キー離し時の処理（既存と同じ）

    bool result = handle_tap_key(
        false, mhenkan_state.pressed_time, &mhenkan_state.released_time,
        &mhenkan_state.code_sent, &mhenkan_state.rapid_press,
        &mhenkan_state.repeat_active, &mhenkan_state.mods_active,
        mhenkan_state.other_key_pressed, KC_MHENKAN, KC_LALT,
        record->event.time);

    // 状態リセット
    mhenkan_state.pressed = false;
    unregister_os_specific_key(KC_LALT);

    // タップ時の追加処理（薙刀式オフ）
    if (mhenkan_state.code_sent) {
      naginata_off();
    }

    return result;
  }
}

bool handle_c_bspc_key(keyrecord_t *record) {
  if (record->event.pressed) {
    // キー押下時の共通処理
    c_bspc_state.pressed = true;
    c_bspc_state.pressed_time = record->event.time;
    c_bspc_state.other_key_pressed = false;
    c_bspc_state.mods_active = true;

    // rapid_press判定（前回のタップからの継続かどうか）
    if (timer_elapsed(c_bspc_state.released_time) < TAPPING_TERM) {
      c_bspc_state.rapid_press = true;
    } else {
      c_bspc_state.rapid_press = false;
    }

    // 他のキーが押されていることを記録
    other_key_pressed_except(&c_bspc_state);

    return false;
  } else {
    // キー離し時の処理
    bool result = handle_tap_key(
        false, c_bspc_state.pressed_time, &c_bspc_state.released_time,
        &c_bspc_state.code_sent, &c_bspc_state.rapid_press,
        &c_bspc_state.repeat_active, &c_bspc_state.mods_active,
        c_bspc_state.other_key_pressed, KC_BSPC, KC_LCTL, record->event.time);

    // 状態リセット
    c_bspc_state.pressed = false;
    unregister_os_specific_key(KC_LCTL);

    return result;
  }
}

// C_SPCキーを例にした処理
bool handle_c_spc_key(keyrecord_t *record) {
  if (record->event.pressed) {
    // キー押下時の共通処理
    c_spc_state.pressed = true;
    c_spc_state.pressed_time = record->event.time;
    c_spc_state.other_key_pressed = false;
    c_spc_state.mods_active = true;

    // 重要: rapid_press判定（前回のタップからの継続かどうか）
    if (timer_elapsed(c_spc_state.released_time) < TAPPING_TERM) {
      c_spc_state.rapid_press = true;
    } else {
      c_spc_state.rapid_press = false;
    }

    // 他のキーが押されていることを記録
    other_key_pressed_except(&c_spc_state);

    return false;
  } else {
    // キー離し時の処理
    bool result = handle_tap_key(
        false, c_spc_state.pressed_time, &c_spc_state.released_time,
        &c_spc_state.code_sent, &c_spc_state.rapid_press,
        &c_spc_state.repeat_active, &c_spc_state.mods_active,
        c_spc_state.other_key_pressed, KC_SPC, KC_RCTL, record->event.time);

    // 状態リセット
    c_spc_state.pressed = false;
    unregister_os_specific_key(KC_RCTL);

    return result;
  }
}
