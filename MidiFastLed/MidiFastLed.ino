/*
	MidiFastLed

	Describe what it does in layman's terms.  Refer to the components
	attached to the various pins.

*/
#include <FastLED.h>

#include <MIDI.h>

// 
//MIDI_CREATE_DEFAULT_INSTANCE();

// Number of RGB LEDs in the strand
#define NUM_LEDS 50 

#define LED_TYPE    WS2811

// Arduino pin used for Data
#define PIN 9 

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  // Setting up LED info for the FastLED library
  FastLED.addLeds<LED_TYPE, PIN, RGB>(leds, NUM_LEDS);

  // Set all led color to red
  setColorToAllLed(CRGB::Red);
    
  // Set all led color to black
  setColorToAllLed(CRGB::Black);
    
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin();
}

// ***** Running program loop *****
void loop() {
  MIDI.read();
}

// What to do if MIDI note on is read
void handleNoteOn(byte channel, byte note, byte velocity) {
  if (note >= NUM_LEDS) {
    return;
  }
  leds[note] = CRGB::White;
  
  FastLED.show(); 
}

// What to do if MIDI note off is read
void handleNoteOff(byte channel, byte note, byte velocity) {
  if (note >= NUM_LEDS) {
    return;
  }
  
  leds[note] = CRGB::Black;
  
  FastLED.show(); 
}

void setColorToAllLed(CRGB color) {
      for(int i = 0 ; i < NUM_LEDS; i++ ) {
      leds[i] = color;
    }
    FastLED.show(); 
}
