// ALL COMPONENTS

#include <Adafruit_NeoPixel.h>

#define PIN 2

float sound = 0;
//int delayval = 0;
int NUMPIXELS = 12;
int startflash = 400;

int r = 150;
int g = 0;
int b = 0;

int low = 100;
int high = 400;

// these constants describe the pins. They won't change:
const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A2;                  // x-axis of the accelerometer
const int ypin = A3;                  // y-axis
const int zpin = A4;                  // z-axis (only on 3-axis models)

int x = 0;
int y = 0;
int z = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'

  // Provide ground and power by using the analog inputs as normal digital pins.
  // This makes it possible to directly connect the breakout board to the
  // Arduino. If you use the normal 5V and GND pins on the Arduino,
  // you can remove these lines.
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() >= 4 and Serial.read() == 0xff) {
    r = Serial.read();
    g = Serial.read();
    b = Serial.read();

    Serial.println(r);
    Serial.println(g);
    Serial.println(b);
  }
//  else {
//    sound = analogRead(A0);
//    Serial.print(sound);
//    // print a tab between values:
//    Serial.print("\t");
//  
//    x = analogRead(xpin);
//    y = analogRead(ypin);
//    z = analogRead(zpin);
//    
//    if (sound < low) {
//      r = 0;
//      g = 150;
//      b = 0;
//    }
//  
//    if (sound >= low & sound <= high) {
//      r = 255;
//      g = 155;
//      b = 0;
//    }
//  
//    if (sound > high) {
//      r = 0;
//      g = 0;
//      b = 150;
//    }
//  }
//   
//  if (x > startflash or y > startflash or z > startflash) {
//    theaterChase(pixels.Color(r, g, b), 50);
//  }
//  else {
    solidcolor(r, g, b, 50);
//  }


//  Serial.print(x);
//  Serial.println();
//  theaterChase(pixels.Color(0, 0, 127), 50); // Blue
//  green();

  delay(100);
}

void solidcolor(int r, int g, int b, int delayval) {
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  }

//void red() {
//  Serial.println("green");
//  for (int i = 0; i < NUMPIXELS; i++) {
//
//    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels.setPixelColor(i, pixels.Color(150, 0, 0)); // Moderately bright red color.
//
//    pixels.show(); // This sends the updated pixel color to the hardware.
//
//    delay(delayval); // Delay for a period of time (in milliseconds).
//
//  }
//}
//
//void green() {
//  Serial.println("green");
//  for (int i = 0; i < NUMPIXELS; i++) {
//
//    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels.setPixelColor(i, pixels.Color(0, 150, 0)); // Moderately bright green color.
//
//    pixels.show(); // This sends the updated pixel color to the hardware.
//
//    delay(delayval); // Delay for a period of time (in milliseconds).
//
//  }
//}
//
//void yellow() {
//  Serial.println("yellow");
//  for (int i = 0; i < NUMPIXELS; i++) {
//
//    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels.setPixelColor(i, pixels.Color(255, 100, 0)); // Yellow color.
//
//    pixels.show(); // This sends the updated pixel color to the hardware.
//
//    delay(delayval); // Delay for a period of time (in milliseconds).
//
//  }
//}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, c);    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (uint16_t i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
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
