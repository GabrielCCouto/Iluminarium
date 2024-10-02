#include "effects.h"
#include <EEPROM.h>

#define NUM_PALETTES 11

extern int EFFECT_ADDRESS;

uint16_t breatheLevel = 0;
uint8_t palleteIndex = 0;


void write_effect(int value) {
  for (unsigned int i = 0; i < sizeof(value); i++) {
    EEPROM.write(EFFECT_ADDRESS + i, (value >> (i * 8)) & 0xFF);
  }
}


// int read_effect() {
//   File file = SPIFFS.open("/data.txt", "r");
//   if (!file) {
//     Serial.println("Failed to open file for reading");
//     return 0;
//   }

//   String valueString = file.readStringUntil('\n');

//   file.close();

//   return valueString.toInt();
// }

// void write_effect(int value) {
//   File file = SPIFFS.open("/data.txt", "w");
//   if (!file) {
//     Serial.println("Failed to open file for writing");
//     return;
//   }

//   String valueString = String(value);

//   file.println(valueString);

//   file.close();
// }

void which_effect(int effect_counter, struct EffectsStatus *status) {

  // Set Static Colors
  if (effect_counter >= 0 && effect_counter <=8) {
    switch (effect_counter) {
      case DISABLE_LAMP:
        fillSolidColor(CRGB::Black);
        break;
      case COLOR_RED:
        fillSolidColor(CRGB::Red);
        break;
      case COLOR_BLUE:
        fillSolidColor(CRGB::Blue);
        break;
      case COLOR_GREEN:
        fillSolidColor(CRGB::Green);
        break;
      case COLOR_WHITE:
        fillSolidColor(CRGB::White);
        break;
      case COLOR_ORANGE_RED:
        fillSolidColor(CRGB::OrangeRed);
        break;
      case COLOR_YELLOW:
        fillSolidColor(CRGB::Yellow);
        break;
      case COLOR_DARK_VAIOLET:
        fillSolidColor(CRGB::DarkViolet);
        break;
      case COLOR_CYAN:
        fillSolidColor(CRGB::Cyan);
        break;
      default:
        fillSolidColor(CRGB::Black);
        write_effect(0);
        break;
    }
  }

  // Set Color Effect wave Gradient
  if (effect_counter >= 9 && effect_counter <= 13)
  {
    switch (effect_counter) {
      case GRADIENT_FIRE_ICE:
        gradienteOndas(1, status);
        break;
      case GRADIENT_HEAT_MAP:
        gradienteOndas(3, status);
        break;
      case GRADIENT_PURPLE:
        gradienteOndas(6, status);
        break;
      case GRADIENT_BLUE_GREEN:
        gradienteOndas(4, status);
        break;
      case GRADIENT_SUNSET:
        gradienteOndas(5, status);
        break;
      default:
        fillSolidColor(CRGB::Black);
        write_effect(0);
        break;
    }
  }

  // Set Color Effect wave Gradient
  if (effect_counter >= 14 && effect_counter <= 18)
  {
    switch (effect_counter) {
      case CIRCULAR_GRADIENT_FIRE_ICE:
        circular_gradient(1, status);
        break;
      case CIRCULAR_GRADIENT_HEAT_MAP:
        circular_gradient(3, status);
        break;
      case CIRCULAR_GRADIENT_PURPLE:
        circular_gradient(6, status);
        break;
      case CIRCULAR_GRADIENT_BLUE_GREEN:
        circular_gradient(4, status);
        break;
      case CIRCULAR_GRADIENT_SUNSET:
        circular_gradient(5, status);
        break;
      default:
        fillSolidColor(CRGB::Black);
        write_effect(0);
        break;
    }
  }

  // Random effects
  if (effect_counter >= 19 && effect_counter <= 21)
  {
    switch (effect_counter)
    {
    case EXPLOSION:
        explosion(status);
        break;
      case HELICOPTER:
        helicopter(status);
        break;
      case BREATHING:
        breathing(status);
        break;
      default:
        fillSolidColor(CRGB::Black);
        write_effect(0);
        break;
    }
  }

  if (effect_counter >= 22 && effect_counter <= 23)
  {
    switch (effect_counter)
    {
    case RAINBOW:
        rainbow(status);
        break;
      case CIRCULAR_RAINBOW:
        circular_rainbow(status);
        break;
      default:
        fillSolidColor(CRGB::Black);
        write_effect(0);
        break;
    }
  }
}

void fillSolidColor(CRGB selcor) {
  for (int i = 0; i < NUM_LEDS_FITA; i++)
  {
    fill_solid(fita, NUM_LEDS_FITA, selcor);
    FastLED.show();
  }
}

