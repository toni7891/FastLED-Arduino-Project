//define event rainbowFade2
void rainbowFade()
{
  int currentLed = 0;
  int color = 0;

  for (color = 0; color < 766; color++)
  {
    if (color < 256)
    {
      leds[currentLed].r = color;
    }

    else if (color > 255 && color < 511)
    {
      leds[currentLed].g = color;
    }

    else if (color > 511 && color < 766)
    {
      leds[currentLed].b = color;
    }
    currentLed++;
    FastLED.show();
    delay(SPEED);
  }
}

void rainbowFireBall()
{
    int repeat = 0;
    while (repeat == 10)
    {
        for (int i = 0; i < NUM_LEDS - 1; i++)
        {
            hue += 15;
            leds(i, i + 5).fill_rainbow(hue);
            fadeToBlackBy(leds, NUM_LEDS, 150);
            FastLED.show();
            delay(SPEED);
        }

        for (int j = NUM_LEDS; j != 0; j--)
        {
            hue += 15;
            leds(j, j + 5).fill_rainbow(hue);
            fadeToBlackBy(leds, NUM_LEDS, 150);
            FastLED.show();
            delay(100);
        }
        repeat++;
    }
}

