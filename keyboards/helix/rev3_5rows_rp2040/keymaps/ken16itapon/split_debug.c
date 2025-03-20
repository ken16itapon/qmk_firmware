#include QMK_KEYBOARD_H
#include "print.h"
#include "split_util.h"
#include "split_debug.h"
#include "transport.h"
#include "timer.h"
#include "debug.h"

// スプリット状態の追跡用static変数
static struct {
    uint32_t last_debug_time;
    uint32_t error_count;
    uint32_t last_sync_time;
    uint32_t matrix_scan_rate;
    bool     last_transport_state;
} debug_stats = {0};

void keyboard_post_init_debug(void) {
#ifndef NO_DEBUG
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
#endif
    print_set_sendchar(sendchar);
}

void monitor_split_status(void) {
    uint32_t current_time        = timer_read32();
    bool     transport_connected = is_transport_connected();

    // 接続状態の変化を検出
    if (transport_connected != debug_stats.last_transport_state) {
        if (!transport_connected) {
            debug_stats.error_count++;
        } else {
            debug_stats.last_sync_time = current_time;
        }
        debug_stats.last_transport_state = transport_connected;
    }

    // 500ms毎にデバッグ情報を出力
    if (timer_elapsed32(debug_stats.last_debug_time) > 500) {
        debug_stats.last_debug_time  = current_time;
        debug_stats.matrix_scan_rate = (uint32_t)get_matrix_scan_rate();

        xprintf("スプリットキーボード状態:\n");
        xprintf("- マスター側: %s\n", is_keyboard_master() ? "はい" : "いいえ");
        xprintf("- 通信状態: %s\n", transport_connected ? "接続中" : "切断");
        xprintf("- スキャンレート: %lu Hz\n", debug_stats.matrix_scan_rate);
        xprintf("- 通信エラー: %lu回\n", debug_stats.error_count);

        if (transport_connected && debug_stats.last_sync_time > 0) {
            xprintf("- 最後の同期: %lums前\n", timer_elapsed32(debug_stats.last_sync_time));
        }

        if (!transport_connected) {
            xprintf("\nトラブルシューティング:\n");
            xprintf("1. TRRSケーブルの接続確認\n");
            xprintf("2. 両側の電源確認\n");
            xprintf("3. USBケーブルの接続確認\n");
        }
    }
}

void monitor_keyboard_state(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        xprintf("キーイベント:\n");
        xprintf("- 位置: Row=%u, Col=%u\n", record->event.key.row, record->event.key.col);
        xprintf("- キーコード: %u\n", keycode);
        xprintf("- レイヤー: %u\n", get_highest_layer(layer_state));

        if (!is_transport_connected()) {
            xprintf("警告: スプリット接続が切断されています\n");
        }
    }
}
