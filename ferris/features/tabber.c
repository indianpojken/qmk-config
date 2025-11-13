#include "tabber.h"

void update_tabber_action(
    tabber_t *tabber,
    tabber_action_t *action,

    uint16_t trigger,

    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode != trigger) {
        return;
    }

    uint16_t tab_key = tabber->enabled
        ? action->active
        : action->normal;

    if (record->event.pressed) {
        register_code16(tab_key);

        if (tabber->enabled) {
            tabber->previous = tab_key;
        }
    } else {
        unregister_code16(tab_key);
    }
}

void update_tabber(
    tabber_t *tabber,

    uint16_t trigger,

    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode != trigger && !is_tabber_ignored_key(keycode)) {
        unregister_code(tabber->modifier);

        tabber->enabled = false;
        tabber->previous = KC_NO;

        return;
    }

    if (keycode != trigger) {
        return;
    }

    uint16_t tab_key = tabber->previous != KC_NO
        ? tabber->previous
        : KC_TAB;

    if (record->event.pressed) {
        if (!tabber->enabled) {
            register_code16(tabber->modifier);
            tabber->enabled = true;
        }

        register_code16(tab_key);
    } else {
        unregister_code16(tab_key);
    }
}
