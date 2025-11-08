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

// ============================================================
// タップ判定設定
// ============================================================
#define TAPPING_TERM 200        // タップ判定時間（ミリ秒）

// タップ判定を厳密にする（他のキー押下時に即座にホールド判定）
#define PERMISSIVE_HOLD

// Mod-Tap時のタップ優先
#define IGNORE_MOD_TAP_INTERRUPT

// タップ/ホールド判定の厳密化（推奨）
// #define TAPPING_FORCE_HOLD

// ============================================================
// マウスキー設定
// ============================================================
#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_DELAY 0
#    define MOUSEKEY_INTERVAL 16
#    define MOUSEKEY_MAX_SPEED 6
#    define MOUSEKEY_TIME_TO_MAX 40
#    define MOUSEKEY_WHEEL_DELAY 0
#endif

// ============================================================
// コンボ機能設定
// ============================================================
#ifdef COMBO_ENABLE
#    define COMBO_COUNT 5       // 定義するコンボの数
#    define COMBO_TERM 50       // コンボ判定時間（ミリ秒）
#endif

// ============================================================
// RGB Matrix設定
// ============================================================
#ifdef RGB_MATRIX_ENABLE
// RGB輝度のデフォルト値
#    define RGB_MATRIX_DEFAULT_VAL 128

// RGB色相のデフォルト値
#    define RGB_MATRIX_DEFAULT_HUE 0

// RGBアニメーションのデフォルト速度
#    define RGB_MATRIX_DEFAULT_SPD 127

// アイドル時にRGBをオフにする（秒）
// #    define RGB_MATRIX_TIMEOUT 300000

// キー押下時のRGBエフェクトを有効化
#    define RGB_MATRIX_KEYPRESSES
#endif

// ============================================================
// デバッグ設定
// ============================================================
// デバッグコンソールを有効化する場合はコメント解除
// #define DEBUG_MATRIX_SCAN_RATE

// ============================================================
// その他の設定
// ============================================================
// USBポーリングレート（推奨: 変更不要）
// #define USB_POLLING_INTERVAL_MS 1

// Nキーロールオーバーをデフォルトで有効化
// #define FORCE_NKRO
