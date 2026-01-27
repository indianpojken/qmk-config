#pragma once

#include QMK_KEYBOARD_H

typedef struct {
  bool enabled;

  uint16_t modifier;
  uint16_t key;
} tabber_t;

void update_tabber(
  tabber_t *tabber,

  uint16_t trigger,

  uint16_t keycode,
  keyrecord_t *record
);

bool is_tabber_ignored_key(uint16_t keycode);
