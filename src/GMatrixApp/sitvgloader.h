#ifndef SITVGLOADER_H
#define SITVGLOADER_H

#include "rgbcolor.h"
#include "sitvgdata.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class SITVGData; // Forward declaration.

/**
 * @brief The SITVGLoader class used for opening and reading or writing SITVG files.
 */
class SITVGLoader
{
  private:
    struct Coordinates
    {
      public:
        float x, y;
        Coordinates(float x = 0, float y = 0):
            x (x),
            y (y)
        {}
    };
  public:

    /// Default constructor
    SITVGLoader();

    /**
     * @brief Opens the SITVG file at filePath, reads it and stores its data in a structure.
     * @param filePath Path to the file to be read.
     * @return SITVGData object with the read data.
     * @remarks The path must be valid, and the file must exist.
     */
    static SITVGData readSitvgFile (const std::string & filePath);

    /**
     * @brief Writes data of a SITVGData object to the file at filePath.
     * @param filePath Path to save the file. Might not contain a pre-existing file.
     * @param data Data to be written to the file.
     * @remarks If the file at filePath already exists, it will be rewritten.
     */
    static void writeSitvgFile (const std::string filePath, const SITVGData & data);
};

#endif // SITVGLOADER_H
