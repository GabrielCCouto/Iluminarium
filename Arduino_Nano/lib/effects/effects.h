#ifndef __effects__
#define __effects__

#pragma once

#include <FastLED.h>

#define PINO_FITA 11
#define NUM_LEDS_FITA 24

/* Static Colors*/
#define DISABLE_LAMP 0
#define COLOR_RED 1
#define COLOR_BLUE 2
#define COLOR_GREEN 3
#define COLOR_WHITE 4
#define COLOR_ORANGE_RED 5
#define COLOR_YELLOW 6
#define COLOR_DARK_VAIOLET 7
#define COLOR_CYAN 8

/* Gradient wave colors*/
#define GRADIENT_FIRE_ICE 9
#define GRADIENT_HEAT_MAP 10
#define GRADIENT_PURPLE 11
#define GRADIENT_BLUE_GREEN 12
#define GRADIENT_SUNSET 13

/* Circular Gradient colors*/
#define CIRCULAR_GRADIENT_FIRE_ICE 14
#define CIRCULAR_GRADIENT_HEAT_MAP 15
#define CIRCULAR_GRADIENT_PURPLE 16
#define CIRCULAR_GRADIENT_BLUE_GREEN 17
#define CIRCULAR_GRADIENT_SUNSET 18

/* Random effects */
#define EXPLOSION 19
#define HELICOPTER 20
#define BREATHING 21

/* Rainbows */
#define RAINBOW 22
#define CIRCULAR_RAINBOW 23

#define MAX_EFFECT 23

inline CRGB fita[NUM_LEDS_FITA];

struct EffectsStatus
{
    bool break_effect = false;
    const bool last_effect = false;
    bool current_effect = false;
};

void colorLightChanged(uint8_t brightness, uint32_t rgb);

int read_effect();
void write_effect(int value);
void which_effect(int effect_counter, struct EffectsStatus *status);

void fillSolidColor(CRGB selcor);

void gradienteOndas(int selPalette, struct EffectsStatus *status);
void circular_gradient(int selPalette ,struct EffectsStatus *status);

void rainbow(struct EffectsStatus *status);
void circular_rainbow(struct EffectsStatus *status);

void explosion(struct EffectsStatus *status);
void helicopter(struct EffectsStatus *status);
void breathing(struct EffectsStatus *status);

// Effect WiFi config
void searching_network();
void network_connected();

// Maybe not use
void PixelsAleatorios(struct EffectsStatus *status);
void bolasColoridas(struct EffectsStatus *status);
void cometa(struct EffectsStatus *status);

#endif