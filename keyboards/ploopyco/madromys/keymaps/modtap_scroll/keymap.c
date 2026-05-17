/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
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

enum {
    TD_DS,
};
enum {
    TD_TAB_CLOSE,
    WIN_TAB,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_TAB_CLOSE] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_W), LSFT(LCTL(KC_T))),
    [WIN_TAB]      = ACTION_TAP_DANCE_DOUBLE(MS_BTN5, LGUI(KC_TAB)),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0, TD_DS):
            if (record->tap.count == 0) {
                if (record->event.pressed) {
                    set_drag_scroll(true);
                } else {
                    set_drag_scroll(false);
                }
            } else {
                if (record->event.pressed) {
                    toggle_drag_scroll();
                }
            }
            // if (record->tap.count && record->event.pressed) {
            //     // tap_code16(MOMENTARY_DRAG_SCROLL); // Intercept tap function to send Ctrl-C
            //     // process_record_kb(TOGGLE_DRAG_SCROLL, record);
            //     //toggle_drag_scroll();
            // } else if (record->event.pressed) {
            //     momentary_drag_scroll(record);
            //     // is_drag_scroll = record->event.pressed;
            //     // process_record_kb(MOMENTARY_DRAG_SCROLL, record);
            //     // tap_code16(TOGGLE_DRAG_SCROLL); // Intercept hold function to send Ctrl-V
            // }
            // return false;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(MO(1), TD(TD_TAB_CLOSE), LT(0, TD_DS), MS_BTN4, MS_BTN1, MS_BTN2),
    // [0] = LAYOUT(MO(1), LCTL(KC_W), MS_BTN4, MOMENTARY_DRAG_SCROLL, MS_BTN1, MS_BTN2),
    [1] = LAYOUT(KC_TRNS, MS_BTN3, DPI_CONFIG, TD(WIN_TAB), LGUI(KC_LEFT), LGUI(KC_RGHT)),
};