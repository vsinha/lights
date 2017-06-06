#include "FastLED.h"

#include "life.hpp"

#define NUM_LEDS 1440
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

GameOfLife life;

int numRows = 10;
int numColumns = 144;

int coord2index(byte row, byte col) {
    int index = 0;
    if (row % 2 == 0) {
        index = (numColumns * row) + col;
    } else {
        index = (numColumns * row) + (numColumns - col - 1);
    }
    return index;
}

void setup() {

    Serial.begin(115200);
    Serial.println("hello world");

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(30);

    life.init();
}

uint8_t hue = 0;
uint8_t tick = 0;
int angle = 0;
int deltaAngle = 2;
bool forward = true;

void rainbowUpdate() {
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numColumns; c++) {
            leds[coord2index(r, c)].setHue(tick + (2*c) + r);
        }
    }
    tick += 2;
}


void lifeUpdate() {
    life.update();
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numColumns; c++) {
            if (life.getCurrentBoard().get(r, c)) {
                leds[coord2index(r, c)] = CRGB::White;
            }
        }
    }
}

void loop() {
    //FastLED.clear();

    rainbowUpdate();
    lifeUpdate();

    FastLED.show();
}
