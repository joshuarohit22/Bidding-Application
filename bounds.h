#ifndef BOUNDS_H
#define BOUNDS_H

class Bounds
{
public:
    int lower;
    int upper;
    int min_value;
    int max_value;

    Bounds();
    Bounds(int min_value, int max_value);
    int min(int a, int b);
    int max(int a, int b);
    void setBounds(int lower, int upper);
};


#endif // BOUNDS_H
