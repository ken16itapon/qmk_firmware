/*
Copyright 2020 yushakobo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// デバッグ設定（条件付き）
#ifdef CONSOLE_ENABLE
#    ifndef DEBUG_MATRIX_SCAN_RATE
#        define DEBUG_MATRIX_SCAN_RATE
#    endif

#    ifndef SPLIT_DEBUG
#        define SPLIT_DEBUG
#    endif

#    ifndef DEBUG_TRANSPORT
#        define DEBUG_TRANSPORT
#    endif
#endif

// なぎなた式設定
#define NG_NO_HENSHU
#define NG_NO_KOYUMEISHI
#define SHINGETA

#ifdef RGB_MATRIX_ENABLE
#    undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
#endif

// キーボード設定
#define TAPPING_TERM 180

// シリアル設定
#ifndef SERIAL_DEBUG
#    define SERIAL_DEBUG
#endif

// RGBライトの設定
#ifndef RGBLED_NUM
#    define RGBLED_NUM 6
#endif

#ifndef RGBLIGHT_LIMIT_VAL
#    define RGBLIGHT_LIMIT_VAL 255
#endif

// スキャンマトリックスデバッグ
#ifdef CONSOLE_ENABLE
#    ifndef DEBUG_SPLIT_MATRIX
#        define DEBUG_SPLIT_MATRIX
#    endif
#endif
