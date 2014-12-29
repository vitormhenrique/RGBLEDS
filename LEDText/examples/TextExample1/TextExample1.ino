#include <FastLED.h>

#include <LEDMatrix.h>
#include <LEDText.h>
#include <FontRobotron.h>

// Change the next 6 defines to match your matrix type and size

#define LED_PIN        7
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B

#define MATRIX_WIDTH   16
#define MATRIX_HEIGHT  5
#define MATRIX_TYPE    HORIZONTAL_ZIGZAG_MATRIX

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

cLEDText ScrollingMsg;
#define MESSAGE_WIDTH   68
#define MESSAGE_HEIGHT  6
#define MESSAGE_Y       0

const unsigned char TxtDemo[] = { EFFECT_SCROLL_LEFT "         LEFT SCROLL"
                                  EFFECT_SCROLL_RIGHT "         LLORCS THGIR"
                                  EFFECT_HSV_CH "\x00\xff\xff\x40\xff\xff" "   HSV_CH 00-40"
                                  EFFECT_HSV_AV "\x00\xff\xff\x40\xff\xff" "   HSV_AV 00-40"
                                  EFFECT_HSV_AH "\x00\xff\xff\xff\xff\xff" "   HSV_AH 00-FF"
                                  EFFECT_SCROLL_LEFT  "     " EFFECT_HSV "\x00\xff\xff" "H" EFFECT_HSV "\x20\xff\xff" "E" EFFECT_HSV "\x40\xff\xff" "L" EFFECT_HSV "\x60\xff\xff" "L" EFFECT_HSV "\xe0\xff\xff" "O" EFFECT_HSV "\xc0\xff\xff" "!"
                                  EFFECT_HSV "\xa0\xff\xff" "!" EFFECT_HSV "\x80\xff\xff" "!" };

void setup()
{
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.setBrightness(30);
  FastLED.clear(true);
  FastLED.show();

  ScrollingMsg.SetFont(ROBOTRON_WIDTH, ROBOTRON_HEIGHT, ROBOTRON_CHAR_LOW, ROBOTRON_CHAR_HIGH, RobotronData);
  ScrollingMsg.Init(&leds, MESSAGE_WIDTH, MESSAGE_HEIGHT, 0, MESSAGE_Y);
  ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
  ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);
}


void loop()
{
  if (ScrollingMsg.UpdateText() == -1)
    ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
  else
    FastLED.show();
  delay(25);
}
