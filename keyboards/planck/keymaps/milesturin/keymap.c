/* Copyright 2015-2021 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  //_GAMING,
  _KEYBOARD
};

#define LOWER TT(_LOWER)
#define RAISE TT(_RAISE)
#define GAMING KC_NO//TG(_GAMING)
#define KEYBRD TG(_KEYBOARD)
#define TASK C(S(KC_ESC))

#define QUIT A(KC_F4)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_planck_grid(
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
     KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT,
    KC_HOME,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_QUOT,
     GAMING,KEYBRD, KC_LGUI, KC_LALT, KC_LCTL,   LOWER,  KC_SPC, KC_LSFT,   RAISE, KC_PGDN, KC_PGUP,    TASK
),

[_LOWER] = LAYOUT_planck_grid(
     KC_GRV,   KC_AT, KC_AMPR, KC_PLUS, KC_BSLS, KC_LCBR, KC_RCBR,    KC_7,    KC_8,    KC_9, KC_HASH,  KC_DEL, 
    KC_TILD, KC_EXLM, KC_ASTR, KC_MINS, KC_UNDS, KC_LPRN, KC_RPRN,    KC_4,    KC_5,    KC_6,    KC_0, _______,
     KC_END,  KC_DLR, KC_CIRC,  KC_EQL, KC_PIPE, KC_LBRC, KC_RBRC,    KC_1,    KC_2,    KC_3, KC_PERC, _______, 
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_RAISE] = LAYOUT_planck_grid(
    XXXXXXX,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    QUIT,
    XXXXXXX,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX, KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
    XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
   
),
/*
[_GAMING] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,    KC_5,    KC_4,    KC_3,    KC_2,    KC_1,  KC_SPC,  KC_SPC, _______, _______, _______, _______
),
*/
[_KEYBOARD] = LAYOUT_planck_grid(
    XXXXXXX, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   RESET,
    XXXXXXX,RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   DEBUG,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)};

const uint16_t ALT_TAB_DURATION = 650;
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

void matrix_scan_user(void) {
  if(is_alt_tab_active && timer_elapsed(alt_tab_timer) > ALT_TAB_DURATION) {
    is_alt_tab_active = false;
    unregister_code(KC_LALT);
  }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  switch(get_highest_layer(layer_state)) {
    case _BASE:
    //case _GAMING:
      if(!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(KC_LALT);
      }
      alt_tab_timer = timer_read();
      tap_code16(clockwise ? KC_TAB : S(KC_TAB));
      break;
    case _KEYBOARD:
      if(clockwise) rgb_matrix_decrease_hue();
      else rgb_matrix_increase_hue();
      break;
  }
  return false;
}
