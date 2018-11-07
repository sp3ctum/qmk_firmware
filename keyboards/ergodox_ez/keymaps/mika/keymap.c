#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "sendchar.h"
#include "virtser.h"

/* https://github.com/qmk/qmk_firmware/commit/a25dbaad327f834dad6fb572b074bab7be1e1d0f */
#define NO_ASTR LSFT(KC_BSLS)  // *

// easy access to symbols that actually work when the system keyboard is Finnish
#include "keymap_nordic.h"
#include "keymap_german.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define TXBOLT 3 // TxBolt Steno Virtual Serial
#define KEYLOCK 4 // key lock layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Basic layer
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |   \    |   !  |   "  |   @  |   $  |   %  |   <  |           |  >   |   &  |   {  |   (  |   )  |   }  |   =    |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * | Del    |   P  |   H  |   R  |   K  |  TAB |  L1  |           |  TX  |   /  |   W  |   U  |   Y  |   B  |   Q    |
   * |--------+------+------+------+------+------|      |           | BOLT |------+------+------+------+------+--------|
   * |   Z    |   S  |   L  |   N  |   T  |   V  |------|           |------|   G  |   A  |   I  |   O  |   E  |   C    |
   * |--------+------+------+------+------+------| DOWN |           |  UP  |------+------+------+------+------+--------|
   * | LShift |   X  |   D  |   M  |   J  |   F  |      |           |      |   Ö  |   Ä  |   M  |   ,  |   .  | -      |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  ?   | Down |   |  |   ¨  | ~L1  |
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
                  KC_Z, KC_S,        KC_L,      KC_N,          KC_T,    KC_V,
                  KC_LSFT, KC_X, KC_D,      KC_M,          KC_J,    KC_F,    KC_DOWN,
                  TG(MDIA), KC_QUOT, LALT(KC_LSFT), KC_LEFT, KC_RGHT,

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
                  NO_GRTR, NO_AMPR, DE_LCBR, NO_LPRN, NO_RPRN, DE_RCBR,             NO_EQL,
                  TG(TXBOLT),  KC_AMPR,   KC_W,   KC_U,   KC_Y,   KC_B,             KC_Q,
                  KC_G,   KC_A,   KC_I,   KC_O,   KC_E, KC_C,
                  KC_UP, DE_OE, DE_AE, KC_COMMA, KC_DOT, NO_MINS, MO(SYMB),
                  DE_QST,  KC_DOWN, DE_PIPE,KC_RBRC, TG(KEYLOCK),

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
   * |        |   !  |   @  |   {  |   }  |   |  |(base)|           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |   #  |   $  |   €  |   *  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
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
                  M(0),   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
                  KC_TRNS,DE_EXLM,NO_AT,  NO_LCBR,NO_RCBR,NO_PIPE,KC_TRNS,
                  KC_TRNS,KC_HASH,NO_DLR, NO_EURO,NO_ASTR,NO_GRV,
                  KC_TRNS,DE_PERC,NO_CIRC,DE_LBRC,DE_RBRC,DE_TILD,KC_TRNS,
                  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                  KC_TRNS,KC_TRNS,
                  KC_TRNS,
                  KC_TRNS,KC_TRNS,KC_TRNS,
                  // right hand
                  KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
                  KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                  KC_DOWN, KC_4,   KC_5,    KC_6,    NO_PLUS, KC_TRNS,
                  KC_TRNS, NO_AMPR, KC_1,   KC_2,    KC_3,    NO_BSLS, KC_TRNS,
                  KC_0,   KC_DOT,  KC_TRNS, NO_EQL,  KC_TRNS,
                  KC_VOLD, KC_VOLU,
                  KC_MUTE,
                  KC_TRNS, KC_TRNS, KC_TRNS
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
   *                                 |      |      |      |       |      |      |Brwser|
   *                                 |      |      |------|       |------|      |Back  |
   *                                 |      |      |      |       | VI _ |      |      |
   *                                 `--------------------'       `--------------------'
   */
  // MEDIA AND MOUSE
  [MDIA] = KEYMAP(
                  RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_END, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS,
                  KC_TRNS,
                  KC_TRNS, KC_TRNS, KC_TRNS,
                  // right hand
                  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_TRNS,  KC_TRNS, LCTL(KC_RIGHT), KC_TRNS, KC_TRNS, LCTL(KC_LEFT), KC_TRNS,
                  KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_MPLY,
                  KC_TRNS,  KC_TRNS, KC_WBAK, KC_WFWD, KC_TRNS, KC_TRNS, KC_TRNS,
                  KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
                  KC_TRNS, KC_TRNS,
                  KC_TRNS,
                  KC_HOME, KC_TRNS, KC_WBAK
                  ),
  // TxBolt Codes
