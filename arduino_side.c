/*
  Sketch to learn fastLED
*/

#include <FastLED.h>

#define NUM_LEDS 26 // Add one for LED0
#define DATA_PIN D1
#define BRIGHTNESS 20
#define LED_TYPE WS2811
#define COLOR_ORDER RGB

// Set up the block of memory that will be used for storing and manipulating the led data:
// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

#define sceneDelay 2000 // Delay between scenes
#define pixelDelay 10   // Delay between pixels

// =========================== setup() ===========================
// Set up the leds and tell the controller about them
void setup()
{
    Serial.begin(115200);
    Serial.println();

    // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(2000);

    // This tells the library that there's a strand of LED_TYPE on pin DATA_PIN,
    // and those leds will use the led array leds, and there are NUM_LEDS of them.
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);

    rbgLed();
}

// =================== loop() ===================
void loop()
{
}

// =========================== rbgLed() ===========================
void rbgLed()
{
    // Every three LEDs is RGB.
    int ledNum = 0;
    while (ledNum < NUM_LEDS)
    {
        leds[ledNum++] = CRGB::Red;
        LEDS.show();
        //FastLED.show();
        delay(pixelDelay);
        leds[ledNum++] = CRGB::Green;
        LEDS.show();
        //FastLED.show();
        delay(pixelDelay);
        leds[ledNum++] = CRGB::Blue;
        LEDS.show();
        //FastLED.show();
        delay(pixelDelay);
    }
}