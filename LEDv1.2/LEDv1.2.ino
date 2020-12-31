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

// Including needed librarays
#include <FastLED.h>
#include <Arduino.h>
#include <colorpalettes.h>
#include <pixeltypes.h>
#include <hsv2rgb.h>
#include <colorpalettes.h>

// Defining un-changeabel variabels
#define FALSE 0
#define TRUE !FALSE
#define HIGH 1           // ON mode
#define LOW 0            // OFF mode
#define NUM_LEDS 301     // Number of LED's in the strip [ 5 meter * 60 LED's per meter = 300 LED's in the whole strip  ] 300+1 for the array
#define LED_FADE 87
#define DATA_PIN 3       // Change later when arduino arrives
#define POTI_PIN 0       // Potentiometer Data Pin [A0]
#define LED_TYPE WS2812B // Type of the LED strip
#define BRIGHTNESS 150   // MIN [0 -> 255] MAX
#define SATURATION 255   // MIN [0 -> 255] MAX
#define HUE 255          // to cycle throw HUE
#define SPEED 25         // Speed of refreshing the animation

// Defining functions
void rainbowWave1();
void both();
void black();
void purp();

// Global variabels
int count = 0;       // flag to clear leds at first startup... upgrade soon...
CRGB leds[NUM_LEDS]; // define the array of the LED's

/*
Setup the parmeters of the led strip for the library    
input: parameter's of the LED Strip
output: None 
*/
void setup()
{
    Serial.begin(9600);
    FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
}

//loop for main events
void loop()
{
    black();
    //purp();
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

void purp()
{
  for(int i = 0; i < LED_FADE; i++)
  {
    leds[i] = CRGB::Purple; 
  }
  FastLED.show();
  delay(SPEED);
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

        FastLED.show();
        delay(SPEED);
    }
}

//define event rainbowWave1
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

        // send data to the led strip and make the LED show the NOW color
        FastLED.show();

        // FADE Speed
        delay(SPEED); // The lower the value the faster the wave move's (and vice versa)
    }
}
