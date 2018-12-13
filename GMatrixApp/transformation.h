#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

/**
 * @brief Enumeration of the identifiers for every transformation.
 */
enum transformationId {
    vectReflexion,
    vectScaling,
    vectTranslation,

    matBrightness,
    matNegative,
    matRedSat
};

// struct VectReflexion {  };
struct VectScaling { float scalePercent; };
struct VectTranslation { float xTranslating; float yTranslating; };
struct MatBrightness { unsigned char brightnessChange; };
// struct MatNegative {  };
struct MatRedSat { unsigned char redSatChange; };


/**
 * @brief Structure that can store data of any of the transformations and also an
 * identifier to which transformation it is representing.
 */
struct Transformation
{
  public:
    transformationId id;
    union {
        VectScaling vScaling;
        VectTranslation vTranslation;
        MatBrightness mBrightness;
        MatRedSat mRedSat;
    } dataOf;
};

#endif // TRANSFORMATION_H
