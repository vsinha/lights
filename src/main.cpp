/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

#include "shape.cpp"

#define LEDPIN 6 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIXELS 1440 // the number of pixels in your LED strip

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
uint8_t numPixels = strip.numPixels();

struct Point {
    uint8_t  x;
    uint8_t  y;
};

Point point[10] = {};

void allPixelsTest() {
    uint32_t color = strip.Color(200, 200, 200);
    for (uint8_t i = 0; i < NUMBER_PIXELS; i++) {
        strip.setPixelColor(i, color);
    }
    strip.show();
    delay(100);
}

void setup()
{
    strip.begin();
    strip.setBrightness(10);
}

void loop()
{
    allPixelsTest();
}
