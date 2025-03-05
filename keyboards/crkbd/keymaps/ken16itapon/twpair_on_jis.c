/* Copyright 2018-2020 eswai <@eswai>
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

/*

  OSで日本語キーボード(logical bit pairing)と設定/認識されているキーボードで、
  USキーキャップの文字、記号(typewriter pairing)を正しく出力する。

  例: Shift + 2 で @ を入力する

  変換された文字はキーリピートが無効です。

*/

#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
// キーマップの定義を直接使用するために修正
#ifdef OS_DETECTION_ENABLE
#include "os_detection.h"
#endif

// GET_OS関数もexternで宣言
#ifdef OS_DETECTION_ENABLE
extern os_variant_t get_current_os(void);
#else
extern keyboard_os_t get_current_os(void);
#endif

const uint16_t us2jis[][2] = {
    {KC_LPRN, JP_LPRN},
    {KC_RPRN, JP_RPRN},
    {KC_AT, JP_AT},
    {KC_LBRC, JP_LBRC},
    {KC_RBRC, JP_RBRC},
    {KC_LCBR, JP_LCBR},
    {KC_RCBR, JP_RCBR},
    {KC_MINS, JP_MINS},
    {KC_EQL, JP_EQL},
    // KC_BSLS はOS別に処理するため、ここから削除
    {KC_SCLN, JP_SCLN},
    {KC_QUOT, JP_QUOT},
    {KC_GRV, JP_GRV},
    {KC_PLUS, JP_PLUS},
    {KC_COLN, JP_COLN},
    {KC_UNDS, JP_UNDS},
    // {KC_PIPE, JP_PIPE},
    {KC_DQT, JP_DQUO},
    {KC_ASTR, JP_ASTR},
    {KC_TILD, JP_TILD},
    {KC_AMPR, JP_AMPR},
    {KC_CIRC, JP_CIRC},
};

bool twpair_on_jis(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed) return true;

  uint16_t skeycode;  // シフトビットを反映したキーコード
  bool lshifted = get_mods() & MOD_BIT(KC_LSFT);  // シフトキーの状態
  bool rshifted = get_mods() & MOD_BIT(KC_RSFT);
  bool shifted = lshifted | rshifted;

  if (shifted) {
    skeycode = QK_LSFT | keycode;
  } else {
    skeycode = keycode;
  }

  // KC_BSLSは特別処理（OS別に異なる動作）
  if (keycode == KC_BSLS || skeycode == (QK_LSFT | KC_BSLS)) {
    // グローバル変数を使わず、直接関数を呼び出す
#ifdef OS_DETECTION_ENABLE
    os_variant_t current_os = get_current_os();
#else
    keyboard_os_t current_os = get_current_os();
#endif

    unregister_mods(MOD_BIT(KC_LSFT));
    unregister_mods(MOD_BIT(KC_RSFT));

    if (shifted) {
      // Shift + バックスラッシュの場合
      switch (current_os) {
        case OS_MACOS:  // MacOS
          register_mods(MOD_BIT(KC_LSFT));
          tap_code(KC_INT3);  // Macでは¥マークのためのキーコード
          unregister_mods(MOD_BIT(KC_LSFT));
          break;
        default:  // Windows/Linux
          register_mods(MOD_BIT(KC_LSFT));
          tap_code(JP_YEN);  // Windowsでは|（パイプ）
          unregister_mods(MOD_BIT(KC_LSFT));
          break;
      }
    } else {
      // バックスラッシュだけの場合
      switch (current_os) {
        case OS_MACOS:        // MacOS
          tap_code(KC_INT3);  // Macでは¥マーク
          break;
        default:              // Windows/Linux
          tap_code(JP_BSLS);  // Windowsでは\（バックスラッシュ）
          break;
      }
    }

    if (lshifted) register_mods(MOD_BIT(KC_LSFT));
    if (rshifted) register_mods(MOD_BIT(KC_RSFT));
    return false;
  }

  // 他のキーは従来通りの変換
  for (int i = 0; i < sizeof(us2jis) / sizeof(us2jis[0]); i++) {
    if (us2jis[i][0] == skeycode) {
      unregister_mods(MOD_BIT(KC_LSFT));
      unregister_mods(MOD_BIT(KC_RSFT));
      if ((us2jis[i][1] & QK_LSFT) == QK_LSFT ||
          (us2jis[i][1] & QK_RSFT) == QK_RSFT) {
        register_mods(MOD_BIT(KC_LSFT));
        tap_code(us2jis[i][1]);
        unregister_mods(MOD_BIT(KC_LSFT));
      } else {
        tap_code(us2jis[i][1]);
      }
      if (lshifted) register_mods(MOD_BIT(KC_LSFT));
      if (rshifted) register_mods(MOD_BIT(KC_RSFT));
      return false;
    }
  }

  return true;
}
