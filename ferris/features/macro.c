#include "macro.h"

void process_macro_key(
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
