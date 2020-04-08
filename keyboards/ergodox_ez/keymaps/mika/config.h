#define FORCE_NKRO
#define MOUSEKEY_WHEEL_INTERVAL 90
#define MOUSEKEY_WHEEL_TIME_TO_MAX 5

#define TAPPING_TERM 200

#define TAP(keycode) register_code16(keycode); unregister_code16(keycode)

#define TAP_WITH_MOD(mod, key)                  \
    register_code(mod);                         \
    register_code(key);                         \
    unregister_code(key);                       \
    unregister_code(mod)
