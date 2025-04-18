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
#include "os_specific.h"

const uint16_t us2jis[][2] = {
    {KC_LPRN, JP_LPRN}, {KC_RPRN, JP_RPRN}, {KC_AT, JP_AT},
    {KC_LBRC, JP_LBRC}, {KC_RBRC, JP_RBRC}, {KC_LCBR, JP_LCBR},
    {KC_RCBR, JP_RCBR}, {KC_MINS, JP_MINS}, {KC_EQL, JP_EQL},
    {KC_BSLS, JP_BSLS}, {KC_PIPE, JP_PIPE}, {KC_SCLN, JP_SCLN},
    {KC_QUOT, JP_QUOT}, {KC_GRV, JP_GRV},   {KC_PLUS, JP_PLUS},
    {KC_COLN, JP_COLN}, {KC_UNDS, JP_UNDS}, {KC_DQT, JP_DQUO},
    {KC_ASTR, JP_ASTR}, {KC_TILD, JP_TILD}, {KC_AMPR, JP_AMPR},
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

  if (keycode == KC_BSLS || skeycode == (QK_LSFT | KC_BSLS)) {
    unregister_mods(MOD_BIT(KC_LSFT));
    unregister_mods(MOD_BIT(KC_RSFT));

    // キー入力を追加
    if (shifted) {
      // パイプ記号
      register_mods(MOD_BIT(KC_LSFT));
      tap_code(JP_YEN);
      unregister_mods(MOD_BIT(KC_LSFT));
    } else {
      // バックスラッシュ
      if (global_os_cache == OS_MACOS) {
        // Save Option key state
        bool opt_state = get_mods() & MOD_BIT(KC_LOPT);
        // Turn on Option key
        register_mods(MOD_BIT(KC_LOPT));
        // Send the key
        tap_code(KC_INT3);
        // Turn off Option key
        unregister_mods(MOD_BIT(KC_LOPT));
        // Restore Option key state if it was on
        if (opt_state) {
            register_mods(MOD_BIT(KC_LOPT));
        }
      } else {
        tap_code(JP_BSLS);
      }
    }

    // シフト状態を復元
    if (lshifted) register_mods(MOD_BIT(KC_LSFT));
    if (rshifted) register_mods(MOD_BIT(KC_RSFT));
    return false;
  }

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
