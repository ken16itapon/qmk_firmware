#include "special_keys_config.h"
#include "state_manager.h"
#include "keymap.h"
#include "os_specific.h"



// グローバル設定テーブル
const special_key_config_t special_key_configs[SK_COUNT] = {
    // SK_HENKAN - 変換キー
    [SK_HENKAN] = {
        .macos = {
            .mod_keys = {KC_RCMD},
            .mod_count = 1,
            .tap_key = MC_HENKAN
        },
        .windows = {
            .mod_keys = {KC_RWIN},
            .mod_count = 1,
            .tap_key = WC_HENKAN
        },
        .linux = {
            .mod_keys = {KC_RWIN},
            .mod_count = 1,
            .tap_key = HENKAN
        }
    },

    // SK_MHENKAN - 無変換キー
    [SK_MHENKAN] = {
        .macos = {
            .mod_keys = {KC_LCMD},
            .mod_count = 1,
            .tap_key = MC_MHENKAN
        },
        .windows = {
            .mod_keys = {KC_LALT},
            .mod_count = 1,
            .tap_key = WC_MHENKAN
        },
        .linux = {
            .mod_keys = {KC_LALT},
            .mod_count = 1,
            .tap_key = MHENKAN
        }
    },

    // SK_C_BSPC - Ctrl/Cmd + Backspace
    [SK_C_BSPC] = {
        .macos = {
            .mod_keys = {KC_RSFT},
            .mod_count = 1,
            .tap_key = KC_BSPC
        },
        .windows = {
            .mod_keys = {KC_RSFT},
            .mod_count = 1,
            .tap_key = KC_BSPC
        },
        .linux = {
            .mod_keys = {KC_RSFT},
            .mod_count = 1,
            .tap_key = KC_BSPC
        }
    },

    // SK_CC_BSPC - Ctrl + Backspace（全OS共通）
    [SK_CC_BSPC] = {
        .macos = {
            .mod_keys = {KC_LCTL},
            .mod_count = 1,
            .tap_key = KC_BSPC
        },
        .windows = {
            .mod_keys = {KC_LCTL},
            .mod_count = 1,
            .tap_key = KC_BSPC
        },
        .linux = {
            .mod_keys = {KC_LCTL},
            .mod_count = 1,
            .tap_key = KC_BSPC
        }
    },

    // SK_C_SPC - Ctrl/Cmd + Space
    [SK_C_SPC] = {
        .macos = {
            .mod_keys = {KC_RCMD},
            .mod_count = 1,
            .tap_key = KC_SPC
        },
        .windows = {
            .mod_keys = {KC_RCTL},
            .mod_count = 1,
            .tap_key = KC_SPC
        },
        .linux = {
            .mod_keys = {KC_RCTL},
            .mod_count = 1,
            .tap_key = KC_SPC
        }
    },

    // SK_C_ENT - Ctrl/Cmd + Enter
    [SK_C_ENT] = {
        .macos = {
            .mod_keys = {KC_RCMD},
            .mod_count = 1,
            .tap_key = KC_ENT
        },
        .windows = {
            .mod_keys = {KC_RCTL},
            .mod_count = 1,
            .tap_key = KC_ENT
        },
        .linux = {
            .mod_keys = {KC_RCTL},
            .mod_count = 1,
            .tap_key = KC_ENT
        }
    },

    // SK_CS_TAB - Ctrl/Cmd + Shift + Tab（複数修飾キーの例）
    [SK_CS_TAB] = {
        .macos = {
            .mod_keys = {KC_LCMD, KC_LSFT},
            .mod_count = 2,
            .tap_key = KC_TAB
        },
        .windows = {
            .mod_keys = {KC_LCTL, KC_LSFT},
            .mod_count = 2,
            .tap_key = KC_TAB
        },
        .linux = {
            .mod_keys = {KC_LCTL, KC_LSFT},
            .mod_count = 2,
            .tap_key = KC_TAB
        }
    },

    // SK_LOWER - レイヤー切り替え + タップでBackspace
    [SK_LOWER] = {
        .macos = {
            .mod_keys = {},
            .mod_count = 0,
            .tap_key = KC_BSPC
        },
        .windows = {
            .mod_keys = {},
            .mod_count = 0,
            .tap_key = KC_BSPC
        },
        .linux = {
            .mod_keys = {},
            .mod_count = 0,
            .tap_key = KC_BSPC
        }
    },

    // SK_RAISE - レイヤー切り替え + タップでSpace
    [SK_RAISE] = {
        .macos = {
            .mod_keys = {},
            .mod_count = 0,
            .tap_key = KC_SPC
        },
        .windows = {
            .mod_keys = {},
            .mod_count = 0,
            .tap_key = KC_SPC
        },
        .linux = {
            .mod_keys = {},
            .mod_count = 0,
            .tap_key = KC_SPC
        }
    }
};

// OS別設定取得関数
const os_key_config_t* get_os_key_config(special_key_id_t key_id) {
    if (key_id >= SK_COUNT) {
        return NULL;
    }

    keyboard_os_t current_os = get_current_os();
    const special_key_config_t* config = &special_key_configs[key_id];

    switch (current_os) {
        case OS_MACOS:
            return &config->macos;
        case OS_WINDOWS:
            return &config->windows;
        case OS_LINUX:
            return &config->linux;
        default:
            return &config->windows;  // デフォルトはWindows設定
    }
}

// OS対応版修飾キー登録関数
void register_mods_for_key_os(key_state_t* key_state) {
    const os_key_config_t* config = get_os_key_config(key_state->key_id);
    if (config && config->mod_count > 0) {
        for (uint8_t i = 0; i < config->mod_count; i++) {
            register_code(config->mod_keys[i]);
        }
    }
}

// OS対応版修飾キー解除関数
void unregister_mods_for_key_os(key_state_t* key_state) {
    const os_key_config_t* config = get_os_key_config(key_state->key_id);
    if (config && config->mod_count > 0) {
        for (uint8_t i = 0; i < config->mod_count; i++) {
            unregister_code(config->mod_keys[i]);
        }
    }
}
