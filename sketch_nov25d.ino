// ALL COMPONENTS

#include <Adafruit_NeoPixel.h>

#define PIN 2

float sound = 0;
int flashspeed = 0;
int NUMPIXELS = 12;
int startflash = 500;

int r = 0;
int g = 0;
int b = 150;
int mode = 0; //0 = sensors ; 1=rainbow; 2 = solidcolor; 3 = color + flashing;
int low = 100;
int high = 350;

// these constants describe the pins. They won't change:
const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A2;                  // x-axis of the accelerometer
const int ypin = A3;                  // y-axis
const int zpin = A4;                  // z-axis (only on 3-axis models)

const int buttonPin = 4;

int x = 0;
int y = 0;
int z = 0;

int lastButtonState = 0;
int buttonState = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS, 3, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixels.setBrightness(50);
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

//  pinMode(buttonPin, INPUT);

  // Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
//  buttonState = digitalRead(buttonPin);
//  if (buttonState == LOW and lastButtonState == HIGH) {
//    Serial.write(1);
//  }
// else{
//  Serial.write(2);
// }
//  lastButtonState = buttonState;
//  delay(1000);
  if (Serial.available() >= 4) {
    if (Serial.read() == 0x00) {
      r = Serial.read();
      g = Serial.read();
      b = Serial.read();
      if (mode != 3) { mode = 2;}
      //mode = 2;
    }
   //delay(100);
  }
  else if (Serial.available() >= 3){
    if (Serial.read() == 0x00){
      int prevmode = mode;
      mode = Serial.read();
      if (mode == 3){
        int argu;
        argu = Serial.read();
        if (argu == 2){
          mode = 2;
        }
        else if (argu == 1){
          flashspeed = max(0,flashspeed - 50);
        }
        else {
          flashspeed = min(flashspeed + 50, 100);
        }
      }
      else if (mode == 4){
        int argu;
        argu = Serial.read();
        if (argu == 4){
          low = min (1000, low+100);
          high = min(1000, high+100);
        }
        else{
          low = max (0, low - 100);
          high = min (0, high - 100);
        }
        mode = prevmode;
      }
      else if (mode == 5){
//        int argu1, argu2;
//        argu1 = Serial.read();
//        argu2 = Serial.read();
//        startflash = argu;
//        mode = prevmode;
      } 
    }
  }
  else if (Serial.available() >= 2){
    if (Serial.read() == 0x00){
      mode = Serial.read();
    }
  }

  if (mode == 0){
        sound = analogRead(A0);
//    Serial.print(sound);
    // print a tab between values:
//    Serial.print("\t");
  
    x = analogRead(xpin);
    y = analogRead(ypin);
    z = analogRead(zpin);

    Serial.print(x);
    Serial.print("\t");
    Serial.print(y);
    Serial.print("\t");
    Serial.print(z);
    Serial.println();
   
    
    if (sound < low) {
      r = 0;
      g = 150;
      b = 0;
    }
  
    if (sound >= low & sound <= high) {
      r = 255;
      g = 155;
      b = 0;
    }
  
    if (sound > high) {
      r = 0;
      g = 0;
      b = 150;
    }
  
   
  if (x > startflash or y > startflash or z > startflash) {
    theaterChase(pixels.Color(r, g, b), 50);
//    theaterChase2(pixels2.Color(r, g, b), 50);
  }
  else {
    solidcolor(r, g, b, 0);
//    solidcolor2(r, g, b, 50);
  }
  
  }  
else if (mode == 1 ){
  rainbow(20);
//  rainbow2(20);
}
else if (mode == 2){
  solidcolor(r,g,b,50);
//  solidcolor2(r,g,b,50);
}
else if (mode == 3){
  flash(r,g,b,flashspeed);
//  flash2(r,g,b,flashspeed);
}
//  if (b == 150){
//   Serial.print(1);
//  }
  delay(100);
}

void flash(int r, int g, int b, int delayval){
  //flash 10 times
  for (int i =0; i<10; i++){
    solidcolor(r,g,b,0);
    delay(delayval);
    solidcolor(0,0,0,0);
    delay(delayval);
  }
}
//void flash2(int r, int g, int b, int delayval){
//  //flash 10 times
//  for (int i =0; i<10; i++){
//    solidcolor2(r,g,b,0);
//    delay(delayval);
//    solidcolor2(0,0,0,0);
//    delay(delayval);
//  }
//}
void solidcolor(int r, int g, int b, int delayval) {
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  }
//void solidcolor2(int r, int g, int b, int delayval) {
//  for (int i = 0; i < NUMPIXELS; i++) {
//
//    // pixels2.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels2.setPixelColor(i, pixels2.Color(r, g, b));
//    
//    pixels2.show(); // This sends the updated pixel color to the hardware.
//
//    delay(delayval); // Delay for a period of time (in milliseconds).
//
//  }
//  }

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

//void theaterChase2(uint32_t c, uint8_t wait) {
//  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
//    for (int q=0; q < 3; q++) {
//      for (uint16_t i=0; i < pixels2.numPixels(); i=i+3) {
//        pixels2.setPixelColor(i+q, c);    //turn every third pixel on
//      }
//      pixels2.show();
//
//      delay(wait);
//
//      for (uint16_t i=0; i < pixels2.numPixels(); i=i+3) {
//        pixels2.setPixelColor(i+q, 0);        //turn every third pixel off
//      }
//    }
//  }
//}

void rainbow(uint8_t wait) {
//  Serial.println("rainbow");
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i < pixels.numPixels(); i++) { //fade through all colors
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(wait);
  }
}

//void rainbow2(uint8_t wait) {
////  Serial.println("rainbow");
//  uint16_t i, j;
//
//  for(j=0; j<256; j++) {
//    for(i=0; i < pixels2.numPixels(); i++) { //fade through all colors
//      pixels2.setPixelColor(i, Wheel2((i+j) & 255));
//    }
//    pixels2.show(); // This sends the updated pixel color to the hardware.
//    delay(wait);
//  }
//}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

//uint32_t Wheel2(byte WheelPos) {
//  WheelPos = 255 - WheelPos;
//  if(WheelPos < 85) {
//    return pixels2.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  }
//  if(WheelPos < 170) {
//    WheelPos -= 85;
//    return pixels2.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  }
//  WheelPos -= 170;
//  return pixels2.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//}
