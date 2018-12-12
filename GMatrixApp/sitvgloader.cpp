#include "sitvgloader.h"

#define READ_ITEM(ITEM) \
    read( (char *) &ITEM, sizeof(ITEM) )

#define WRITE_ITEM(ITEM) \
    write( (char *) &ITEM, sizeof(ITEM) )

SITVGLoader::SITVGLoader()
{}

SITVGData SITVGLoader::readSitvgFile(const std::string & filePath)
{
    SITVGData data;
    std::ifstream file (filePath, std::ios_base::in | std::ios_base::binary);
    std::vector<Coordinates> coords;

    file.READ_ITEM(data.figuresAmount);
    file.READ_ITEM(data.width);
    file.READ_ITEM(data.height);

    data.figsColors = new RGBColor[data.figuresAmount];
    data.figsThicknesses = new unsigned short [data.figuresAmount];
    data.figsVerticesAmounts = new short [data.figuresAmount];

    float x = 0, y = 0;
    short verAmount = 0;

    for (unsigned fig = 0; fig < data.figuresAmount; ++fig)
    {
        file.READ_ITEM(data.figsColors[fig]);
        file.READ_ITEM(data.figsThicknesses[fig]);
        file.READ_ITEM(data.figsVerticesAmounts[fig]);

        verAmount = data.figsVerticesAmounts[fig];
        if (verAmount < 0)
            verAmount *= -1;

        for (short ver = 0; ver < verAmount; ++ver)
        {
            file.READ_ITEM(x);
            file.READ_ITEM(y);
            coords.push_back(Coordinates(x,y));
        }
    }

    data.coordsAmount = coords.size();
    data.xCoords = new float[data.coordsAmount];
    data.yCoords = new float[data.coordsAmount];

    for (unsigned long long coord = 0; coord < data.coordsAmount; ++coord)
    {
        data.xCoords[coord] = coords[coord].x;
        data.yCoords[coord] = coords[coord].y;
    }

    coords.clear();

    file.close();

    return data;
}

void SITVGLoader::writeSitvgFile(const std::string filePath, const SITVGData &data)
{
    std::ofstream file (filePath, std::ios_base::out | std::ios_base::binary);

    file.WRITE_ITEM(data.figuresAmount);
    file.WRITE_ITEM(data.width);
    file.WRITE_ITEM(data.height);

    short verAmount = 0;
    unsigned long long coordIndex = 0;

    for (unsigned fig = 0; fig < data.figuresAmount; ++fig)
    {
        file.WRITE_ITEM(data.figsColors[fig]);
        file.WRITE_ITEM(data.figsThicknesses[fig]);
        file.WRITE_ITEM(data.figsVerticesAmounts[fig]);

        verAmount = data.figsVerticesAmounts[fig];
        if (verAmount < 0)
            verAmount *= -1;

        for (short ver = 0; ver < verAmount; ++ver)
        {
            file.WRITE_ITEM(data.xCoords[coordIndex]);
            file.WRITE_ITEM(data.yCoords[coordIndex ++]);
        }
    }

    file.close();
}
