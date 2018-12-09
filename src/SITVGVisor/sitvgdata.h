#ifndef SITVGDATA_H
#define SITVGDATA_H

#include "sitvgloader.h"
#include "rgbcolor.h"

/**
 * @brief The SITVGData class used for storing data of a .sitvg file.
 */
class SITVGData
{
    friend class SITVGLoader; // So only it may access to SITVGData's private info.

  private:
    /// Amount of figures.
    unsigned figuresAmount = 0;
    /// X size of the image.
    float width = 1;
    /// Y size of the image.
    float height = 1;

    /// Array with the color for each figure.
    RGBColor * figsColors = nullptr;
    /// Array with thickness of the lines in each figure.
    unsigned short * figsThicknesses = nullptr;
    /// Array with amounts of vertices that each figure has. Might be negative.
    short * figsVerticesAmounts = nullptr;

    /// Total amount of coordinates found in the image.
    unsigned long long coordsAmount = 0; // Not part of the raw file.

    /// Horizontal values for every coordinate in the image.
    float * xCoords = nullptr;
    /// Vertical values for every coordinate in the image.
    float * yCoords = nullptr;

  public:
    /// Default constructor.
    SITVGData ();

    /// Disabled copy constructor.
    SITVGData (const SITVGData & other) = delete;

    /// Move constructor.
    SITVGData (SITVGData && other);

    /// Destructor.
    ~SITVGData();

    /// Disabled copy assignment operator.
    SITVGData & operator= (const SITVGData & other) = delete;

    /// Move assignment operator.
    SITVGData & operator= (SITVGData && other);

    /**
     * @brief Get method for the image's number of figures.
     */
    inline float getFigsAmount() const { return this->figuresAmount; }

    /**
     * @brief Get method for the image's width.
     */
    inline float getWidth() const { return this->width; }

    /**
     * @brief Get method for the image's height.
     */
    inline float getHeight() const { return this->height; }

    /**
     * @brief Get method for a figure's line color.
     */
    inline const RGBColor colorAt (unsigned figureNo) const { return this->figsColors[figureNo]; }

    /**
     * @brief Get method for a figure's line thickness.
     */
    inline unsigned short thicknessAt (unsigned figureNo) const { return this->figsThicknesses[figureNo]; }

    /**
     * @brief Get method for a figure's number of vertices.
     */
    inline short verticesAmountAt (unsigned figureNo) const { return this->figsVerticesAmounts [figureNo]; }

    /**
     * @brief Get method for the x component of the coordinate number index.
     */
    inline float xAt(unsigned long long index) const { return this->xCoords[index]; }

    /**
     * @brief Get method for the y component of the coordinate number index.
     */
    inline float yAt(unsigned long long index) const { return this->yCoords[index]; }

    /**
     * @brief Get method for sum of the amounts of coordinates in every figure.
     */
    inline unsigned long long getCoordsAmount() const { return this->coordsAmount; }

    /**
     * @brief Get a copy of the coordinates in this SITVG image.
     * @details The first half of the array is for X values, while the second half
     * is for the Y values. The size of the array is, therefore, twice the amount
     * of coordinates in the image.
     * @return Float array with the X values of the coordinates followed by the Y values.
     * @remarks The returned array must be deleted with the standard function delete [].
     */
    float * getXsThenYsArray() const;

    /**
     * @brief Sets the coordinates to a copy of the ones used as argument.
     * @param xsThenYsArray Array that contains all of the new X values to set, followed
     * by the new Y values.
     * @remarks Size of xsThenYsArray must be at least twice of the amount of coordinates
     * in the image.
     */
    void setXsThenYs( const float * xsThenYsArray );

    /**
     * @brief Deletes all the data contained in the object, freeing dynamic memory.
     */
    void clear();

};

#endif // SITVGDATA_H
