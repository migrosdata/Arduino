
//******** Teensy MIDI Color Ring ********
// Uses 16 LED Neopixel Ring from Adafruit as written - change NUM_LEDS and divisor of note/8 to adapt
// Hacked together by Dave Pentecost - to use palettes, MIDI input, velocity change of color, notes on different LEDs
//
#include "FastLED.h" //We are using the FastLED library instead of the Adafruit Neopixel library, to work better with Teensy

#define LED_PIN     9
#define NUM_LEDS    50
#define BRIGHTNESS  100
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

//Palette setup
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
extern CRGBPalette16 RainbowColors;
extern const TProgmemPalette16 RainbowColors_p PROGMEM;

//Set variables for velocity (color) and note (LED position on ring)
uint8_t NewVelocity;
uint8_t NewNote;

//******************************************
//Functions defined below

//What to do if MIDI note on is read
void OnNoteOn(byte channel, byte note, byte velocity)
{
  if (note >= NUM_LEDS) {
    return;
  }
  leds[note] = CRGB::White;
  FastLED.show(); //Turn on that LED when you get back from the color routine
}

//What to do if MIDI note off is read
void OnNoteOff(byte channel, byte note, byte velocity)
{
    if (note >= NUM_LEDS) {
      return;
  }
  leds[note] = CRGB::Black;
  FastLED.show(); //turn off that LED by making it black
}

void setup()
{
  //MIDI handles to set up actions on note on and note off
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
  
  //Setting up LED info for the FastLED library
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND; //BLEND;
  
  //Turn on one red LED to show sketch has started
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(1000);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);
  
  //Print OK for start
  Serial.begin(115200);
  Serial.print("Okay Okay Okay");
}


//***** Running program loop *****
void loop()
{
  //This is all we need, since we have actions set when MIDI is read
  usbMIDI.read();
}