void colorLightChanged(uint8_t brightness, uint32_t rgb) {
  float r = ((rgb >> 16) & 0xFF);
  float g = ((rgb >>  8) & 0xFF);
  float b = (rgb & 0xFF);

  FastLED.setBrightness(brightness);

  bool cozy_white = false;
  if(r == 255 && b == 79 && g == 162) {
    cozy_white = true;
  }

  for (int i = 0; i < NUM_LEDS_FITA; i++)
  {
    if (cozy_white) {
      fill_solid(fita, NUM_LEDS_FITA, CRGB::OrangeRed);
    } else {
      fill_solid(fita, NUM_LEDS_FITA, CRGB(r,g,b));
    }
    FastLED.show();
  }
}

DEFINE_GRADIENT_PALETTE( fireandice_gp ) {
  0,  80,  2,  1,
  51, 206, 15,  1,
  101, 242, 34,  1,
  153,  16, 67, 128,
  204,   2, 21, 69,
  255,   1,  2,  4
};
CRGBPalette16 fireandicePalette = fireandice_gp;

DEFINE_GRADIENT_PALETTE( browngreen_gp ) {
  0,    6,  255,    0,     //green
  71,    0,  255,  153,     //bluegreen
  122,  200,  200,  200,     //gray
  181,  110,   61,    6,     //brown
  255,    6,  255,    0      //green
};
CRGBPalette16 brownGreenPalette = browngreen_gp;

DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
  0,      0,    0,    0,  // black
  128,  255,    0,    0,  // red
  200,  255,  255,    0,  // bright yellow
  255,  255,  255,  255,  // full white
};
CRGBPalette16 heatPalette = heatmap_gp;

DEFINE_GRADIENT_PALETTE( greenblue_gp ) {
  0,    0,    255,    245,
  46,   0,    21,     255,
  179,  12,   250,    0,
  255,  0,    255,    245
};
CRGBPalette16 greenbluePalette = greenblue_gp;

DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
  0,    120,   0,    0,
  22,   179,   22,   0,
  51,   255,   104,  0,
  85,   167,   22,   18,
  135,  100,   0,    103,
  198,  16,    0,    130,
  255,  0,     0,    160
};
CRGBPalette16 sunsetPalette = Sunset_Real_gp;

DEFINE_GRADIENT_PALETTE( bhw2_turq_gp ) {
  0,   1, 33, 95,
  38,   1, 107, 37,
  76,  42, 255, 45,
  127, 255, 255, 45,
  178,  42, 255, 45,
  216,   1, 107, 37,
  255,   1, 33, 95
};
CRGBPalette16 turqPalette = bhw2_turq_gp;

DEFINE_GRADIENT_PALETTE( autumnrose_gp ) {
  0,  71,  3,  1,
  45, 128,  5,  2,
  84, 186, 11,  3,
  127, 215, 27,  8,
  153, 224, 69, 13,
  188, 229, 84,  6,
  226, 242, 135, 17,
  255, 247, 161, 79
};
CRGBPalette16 autumnrosePalette = autumnrose_gp;

DEFINE_GRADIENT_PALETTE( bhw1_06_gp ) {
  0, 184,  1, 128,
  160,   1, 193, 182,
  219, 153, 227, 190,
  255, 255, 255, 255
};
CRGBPalette16 bhw1_06Palette = bhw1_06_gp;

DEFINE_GRADIENT_PALETTE( bhw2_xmas_gp ) {
  0,   0, 12,  0,
  40,   0, 55,  0,
  66,   1, 117,  2,
  77,   1, 84,  1,
  81,   0, 55,  0,
  119,   0, 12,  0,
  153,  42,  0,  0,
  181, 121,  0,  0,
  204, 255, 12,  8,
  224, 121,  0,  0,
  244,  42,  0,  0,
  255,  42,  0,  0
};
CRGBPalette16 xmasPalette = bhw2_xmas_gp;

DEFINE_GRADIENT_PALETTE( bhw1_justducky_gp ) {
  0,  47, 28,  2,
  76, 229, 73,  1,
  163, 255, 255,  0,
  255, 229, 73,  1
};
CRGBPalette16 justduckyPalette = bhw1_justducky_gp;


