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

// ============================================================
// キー状態構造体
// ============================================================
typedef struct {
    bool is_pressed;           // 現在押下中か
    uint16_t pressed_time;     // 押下開始時刻
    uint16_t released_time;    // リリース時刻
    bool code_sent;            // キーコード送信済みか
    bool rapid_press;          // 連続押し判定
    bool other_key_pressed;    // 他のキーが押された
} key_state_t;

// ============================================================
// OS モード
// ============================================================
typedef enum {
    OS_MAC,
    OS_WINDOWS,
    OS_LINUX
} os_mode_t;

// ============================================================
// グローバル状態変数（extern宣言）
// ============================================================
extern os_mode_t current_os;

// ============================================================
// 初期化関数
// ============================================================
void initialize_key_states(void);

// ============================================================
// OS切替関数
// ============================================================
void toggle_os_mode(void);
os_mode_t get_current_os(void);
void set_os_mode(os_mode_t mode);

// ============================================================
// レイヤー変更通知
// ============================================================
void on_layer_change(uint8_t layer);

// ============================================================
// キー状態管理
// ============================================================
void reset_all_key_states(void);
void reset_key_state(key_state_t *state);
