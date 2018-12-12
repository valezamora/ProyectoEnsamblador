#include "sitvgdata.h"

SITVGData::SITVGData()
{}

SITVGData::SITVGData (const SITVGData & other):
    figuresAmount ( other.figuresAmount ),
    width ( other.width ),
    height ( other.height ),
    figsColors ( new RGBColor[figuresAmount] ),
    figsThicknesses ( new unsigned short[figuresAmount] ),
    figsVerticesAmounts ( new short[figuresAmount] ),
    coordsAmount ( other.coordsAmount ),
    xCoords ( new float[coordsAmount] ),
    yCoords ( new float[coordsAmount] )

{
    for (unsigned int fig = 0; fig < figuresAmount; ++fig)
    {
        figsColors[fig] = other.figsColors[fig];
        figsThicknesses[fig] = other.figsThicknesses[fig];
        figsVerticesAmounts[fig] = other.figsVerticesAmounts[fig];
    }

    for (unsigned long long coord = 0; coord < coordsAmount; ++coord)
    {
        xCoords[coord] = other.xCoords[coord];
        yCoords[coord] = other.yCoords[coord];
    }
}

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
    int paddingCoords = (this->coordsAmount % 16);
    float * arr = new float [(this->coordsAmount + paddingCoords) * 2];
    float * xArr = arr;
    float * yArr = arr + (this->coordsAmount + paddingCoords);

    for (unsigned index = 0; index < this->coordsAmount; ++ index)
    {
        xArr[index] = this->xCoords[index];
        yArr[index] = this->yCoords[index];
    }

    for (int index = 0; index < paddingCoords; ++ index)
    {
        xArr[this->coordsAmount + index] = 0;
        yArr[this->coordsAmount + index] = 0;
    }

    return arr;
}

void SITVGData::setXsThenYs(const float *xsThenYsArray)
{
    int paddingCoords = (this->coordsAmount % 16);
    const float * xArr = xsThenYsArray;
    const float * yArr = xsThenYsArray + (this->coordsAmount + paddingCoords);

    for (unsigned index = 0; index < this->coordsAmount; ++ index)
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
