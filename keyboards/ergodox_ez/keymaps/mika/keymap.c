#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "sendchar.h"
#include "virtser.h"

/* https://github.com/qmk/qmk_firmware/commit/a25dbaad327f834dad6fb572b074bab7be1e1d0f */
#define NO_ASTR LSFT(KC_BSLS)  // *
#define ____ KC_TRNS

// easy access to symbols that actually work when the system keyboard is Finnish
#include "keymap_nordic.h"
#include "keymap_german.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define PLOVER 3 // Steno QWERTY
#define KEYLOCK 4 // key lock layer
#define WNDOW 5 // window management in Fedora Linux

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Basic layer
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |   \    |   !  |   "  |   @  |   $  |   %  |   <  |           |  >   |   &  |   {  |   (  |   )  |   }  |   =    |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * | Del    |   P  |   H  |   R  |   K  |  TAB |  L1  |           |  TX  |   /  |   W  |   U  |   Y  |   B  |   Q    |
   * |--------+------+------+------+------+------|      |           | BOLT |------+------+------+------+------+--------|
   * |   Z    |   S  |   L  |N/SYMB|T/WIND|   V  |------|           |------|   G  |   A  |   I  |   O  |   E  |   C    |
   * |--------+------+------+------+------+------| DOWN |           |  UP  |------+------+------+------+------+--------|
   * | LShift |   X  |   D  |M/MDIA|   J  |   F  |      |           |      |   Ö  |   Ä  |   M  |   ,  |   .  | -      |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |Grv/L1|CoSTab|CtlTab| Left | Right|                                       |  ?   |Alttab|   |  |   ¨  | ~L1  |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
   *                                 ,------|------|------|       |------+--------+------.
   *                                 |Ctrl /|      | Home |       | PgUp |        |      |
   *                                 |Esc   |Backsp|------|       |------|  Back- |Space |
   *                                 |      |ace   | '/ALT|       |  _   |  Space |      |
   *                                 `--------------------'       `----------------------'
   */
  [BASE] = KEYMAP(  // layer 0 : default
                  // left hand
                  NO_BSLS, DE_EXLM, NO_QUO2, NO_AT, NO_DLR, DE_PERC, NO_LESS,
                  KC_DELT, KC_P,        KC_H,      KC_R,          KC_K,    KC_TAB,    MO(SYMB),
                  KC_Z, KC_S,        KC_L, LT(SYMB, KC_N), LT(WNDOW, KC_T),    KC_V,
                  KC_LSFT, KC_X, KC_D, LT(MDIA, KC_M), KC_J, KC_F, KC_DOWN,
                  TG(MDIA), LCTL(LSFT(KC_TAB)), LCTL(KC_TAB), KC_LEFT, KC_RGHT,

                  // left thumb cluster
                  // two top keys
                  ALT_T(KC_APP),  KC_LGUI,
                  // left small middle key
                  KC_HOME,
                  // two big keys
                  CTL_T(KC_ESCAPE),KC_ENTER,
                  // left small bottom key
                  ALT_T(NO_APOS),

                  // right hand
                  NO_GRTR, NO_AMPR, DE_LCBR, NO_LPRN, NO_RPRN, DE_RCBR, NO_EQL,
                  TG(PLOVER),  KC_AMPR,   KC_W,   KC_U,   KC_Y,   KC_B, KC_Q,
                  KC_G,   KC_A,   KC_I,   KC_O,   KC_E, KC_C,
                  KC_UP, DE_OE, DE_AE, KC_COMMA, KC_DOT, NO_MINS, MO(SYMB),
                  DE_QST, LALT(KC_TAB), DE_PIPE,KC_RBRC, TG(KEYLOCK),

                  // right thumb cluster
                  // two top small keys
                  KC_LALT,        CTL_T(KC_ESC),
                  // right middle and bottom small keys
                  KC_PGUP, NO_UNDS,
                  // right big keys
                  KC_BSPACE, KC_SPACE),
  /* Keymap 1: Symbol Layer
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |Version |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |        |      |      |      |      |   <  |(base)|           |      |   >  |   7  |   8  |   9  |   *  |   F12  |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |   #  |   $  |   €  |   *  |   `  |------|           |------|      |   4  |   5  |   6  |   +  |        |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  | (base) |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |      |      |      |      |      |                                       |   0  |    . |      |   =  |      |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        |      |      |       | vol- | vol- |
   *                                 ,------|------|------|       |------+------+------.
   *                                 |      |      |      |       | mute |      |      |
   *                                 |      |      |------|       |------|      |      |
   *                                 |      |      |      |       |      |      |      |
   *                                 `--------------------'       `--------------------'
   */
  // SYMBOLS
  [SYMB] = KEYMAP(
                  // left hand
                  M(0),   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  ____,
                  ____,____,____, ____,____,DE_LESS,____,
                  ____,KC_HASH,NO_DLR, NO_EURO,NO_ASTR,NO_GRV,
                  ____,DE_PERC,NO_CIRC,DE_LBRC,DE_RBRC,DE_TILD,____,
                  ____,____,____,____,____,
                  ____,____,
                  ____,
                  ____,____,____,
                  // right hand
                  ____, KC_F6,  KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
                  ____, DE_MORE,KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                  ____, KC_4,   KC_5,    KC_6,    NO_PLUS, ____,
                  ____, NO_AMPR, KC_1,   KC_2,    KC_3,    NO_BSLS, ____,
                  KC_0,   KC_DOT,  ____, NO_EQL,  ____,
                  KC_VOLD, KC_VOLU,
                  KC_MUTE,
                  ____, ____, ____
                  ),
  /* Keymap 2: Media and mouse keys
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |        |      |      |      | VI $ |      |      |           |      |      |      |      |      |      |        |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |           |      |      | Vi W |      |      | Vi B |        |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |------|           |------|      | Left | Down | Up   | Right|  Play  |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |           |      |      | Back | Fwd  |      |      |        |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        |      |      |       |      |      |
   *                                 ,------|------|------|       |------+------+------.
   *                                 |      |      |      |       |      |      |      |
   *                                 |      |      |------|       |------|      |      |
   *                                 |      |      |      |       | VI _ |      |      |
   *                                 `--------------------'       `--------------------'
   */
  // MEDIA AND MOUSE
  [MDIA] = KEYMAP(
                  RESET,   ____, ____, ____, KC_END, ____, ____,
                  ____, ____, ____, ____, ____, ____, ____,
                  ____, ____, ____, ____, ____, ____,
                  ____, ____, ____, ____, ____, ____, ____,
                  ____, ____, ____, ____, ____,
                  ____, ____,
                  ____,
                  ____, ____, ____,
                  // right hand
                  ____,  ____, ____, ____, ____, ____, ____,
                  ____,  ____, LCTL(KC_RIGHT), ____, ____, LCTL(KC_LEFT), ____,
                  ____, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_MPLY,
                  ____,  ____, KC_WBAK, KC_WFWD, ____, ____, ____,
                  KC_VOLU, KC_VOLD, KC_MUTE, ____, ____,
                  ____, ____,
                  ____,
                  KC_HOME, ____, ____
                  ),

