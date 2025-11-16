
#include "pointwell.h"

//default constructor
PointWell::PointWell() 
    : pointMax(1u), pointCurrent(1u) {}

//parameter constructor
PointWell::PointWell (point_t inMax, point_t inCurrent)
    : pointMax(1u), pointCurrent(1u)
{
    setMax(inMax);
    setCurrent(inCurrent);

    if(pointCurrent > pointMax)
        pointCurrent = pointMax;
}

// ----- Getters -----
point_t PointWell::getMax() const { return pointMax; } //const means this function won't change any member variables
point_t PointWell::getCurrent() const { return pointCurrent; }

//// ----- Setters -----
bool PointWell::setMax(const point_t& newMax)
{
    if (newMax < 1)
        return false;

    pointMax = newMax;

    if (pointCurrent > newMax)
        pointCurrent = newMax;

    return true;
}

bool PointWell::setCurrent(const point_t& newCurrent)
{
    if (newCurrent < 1)
        return false;
    
    pointCurrent = (newCurrent > pointMax) ? pointMax : newCurrent;
    return true;
}

// ----- Utility -----

//reduce current point, returns 0 if reduction is more than current
void PointWell::reduceCurrent(const point_t& amount)
{
    pointCurrent = (amount > pointCurrent) ? 0 : pointCurrent -= amount;
}

//increase current point, returns max points if increase + current is more than max
void PointWell::increaseCurrent(const point_t& amount)
{
    if ((pointCurrent + amount) > pointMax)
        pointCurrent = pointMax;
    else
        pointCurrent += amount;
}


