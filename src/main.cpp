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

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
int numPixels = strip.numPixels();

int numRows = 10;
int numColumns = 144;

uint32_t white = strip.Color(255, 255, 255);
uint32_t red = strip.Color(255, 0, 0);

struct Point {
    uint8_t  x;
    uint8_t  y;
};

void writePixel(byte row, byte col, uint32_t color) {
    int index = 0;
    if (row % 2 == 0) {
        index = (numColumns * row) + col;
    } else {
        index = (numColumns * row) + (numColumns - col - 1);
    }
    strip.setPixelColor(index, color);
}

Point points[10] = {};
uint numPoints = sizeof(points) / sizeof(Point);

int columnTick = 0;
bool wipeForward = true;
void columnWipe() {

    if (!wipeForward) {
        columnTick -= 1;
    }

    for (int r = 0; r < numRows; r++) {
        writePixel(r, columnTick, strip.Color(25*r, 25*r, 111+columnTick));
    }

    if (wipeForward) {
        columnTick += 1;
    }

    if (columnTick >= numColumns || columnTick <= 0) {
        wipeForward = !wipeForward;
    }
}

void randomizePoints() {
    for (uint i = 0; i < numPoints; i++) {
        uint8_t randRow = random(10);
        uint8_t randCol = random(144);
        points[i] = {randRow, randCol};
    }
}

void drawPoints() {
    for (uint i = 0; i < numPoints; i++) {
        writePixel(points[i].x, points[i].y, red);
    }
}

void setup()
{
    pinMode(LEDPIN, OUTPUT);

    randomSeed(analogRead(0));

    strip.begin();
    strip.setBrightness(10);

    for (uint i = 0; i < numPoints; i++) {
        points[i] = {0, 0};
    }
}

void loop() {
    columnWipe();

    randomizePoints();
    drawPoints();

    strip.show();
}
