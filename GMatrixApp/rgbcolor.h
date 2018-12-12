#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#ifndef BYTE_TYPE
#define BYTE_TYPE
typedef unsigned char byte;
#endif // BYTE_TYPE

/**
 * @brief The RGBColor Structure for storing a 24-bit rgb color.
 */
struct RGBColor
{
  public:
    byte red;
    byte green;
    byte blue;

    /**
     * @brief Default constructor and converting constructor.
     * @param red Red value.
     * @param green Green value.
     * @param blue Blue value.
     */
    RGBColor (byte red = 0, byte green = 0, byte blue = 0):
        red (red),
        green (green),
        blue (blue)
    {}

    /**
     * @brief Converts the structure to a ARGB unsigned int color, one more Qt friendly.
     */
    inline unsigned argb() const { return (0xFF << 24) | ((unsigned)red << 16) | ((unsigned)green << 8) | ((unsigned)blue); }
};

#endif // RGBCOLOR_H
