/* Copyright 2018 Eucalyn
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
#include <keymap_jp.h>
#include <sendstring_jis.h>
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum custom_keycodes {
  RGBRST = SAFE_RANGE
};

#define MT_EISU MT(MOD_LGUI, JP_MEISU)
#define MT_KANA MT(MOD_RGUI, JP_MKANA)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,    JP_YEN,  \
    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JP_LBRC, JP_RBRC, KC_BSPC,  \
    KC_LCTL,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,        KC_ENT,   \
    KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, LT(1, JP_UNDS),   KC_UP,  KC_RSFT,   \
    MO(2),    XXXXXXX,    KC_LALT,    MT_EISU,    KC_SPC,        KC_SPC, MT_KANA,  XXXXXXX,               KC_LEFT,KC_DOWN,KC_RGHT \
  ),
  [1] = LAYOUT( \
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,    KC_DEL, \
    XXXXXXX,   XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, RGUI(JP_LCBR), RGUI(JP_RCBR), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    XXXXXXX,    LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5),   LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), XXXXXXX, XXXXXXX,  XXXXXXX, \
    _______,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_PGUP, _______, \
    XXXXXXX,   _______,    _______,    _______,    JP_AT,       KC_BSPC, XXXXXXX, XXXXXXX,                   KC_HOME, KC_PGDN, KC_END \
  ),
  [2] = LAYOUT( \
    XXXXXXX,  XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,     XXXXXXX,   XXXXXXX,   JP_SLSH,   JP_ASTR,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
    RGB_TOG,   RGBRST,  RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,   XXXXXXX,  KC_7,      KC_8,      KC_9,      KC_MINS, JP_AT, XXXXXXX, XXXXXXX, \
    XXXXXXX,     RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,   XXXXXXX,  KC_4,     KC_5,      KC_6,      JP_PLUS, XXXXXXX,        KC_ENT, \
    _______,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,  KC_1,    KC_2,      KC_3,      XXXXXXX, _______, XXXXXXX, _______, \
    _______,   _______,    _______,    _______,    XXXXXXX,       KC_SPC,  KC_0, KC_DOT,                   XXXXXXX, XXXXXXX, XXXXXXX \
  )
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
