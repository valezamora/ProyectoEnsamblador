#include "transformation.h"

Transformation::Transformation(transformationId id, int param1, int param2):
    id (id),
    parameters {param1, param2}
{}
Transformation::Transformation(transformationId id, float param1, float param2):
    id (id),
    parameters {0, 0}
{
    parameters.floating[0] = param1;
    parameters.floating[1] = param2;
}
