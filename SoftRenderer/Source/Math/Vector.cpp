#include <iostream>
#include "Vector.h"
using namespace std;

void Print(const Vector4& Vector)
{
    cout << '(' << Vector.GetX() << ' ' << Vector.GetY() << ' ' << Vector.GetZ() << ' ' << Vector.GetW() << ')' << endl;
}

Vector4 operator*(float Scalar, const Vector4& Vector)
{
    return Vector.Multiply(Scalar);
}
