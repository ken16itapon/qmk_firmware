# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a QMK Firmware repository focused on custom keyboard configurations, specifically for:
- **crkbd** (Corne Keyboard) with custom keymaps including ken16itapon and ken16naginata
- **helix** keyboards with rev3_5rows_rp2040 variant

The repository includes Japanese input support with Naginata-style (薙刀式) layout implementations.

## Build Commands

### Compiling Firmware
```bash
# Standard compilation for specific keyboard/keymap
qmk compile -kb <keyboard> -km <keymap>

# Examples for this repository:
qmk compile -kb crkbd -km ken16itapon
qmk compile -kb crkbd -km ken16naginata
qmk compile -kb helix/rev3_5rows_rp2040 -km ken16itapon

# Clean build (removes object files first)
qmk clean
qmk compile -c -kb <keyboard> -km <keymap>
```

### Flashing Firmware
```bash
# Flash compiled firmware to keyboard
qmk flash -kb <keyboard> -km <keymap>

# Example:
qmk flash -kb crkbd -km ken16itapon
```

### Testing
```bash
# Run specific test suite
make test:<test_name>

# Example:
make test:basic
```

## Architecture & Key Components

### Custom Keymap Structure (crkbd/ken16itapon)
The main custom keymap implementation consists of modular components:

- **keymap.c** - Main keymap definitions and layer configurations
- **keymap.h** - Header with layer enums and macro definitions
- **key_handlers.c/h** - Modular key event processing and custom behaviors
- **state_manager.c** - State management for layers and modes
- **os_specific.c** - OS-specific functionality (OS detection enabled)
- **naginata_v15.c** - Naginata-style Japanese input implementation
- **twpair_on_jis.c** - JIS keyboard pair handling
- **japanese_kana.h** - Japanese kana character definitions

### Build Configuration (rules.mk)
Key features enabled in custom keymaps:
- **NAGINATA_ENABLE** - Japanese Naginata layout support
- **TAP_DANCE_ENABLE** - Complex tap/hold behaviors
- **OS_DETECTION_ENABLE** - Automatic OS detection for adaptive behavior
- **RGB_MATRIX_ENABLE** - RGB lighting effects
- **UNICODE_ENABLE** - Unicode character support
- **CONSOLE_ENABLE** - Debug console output

### Keyboard Variants
- **crkbd**: Split keyboard with multiple revisions (rev1, rev4_0, rev4_1, r2g)
- **helix**: Multiple variants including rev3_5rows_rp2040 (RP2040-based)

## Development Workflow

### Adding/Modifying Keymaps
1. Keymaps are located in `keyboards/<keyboard>/keymaps/<keymap_name>/`
2. Each keymap requires at minimum:
   - `keymap.c` - Keymap implementation
   - `rules.mk` - Build configuration
   - Optional: `config.h` for keymap-specific settings

### Modular Code Organization
When modifying the ken16itapon keymap, maintain the modular structure:
- Keep key handling logic in `key_handlers.c`
- State management in `state_manager.c`
- OS-specific code in `os_specific.c`
- Japanese input logic in `naginata_v15.c`

### Debug Console
Console output is enabled for debugging. Use:
```c
uprintf("Debug message\n");  // For user-facing debug
dprintf("Debug message\n");  // For developer debug
```

## Important Notes

- The repository uses a cleaned version with only crkbd and helix keyboards (commit: d78ca8c88e)
- Git submodules are present for lib/chibios, lib/chibios-contrib, and lib/lvgl
- VS Code tasks are configured for common QMK operations (see .vscode/tasks.json)
- The main branch is `master` (not `main`)
- あなたは経験豊富なプロジェクトマネージャーです。
- 質疑応答をしながら､キーボードファームウェアの改修計画を立てます。
- 目的 要件定義書を作成します。