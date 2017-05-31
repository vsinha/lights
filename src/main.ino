#include <Adafruit_NeoPixel.h>
#define LEDPIN 6 // connect the Data from the strip to this pin on the Arduino
#define NUMBER_PIXELS 1440 // the number of pixels in your LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMBER_PIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

int wait = 10; // how long we wait on each color (milliseconds)

int numPixels = strip.numPixels();



int numRows = 10;
int numColumns = 144;

uint32_t white = strip.Color(255, 255, 255);


//uint16_t coordinateToPixel(byte row, byte col) {
//  return (Height * col) + row;
//}

void writePixel(byte row, byte col, uint32_t color) {
    int index = 0;
    if (row % 2 == 0) {
        index = (numColumns * row) + col;
    } else {
        index = (numColumns * row) + (numColumns - col);
    }
    strip.setPixelColor(index, color);
}


// int trailLength = 10;
// int multiplier = 255 / trailLength;
// void raindrop(int column) {
//     uint32_t color = 0;
//     uint8_t val = 0;
//     for (int i = 0; i < numRows; i++) {
//         strip.clear();
//         for (int j = 0; j < trailLength; j++) {
//             int index = i - j;
//             if (i - j < 0) {
//                 continue;
//             }
//             val = 255 - (multiplier * j);
//             color = strip.Color(val, val, val);
//             writePixel(index, column, color);
//         }
//         strip.show();
//         delay(15);
//     }
// }




/////////////////////////////
// tests
void allPixelsTest() {

    uint32_t color = strip.Color(200, 200, 200);

    for (uint16_t i = 0; i < numPixels; i++) {
        strip.setPixelColor(i, color);
    }

    strip.show();

    delay(100);
}
/////////////////////////////

int singlePixelTick = 0;
void singlePixelTest() {

    strip.setPixelColor(singlePixelTick, strip.Color(255, 255, 255));

    singlePixelTick += 1;
    if (singlePixelTick > numPixels) {
        singlePixelTick = 0;
    }

    strip.show();
}
/////////////////////////////

int oscillateTick = 0;
void oscillateTest() {

    strip.clear();

    uint32_t color = white;

    if (singlePixelTick % 2 == 0) {
        // all even pixels
        for (int i = 0; i < numPixels; i += 2) {
            strip.setPixelColor(i, color);
        }
    } else {
        // all odd pixels
        for (int i = 1; i < numPixels; i += 2) {
            strip.setPixelColor(i, color);
        }
    }

    singlePixelTick += 1;
    if (singlePixelTick > numPixels) {
        singlePixelTick = 0;
    }

    strip.show();

    delay(25);
}
/////////////////////////////

int columnTick = 0;
void columnWipe() {

    for (int r = 0; r < numRows; r++) {
        writePixel(r, columnTick, white);
    }

    columnTick += 1;
    if (columnTick > numColumns) {
        columnTick = 0;
        strip.clear();
    }

    strip.show();
}


/////////////////////////////




void setup() {
    strip.begin();
    strip.setBrightness(10);
}

void loop() {

    //allPixelsTest();
    //singlePixelTest();
    //oscillateTest();

    columnWipe();

    // for (int row = 0; row = numRows; row++) {
    //     writePixel(row, 1, strip.Color(255, 255, 255));
    //
    //     //writePixel(row, tick, strip.Color(255, 255, 255));
    // }
    //
    // strip.show();
    //
    // tick += 1;
    // if (tick > numColumns) {
    //     tick = 0;
    // }
    //

}


// // Input a value 0 to 255 to get a color value.
// // The colours are a transition r - g - b - back to r.
// uint32_t Wheel(byte WheelPos) {
//     if(WheelPos < 85) {
//         return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//     } else if(WheelPos < 170) {
//         WheelPos -= 85;
//         return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//     } else {
//         WheelPos -= 170;
//         return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//     }
// }


// // Calculate 1/2^nth dimmed version of a color (used by ScannerUpdate)
// uint32_t DimColor(uint32_t color, uint8_t n){
//     // Shift R, G and B components one bit to the right
//     uint32_t dimColor = Adafruit_NeoPixel::Color(Red(color) >> n, Green(color) >> n, Blue(color) >> n);
//     return dimColor;
// }

// // Returns the Red component of a 32-bit color
// uint8_t Red(uint32_t color)
// {
//     return (color >> 16) & 0xFF;
// }
//
// // Returns the Green component of a 32-bit color
// uint8_t Green(uint32_t color)
// {
//     return (color >> 8) & 0xFF;
// }
//
// // Returns the Blue component of a 32-bit color
// uint8_t Blue(uint32_t color)
// {
//     return color & 0xFF;
// }
