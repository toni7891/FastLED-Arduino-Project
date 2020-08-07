/*
coded by:

         @@@  @@@@@@@   @@@@@@@ @@@  @@@ @@@@@@  @@@@@@@
        @@@@  @@@@@@@@ @@@@@@@@ @@@  @@@ @@@@@@@ @@@@@@@@
       @@!@!  @@!  @@@ !@@      @@!  @@@     @@@ @@!  @@@
      !@!!@!  !@!  @!@ !@!      !@!  @!@     @!@ !@!  @!@
     @!! @!!  @!@!!@!  !@!      @!@!@!@! @!@!!@  @!@!!@!
    !!!  !@!  !!@!@!   !!!      !!!@!!!! !!@!@!  !!@!@!
    :!!:!:!!: !!: :!!  :!!      !!:  !!!     !!: !!: :!!
    !:::!!::: :!:  !:! :!:      :!:  !:!     :!: :!:  !:!
         :::  ::   :::  ::: ::: ::   ::: :: :::: ::   :::
         :::   :   : :  :: :: :  :   : :  : : :   :   : :

*/

#include <FastLED.h>

#define NUM_LEDS 300      // Number of LED's in the strip [ 5 meter * 60 LED's per meter = 300 LED's in the whole strip  ]
#define DATA_PIN 6         // Change later when arduino arrives      
#define LED_TYPE WS2812B  // Type of the LED strip
#define BRIGHTNESS 255    // MIN [0 -> 255] MAX
#define SATURATION 255    // MIN [0 -> 255] MAX
#define HUE 255           // HUE to cycle throw in the RainbowWaveLoop

CRGB leds[NUM_LEDS]; // define the array of the LED's

/*
Setup the parmeters of the led strip for the library    
input: parameter's of the LED Strip
output: None 
*/
void setup() 
{
    FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
}

void loop()
{
    leds[1] = 
    rainbowWaveLoop();

}

/*
check LED strip fully working [each led works as needed!]
*/
void check()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i] = CHSV(20, BRIGHTNESS, SATURATION);
    }
    FastLED.show();
    delay(25)
}


/*
loop for main event "RAINBOW WAVE"
input: parameter's of the LED strip and the color settings
output: NOW color grade and parameter's of the color 
*/
void rainbowWaveLoop()
{
    // Cycle hue
    for (int i = 0; i < HUE; i++)
    {
        // Cycle LED's
        for (int j = 0; j < NUM_LEDS; j++)
        {
            // setting led color, brightness, and saturation
            leds[j] = CHSV(j - (i * 2), BRIGHTNESS, SATURATION); /* The higher the value 4 the less fade there is and vice versa */
        }

        // send data to the led strip and make the LED show the NOW color
        FastLED.show();

        // FADE Speed
        delay(25); // The lower the value the faster the wave move's (and vice versa)
    }
}