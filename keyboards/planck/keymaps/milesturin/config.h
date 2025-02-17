#pragma once

#ifdef AUDIO_ENABLE
#    define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

#define ENCODER_RESOLUTION 4
#define ENCODER_DIRECTION_FLIP

#define ENCODERS_PAD_A { B12 }
#define ENCODERS_PAD_B { B13 }

#define ENABLE_RGB_MATRIX_SOLID_COLOR
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_WAVE
