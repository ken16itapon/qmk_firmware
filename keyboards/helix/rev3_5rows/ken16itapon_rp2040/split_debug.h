#pragma once

#include "quantum.h"
#include "transport.h"

// transport用のデバッグ構造体
typedef struct {
    bool     connected;
    uint32_t last_sync;
    uint32_t errors;
    uint32_t successful_syncs;
    uint32_t matrix_scan_rate;
} transport_debug_state_t;

// 関数プロトタイプ
void monitor_split_status(void);
void monitor_keyboard_state(uint16_t keycode, keyrecord_t *record);

#ifdef DEBUG_TRANSPORT
transport_debug_state_t *get_transport_debug(void);
#endif
