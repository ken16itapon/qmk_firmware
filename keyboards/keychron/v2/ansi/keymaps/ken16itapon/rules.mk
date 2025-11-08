# Copyright 2024 @ Ken16itapon
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# ============================================================
# 基本機能
# ============================================================
MOUSEKEY_ENABLE = yes       # マウスキー
EXTRAKEY_ENABLE = yes       # メディアキー（音量、再生等）
CONSOLE_ENABLE = no         # デバッグコンソール（サイズ削減のため無効）
COMMAND_ENABLE = no         # デバッグコマンド（サイズ削減のため無効）

# ============================================================
# 拡張機能
# ============================================================
COMBO_ENABLE = no           # キーコンボ（必要なら yes に変更）
TAP_DANCE_ENABLE = no       # タップダンス（必要なら yes に変更）
KEY_OVERRIDE_ENABLE = no    # キーオーバーライド（必要なら yes に変更）
AUTO_SHIFT_ENABLE = no      # オートシフト（必要なら yes に変更）

# ============================================================
# 追加ソースファイル
# ============================================================
SRC += key_handlers.c
SRC += state_manager.c

# ============================================================
# OS検出機能（必要な場合）
# ============================================================
# OS_DETECTION_ENABLE = yes

# ============================================================
# ファームウェアサイズ削減
# ============================================================
LTO_ENABLE = yes            # Link Time Optimization（サイズ削減）

# ============================================================
# デバッグ用（開発時のみ有効化）
# ============================================================
# CONSOLE_ENABLE = yes
# COMMAND_ENABLE = yes
