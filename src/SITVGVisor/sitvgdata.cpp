#include "sitvgdata.h"

SITVGData::SITVGData()
{}

SITVGData::SITVGData (SITVGData && other):
    figuresAmount ( other.figuresAmount ),
    width ( other.width ),
    height ( other.height ),
    figsColors ( other.figsColors ),
    figsThicknesses ( other.figsThicknesses ),
    figsVerticesAmounts ( other.figsVerticesAmounts ),
    coordsAmount ( other.coordsAmount ),
    xCoords ( other.xCoords ),
    yCoords ( other.yCoords )

{
    // Destroy other.
    other.figuresAmount = 0;
    other.width = 1;
    other.height = 1;
    other.figsColors = nullptr;
    other.figsThicknesses = nullptr;
    other.figsVerticesAmounts = nullptr;
    other.coordsAmount = 0;
    other.xCoords = nullptr;
    other.yCoords = nullptr;
}


SITVGData::~SITVGData()
{
    this->clear();
}

SITVGData & SITVGData::operator= (SITVGData && other)
{
    // Copy (transfer) all data.
    this->figuresAmount = other.figuresAmount;
    this->width = other.width;
    this->height = other.height;
    this->figsColors = other.figsColors;
    this->figsThicknesses = other.figsThicknesses;
    this->figsVerticesAmounts = other.figsVerticesAmounts;
    this->coordsAmount = other.coordsAmount;
    this->xCoords = other.xCoords;
    this->yCoords = other.yCoords;

    // Empty other.
    other.figuresAmount = 0;
    other.width = 1;
    other.height = 1;
    other.figsColors = nullptr;
    other.figsThicknesses = nullptr;
    other.figsVerticesAmounts = nullptr;
    other.coordsAmount = 0;
    other.xCoords = nullptr;
    other.yCoords = nullptr;

    return *this;
}

float *SITVGData::getXsThenYsArray() const
{
    float * arr = new float [this->coordsAmount << 1];
    float * xArr = arr;
    float * yArr = arr + this->coordsAmount;

    for (unsigned long long index = 0; index < this->coordsAmount; ++ index)
    {
        xArr[index] = this->xCoords[index];
        yArr[index] = this->yCoords[index];
    }

    return arr;
}

void SITVGData::setXsThenYs(const float *xsThenYsArray)
{
    const float * xArr = xsThenYsArray;
    const float * yArr = xsThenYsArray + this->coordsAmount;

    for (unsigned long long index = 0; index < this->coordsAmount; ++ index)
    {
        this->xCoords[index] = xArr[index];
        this->yCoords[index] = yArr[index];
    }
}

void SITVGData::clear()
{
    delete [] figsColors;
    delete [] figsThicknesses;
    delete [] figsVerticesAmounts;
    delete [] xCoords;
    delete [] yCoords;
}
