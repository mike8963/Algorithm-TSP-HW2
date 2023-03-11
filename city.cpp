#include "tsp.hpp"

city::city(string str,double a,double b):cityname(str), x(a), y(b){}

double distance(city a, city b)
{
    double x_shift = a.x - b.x;
    double y_shift = a.y - b.y;
    return sqrt(x_shift * x_shift + y_shift * y_shift);
}
string city::getName()
{
    return cityname;
}
double city::get_x()
{
    return x;
}
double city::get_y()
{
    return y;
}