CRGBPalette16 purplePalette = CRGBPalette16 (
                                CRGB::DarkViolet,
                                CRGB::DarkViolet,
                                CRGB::DarkViolet,
                                CRGB::DarkViolet,

                                CRGB::Magenta,
                                CRGB::Magenta,
                                CRGB::Linen,
                                CRGB::Linen,

                                CRGB::Magenta,
                                CRGB::Magenta,
                                CRGB::DarkViolet,
                                CRGB::DarkViolet,

                                CRGB::DarkViolet,
                                CRGB::DarkViolet,
                                CRGB::Linen,
                                CRGB::Linen
                              );

CRGBPalette16 returnPalette(int selPalette) {
  switch (selPalette) {
    case 1:
      return fireandice_gp;
      break;
    case 2:
      return browngreen_gp;
      break;
    case 3:
      return heatmap_gp;
      break;
    case 4:
      return greenblue_gp;
      break;
    case 5:
      return Sunset_Real_gp;
      break;
    case 6:
      return purplePalette;
      break;
    case 7:
      return bhw2_turq_gp;
      break;
    case 8:
      return autumnrose_gp;
      break;
    case 9:
      return bhw1_06_gp;
      break;
    case 10:
      return bhw2_xmas_gp;
      break;
    case 11:
      return bhw1_justducky_gp;
      break;
    default:
      return fireandice_gp;
      break;
  }
}

void gradienteOndas(int selPalette, struct EffectsStatus *status) {
  CRGBPalette16 Palette = returnPalette(selPalette);
  int indexPal = 2;
  while (status->break_effect != true) {
    byte beatA = beatsin16(30, 0, 255);
    byte beatB = beatsin16(20, 0, 255);
    fill_palette(fita, NUM_LEDS_FITA, (beatA + beatB) / 2, indexPal, Palette, 255, LINEARBLEND);
    FastLED.show();
    delay(10);
    if(status->break_effect == true) {
      fillSolidColor(CRGB::Black);
      return;
    }
  }
}

void rainbow(struct EffectsStatus *status) {
  static uint8_t hue = 0;
  int dir1 = 0;
  int i1 = 0;

  while (status->break_effect != true)
  {
    fita[i1] = CHSV(hue++, 255, 255);
    FastLED.show();
    for (int i = 0; i < NUM_LEDS_FITA; i++) {
      fita[i].nscale8(250);
    }
    if (dir1 == 0) {
      i1++;
    } else {
      i1--;
    }
    if (i1 == NUM_LEDS_FITA) {
      dir1 = 1;
    } else if ( i1 == 0) {
      dir1 = 0;
    }
    delay(20);
    if(status->break_effect == true) {
      fillSolidColor(CRGB::Black);
      return;
    }
  }
  fillSolidColor(CRGB::Black);
}

void circular_rainbow(struct EffectsStatus *status) {
  static uint8_t hue = 0;
  int i1 = 0;

  while (status->break_effect != true) {
    fita[i1] = CHSV(hue++, 255, 255);

    FastLED.show();
    for (int i = 0; i < NUM_LEDS_FITA; i++) {
      fita[i].nscale8(250);
    }
    i1++;
    if (i1 == NUM_LEDS_FITA) {
      i1 = 0;
    }
    delay(40);
    if(status->break_effect == true) {
      fillSolidColor(CRGB::Black);
      return;
    }
  }
  fillSolidColor(CRGB::Black);
}

void cometa(struct EffectsStatus *status) {
  byte fade = 254;
  int random_color = random (50, 255);

  int cometaSize = 2;
  int iDirection = 1;
  int iPos = 0;

  while (status->break_effect != true) {
    iPos += iDirection;
    if (iPos == (NUM_LEDS_FITA - cometaSize) || iPos == 0)
      iDirection *= -1;

    for (int i = 0; i < cometaSize; i++)
      fita[iPos + i].setHue(random_color);

    // Randomly fade the LEDs
    for (int j = 0; j < NUM_LEDS_FITA; j++)
      if (random(10) > 5)
        fita[j] = fita[j].fadeToBlackBy(fade);
    delay(40);
    FastLED.show();
    if(status->break_effect == true) {
        fillSolidColor(CRGB::Black);
      return;
    }
  }
  fillSolidColor(CRGB::Black);
}

void breathing(struct EffectsStatus *status) {
  int random_color = random (15, 255);
  while (status->break_effect != true) {
    for (int i = 0; i < 100; i++) {
      breatheLevel = beatsin16(10, 0, 255);
      fill_solid(fita, NUM_LEDS_FITA, CHSV(random_color, 255, breatheLevel));
      FastLED.show();
      delay(10);
      if(status->break_effect == true) {
        fillSolidColor(CRGB::Black);
      return;
      }
    }
  }
}

