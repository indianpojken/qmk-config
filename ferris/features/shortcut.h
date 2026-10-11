#pragma once

#include QMK_KEYBOARD_H

typedef struct {
    uint16_t trigger;
    uint16_t action;
} shortcut_t;

void process_shortcut_key(
    uint16_t trigger,
    uint16_t action,

    uint16_t keycode,
    keyrecord_t *record
);

void process_shortcuts(
    const shortcut_t *shortcuts,
    uint8_t count,

    uint16_t keycode,
    keyrecord_t *record
);
