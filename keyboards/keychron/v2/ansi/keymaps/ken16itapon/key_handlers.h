/* Copyright 2024 @ Ken16itapon
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include QMK_KEYBOARD_H
#include "state_manager.h"

// ============================================================
// キー処理のメイン関数
// ============================================================
bool handle_custom_keys(uint16_t keycode, keyrecord_t *record);

// ============================================================
// 個別キーハンドラー
// ============================================================
bool handle_double_tap_key(keyrecord_t *record);
bool handle_hold_action_key(keyrecord_t *record);
bool handle_combo_key(keyrecord_t *record);
bool handle_macro_key(uint16_t keycode, keyrecord_t *record);
bool handle_os_switch_key(keyrecord_t *record);

// ============================================================
// ユーティリティ関数
// ============================================================
void check_tapping_timeout(void);
bool is_key_within_tapping_term(key_state_t *state);
void send_custom_sequence(const uint16_t *sequence, uint8_t length);
void send_os_specific_key(uint16_t mac_key, uint16_t win_key);
