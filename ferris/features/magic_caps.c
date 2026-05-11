#include "magic_caps.h"

bool process_magic_caps(uint16_t keycode, keyrecord_t *record) {
  bool is_caps_word_pressed = keycode == CW_TOGG && record->event.pressed;

  if (!is_caps_word_pressed) {
    return true;
  }

  bool caps_lock_active = host_keyboard_led_state().caps_lock;
  
  if (caps_lock_active) {
    tap_code(KC_CAPS);
    return false;
  }

  bool has_shift_modifier = get_mods() & MOD_MASK_SHIFT;

  if (has_shift_modifier) {
    caps_word_off();

    del_mods(MOD_MASK_SHIFT);
    tap_code(KC_CAPS);

    return false;
  }

  return true;
}
