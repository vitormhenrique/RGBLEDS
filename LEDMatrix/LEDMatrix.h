#ifndef LEDMatrix_h
#define LEDMatrix_h

enum MatrixType_t { HORIZONTAL_MATRIX,
                    VERTICAL_MATRIX,
                    HORIZONTAL_ZIGZAG_MATRIX,
                    VERTICAL_ZIGZAG_MATRIX };

class cLEDMatrixBase
{
  friend class cSprite;

  protected:
    int16_t m_Width, m_Height;
    MatrixType_t m_Type;
    struct CRGB *m_LED;
    struct CRGB m_OutOfBounds;

  public:
    cLEDMatrixBase();
    virtual uint16_t mXY(uint16_t x, uint16_t y)=0;

    struct CRGB *operator[](int n);
    struct CRGB &operator()(int16_t x, int16_t y);

    int Size()  { return(m_Width * m_Height); }
    int Width() { return(m_Width);  }
    int Height()  { return(m_Height); }

    void HorizontalMirror(bool FullHeight = true);
    void VerticalMirror();
    void QuadrantMirror();
    void QuadrantRotateMirror();
    void TriangleTopMirror(bool FullHeight = true);
    void TriangleBottomMirror(bool FullHeight = true);
    void QuadrantTopTriangleMirror();
    void QuadrantBottomTriangleMirror();

    void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col);
    void DrawRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col);
    void DrawCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col);
    void DrawFilledRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col);
    void DrawFilledCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col);
};

