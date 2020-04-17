#include "functions.h"

Functions::Functions()
{

}

float Functions::SinCos(float x, float y)
{
    return sinf(x)*cosf(y);
}

float Functions::Himmelblau(float x, float y)
{
    return (powf((powf(x,2) + y - 11),2) + powf((x + powf(y,2) - 7),2));
}

float Functions::Ekli(float x, float y)
{
    return (-20 * expf(-0.2 * sqrtf(0.5 * (powf(x,2) + powf(y,2)))) - expf(0.5 * (cosf(2*PI*x) + cosf(2*PI*y))) + E + 20);
}

float Functions::Rastrigin(float x, float y)
{
    int n = 2;
    return 10*n + (powf(x,2) - 10 * cosf(2*PI*x)) + (powf(y,2) - 10 * cosf(2*PI*y));
}