void circular_gradient(int selPalette, struct EffectsStatus *status) {
  CRGBPalette16 palette = returnPalette(selPalette);
  while (status->break_effect != true) {
    fill_palette(fita, NUM_LEDS_FITA, palleteIndex, 255 / NUM_LEDS_FITA, palette, 255, LINEARBLEND);
    FastLED.show();
    palleteIndex++;
    delay(10);
  }
}

void searching_network() {
  CRGBPalette16 selPalette = returnPalette(4);
  for (int i = 0; i < 900; i++) {
    fill_palette(fita, NUM_LEDS_FITA, palleteIndex, 255 / NUM_LEDS_FITA, selPalette, 255, LINEARBLEND);
    FastLED.show();
    palleteIndex++;
    delay(10);
  }
  fillSolidColor(CRGB::OrangeRed);
}

void network_connected() {
  for (int i = 0; i < 2000; i++) {
    breatheLevel = beatsin16(20, 60, 255);
    fill_solid(fita, NUM_LEDS_FITA, CHSV(138, 255, breatheLevel));
    FastLED.show();
    delay(3);
  }
}

void PixelsAleatorios(struct EffectsStatus *status) {
  CRGBPalette16 selPalette = returnPalette(random(1, NUM_PALETTES + 1));
  while (status->break_effect != true) {
    for (int i = 0; i < 1000; i++) {
      if (i % 5 == 0) {
        fita[random16(0, NUM_LEDS_FITA - 1)] = ColorFromPalette(selPalette, random8(), 255, LINEARBLEND);
      }
      fadeToBlackBy(fita, NUM_LEDS_FITA, 1);
      FastLED.show();
      delay(10);
      if(status->break_effect == true) {
        fillSolidColor(CRGB::Black);
        return;
      }
    }
  }
}

void bolasColoridas(struct EffectsStatus *status) {
  byte dothue = 0;
  while (status->break_effect != true) {
    fadeToBlackBy( fita, NUM_LEDS_FITA, 20);

    for ( int i = 0; i < 8; i++) {
      fita[beatsin16( i + 7, 0, NUM_LEDS_FITA - 1 )] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }
    FastLED.show();
  }
}

void explosion(struct EffectsStatus *status) {
  FastLED.clear();
  byte fade = 128;
  int expSize = NUM_LEDS_FITA / 2;   // tamanho da explosao
  int numExplosoes = 4;         // quantas explosoes no efeito

  while (status->break_effect != true) {
    for (int x = 0; x < numExplosoes ; x++) {
      byte hue = random(1, 255);        // escolhe cor aleatoria

      for (int i = 0; i < expSize; i++) {
        fita[NUM_LEDS_FITA / 2 + i].setHue(hue);
        fita[NUM_LEDS_FITA / 2 - i].setHue(hue);
        if (i > expSize / 2) {
          i++;
          fita[NUM_LEDS_FITA / 2 + i].setHue(hue);
          fita[NUM_LEDS_FITA / 2 - i].setHue(hue);
        }
        FastLED.show();
      }

      if(status->break_effect == true) {
        fillSolidColor(CRGB::Black);
        return;
      }

      delay(100);
      for (int i = 0; i < 400; i++) {
        for (int j = 0; j < NUM_LEDS_FITA; j++) {
          if (random(10) > 8)
            fita[j] = fita[j].fadeToBlackBy(fade);
        }
        delay(10);
        FastLED.show();
      }
    }
  }
}

void helicopter(struct EffectsStatus *status) {
  int random_color = random (50, 255);
  int tamLuz = 6;
  int luzes[tamLuz];
  int luzesTemp;
  luzes[0] = 125;//CHSV(selcor, 255, 125);
  luzes[1] = 255;//CHSV(selcor, 255, 255);
  luzes[2] = 255;//CHSV(selcor, 255, 255);
  luzes[3] = 125;//CHSV(selcor, 255, 125);
  luzes[4] = 0;//CHSV(selcor, 255, 0);
  luzes[5] = 0;//CHSV(selcor, 255, 0);

  while (status->break_effect != true) {

    for (int l = 0; l < NUM_LEDS_FITA; l = l + tamLuz) {
      for (int m = 0; m < tamLuz; m++) {
        fita[l + m] = CHSV(random_color, 255, luzes[m]);
      }
      FastLED.show();
    }

    if(status->break_effect == true) {
        fillSolidColor(CRGB::Black);
      return;
    }

    luzesTemp = luzes[0];
    for (int n = 0; n < tamLuz - 1; n++) {
      luzes[n] = luzes[n + 1];
    }
    luzes[tamLuz - 1] = luzesTemp;

    delay(30);
  }
}