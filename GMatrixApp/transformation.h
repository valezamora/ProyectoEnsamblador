#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

/**
 * @brief Enumeration of the identifiers for every transformation.
 */
enum transformationId : int
{
    vectReflexion,
    vectScaling,
    vectTranslation,

    matBrightness,
    matNegative,
    matContrast,

    invalidTransformation = -1
};

// New version
/**
 * @brief The Transformation class contains data of any transformation:
 * the identifier number and the parameters used, if any.
 */
class Transformation
{
  public:
    /// Transformation identifier.
    transformationId id;

  private:
    /// Parameters data.
    union
    {
        int integer[2];
        float floating[2];
    } parameters;

  public:

    /// Constructor of transformation with integer parameters
    explicit Transformation (transformationId id = invalidTransformation, int param1 = 0, int param2 = 0);
    /// Constructor of transformation with floating point parameters.
    explicit Transformation (transformationId id, float param1, float param2 = 0);

    /// Easy read only access to the integer parameters
    inline const int & intParam (int index) const { return parameters.integer[(index-1)%2]; }
    /// Easy read and write access to the integer parameters
    inline int & intParam (int index) { return parameters.integer[(index-1)%2]; }
    /// Easy read only access to the floating point parameters
    inline const float & floatParam (int index) const { return parameters.floating[(index-1)%2]; }
    /// Easy read and write access to the floating point parameters
    inline float & floatParam (int index) { return parameters.floating[(index-1)%2]; }
};

#endif // TRANSFORMATION_H
