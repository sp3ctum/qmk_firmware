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
#define TXBOLT 3 // TxBolt Steno Virtual Serial
#define KEYLOCK 4 // key lock layer
#define WNDOW 5 // window management in Fedora Linux
#define LINUXMOUSE 6 // mouse emulation in linux with the numpad

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap 0: Basic layer
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |   \    |   !  |   "  |   @  |   $  |   %  |   <  |           |  >   |   &  |   {  |   (  |   )  |   }  |   =    |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * | Del    |   P  |   H  |   R  |   K  |  TAB |Xmouse|           |  TX  |   /  |   W  |   U  |   Y  |   B  |   Q    |
   * |--------+------+------+------+------+------|layer |           | BOLT |------+------+------+------+------+--------|
   * |   Z    |   S  |   L  |N/SYMB|T/WIND|   V  |------|           |------|   G  |   A  |   I  |   O  |   E  |   C    |
   * |--------+------+------+------+------+------| DOWN |           |  UP  |------+------+------+------+------+--------|
   * | LShift |   X  |   D  |M/MDIA|   J  |   F  |      |           |      |   Ö  |   Ä  |   M  |   ,  |   .  | -      |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |T_SYMB|CoSTab|CtlTab| Left | Right|                                       |  ?   |Alttab|   |  |   ¨  | ~L1  |
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
                  KC_DELT, KC_P,        KC_H,      KC_R,          KC_K,    KC_TAB, TG(LINUXMOUSE),
                  KC_Z, KC_S,        KC_L, LT(SYMB, KC_N), LT(WNDOW, KC_T),    KC_V,
                  KC_LSFT, KC_X, KC_D, LT(MDIA, KC_M), KC_J, KC_F, KC_DOWN,
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
                  NO_GRTR, NO_AMPR, DE_LCBR, NO_LPRN, NO_RPRN, DE_RCBR, NO_EQL,
                  TG(TXBOLT),  KC_AMPR,   KC_W,   KC_U,   KC_Y,   KC_B, KC_Q,
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
  [MDIA] = KEYMAP(
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
       ____,  M(NM),   M(NM),   M(NM),   M(NM),   M(NM),   M(NM),
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
         KC_NO, KC_NO, LALT(LSFT(KC_TAB))),

  /* Keymap 6: linux mouse emulation
   *
   * ,--------------------------------------------------.           ,--------------------------------------------------.
   * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
   * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |back  |           |      |      |  7   |  8   |  9   |      |        |
   * |--------+------+------+------+------+------|layer1|           |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |------|           |------|      |  4   |drag  |  6   |      |        |
   * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |           |      |      |  1   |  2   |  3   |      |        |
   * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
   *   |      |      |      |      |      |                                       |      |      |      |      |      |
   *   `----------------------------------'                                       `----------------------------------'
   *                                        ,-------------.       ,-------------.
   *                                        |      |      |       |      |      |
   *                                 ,------|------|------|       |------+------+------.
   *                                 |      |      |      |       |      |click |click |
   *                                 |      |      |------|       |------| rmb  | lmb  |
   *                                 |      |      |      |       |      |      |      |
   *                                 `--------------------'       `--------------------'
   */
  [LINUXMOUSE] =
  KEYMAP(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(BASE),
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_NO, KC_NO,
         KC_NO,
         KC_NO, KC_NO, KC_NO,
         // right hand
         // right hand
         KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO,
         KC_NO, KC_NO, KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_NO,   KC_NO,
         KC_NO, KC_KP_4,  KC_KP_0,  KC_KP_6,  KC_NO, KC_NO,
         KC_NO, KC_NO, KC_KP_1,  KC_KP_2,  KC_KP_3,  NO_BSLS, KC_NO,
         KC_KP_0,  KC_NO, KC_NO, KC_NO, KC_NO,
         KC_NO, KC_NO,
         KC_NO,
         KC_NO, KC_APP, KC_KP_5
         )
};

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
