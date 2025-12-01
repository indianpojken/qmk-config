#pragma once

#include QMK_KEYBOARD_H

typedef struct {
  bool enabled;
  uint16_t previous;

  uint16_t modifier;
} tabber_t;

typedef struct {
  uint16_t active;
  uint16_t normal;
} tabber_action_t;

void update_tabber_action(
  tabber_t *tabber,
  tabber_action_t *action,

  uint16_t trigger,

  uint16_t keycode,
  keyrecord_t *record
);

void update_tabber(
  tabber_t *tabber,

  uint16_t trigger,

  uint16_t keycode,
  keyrecord_t *record
);

bool is_tabber_ignored_key(uint16_t keycode);
