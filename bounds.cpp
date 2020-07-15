#include "bounds.h"
#include "iostream"

Bounds::Bounds()
{

}

Bounds::Bounds(int min_value, int max_value)
{
    this->min_value = min_value;
    this->max_value = max_value;
    this->lower = min_value;
    this->upper = max_value;
}

int Bounds::min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int Bounds::max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

void Bounds::setBounds(int lower, int upper)
{
    this->lower = max(min_value, lower);
    this->upper = min(max_value, upper);

    std::cout << "min_value = " << min_value << " " << " this->lower = " << this->lower << std::endl;
    std::cout << "max_value = " << max_value << " " << " this->upper = " << this->upper << std::endl;
}
