#include "tabber.h"

void update_tabber(
  tabber_t *tabber,

  uint16_t trigger,

  uint16_t keycode,
  keyrecord_t *record
) {
  if (keycode != trigger && !is_tabber_ignored_key(keycode)) {
    if (tabber->enabled) {
      unregister_code(tabber->modifier);
      tabber->enabled = false;
    }

    return;
  }

   if (keycode != trigger) {
    return;
  }

  if (record->event.pressed) {
    if (!tabber->enabled) {
      register_code16(tabber->modifier);
      tabber->enabled = true;
    }

    register_code16(tabber->key);
  } else {
    unregister_code16(tabber->key);
  }
}
