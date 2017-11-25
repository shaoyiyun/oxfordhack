#include <Adafruit_NeoPixel.h>

#define PIN 2

float sound = 0;
int delayval = 0;
int NUMPIXELS = 12;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'
}

void loop() {
  // put your main code here, to run repeatedly:
  sound = analogRead(A0);
  delay(100);
  Serial.println(sound);

  if (sound < 100) {
    yellow(); }

  if (sound >= 101 & sound <= 699) {
    green();
  }

  if (sound >= 700) {
    yellow();
  }
}

void green() {
  Serial.println("green");
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 150, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
}

void yellow() {
  Serial.println("yellow");
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 100, 0)); // Yellow color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
}

//void rainbow(uint8_t wait) {
//  Serial.println("rainbow");
//  uint16_t i, j;
//
//  for(j=0; j<256; j++) {
//    for(i=0; i < strip.numPixels(); i++) { //fade through all colors
//      strip.setPixelColor(i, Wheel((i+j) & 255));
//    }
//    strip.show(); // This sends the updated pixel color to the hardware.
//    delay(wait);
//  }
//}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
//uint32_t Wheel(byte WheelPos) {
//  WheelPos = 255 - WheelPos;
//  if(WheelPos < 85) {
//    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  }
//  if(WheelPos < 170) {
//    WheelPos -= 85;
//    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  }
//  WheelPos -= 170;
//  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//}
