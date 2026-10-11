#include "oneshot.h"

void update_oneshot(oneshot_state *state, uint16_t mod, uint16_t trigger,
                    uint16_t keycode, keyrecord_t *record) {
  if (keycode == trigger) {
    if (record->event.pressed) {
      // Trigger keydown
      if (*state == os_up_unqueued) {
        register_code(mod);
      }
      *state = os_down_unused;
    } else {
      // Trigger keyup
      switch (*state) {
      case os_down_unused:
        // If we didn't use the mod while trigger was held, queue it.
        *state = os_up_queued;
        break;
      case os_down_used:
        // If we did use the mod while trigger was held, unregister it.
        *state = os_up_unqueued;
        unregister_code(mod);
        break;
      default:
        break;
      }
    }
  } else {
    if (record->event.pressed) {
      if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
        // Cancel oneshot on designated cancel keydown.
        *state = os_up_unqueued;
        unregister_code(mod);
      }
    } else {
      if (!is_oneshot_ignored_key(keycode)) {
        // On non-ignored keyup, consider the oneshot used.
        switch (*state) {
        case os_down_unused:
          *state = os_down_used;
          break;
        case os_up_queued:
          *state = os_up_unqueued;
          unregister_code(mod);
          break;
        default:
          break;
        }
      }
    }
  }
}

void process_oneshots(oneshot_t *oneshots, uint8_t count, uint16_t keycode,
                      keyrecord_t *record) {
  for (uint8_t i = 0; i < count; i++) {
    update_oneshot(&oneshots[i].state, oneshots[i].mod, oneshots[i].trigger,
                   keycode, record);
  }
}