/* Keymap 3: Plover keyboard (QWERTY)
 * (this requires no configuration in plover to get working)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | BKSPC  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   5  |   6  |   7  |   8  |   9  |   0    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  | T (*)|------|           |------|   T  |   Y  |   U  |   I  |   O  |   P    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   T  |      |           |      |   T  |   H  |   J  |   K  |   L  |   ;    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |   C  |   V  |------|       |------|   N  |   M  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
  [PLOVER] = KEYMAP(
       KC_BSPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO,
       KC_NO, KC_Q, KC_W, KC_E, KC_R, KC_T,
       KC_NO, KC_A, KC_S, KC_D, KC_F, KC_T, KC_NO,
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                           KC_NO,   KC_NO,
                                                    KC_NO,
                                        KC_C, KC_V, KC_NO,
    // right hand
       KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       ____, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
              KC_T, KC_U, KC_I, KC_O, KC_P, KC_LBRC,
       KC_NO, KC_T, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_NO, KC_NO,
       KC_NO,
       KC_NO, KC_N, KC_M),

  [KEYLOCK] = KEYMAP(KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,
                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,
                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                     KC_NO,   KC_NO,
                     KC_NO,
                     KC_NO, KC_NO,   KC_NO,
                     // right hand
                     TG(BASE), KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                     KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
                     KC_NO,   KC_NO,
                     KC_NO,
                     KC_NO, KC_NO, KC_NO),


  /* Keymap 5: Window management
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |           |      |      | TO 1 | TO 2 | TO 3 | TO 4 |        |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |------|           |------|      | WS 1 | WS 2 | WS 3 | WS 4 |        |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |           |      |      |SPLIT←|SPLIT→|MONTR←|MONTR→|        |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |      |      |      |      |      |                                       |      |      |      |      |      |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        |      |      |       |      |      |
   *                                 ,------|------|------|       |------+------+------.
   *                                 |      |      |      |       |      |      |Cycle |
   *                                 |      |      |------|       |------|      |Window|
   *                                 |      |      |      |       |      |      |     s|
   *                                 `--------------------'       `--------------------'
  */
  [WNDOW] =
  KEYMAP(KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,
         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         KC_NO,   KC_NO,
         KC_NO,
         KC_NO, KC_NO,   KC_NO,
         // right hand
         KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
         // move window to workspace
         KC_NO, KC_NO, LSFT(LGUI(KC_1)), LSFT(LGUI(KC_2)), LSFT(LGUI(KC_3)), LSFT(LGUI(KC_4)), KC_NO,
         // go to workspace
         KC_NO, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), KC_NO,
         // miscellaneous window actions
         KC_NO, KC_NO, LGUI(KC_LEFT), LGUI(KC_RIGHT), LGUI(LSFT(KC_LEFT)), LGUI(LSFT(KC_RIGHT)), KC_NO,
         KC_NO, KC_NO,   KC_NO,   KC_NO, KC_NO,
         KC_NO, KC_NO,
         KC_NO,
         KC_NO, KC_NO, LALT(LSFT(KC_TAB)))};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  switch (layer) {
    // TODO: Make this relevant to the ErgoDox EZ.
  case 1:
    ergodox_right_led_1_on();
    break;
  case 2:
    ergodox_right_led_2_on();
    break;
  case 3:
    ergodox_right_led_3_on();
    break;
  case 4:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    break;
  case 5:
    ergodox_right_led_1_on();
    ergodox_right_led_3_on();
    break;
  default:
    // none
    break;
  }

};
