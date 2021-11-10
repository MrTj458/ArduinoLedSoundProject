// FastLED library: https://github.com/FastLED/FastLED
#include <FastLED.h>

// Define pins used
#define LED_PIN 2
#define SOUND_PIN A0

// Define led layout
#define NUM_LEDS 128
#define COLS 8
#define ROWS 16

// Other constants
#define SOUND_THRESHOLD 900
#define ANIMATION_DELAY 5

// FastLED array
CRGB leds[NUM_LEDS];

// Turn FastLED 1d array into alternating 2d array
int grid[ROWS][COLS] = {
  {127, 96, 95, 64, 63, 32, 31, 0},
  {126, 97, 94, 65, 62, 33, 30, 1},
  {125, 98, 93, 66, 61, 34, 29, 2},
  {124, 99, 92, 67, 60, 35, 28, 3},
  {123, 100, 91, 68, 59, 36, 27, 4},
  {122, 101, 90, 69, 58, 37, 26, 5},
  {121, 102, 89, 70, 57, 38, 25, 6},
  {120, 103, 88, 71, 56, 39, 24, 7},
  {119, 104, 87, 72, 55, 40, 23, 8},
  {118, 105, 86, 73, 54, 41, 22, 9},
  {117, 106, 85, 74, 53, 42, 21, 10},
  {116, 107, 84, 75, 52, 43, 20, 11},
  {115, 108, 83, 76, 51, 44, 19, 12},
  {114, 109, 82, 77, 50, 45, 18, 13},
  {113, 110, 81, 78, 49, 46, 17, 14},
  {112, 111, 80, 79, 48, 47, 16, 15}
};

// List of colors for columns
int colors[COLS] = {
  CRGB::Blue,
  CRGB::Yellow,
  CRGB::Green,
  CRGB::Orange,
  CRGB::Blue,
  CRGB::Purple,
  CRGB::Cyan,
  CRGB::Magenta
};

void setup()
{
  // Set pins to correct mode
  pinMode(LED_PIN, OUTPUT);
  pinMode(SOUND_PIN, INPUT);

  // FastLED setup
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(30);
  Serial.begin(9600);
}

void loop() {
  // Clear out FastLED data
  FastLED.clear();
  FastLED.show();

  // Check if microphone detects sound
  if (analogRead(SOUND_PIN) > SOUND_THRESHOLD) {
    // Generate random heights for the columns
    int heights[COLS];
    for (int i = 0; i < COLS; i++) {
      heights[i] = random(ROWS / 4, ROWS);
    }

    // Animate the columns up to their random height
    for (int r = 0; r < ROWS; r++) {
      for (int c = 0; c < COLS; c++) {
        // Check the row is within the randomly generated height for current column
        if (r < heights[c]) {
          leds[grid[r][c]] = colors[c]; // Set LED color to the color for that column
        } else {
          leds[grid[r][c]] = CRGB::Black; // LED should be off, make sure it's off
        }
      }
      // Show one row at a time to create the animation
      FastLED.show();
      delay(ANIMATION_DELAY);
    }

    // Animate the colums back down, turning the LEDs off
    for (int r = ROWS - 1; r >= 0; r--) {
      for (int c = COLS - 1; c >= 0; c--) {
        leds[grid[r][c]] = CRGB::Black;
      }
      FastLED.show();
      delay(ANIMATION_DELAY);
    }
  }
}
