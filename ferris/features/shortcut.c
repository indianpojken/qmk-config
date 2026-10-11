#include "shortcut.h"

void process_shortcut_key(
    uint16_t trigger,
    uint16_t action,

    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger && record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          return;
        }

        uint8_t mods = get_mods();

        clear_mods();
        clear_oneshot_mods();

        tap_code16(action);
        set_mods(mods);
    }
}

void process_shortcuts(
    const shortcut_t *shortcuts,
    uint8_t count,

    uint16_t keycode,
    keyrecord_t *record
) {
    for (uint8_t i = 0; i < count; i++) {
        if (shortcuts[i].trigger == keycode) {
            process_shortcut_key(
                shortcuts[i].trigger,
                shortcuts[i].action,
                keycode,
                record
            );
            return;
        }
    }
}
