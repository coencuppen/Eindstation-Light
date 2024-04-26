#ifndef LIGHT_EFFECTS_HPP
#define LIGHT_EFFECTS_HPP

#define BRIGHTNESS 255

#include <util/delay.h>

#include "APA102.hpp"
#include "Analog.hpp"

class LightEffects {
private:
  APA102 *Leds;

public:
  LightEffects(uint8_t numOfLeds) {
    Leds = new APA102{numOfLeds};
    analog::initADC();

    randomSeed(millis() + analogRead(0));
    loopEffect();
  }

  uint8_t getRandomByte() { return random(256); }

  void wait(uint16_t ms) {
    for (uint16_t time = 0; time < ms; ++time) {
      _delay_ms(1);
    }
  }

  void flickerEffect(const uint8_t colors[]) {
    uint8_t loopTimes = random(10);

    for (uint8_t flickers = 0; flickers < loopTimes; ++flickers) {
      Leds->sendColor(colors[0], colors[1], colors[2], random(3));

      wait(random(180));

      Leds->sendColor(colors[0], colors[1], colors[2], BRIGHTNESS);

      wait(random(180));
    }

    Leds->sendColor(colors[0], colors[1], colors[2], 0);
    wait(random(1800));
  }

  void loopEffect() {
    for (;;) {

      uint8_t colors[] = {getRandomByte(), getRandomByte(), getRandomByte()};

      Leds->sendColor(colors[0], colors[1], colors[2], BRIGHTNESS);

      uint16_t waitTime = (uint16_t)(random(60000));
      uint8_t choice = random(3);
      uint16_t devider = waitTime / colors[choice];

      for (uint16_t time = 0; time < waitTime; ++time) {
        if (time % devider == 0 && colors[choice] > 0) {
          colors[choice] -= 1;
        }
        Leds->sendColor(colors[0], colors[1], colors[2], BRIGHTNESS);
        wait(1);
      }

      flickerEffect(colors);
    }
  }
};

#endif