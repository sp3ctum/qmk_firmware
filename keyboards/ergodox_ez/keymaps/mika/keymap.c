#include QMK_KEYBOARD_H
#include "version.h"

/* https://github.com/qmk/qmk_firmware/commit/a25dbaad327f834dad6fb572b074bab7be1e1d0f */
#define NO_ASTR LSFT(KC_BSLS)  // *
#define ____ KC_TRNS

// easy access to symbols that actually work when the system keyboard is Finnish
#include "keymap_nordic.h"
#include "keymap_german.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define KEYLOCK 4 // key lock layer
#define WNDOW 5 // window management in Fedora Linux
#define LINUXMOUSE 6 // mouse emulation in linux with the numpad

// Tap Dance Declarations
enum {
      ESC_ALTF4 = 0, // Single tap = ESCAPE; Triple tap = ALT+F4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Basic layer
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |   \    |   !  |   "  |   @  |   $  |   %  |   <  |           |  >   |   &  |   {  |   (  |   )  |   }  |   =    |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * | Del    |   P  |   H  |   R  |   K  |  TAB |Xmouse|           |      |   /  |   W  |   U  |   Y  |   B  |   Q    |
   * |--------+------+------+------+------+------|layer |           |      |------+------+------+------+------+--------|
   * |   Z    |   S  |   L  |N/SYMB|T/WIND|   V  |------|           |------|   G  |   A  |   I  |   O  |   E  |   C    |
   * |--------+------+------+------+------+------| DOWN |           |  UP  |------+------+------+------+------+--------|
   * | LShift |   X  |   D  |M/MDIA|   J  |   F  |      |           |      |   Ö  |   Ä  |   M  |   ,  |   .  | -      |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |T_SYMB|CoSTab|CtlTab| Left | Right|                                       |  ?   |Alttab|   |  |   ¨  | ~L1  |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
   *                                 ,------|------|------|       |------+--------+------.
   *                                 |Ctrl /|      | Home |       | PgUp | Shift/ |      |
   *                                 |Esc   |Enter |------|       |------|  Back- |Space |
   *                                 |      |      | '/ALT|       |  _   |  Space |      |
   *                                 `--------------------'       `----------------------'
   */
  [BASE] = LAYOUT_ergodox(  // layer 0 : default
                  // left hand
                  NO_BSLS,  DE_EXLM,            NO_QUO2,      NO_AT,   NO_DLR,  DE_PERC,  NO_LESS,
                  KC_DELT,  KC_P,               KC_H,         KC_R,    KC_K,    KC_TAB,   TG(LINUXMOUSE),
                  KC_Z,     KC_S,               KC_L,         LT(SYMB, KC_N),   LT(WNDOW, KC_T),          KC_V,
                  KC_LSFT,  KC_X,               KC_D,         LT(MDIA, KC_M),   KC_J,     KC_F,           KC_DOWN,
                  TG(SYMB), LCTL(LSFT(KC_TAB)), LCTL(KC_TAB), KC_LEFT, KC_RGHT,

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
                  NO_GRTR,       NO_AMPR,      DE_LCBR, NO_LPRN,  NO_RPRN,     DE_RCBR, NO_EQL,
                  TD(ESC_ALTF4), KC_AMPR,      KC_W,    KC_U,     KC_Y,        KC_B,    KC_Q,
                  KC_G,          KC_A,         KC_I,    KC_O,     KC_E,        KC_C,
                  KC_UP,         DE_OE,        DE_AE,   KC_COMMA, KC_DOT,      NO_MINS, MO(SYMB),
                  DE_QST,        LALT(KC_TAB), DE_PIPE, KC_RBRC,  TG(KEYLOCK),

                  // right thumb cluster
                  // two top small keys
                  KC_LALT,        CTL_T(KC_ESC),
                  // right middle and bottom small keys
                  KC_PGUP, NO_UNDS,
                  // right big keys
                  SFT_T(KC_BSPACE), KC_SPACE),
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
  [SYMB] = LAYOUT_ergodox(
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
   * |        |      |      |      |scrsht|      |      |           |      |      | Back | Fwd  |      |      |        |
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
  [MDIA] = LAYOUT_ergodox(
                  RESET,   ____, ____, ____, KC_END, ____, ____,
                  ____, ____, ____, ____, ____, ____, ____,
                  ____, ____, ____, ____, ____, ____,
                  ____, ____, ____, ____, LCTL(LSFT(KC_PSCREEN)), ____, ____,
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
  [KEYLOCK] = LAYOUT_ergodox(KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,
                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,
                     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                     KC_NO,   KC_NO,
                     KC_NO,
                     KC_NO, KC_NO,   KC_NO,
                     // right hand
                     TO(BASE), KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
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
  LAYOUT_ergodox(KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
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
         KC_NO, KC_NO, LALT(LSFT(KC_TAB))),

  /* Keymap 6: mouse emulation
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |back  |           |      |      |  ↖   |  ↗   |      |      |        |
   * |--------+------+------+------+------+------|layer1|           |      |------+------+------+------+------+--------|
   * |        |      |      |      |      | key ↑|------|           |------| key ↓|  ←   |  ↓   |  ↑   |  →   |        |
   * |--------+------+------+------+------+------|scroll|           |scroll|------+------+------+------+------+--------|
   * |        |      |      |      |      |scrLft| down |           |  up  |scrRgt|  ↙   |  ↘   |      |      |        |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |      |      |      |      |      |                                       |      |      |      |      |      |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        |      |      |       |      |      |
   *                                 ,------|------|------|       |------+------+------.
   *                                 |      |      |      |       |      |click |click |
   *                                 | esc  |  ⏎   |------|       |------| rmb  | lmb  |
   *                                 |      |      |      |       |middle|      |      |
   *                                 `--------------------'       `--------------------'
   */
  [LINUXMOUSE] =
  LAYOUT_ergodox(
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(BASE),
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_D,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_WH_L, KC_DOWN,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,
                 KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS,
                 // right hand
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_KP_7, KC_KP_9, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_WH_U, KC_KP_4, KC_KP_2, KC_KP_8, KC_KP_6, KC_TRNS,
                 KC_UP,   KC_WH_R, KC_KP_1, KC_KP_3, KC_TRNS, NO_BSLS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,
                 KC_TRNS,
                 KC_BTN3, KC_BTN2, KC_BTN1
         )
};

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
  case LINUXMOUSE:
    ergodox_right_led_1_on();

  default:
    // none
    break;
  }

};


void escape_and_altf4_tapdance(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        TAP(KC_ESC);
    }
    else if (state->count == 3) {
        TAP_WITH_MOD(KC_LALT, KC_F4);
    }
}

qk_tap_dance_action_t tap_dance_actions[] =
    {
     [ESC_ALTF4] = ACTION_TAP_DANCE_FN(escape_and_altf4_tapdance)
    };
