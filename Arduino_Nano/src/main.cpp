#include <FastLED.h>
#include <Arduino.h>
#include <EEPROM.h>
#include "effects.h"

#define touch 2
int EFFECT_ADDRESS = 0;

struct EffectsStatus EffectsStatus;

int effect_counter = 0;

int read_effect() {
  return EEPROM.read(EFFECT_ADDRESS);
}

void(* resetFunc) (void) = 0;

void is_disable(struct EffectsStatus *status) {
  delay(500);
  if (digitalRead(touch) == HIGH) {
    effect_counter = -1;
    which_effect(DISABLE_LAMP, status);
    delay(500);
  }
}

void pinTouch() {
  if (effect_counter == MAX_EFFECT) { effect_counter = -1; }
  write_effect(effect_counter + 1);
  effect_counter = read_effect();
  EffectsStatus.break_effect = true;
  EffectsStatus.current_effect = EffectsStatus.last_effect;
}

void setup() {
  Serial.begin(115200);
  pinMode(touch, INPUT);

  // Inicializa a EEPROM
  EEPROM.begin();

  attachInterrupt(digitalPinToInterrupt(touch), pinTouch, FALLING);

  effect_counter = read_effect();

  FastLED.addLeds<WS2812, PINO_FITA, GRB>(fita, NUM_LEDS_FITA);
  FastLED.setBrightness(255);

  delay(800);
  if (digitalRead(touch) == HIGH) {
    Serial.println("Restart Wifi Config");
    write_effect(DISABLE_LAMP);
    resetFunc();
  }
}

void loop() {
  if (EffectsStatus.current_effect == EffectsStatus.last_effect) {
    Serial.println("Change effect");
    EffectsStatus.current_effect = !EffectsStatus.last_effect;
    EffectsStatus.break_effect = false;

    is_disable(&EffectsStatus);
    which_effect(effect_counter, &EffectsStatus);
    Serial.println(effect_counter);
  }
}
