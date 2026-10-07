#pragma once

#include QMK_KEYBOARD_H

#include "keymap_swedish.h"
#include "keydefs/shortcuts.h"

const key_override_t ques_exlm_override = ko_make_basic(
  MOD_MASK_SHIFT, SE_QUES,
  SE_EXLM
); // S-? -> !

const key_override_t quot_dquo_override = ko_make_basic(
  MOD_MASK_SHIFT, SE_QUOT,
  SE_DQUO
); // S-' -> "

const key_override_t pgup_mhlu_override = ko_make_basic(
  MOD_MASK_SHIFT, KC_PGUP,
  MS_WHLU
);

const key_override_t pgdn_whld_override = ko_make_basic(
  MOD_MASK_SHIFT, KC_PGDN,
  MS_WHLD
);

const key_override_t tabn_tabc_override = ko_make_basic(
  MOD_MASK_SHIFT, KC_TABN,
  SC_TABC
);

const key_override_t *key_overrides[] = {
  &ques_exlm_override,
  &quot_dquo_override,
  &pgup_mhlu_override,
  &pgdn_whld_override,
  &tabn_tabc_override,
};
