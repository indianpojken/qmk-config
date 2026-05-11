#pragma once

#include QMK_KEYBOARD_H

#include "keymap_swedish.h"
#include "keydefs/macros.h"

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

const key_override_t app_tmgr_override = ko_make_basic(
  MOD_MASK_SHIFT, KC_APP,
  MC_TMGR
);

const key_override_t tabc_tabn_override = ko_make_basic(
  MOD_MASK_SHIFT, KC_TABC,
  MC_TABN
);

const key_override_t esc_quit_override = ko_make_with_layers_and_negmods(
  MOD_MASK_SHIFT, KC_ESC,
  MC_QUIT,
  ~0,
  MOD_MASK_CTRL | MOD_MASK_GUI | MOD_MASK_ALT
);


const key_override_t *key_overrides[] = {
  &ques_exlm_override,
  &quot_dquo_override,
  &pgup_mhlu_override,
  &pgdn_whld_override,
  &app_tmgr_override,
  &tabc_tabn_override,
  &esc_quit_override
};
