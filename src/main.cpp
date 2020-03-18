#include <config.h>

#include <Arduino.h>
#include <GyverButton.h>

GButton touch(TOUCH_PIN, LOW_PULL, NORM_OPEN);

int bright = MIN_BRI;
byte state = LOW;

void setup()
{
  touch.setStepTimeout(BUTTON_STEP_TIMEOUT);
  touch.setClickTimeout(BUTTON_CLICK_TIMEOUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TOUCH_PIN, INPUT);
}

void loop()
{
  touch.tick();
  uint8_t clickCount = touch.hasClicks() ? touch.getClicks() : 0;
  if (clickCount == 1 && !touch.isHolded())
  {
    if (!state)
    {
      bright = MIN_BRI;
    }
    state = !state;
  }

  if (touch.isStep())
  {
    if (!state)
    {
      state = !state;
      bright = MIN_BRI;
    }
    int8_t delta = bright < 10 ? 1 : bright > 16 ? 15 : 5;
    bright = constrain(
        touch.getHoldClicks() >= 1 ? bright - delta : bright + delta,
        MIN_BRI,
        MAX_BRI);
  }

  if (state)
  {
    analogWrite(LED_PIN, bright);
  }
  else
  {
    analogWrite(LED_PIN, 0);
  }
}
