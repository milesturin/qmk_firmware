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
  _GAMING,
  _LOWER,
  _RAISE,
  _NAVIGATION,
  _KEYBOARD
};

#define LOWER TT(_LOWER)
#define RAISE MO(_RAISE)
#define GAMING TG(_GAMING)
#define NAV MO(_NAVIGATION)
#define KEYBRD TG(_KEYBOARD)
#define SPIFT SFT_T(KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT,
       NAV,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_HOME,
    GAMING,KEYBRD, XXXXXXX, KC_LCTL,   LOWER,   RAISE,   SPIFT,   SPIFT, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT
),

[_GAMING] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,    KC_5,    KC_4,    KC_3,    KC_2,    KC_1,  KC_SPC,  KC_SPC, _______, _______, _______, _______
),

[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, XXXXXXX, KC_SLSH, KC_ASTR, XXXXXXX, XXXXXXX, XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX,  KC_DEL, 
    XXXXXXX,  KC_EQL, KC_MINS, KC_PLUS,  KC_DOT, XXXXXXX, XXXXXXX,    KC_4,    KC_5,    KC_6, XXXXXXX, KC_DQUO, 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_1,    KC_2,    KC_3, XXXXXXX,  KC_END, 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,    KC_0,    KC_0, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,    KC_LT,   KC_GT, KC_LBRC, KC_RBRC, XXXXXXX, XXXXXXX, KC_AMPR, KC_ASTR, XXXXXXX, KC_BSLS, XXXXXXX,
    XXXXXXX, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX,  KC_DLR, KC_PERC, KC_CIRC, KC_PIPE, KC_QUOT, 
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_EXLM,   KC_AT, KC_HASH, KC_SLSH, XXXXXXX, 
    XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, KC_UNDS, KC_UNDS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

[_NAVIGATION] = LAYOUT_planck_grid(
     KC_TAB,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX,   KC_F5,   KC_F6,   KC_F7,   KC_F8, XXXXXXX, KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,
    _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_LGUI, XXXXXXX, KC_LALT, KC_LALT, KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT
),

[_KEYBOARD] = LAYOUT_planck_grid(
    XXXXXXX, RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   RESET,
    XXXXXXX,RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   DEBUG,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

)};

const uint16_t ALT_TAB_DURATION = 650;
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
bool is_spift_held = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case SPIFT:
      is_spift_held = record->event.pressed;
      return true;
    default:
      return true;
  }
}

void matrix_scan_user(void) {
  if(is_alt_tab_active && timer_elapsed(alt_tab_timer) > ALT_TAB_DURATION) {
    is_alt_tab_active = false;
    unregister_code(KC_LALT);
  }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
  switch(get_highest_layer(layer_state)) {
    case _BASE:
    case _GAMING:
      if(!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(KC_LALT);
      }
      alt_tab_timer = timer_read();
      tap_code16(clockwise ? KC_TAB : S(KC_TAB));
      break;
    case _NAVIGATION:
      tap_code(clockwise ? KC_VOLU : KC_VOLD);
      break;
    case _KEYBOARD:
      switch(clockwise | (is_spift_held << 1)) {
        case 0b00:
          rgb_matrix_decrease_hue();
          break;
	case 0b01:
          rgb_matrix_increase_hue();
          break;
        case 0b10:
          rgb_matrix_decrease_speed();
          break;
        case 0b11:
          rgb_matrix_increase_speed();
	  break;
      }
      break;
  }
  return false;
}
