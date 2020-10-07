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
#include <Arduino.h>
#include <colorpalettes.h>
#include <pixeltypes.h>

#include <hsv2rgb.h>
#include <colorpalettes.h>

#define FALSE 0
#define TRUE !FALSE
#define NUM_LEDS 301 // Number of LED's in the strip [ 5 meter * 60 LED's per meter = 300 LED's in the whole strip  ] 300+1 for the array
#define LED_FADE 31
#define DATA_PIN 3       // Change later when arduino arrives
#define LED_TYPE WS2812B // Type of the LED strip
#define BRIGHTNESS 200   // MIN [0 -> 255] MAX
#define SATURATION 255   // MIN [0 -> 255] MAX
#define HUE 255          // to cycle throw HUE
#define SPEED 25         // Speed of the animation
#define HUE_STEP 5       // [step to change red || green || blue every 51 LED's] bigger step faster HUE repeat in less LED's. Step must me HUE_STEP / HUE = SOLID NUMBEr (without ".num")

/*
        HUE_STEP is how fast the rainbow changes the gamma of rgb
        ---------------------------------------------------------

#define HUE_STEP 17    [more bigger step to change red || green || blue every 15 LED's] - VERY FAST
#define HUE_STEP 1     [less big step to change red || green || blue every 255 LED's] - VERY SLOW
*/


void rainbowWave1();
void both();
void black();
void potiCheck();

//future add...
//void displayInfo();


int count = 0;
CRGB leds[NUM_LEDS]; // define the array of the LED's

/*
Setup the parmeters of the LED strip for the library    
input: parameter's of the LED Strip
output: None 
*/
void setup()
{
    FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
}

/*
loop for main events 
*/
void loop()
{
    black();
    rainbowWave1();
    //both();
}

// turn all leds black before first start.
void black()
{
    if (count == 0)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i].setRGB(0, 0, 0);
        }
        count++;
    }
}

// runing strip of 9 LEDs from both ends.
void both()
{
    int j = 0;
    for (int i = NUM_LEDS; i != 0; i--)
    {
        leds[i].setRGB(255, 0, 0);
        leds[j].setRGB(255, 0, 0);
        j++;
        if (i < (NUM_LEDS - 8) && j > 8)
        {
            leds[i + 10].setRGB(0, 0, 0);
            leds[j - 10].setRGB(0, 0, 0);
        }

        potiCheck();
        FastLED.show();
        delay(SPEED);
    }
}

// define event rainbowWave1
void rainbowWave1()
{
    // Cycle hue
    for (int i = 0; i < HUE; i++)
    {
        // Cycle LED's
        for (int j = 0; j < LED_FADE; j++)
        {
            // setting led color, brightness, and saturation
            leds[j] = CHSV(j - (i * 2), SATURATION, BRIGHTNESS); /* The higher the value 4 the less fade there is and vice versa */
        }

        potiCheck();

        // send data to the led strip and make the LED show the NOW color
        FastLED.show();

        // FADE Speed
        delay(SPEED); // The lower the value the faster the wave move's (and vice versa)
    }
}

void potiCheck()
{
    int potiVal = analogRead(POTI_PIN);
    int brightVal = map(potiVal, 0, 1023, 0, 255);
    FastLED.setBrightness(brightVal);
}

/* future add...

void displayInfo()
{



}

*/