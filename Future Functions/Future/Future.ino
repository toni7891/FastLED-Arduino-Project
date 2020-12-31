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

// Main 
#include <Arduino.h>
#include <stdio.h>

// LED's
#include <FastLED.h>
#include <colorpalettes.h>
#include <pixeltypes.h>
#include <hsv2rgb.h>
#include <colorpalettes.h>

// LCD Display
#include <LiquidCrystal.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

/*
    LCD DISPLAY OUTPIN CIRCUIT
   --------------------

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

/*
    OLED DISPLAY OUTPIN CIRCUIT
    The circuit:
    *
    * 
    * 
    * 
    * 
    * 
    * 
*/

// LED Data variabels 

#define FALSE 0
#define TRUE !FALSE
#define NUM_LEDS 301     // Number of LED's in the strip [ 5 meter * 60 LED's per meter = 300 LED's in the whole strip  ] 300+1 for the array
#define LED_FADE 31
#define DATA_PIN 6       // LED DIN pin
#define LED_TYPE WS2812B // Type of the LED strip
#define BRIGHTNESS 200   // MIN [0 -> 255] MAX
#define SATURATION 255   // MIN [0 -> 255] MAX
#define HUE 255          // to cycle throw HUE
#define SPEED 25         // Speed of the animation

// LCD pinout 

#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2

// Rotary potentiometer with push button Pinout

#define Clock 9 //Clock pin connected to D9
#define Data 8  //Data pin connected to D8
#define Push 10 //Push button pin connected to D10

// FUNCTION'S DEFINE
void PotiSetup();
void OLEDisplaySETUP();
void PotiCheckVal() 
void OLEDisplayINFO();
void LCDisplayInfo();
void black();
void rainbowWave1();
void purp();
void both();


// GLOBAL VARIABELS 
int count = 0;
int brightVal = 0;

// Rotary potentiometer with push button Data variabels to store in

int counter = 0;                   //Use this variable to store "steps"
int currentStateClock;             //Store the status of the clock pin (HIGH or LOW)
int lastStateClock;                //Store the PREVIOUS status of the clock pin (HIGH or LOW)
String currentDir = "";            //Use this to print text
unsigned long lastButtonPress = 0; //Use this to store if the push button was pressed or not

// ADD-ON'S SETUP
CRGB leds[NUM_LEDS];                        // define the array of the LED's
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);  // define pinout of LCD display
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &OledPin);

/*
Setup the parmeters of the LED strip for the library    
input: parameter's of the LED Strip
output: None 
*/
void setup()
{
    Serial.begin(9600);
    FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    lcd.begin(16, 2);
    OLEDisplaySETUP();
    PotiSetup();
    lastStateClock = digitalRead(Clock);
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


// PURPLE COLOR OUTPUT FUNCTION
void purp()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].setRGB(255, 0, 255);
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
            Serial.write(j - (i * 2));
        }

        potiCheck();

        // send data to the led strip and make the LED show the NOW color
        FastLED.show();

        // FADE Speed
        delay(SPEED); // The lower the value the faster the wave move's (and vice versa)
    }
}

void PotiSetup()
{
    pinMode(Clock, INPUT_PULLUP);
    pinMode(Data, INPUT_PULLUP);
    pinMode(Push, INPUT_PULLUP);
    
}

void PotiCheckVal()
{
    // Read the current state of CLOCK
    currentStateClock = digitalRead(Clock);

    // If last and current state of Clock are different, then "pulse occurred"
    // React to only 1 state change to avoid double count
    if (currentStateClock != lastStateClock && currentStateClock == 1)
    {

        // If the Data state is different than the Clock state then
        // the encoder is rotating "CCW" so we decrement
        if (digitalRead(Data) != currentStateClock)
        {
            counter--;
            currentDir = "Counterclockwise";
        }
        else
        {
            // Encoder is rotating CW so increment
            counter++;
            currentDir = "Clockwise";
        }

        Serial.print("Direction: ");
        Serial.print(currentDir);
        Serial.print(" | Counter: ");
        Serial.println(counter);
    }

    // We save last Clock state for next loop
    lastStateClock = currentStateClock;

    // Read the button state
    int btnState = digitalRead(Push);

    //If we detect LOW signal, button is pressed
    if (btnState == LOW)
    {
        //if 50ms have passed since last LOW pulse, it means that the
        //button has been pressed, released and pressed again
        if (millis() - lastButtonPress > 50)
        {
            Serial.println("Button pressed!");
        }

        // Remember last button press event
        lastButtonPress = millis();
    }

    // Put in a slight delay to help debounce the reading
    delay(1);
}


void displayInfo()
{
    lcd.print("Brightness is: " + brightVal);
}


void OLEDisplaySETUP()
{
    Serial.println("OLED FeatherWing test");
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    Serial.println("OLED begun");
    display.display();
    delay(1000);
    display.clearDisplay();
    display.display();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Connecting to SSID\n'adafruit':");
    display.print("connected!");
    display.println("IP: 10.0.1.23");
    display.println("Sending val #0");
    display.setCursor(0, 0);
    display.display();
    Serial.println("OLED Display working correctly!");
}

void OLEDisplayINFO()
{

    display.print("Brightness is: " + brightVal);
    delay(10);
    display.display();

}

