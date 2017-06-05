/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

#include "shape.cpp"

#define LEDPIN 7 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIXELS 1440 // the number of pixels in your LED strip

namespace old {

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
int numPixels = strip.numPixels();

int numRows = 10;
int numColumns = 144;

uint32_t white = strip.Color(255, 255, 255);
uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);

struct Point {
    uint8_t  x;
    uint8_t  y;
};

uint32_t oppositeColor(uint32_t color) {
    return ~color;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
    if(WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if(WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
        WheelPos -= 170;
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}

void writePixel(byte row, byte col, uint32_t color) {
    int index = 0;
    if (row % 2 == 0) {
        index = (numColumns * row) + col;
    } else {
        index = (numColumns * row) + (numColumns - col - 1);
    }
    strip.setPixelColor(index, color);
}

Point points[5] = {};
uint numPoints = sizeof(points) / sizeof(Point);

int columnTick = 0;
bool wipeForward = true;

byte colorTick = 0;
uint32_t color = strip.Color(255, 0, 0);

// Returns the Red component of a 32-bit color
uint8_t Red(uint32_t color)
{
    return (color >> 16) & 0xFF;
}

// Returns the Green component of a 32-bit color
uint8_t Green(uint32_t color)
{
    return (color >> 8) & 0xFF;
}

// Returns the Blue component of a 32-bit color
uint8_t Blue(uint32_t color)
{
    return color & 0xFF;
}

uint32_t advanceColor() {
    colorTick += 40;
    return Wheel(colorTick);
}

uint32_t whitenColor(uint32_t color, int n) {
    n = n * 5;

    byte r = Red(color);
    r = max(r, r + n);

    byte g = Green(color);
    g = max(g, g + n);

    byte b = Blue(color);
    b = max(b, b + n);

    return strip.Color(r, g, b);
}

void columnWipe() {

    if (!wipeForward) {
        columnTick -= 1;
    }

    for (int r = 0; r < numRows; r++) {
        //uint32_t grad = whitenColor(color, r);
        writePixel(r, columnTick, color);
    }

    if (wipeForward) {
        columnTick += 1;
    }

    if (columnTick >= numColumns || columnTick <= 0) {
        wipeForward = !wipeForward;

        color = advanceColor();
    }
}

void randomizePoints() {

    if (wipeForward) {
        // [ 0, columnTick ]
        for (uint i = 0; i < numPoints; i++) {
            uint8_t randRow = random(10);
            uint8_t randCol = random(columnTick);
            points[i] = {randRow, randCol};
        }

    } else {
        // [ columnTick, numColumns ]
        for (uint i = 0; i < numPoints; i++) {
            uint8_t randRow = random(10);
            uint8_t randCol = columnTick + random(144 - columnTick);
            points[i] = {randRow, randCol};
        }
    }
}

void drawPoints() {
    for (uint i = 0; i < numPoints; i++) {
        writePixel(points[i].x, points[i].y, oppositeColor(color));
    }
}

// void setup()
// {
//     pinMode(LEDPIN, OUTPUT);
//
//     randomSeed(analogRead(0));
//
//     strip.begin();
//     strip.setBrightness(50);
//
//     for (uint i = 0; i < numPoints; i++) {
//         points[i] = {0, 0};
//     }
// }
//
// void loop() {
//     columnWipe();
//
//     randomizePoints();
//     drawPoints();
//
//     strip.show();
// }

}
