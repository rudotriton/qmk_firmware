#include "layer_hold_actions.h"

void default_hold_actions(int key_idx, bool release) {
    if (release) return;
    switch (key_idx) {
        case 1:
            tap_code16(G(KC_S)); // shuffle
            break;
        case 3:
            tap_code16(G(KC_R)); // repeat
            break;
        case 6:
            l_eight_lock = false;
            layer_move(_MUSIC);
            break;
    }
}

void layer_one_hold_actions(int key_idx, bool release) {
    switch (key_idx) {
        case 6:
            if (!release) {
                to_move_win = true;
            } else {
                to_move_win = false;
            }
            break;
    }
}

void layer_three_hold_actions(int key_idx, bool release) {
    switch (key_idx) {
        case 1:
            if (!release) {
                register_code(KC_LSHIFT);
            } else {
                unregister_code(KC_LSHIFT);
            }
            break;
        case 4:
            if (!release) {
                register_code(KC_LCTL);
            } else {
                unregister_code(KC_LCTL);
            }
            break;
        case 5:
            if (!release) {
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
            }
            break;
        case 6:
            if (!release) {
                register_code(KC_LCMD);
            } else {
                unregister_code(KC_LCMD);
            }
            break;
    }
}

void layer_eight_hold_actions(int key_idx, bool release) {
    if (release && (key_idx == 6 || key_idx == 4) && !l_eight_lock)
        layer_move(_DEFAULT);
    if (release) return;
    switch (key_idx) {
        case 1:
            tap_code(KC_MPRV);
            break;
        case 2:
            tap_code(KC_MPLY);
            break;
        case 3:
            tap_code(KC_MNXT);
            break;
        case 5:
            tap_code(KC_MUTE);
            break;
        case 6:
            tap_code16(G(S(KC_RBRC))); // open spotify w/ BTT
            break;
    }
}

void (*layer_hold_actions[9]) (int, bool) = {
    default_hold_actions,
    layer_one_hold_actions,
    layer_two_actions,
    layer_three_hold_actions,
    layer_four_actions,
    layer_five_actions,
    layer_six_actions,
    layer_seven_actions,
    layer_eight_hold_actions
};
