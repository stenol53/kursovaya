#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>

#define PI 3.14
#define E 2.71

class Functions
{
public:
    Functions();

    static float SinCos(float x, float y);
    static float Himmelblau(float x, float y);
    static float Ekli(float x, float y);
    static float Rastrigin(float x, float y);
};

#endif // FUNCTIONS_H
