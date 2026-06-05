#include "oneshot_fn.h"

bool update_oneshot_fn(
  bool *pending,
  uint16_t trigger,
  uint16_t keycode,
  keyrecord_t *record
) {
  if (keycode == trigger) {
    if (record->event.pressed) {
      *pending = true;
    }

    return false;
  }

  if (!*pending) {
    return true;
  }

  if (record->event.pressed) {
    uint16_t fn_key = oneshot_fn_press_user(keycode);

    if (fn_key != KC_NO) {
      tap_code(fn_key);
      *pending = false;
      
      return false;
    }
    
    *pending = false;
  }

  return true;
}