template<int16_t tWidth, int16_t tHeight, MatrixType_t tMType> class cLEDMatrix : public cLEDMatrixBase
{
  private:
    static const int16_t m_absWidth = (tWidth * ((tWidth < 0) * -1 + (tWidth > 0)));
    static const int16_t m_absHeight = (tHeight * ((tHeight < 0) * -1 + (tHeight > 0)));
    struct CRGB p_LED[m_absWidth * m_absHeight];

  public:
    cLEDMatrix()
    {
      m_Width = m_absWidth;
      m_Height = m_absHeight;
      m_Type = tMType;
      m_LED = p_LED;
    }
    // virtual uint16_t mXY(uint16_t x, uint16_t y)
    // {
    //   if (tWidth < 0)
    //     x = (m_absWidth - 1) - x;
    //   if (tHeight < 0)
    //     y = (m_absHeight - 1) - y;
    //   if (tMType == HORIZONTAL_MATRIX)
    //     return((y * m_absWidth) + x);
    //   else if (tMType == VERTICAL_MATRIX)
    //     return((x * m_absHeight) + y);
    //   else if (tMType == HORIZONTAL_ZIGZAG_MATRIX)
    //   {
    //     if (y % 2)
    //       return((((y + 1) * m_absWidth) - 1) - x);
    //     else
    //       return((y * m_absWidth) + x);
    //   }
    //   else /* if (tMType == VERTICAL_ZIGZAG_MATRIX) */
    //   {
    //     if (x % 2)
    //       return((((x + 1) * m_absHeight) - 1) - y);
    //     else
    //       return((x * m_absHeight) + y);
    //   }
    // }
    static const uint8_t kMatrixWidth = 16;
    static const uint8_t kMatrixHeight = 5;

    // Pixel layout
    //
    //      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
    //   +------------------------------------------------
    // 0 |  .  0  1  2  3  4  5  6  7  8  9 10 11 12 13  .
    // 1 | 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14
    // 2 | 30 31 32 33 34 35 36  .  . 37 38 39 40 41 42 43
    // 3 | 57 56 55 54 53 52 51  .  . 50 49 48 47 46 45 44
    // 4 |  . 58 59 60 61 62  .  .  .  . 63 64 65 66 67  .

    #define NUM_LEDS (kMatrixWidth * kMatrixHeight)
    CRGB leds[ NUM_LEDS ];


    // This function will return the right 'led index number' for 
    // a given set of X and Y coordinates on your RGB Shades. 
    // This code, plus the supporting 80-byte table is much smaller 
    // and much faster than trying to calculate the pixel ID with code.
    #define LAST_VISIBLE_LED 67
    virtual uint16_t mXY(uint16_t x, uint16_t y)
    {
      // any out of bounds address maps to the first hidden pixel
      if( (x >= kMatrixWidth) || (y >= kMatrixHeight) ) {
        return (LAST_VISIBLE_LED + 1);
      }

      const uint16_t ShadesTable[] = {
        74, 58, 59, 60, 61, 62, 75, 76, 77, 78, 63, 64, 65, 66, 67, 79,
        57, 56, 55, 54, 53, 52, 51, 72, 73, 50, 49, 48, 47, 46, 45, 44,
        30, 31, 32, 33, 34, 35, 36, 70, 71, 37, 38, 39, 40, 41, 42, 43,
        29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14,
        68,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 69       
      };

      uint16_t i = (y * kMatrixWidth) + x;
      uint16_t j = ShadesTable[i];
      return j;
    }



    void ShiftLeft(void)
    {
      switch (tMType)
      {
        case HORIZONTAL_MATRIX:
          if (tWidth > 0)
            HPWSL();
          else
            HNWSL();
          break;
        case VERTICAL_MATRIX:
          if (tWidth > 0)
            VPWSL();
          else
            VNWSL();
          break;
        case HORIZONTAL_ZIGZAG_MATRIX:
          if (tWidth > 0)
            HZPWSL();
          else
            HZNWSL();
          break;
        case VERTICAL_ZIGZAG_MATRIX:
          if (tWidth > 0)
            VZPWSL();
          else
            VZNWSL();
          break;
      }
    }

    void ShiftRight(void)
    {
      switch (tMType)
      {
        case HORIZONTAL_MATRIX:
          if (tWidth > 0)
            HNWSL();
          else
            HPWSL();
          break;
        case VERTICAL_MATRIX:
          if (tWidth > 0)
            VNWSL();
          else
            VPWSL();
          break;
        case HORIZONTAL_ZIGZAG_MATRIX:
          if (tWidth > 0)
            HZNWSL();
          else
            HZPWSL();
          break;
        case VERTICAL_ZIGZAG_MATRIX:
          if (tWidth > 0)
            VZNWSL();
          else
            VZPWSL();
          break;
      }
    }

    void ShiftDown(void)
    {
      switch (tMType)
      {
        case HORIZONTAL_MATRIX:
          if (tHeight > 0)
            HPHSD();
          else
            HNHSD();
          break;
        case VERTICAL_MATRIX:
          if (tHeight > 0)
            VPHSD();
          else
            VNHSD();
          break;
        case HORIZONTAL_ZIGZAG_MATRIX:
          if (tHeight > 0)
            HZPHSD();
          else
            HZNHSD();
          break;
        case VERTICAL_ZIGZAG_MATRIX:
          if (tHeight > 0)
            VZPHSD();
          else
            VZNHSD();
          break;
      }
    }

    void ShiftUp(void)
    {
      switch (tMType)
      {
        case HORIZONTAL_MATRIX:
          if (tHeight > 0)
            HNHSD();
          else
            HPHSD();
          break;
        case VERTICAL_MATRIX:
          if (tHeight > 0)
            VNHSD();
          else
            VPHSD();
          break;
        case HORIZONTAL_ZIGZAG_MATRIX:
          if (tHeight > 0)
            HZNHSD();
          else
            HZPHSD();
          break;
        case VERTICAL_ZIGZAG_MATRIX:
          if (tHeight > 0)
            VZNHSD();
          else
            VZPHSD();
          break;
      }
    }

  private:
  	// Functions used by ShiftLeft & ShiftRight
    void HPWSL(void)
    {
      int16_t i = 0;
      for (int16_t y=m_absHeight; y>0; --y)
      {
        for (int16_t x=m_absWidth-1; x>0; --x)
          p_LED[i++] = p_LED[i];
        p_LED[i++] = CRGB(0, 0, 0);
      }
    }
    void HNWSL(void)
    {
      int16_t i = m_absWidth - 1;
      for (int16_t y=m_absHeight; y>0; --y)
      {
        for (int16_t x=m_absWidth-1; x>0; --x)
          p_LED[i--] = p_LED[i];
        p_LED[i] = CRGB(0, 0, 0);
        i += ((m_absWidth * 2) - 1);
      }
    }
    void VPWSL(void)
    {
      int16_t i = 0;
      int16_t j = m_absHeight;
      for (int16_t x=m_absWidth-1; x>0; --x)
      {
        for (int16_t y=m_absHeight; y>0; --y)
          p_LED[i++] = p_LED[j++];
      }
      for (int16_t y=m_absHeight; y>0; --y)
        p_LED[i++] = CRGB(0, 0, 0);
    }
    void VNWSL(void)
    {
      int16_t i = (m_absHeight * m_absWidth) - 1;
      int16_t j = i - m_absHeight;
      for (int16_t x=m_absWidth-1; x>0; --x)
      {
        for (int16_t y=m_absHeight; y>0; --y)
          p_LED[i--] = p_LED[j--];
      }
      for (int16_t y=m_absHeight; y>0; --y)
        p_LED[i--] = CRGB(0, 0, 0);
    }
    void HZPWSL(void)
    {
      int16_t i = 0;
      for (int16_t y=m_absHeight; y>0; y-=2)
      {
        for (int16_t x=m_absWidth-1; x>0; --x)
          p_LED[i++] = p_LED[i];
        p_LED[i++] = CRGB(0, 0, 0);
        if (y > 1)
        {
          i += (m_absWidth - 1);
          for (int16_t x=m_absWidth-1; x>0; --x)
            p_LED[i--] = p_LED[i];
          p_LED[i] = CRGB(0, 0, 0);
          i += m_absWidth;
        }
      }
    }
    void HZNWSL(void)
    {
      int16_t i = m_absWidth - 1;
      for (int16_t y=m_absHeight; y>0; y-=2)
      {
        for (int16_t x=m_absWidth-1; x>0; --x)
          p_LED[i--] = p_LED[i];
        p_LED[i] = CRGB(0, 0, 0);
        if (y > 1)
        {
          i += m_absWidth;
          for (int16_t x=m_absWidth-1; x>0; --x)
            p_LED[i++] = p_LED[i];
          p_LED[i] = CRGB(0, 0, 0);
          i += m_absWidth;
        }
      }
    }
    void VZPWSL(void)
    {
      int16_t i = 0;
      int16_t j = (m_absHeight * 2) - 1;
      for (int16_t x=m_absWidth-1; x>0; x-=2)
      {
        for (int16_t y=m_absHeight; y>0; --y)
          p_LED[i++] = p_LED[j--];
        if (x > 1)
        {
          j += (m_absHeight * 2);
          for (int16_t y=m_absHeight; y>0; --y)
            p_LED[i++] = p_LED[j--];
          j += (m_absHeight * 2);
        }
      }
      for (int16_t y=m_absHeight; y>0; y--)
        p_LED[i++] = CRGB(0, 0, 0);
    }
    void VZNWSL(void)
    {
      int16_t i = (m_absHeight * m_absWidth) - 1;
      int16_t j = m_absHeight * (m_absWidth - 2);
      for (int16_t x=m_absWidth-1; x>0; x-=2)
      {
        for (int16_t y=m_absHeight; y>0; --y)
          p_LED[i--] = p_LED[j++];
        if (x > 1)
        {
          j -= (m_absHeight * 2);
          for (int16_t y=m_absHeight; y>0; --y)
            p_LED[i--] = p_LED[j++];
          j -= (m_absHeight * 2);
        }
      }
      for (int16_t y=m_absHeight; y>0; y--)
        p_LED[i--] = CRGB(0, 0, 0);
    }

  	// Functions used by ShiftDown & ShiftUp
    void HPHSD(void)
    {
      int16_t i = 0;
      int16_t j = m_absWidth;
      for (int16_t y=m_absHeight-1; y>0; --y)
      {
        for (int16_t x=m_absWidth; x>0; --x)
          p_LED[i++] = p_LED[j++];
      }
      for (int16_t x=m_absWidth; x>0; --x)
        p_LED[i++] = CRGB(0, 0, 0);
    }
    void HNHSD(void)
    {
      int16_t i = (m_absWidth * m_absHeight) - 1;
      int16_t j = i - m_absWidth;
      for (int16_t y=m_absHeight-1; y>0; --y)
      {
        for (int16_t x=m_absWidth; x>0; --x)
          p_LED[i--] = p_LED[j--];
      }
      for (int16_t x=m_absWidth; x>0; --x)
        p_LED[i--] = CRGB(0, 0, 0);
    }
    void VPHSD(void)
    {
      int16_t i = 0;
      for (int16_t x=m_absWidth; x>0; --x)
      {
        for (int16_t y=m_absHeight-1; y>0; --y)
          p_LED[i++] = p_LED[i];
        p_LED[i++] = CRGB(0, 0, 0);
      }
    }
    void VNHSD(void)
    {
      int16_t i = m_absHeight - 1;
      for (int16_t x=m_absWidth; x>0; --x)
      {
        for (int16_t y=m_absHeight-1; y>0; --y)
          p_LED[i--] = p_LED[i];
        p_LED[i] = CRGB(0, 0, 0);
        i += ((m_absHeight * 2) - 1);
      }
    }
    void HZPHSD(void)
    {
      int16_t i = 0;
      int16_t j = (m_absWidth * 2) - 1;
      for (int16_t y=m_absHeight-1; y>0; y-=2)
      {
        for (int16_t x=m_absWidth; x>0; --x)
          p_LED[i++] = p_LED[j--];
        if (y > 1)
        {
          j += (m_absWidth * 2);
          for (int16_t x=m_absWidth; x>0; --x)
            p_LED[i++] = p_LED[j--];
          j += (m_absWidth * 2);
        }
      }
      for (int16_t x=m_absWidth; x>0; x--)
        p_LED[i++] = CRGB(0, 0, 0);
    }
    void HZNHSD(void)
    {
      int16_t i = (m_absWidth * m_absHeight) - 1;
      int16_t j = m_absWidth * (m_absHeight - 2);
      for (int16_t y=m_absHeight-1; y>0; y-=2)
      {
        for (int16_t x=m_absWidth; x>0; --x)
          p_LED[i--] = p_LED[j++];
        if (y > 1)
        {
          j -= (m_absWidth * 2);
          for (int16_t x=m_absWidth; x>0; --x)
            p_LED[i--] = p_LED[j++];
          j -= (m_absWidth * 2);
        }
      }
      for (int16_t x=m_absWidth; x>0; x--)
        p_LED[i--] = CRGB(0, 0, 0);
    }
    void VZPHSD(void)
    {
      int16_t i = 0;
      for (int16_t x=m_absWidth; x>0; x-=2)
      {
        for (int16_t y=m_absHeight-1; y>0; --y)
          p_LED[i++] = p_LED[i];
        p_LED[i++] = CRGB(0, 0, 0);
        if (x > 1)
        {
          i += (m_absHeight - 1);
          for (int16_t y=m_absHeight-1; y>0; --y)
            p_LED[i--] = p_LED[i];
          p_LED[i] = CRGB(0, 0, 0);
          i += m_absHeight;
        }
      }
    }
    void VZNHSD(void)
    {
      int16_t i = m_absHeight - 1;
      for (int16_t x=m_absWidth; x>0; x-=2)
      {
        for (int16_t y=m_absHeight-1; y>0; --y)
          p_LED[i--] = p_LED[i];
        p_LED[i] = CRGB(0, 0, 0);
        if (x > 1)
        {
          i += m_absHeight;
          for (int16_t y=m_absHeight-1; y>0; --y)
            p_LED[i++] = p_LED[i];
          p_LED[i] = CRGB(0, 0, 0);
          i += m_absHeight;
        }
      }
    }

};

#endif
