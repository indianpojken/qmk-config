#pragma once

#include QMK_KEYBOARD_H

void process_macro_key(
    uint16_t trigger,
    uint16_t action,

    uint16_t keycode,
    keyrecord_t *record
);
