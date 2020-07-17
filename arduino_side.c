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

#define FALSE 0
#define TRUE !FALSE
#define NUM_LEDS 300     // Number of LED's in the strip [ 5 meter * 60 LED's per meter = 300 LED's in the whole strip  ] 300+1 for the array
#define DATA_PIN 3        // Change later when arduino arrives      
#define LED_TYPE WS2812B  // Type of the LED strip
#define BRIGHTNESS 120   // MIN [0 -> 255] MAX
#define SATURATION 255    // MIN [0 -> 255] MAX
#define HUE 255           // to cycle throw HUE
#define SPEED 25          // Speed of the animation
#define HUE_STEP 5        // [step to change r || g || b every 51 LED's] bigger step faster HUE repeat in less LED's. Step must me HUE_STEP / HUE = SOLID NUMBEr (without ".num")

/*
        HUE_STEP is how fast the rainbow changes the gamma of rgb
        ---------------------------------------------------------

#define HUE_STEP 17    [more bigger step to change r || g || b every 15 LED's] - VERY FAST
#define HUE_STEP 1     [less big step to change r || g || b every 255 LED's] - VERY SLOW
*/

//define global variabel's
CRGB leds[NUM_LEDS]; // define the array of the LED's
int currentLed = 0;  // define current led to index the led in the array in loop
int r = 0;
int g = 0;
int b = 0;


/*
Setup the parmeters of the led strip for the library    
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
    rainbowWave();      // Rainbow effect DONE!
    // rainbowFireBall();   temporarily not working

}

//define event rainbowWave1
void rainbowWave()
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
        delay(SPEED); // The lower the value the faster the wave move's (and vice versa)
    }
}


void rainbowFireBall()
{
    int repeat = 0;
    int hue
    while (repeat == 10)
    {
        for (int i = 0; i < NUM_LEDS - 1; i++)
        {
            hue += 15;
            leds(i, i + 5).fill_rainbow(hue);
            fadeToBlackBy(leds, NUM_LEDS, 150);
            FastLED.show();
            delay(100);
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

