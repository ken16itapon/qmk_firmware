/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#undef RGB_LIGHT_ENABLE

#undef RGB_MATRIX_ENABLE
#define RGB_MATRIX_ENABLE

#ifdef RGB_MATRIX_ENABLE
#undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#define RGB_MATRIX_HUE_STEP 8
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8
#define RGB_MATRIX_SPD_STEP 10
#define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#endif

#define TAPPING_TERM 200
#define TAP_CODE_DELAY 10

#define NG_NO_HENSHU
#define NG_NO_KOYUMEISHI

// bootmagic関連の設定を無効化し競合を避ける
#define NO_BOOTMAGIC

// オプション：EEPROMへの書き込み回数を減らす設定
#define BOOTMAGIC_LITE_EEPROM_BLOCK_COUNT 4

// LEDの数を正しく設定
#define RGBLED_NUM 46        // Corne用（通常は27個×2）
#define DRIVER_LED_TOTAL 46  // Corneの場合

// 既存の設定の後に追加

// タップダンス設定
#define TAP_CODE_DELAY 10  // タップ間の遅延
