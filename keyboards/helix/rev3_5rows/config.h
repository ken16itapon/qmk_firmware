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

/* Key Matrix Configuration */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Matrix Pin Configuration for RP2040 */
#define MATRIX_ROW_PINS \
    { GP4, GP5, GP6, GP7, GP8 }
#define MATRIX_COL_PINS \
    { GP29, GP28, GP27, GP26, GP22, GP20, GP23 }
#define DIODE_DIRECTION COL2ROW

/* Split hand configration */
#define SPLIT_HAND_MATRIX_GRID GP6, GP23

/* Split Configuration */
#define USE_SERIAL
// #define SOFT_SERIAL_PIN GP1
// #define MASTER_LEFT // 左側がマスター固定
// #define SERIAL_DRIVER SERCOMM
// #define SERIAL_PIO_USE_PIO0
#define SERIAL_USART_TX_PIN GP1
// #define SERIAL_USART_RX_PIN GP1
#define SERIAL_USART_HALF_DUPLEX
// #define SERIAL_PIO_USE_PIO0
// #define SPLIT_WATCHDOG_ENABLE
// #define SPLIT_CONNECTION_CHECK_TIMEOUT 500
// #define SPLIT_HAND_PIN GP24    // 未配線のためコメントアウト
// #define PAL_USE_CALLBACKS TRUE

// スプリット同期設定を追加
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE

/* Encoder Configuration */
#ifdef ENCODER_ENABLE
#    define ENCODER_RESOLUTION 4
#    define ENCODERS_PAD_A \
        { GP21 }
#    define ENCODERS_PAD_B \
        { GP9 }
#    define ENCODERS_PAD_A_RIGHT \
        { GP21 }
#    define ENCODERS_PAD_B_RIGHT \
        { GP9 }
#    define SPLIT_ENCODER_ENABLE
#    define SPLIT_ENCODER_MATRIX_GRID
#endif

/* OLED Configuration */
#define OLED_DISPLAY_128X32
#define OLED_FONT_H "keyboards/helix/common/glcdfont.c"
#define OLED_TIMEOUT 30000

/* RGB LED Configuration */
#define WS2812_DI_PIN GP0

// RGB LEDの数を定義
#define RGBLED_NUM 64
#define RGBLIGHT_LED_COUNT RGBLED_NUM

// スプリットキーボードのLED設定
#define RGBLIGHT_SPLIT
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_SLEEP

// 明るさと初期設定
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD
#define RGBLIGHT_DEFAULT_HUE 170
#define RGBLIGHT_DEFAULT_SAT 255
#define RGBLIGHT_DEFAULT_VAL RGBLIGHT_LIMIT_VAL

// アニメーション設定
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_STATIC_GRADIENT

/* Debug Configuration */
#ifdef CONSOLE_ENABLE
#    define DEBUG_MATRIX_SCAN_RATE
#    define DEBUG_MATRIX
#endif

