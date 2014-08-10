#include <FastLED.h>

#include <LEDMatrix.h>
#include <LEDSprites.h>

// Change the next 6 defines to match your matrix type and size

#define LED_PIN        2
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B

#define MATRIX_WIDTH   50
#define MATRIX_HEIGHT  10
#define MATRIX_TYPE    HORIZONTAL_MATRIX

cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;


cLEDSprites Sprites(&leds);

#define MY_SPRITE_WIDTH  11
#define MY_SPRITE_HEIGHT 10
#define PACMAN_FRAMES  3
#define PINKY_FRAMES  2

const uint8_t PacmanRightData[] = 
{
  // Pacman Open
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(00000000),
  B8_2BIT(21111110),B8_2BIT(00000000),
  B8_2BIT(11111000),B8_2BIT(00000000),
  B8_2BIT(11111000),B8_2BIT(00000000),
  B8_2BIT(21111110),B8_2BIT(00000000),
  B8_2BIT(01111111),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000),
  // Pacman Half
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(11111200),B8_2BIT(00000000),
  B8_2BIT(11111200),B8_2BIT(00000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000),
  // Pacman Closed
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000)
};
const struct CRGB PacmanRightColTab[] =  {  CRGB(255, 255, 0), CRGB(100, 100, 0), CRGB(255, 255, 255)  };

const uint8_t PinkyData[] = 
{
  // Pinky Frame 1
  B8_2BIT(00001110),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(01122212),B8_2BIT(22000000),
  B8_2BIT(11122312),B8_2BIT(23100000),
  B8_2BIT(11122212),B8_2BIT(22100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11001110),B8_2BIT(01100000),
  // Pinky Frame 2
  B8_2BIT(00001110),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(01122212),B8_2BIT(22000000),
  B8_2BIT(11122312),B8_2BIT(23100000),
  B8_2BIT(11122212),B8_2BIT(22100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(10011011),B8_2BIT(00100000),
};
const struct CRGB PinkyColTab[] =  {  CRGB(255, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 255)  };

const uint8_t PacmanLeftData[] = 
{
  // Pacman Open
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00011111),B8_2BIT(11000000),
  B8_2BIT(00001111),B8_2BIT(11200000),
  B8_2BIT(00000011),B8_2BIT(11100000),
  B8_2BIT(00000011),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11200000),
  B8_2BIT(00011111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000),
  // Pacman Half
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(00000211),B8_2BIT(11100000),
  B8_2BIT(00000211),B8_2BIT(11100000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000),
  // Pacman Closed
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000)
};
const struct CRGB PacmanLeftColTab[] =  {  CRGB(255, 255, 0), CRGB(100, 100, 0), CRGB(255, 255, 255)  };

const uint8_t GhostData[] = 
{
  // Ghost Frame 1
  B8_2BIT(00001110),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(01122122),B8_2BIT(11000000),
  B8_2BIT(11122122),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11131313),B8_2BIT(11100000),
  B8_2BIT(11313131),B8_2BIT(31100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11001110),B8_2BIT(01100000),
  // Ghost Frame 2
  B8_2BIT(00001110),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(01122122),B8_2BIT(11000000),
  B8_2BIT(11122122),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11131313),B8_2BIT(11100000),
  B8_2BIT(11313131),B8_2BIT(31100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(10011011),B8_2BIT(00100000)
};
const struct CRGB GhostColTab[] =  {  CRGB(0, 0, 255), CRGB(255, 255, 255), CRGB(255, 90, 120)  };

cSprite SprPacmanRight(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PacmanRightData, PACMAN_FRAMES, _2BIT, PacmanRightColTab);
cSprite SprPinky(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PinkyData, PINKY_FRAMES, _2BIT, PinkyColTab);
cSprite SprPacmanLeft(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PacmanLeftData, PACMAN_FRAMES, _2BIT, PacmanLeftColTab);
cSprite SprGhost(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, GhostData, PINKY_FRAMES, _2BIT, GhostColTab);


void setup()
{
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds[0], leds.Size());
  FastLED.setBrightness(64);
  FastLED.clear(true);
  delay(500);
  FastLED.showColor(CRGB::Red);
  delay(1000);
  FastLED.showColor(CRGB::Lime);
  delay(1000);
  FastLED.showColor(CRGB::Blue);
  delay(1000);
  FastLED.showColor(CRGB::White);
  delay(1000);
  FastLED.show();

  SprPinky.SetPositionFrameMotion(-26/*X*/, 0/*Y*/, 0/*Frame*/, 2/*FrameRate*/, +1/*XChange*/, 2/*XChangeRate*/, 0/*YChange*/, 0/*YChangeRate*/);
  Sprites.AddSprite(&SprPinky);
  SprPacmanRight.SetPositionFrameMotion(-12/*X*/, 0/*Y*/, 0/*Frame*/, 4/*FrameRate*/, +1/*XChange*/, 2/*XChangeRate*/, 0/*YChange*/, 0/*YChangeRate*/);
  Sprites.AddSprite(&SprPacmanRight);
}


void loop()
{
  FastLED.clear();
  Sprites.UpdateSprites();
  if (Sprites.IsSprite(&SprPinky))
  {
    if ( (SprPinky.GetXYFlags() & SPRITE_X_OFF) && (SprPinky.m_X > 0) )
    {
      Sprites.RemoveSprite(&SprPinky);
      Sprites.RemoveSprite(&SprPacmanRight);
      SprGhost.SetPositionFrameMotion(50, 0, 0, 3, -1, 3, 0, 0);
      Sprites.AddSprite(&SprGhost);
      SprPacmanLeft.SetPositionFrameMotion(90, 0, 0, 4, -1, 2, 0, 0);
      Sprites.AddSprite(&SprPacmanLeft);
    }
  }
  else
  {
    if ( (SprPacmanLeft.GetXYFlags() & SPRITE_X_OFF) && (SprPacmanLeft.m_X < 0) )
    {
      Sprites.RemoveSprite(&SprGhost);
      Sprites.RemoveSprite(&SprPacmanLeft);
      SprPinky.SetPositionFrameMotion(-26, 0, 0, 2, 1, 2, 0, 0);
      Sprites.AddSprite(&SprPinky);
      SprPacmanRight.SetPositionFrameMotion(-12, 0, 0, 4, 1, 2, 0, 0);
      Sprites.AddSprite(&SprPacmanRight);
    }
  }
  FastLED.show();
  delay(10);
}
