#include "vector.h"

class shape{
public:
    shape()= default;
    virtual ~shape() =default;

    virtual vector center() const= 0;

    virtual double perimeter() const= 0;
    virtual double area() const= 0;

    virtual bool operator==(const shape& obj) const= 0;
    virtual bool operator!=(const shape& obj) const = 0;
    virtual bool congruent_to(const shape& obj) const = 0;

    virtual void rotate(double angle) = 0;
    virtual void scale(double coefficient) = 0;
    virtual void translate(vector transform) = 0;
};
