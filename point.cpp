#include "point.h"
#include <cmath>      
#include <limits>     

const double EPS = 10.0 * std::numeric_limits<double>::epsilon();

Point::Point(double x, double y)
{
    this->x = x;
    this->y = y;
}

double Point::getX() const
{
    return this->x;
}

double Point::getY() const
{
    return this->y;
}

bool Point::operator==(const Point& p) const
{
    return (fabs(this->x - p.x) < EPS) && (fabs(this->y - p.y) < EPS);
}

bool Point::operator!=(const Point& p) const
{
    return !(*this == p);
}
