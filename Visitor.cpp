#include "Visitor.h"

int Visitor::chooseVertex(int range)
{
    return 0;
}

void Visitor::addDistance(float const distance)
{
    this->distanceTraveled += distance;
}

float Visitor::getDistance()
{
    return this->distanceTraveled;
}