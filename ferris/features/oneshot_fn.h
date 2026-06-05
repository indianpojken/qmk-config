#pragma once

#include QMK_KEYBOARD_H

bool update_oneshot_fn(
  bool *pending,
  uint16_t trigger,
  uint16_t keycode,
  keyrecord_t *record
);

uint16_t oneshot_fn_press_user(uint16_t keycode);
