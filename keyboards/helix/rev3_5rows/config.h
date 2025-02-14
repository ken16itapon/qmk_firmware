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

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

/*
 * Keyboard Matrix Assignments
 */
// AVR pins are commented out
// #define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
// #define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }

// Add RP2040 pin definitions
#define MATRIX_ROW_PINS \
    { GP4, GP5, GP6, GP7, GP8 }
#define MATRIX_COL_PINS \
    { GP29, GP28, GP27, GP26, GP22, GP20, GP23 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Split hand configuration for RP2040 */
#define SPLIT_HAND_MATRIX_GRID GP6, GP23
// #define SPLIT_HAND_MATRIX_GRID_LOW_IS_RIGHT  // 必要に応じて有効化

/* MCU Configuration */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_FLASH_GENERIC_03H

/* Split Keyboard Configuration */
#define SPLIT_HAND_PIN GP24
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10

/* Serial Configuration */
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

/* OLED Configuration */
#define OLED_FONT_H "keyboards/helix/common/glcdfont.c"

/* Encoder Configuration */
#ifdef ENCODER_ENABLE
#    undef ENCODER_A_PINS
#    undef ENCODER_B_PINS
#    undef ENCODERS_PAD_A
#    undef ENCODERS_PAD_B
#    undef ENCODER_RESOLUTION

// 新しい設定
#    define ENCODER_RESOLUTION 4
#    define ENCODERS_PAD_A \
        { GP16 }
#    define ENCODERS_PAD_B \
        { GP17 }
#    define ENCODERS_PAD_A_RIGHT \
        { GP16 }
#    define ENCODERS_PAD_B_RIGHT \
        { GP17 }
#    define SPLIT_ENCODER_MATRIX_GRID
#endif

#define SPLIT_ENCODER_ENABLE

/* WS2812 RGB LED Configuration */
#define WS2812_DI_PIN GP0 // RGBテープのデータピン
#undef RGBLED_NUM
#undef RGBLIGHT_LED_COUNT
#define RGBLED_NUM 64
#define RGBLIGHT_SLEEP // 省電力モード

// RGBライトエフェクトの設定
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

/* Split keyboard settings */
#define USE_SERIAL
#define SOFT_SERIAL_PIN GP1 // D2からGP1に変更
#define SELECT_SOFT_SERIAL_SPEED \
    0 // or 1, 2, 3, 4, 5
      // 0: 約189kbps (実験値)
      // 1: 約137kbps (実験値)
      // 2: 約75kbps (実験値)
      // 3: 約39kbps (実験値)
      // 4: 約26kbps (実験値)
      // 5: 約20kbps (実験値)

/* Split Keyboard Settings */
#define SPLIT_HAND_PIN GP24        // 左右判定用のピン
#define SPLIT_HAND_PIN_LOW_IS_LEFT // Low=左、High=右

/* Serial Settings */
#define SERIAL_USART_FULL_DUPLEX // 全二重通信を使用
#define SERIAL_USART_TX_PIN GP0  // UART0 TX
#define SERIAL_USART_RX_PIN GP1  // UART0 RX
#define SERIAL_USART_PIN_SWAP    // TX/RXピンのスワップ

#define SERIAL_PIO_USE_PIO0   // PIO0を使用
#define SERIAL_DRIVER SERCOMM // ChibiOSのシリアルドライバを使用

/* Split Communication Timeout */
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
