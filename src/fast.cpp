#include "FastLED.h"

//#include "life.h"

#define NUM_LEDS 1440
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

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

    Serial.println("hello world");

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(30);

    // GOL::initialize();
    // for (int r = 0; r < numRows; r++) {
    //     for (int c = 0; c < numColumns; c++) {
    //         leds[coord2index(r, c)] = GOL::prevBoard[r][c] ? CRGB::White : CRGB::Black;
    //     }
    // }
}

uint8_t hue = 0;
uint8_t tick = 0;
int angle = 0;
int deltaAngle = 2;
bool forward = true;

void loop() {

    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numColumns; c++) {
            leds[coord2index(r, c)].setHue(tick + (2*c) + r);
        }
    }
    tick += 2;


    FastLED.show();

    // for (int c = 0; c < numColumns; c++) {
    //     hue += 1;
    //     for (int r = 0; r < numRows; r++) {
    //         leds[coord2index(r, c)].setHue(hue);
    //     }
    //     FastLED.show();
    // }

    // FastLED.clear();
    //
    // bool (*board)[GOL_ROWS][GOL_COLS];
    // //board = GOL::update();
    // // draw the relevant pixels
    // for (int r = 0; r < numRows; r++) {
    //     for (int c = 0; c < numColumns; c++) {
    //         leds[coord2index(r, c)] = board[r][c] ? CRGB::White : CRGB::Black;
    //     }
    // }
    // FastLED.show();

}
