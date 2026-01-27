#pragma once

#include QMK_KEYBOARD_H
#include "keymap_swedish_pro_mac_ansi.h"

const key_override_t ques_exlm_override = ko_make_basic(MOD_MASK_SHIFT, SE_QUES, SE_EXLM); // S-? -> !
const key_override_t quot_dquo_override = ko_make_basic(MOD_MASK_SHIFT, SE_QUOT, SE_DQUO); // S-' -> "

const key_override_t *key_overrides[] = {
  &ques_exlm_override,
  &quot_dquo_override,
};