#define Sl 0b00000001
#define Tl 0b00000010
#define Kl 0b00000100
#define Pl 0b00001000
#define Wl 0b00010000
#define Hl 0b00100000
#define Rl 0b01000001
#define Al 0b01000010
#define Ol 0b01000100
#define X  0b01001000
#define Er 0b01010000
#define Ur 0b01100000
#define Fr 0b10000001
#define Rr 0b10000010
#define Pr 0b10000100
#define Br 0b10001000
#define Lr 0b10010000
#define Gr 0b10100000
#define Tr 0b11000001
#define Sr 0b11000010
#define Dr 0b11000100
#define Zr 0b11001000
#define NM 0b11010000
#define GRPMASK 0b11000000
#define GRP0 0b00000000
#define GRP1 0b01000000
#define GRP2 0b10000000
#define GRP3 0b11000000
/* Keymap 3: TxBolt (Serial)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | BKSPC  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   #  |   #  |   #  |   #  |   #  |      |           |      |   #  |   #  |   #  |   #  |   #  |   #    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   S  |   T  |   P  |   H  |   *  |------|           |------|   *  |   F  |   P  |   L  |   T  |   D    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   S  |   K  |   W  |   R  |   *  |      |           |      |   *  |   R  |   B  |   G  |   S  |   Z    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |   A  |   O  |------|       |------|   E  |   U  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// TxBolt over Serial
[TXBOLT] = KEYMAP(
       KC_BSPC, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
       KC_NO,   M(NM),   M(NM),   M(NM),   M(NM),   M(NM),  KC_NO,  
       KC_NO,   M(Sl),   M(Tl),   M(Pl),   M(Hl),   M(X),
       KC_NO,   M(Sl),   M(Kl),   M(Wl),   M(Rl),   M(X),   KC_NO,
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                                           KC_NO,   KC_NO,  
                                                    KC_NO,  
                                  M(Al),   M(Ol),   KC_NO,  
    // right hand
       KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
       KC_TRNS,  M(NM),   M(NM),   M(NM),   M(NM),   M(NM),   M(NM),
                 M(X),    M(Fr),   M(Pr),   M(Lr),   M(Tr),   M(Dr),
       KC_NO,    M(X),    M(Rr),   M(Br),   M(Gr),   M(Sr),   M(Zr),
                          KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  
       KC_NO,   KC_NO,  
       KC_NO,  
       KC_NO,   M(Er),   M(Ur)),

  [KEYLOCK] = KEYMAP(KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
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
                     KC_NO, KC_NO, KC_NO)};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

uint8_t chord[4] = {0,0,0,0};
uint8_t pressed_count = 0;

void send_chord(void)
{
  for(uint8_t i = 0; i < 4; i++)
  {
    if(chord[i])
      virtser_send(chord[i]);
  }
  virtser_send(0);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  // We need to track keypresses in all modes, in case the user
  // changes mode whilst pressing other keys.
  if (record->event.pressed)
    pressed_count++;
  else
    pressed_count--;
  return true;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function

  if (record->event.pressed) {
    uint8_t grp = (id & GRPMASK) >> 6;
    chord[grp] |= id;
  }
  else {
    if (pressed_count == 0) {
      send_chord();
      chord[0] = chord[1] = chord[2] = chord[3] = 0;
    }
  }
  return MACRO_NONE;
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
  case 4:
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
  default:
    // none
    break;
  }

};
