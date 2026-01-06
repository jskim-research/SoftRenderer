#ifndef __VECTOR_H__
#define __VECTOR_H__

/*
체의 구조 등 공리는 연산에 있어서 유일하게 믿을 수 있는 기반
체의 구조를 만족한다는 사실만 있어도 사칙연산에 대한 분배, 교환, 결합 성립 및 항등원/역원 존재함을 알 수 있음

예를 들어 곱셈에 대한 분배법칙이 성립한다는 공리에 따라 다음과 같이 전개 가능
(a + b) x (c + d) => (a + b) x c + (a + b) x d 

벡터 합 도 체의 구조를 띄는 스칼라 기반이라 (v1 + v2) = (v2 + v1) 등이 성립함을 공리를 기반으로 빠르게 파악 가능.

정의를 알아야 그 활용 방식을 알 수 있는 간단한 내용임.

Field (체) 의 11가지 공리
1. 연산에 대해 닫혀있음
2. 연산에 대한 결합법칙 성립
3. 연산에 대한 항등원 존재
4. 연산에 대한 역원 존재
5. 연산에 대한 교환법칙 성립
6. 두 번째 연산에 대해 닫혀있음
7. 두 번째 연산에 대한 결합법칙 성립
8. 첫 번째, 두 번째 연산에 대한 분배법칙 성립
9. 두 번째 연산에 대한 교환법칙 성립
10. 두 번째 연산에 대한 항등원 존재
11. 두 번째 연산에 대한 역원 존재 (단, 0은 제외)

벡터
- 체의 구조를 가지는 집합 두 개 이상을 원소 (스칼라) 로 가짐

벡터 공간
- 벡터들로 이루어진 체 집합
- 공리를 기반으로 벡터 합, 스칼라 곱 등 함수 성립
*/

class Vector4
{
public:
    Vector4(): X(0), Y(0), Z(0), W(0)
    {}

    Vector4(float _X, float _Y, float _Z, float _W): X(_X), Y(_Y), Z(_Z), W(_W)
    {}

    Vector4 operator+(const Vector4& Rhs)
    {
        return Add(Rhs);
    }

    Vector4 operator*(float Rhs)
    {
        return Multiply(Rhs);
    }

    bool operator==(const Vector4& Rhs)
    {
        return GetX() == Rhs.GetX() && GetY() == Rhs.GetY();
    }

    Vector4 Add(const Vector4& Rhs) const
    {
        Vector4 Result;
        Result.X = X + Rhs.X;
        Result.Y = Y + Rhs.Y;
        Result.Z = Z + Rhs.Z;
        Result.W = W + Rhs.W;
        return Result;
    }

    Vector4 Multiply(float Scalar) const
    {
        Vector4 Result;
        Result.X = X * Scalar;
        Result.Y = Y * Scalar;
        Result.Z = Z * Scalar;
        Result.W = W * Scalar;
        return Result;
    }

    inline float GetX() const { return X; }
    inline void SetX(float _X) { X = _X; }

    inline float GetY() const { return Y; }
    inline void SetY(float _Y) { Y = _Y; }

    inline float GetZ() const { return Z; }
    inline void SetZ(float _Z) { Z = _Z; }

    inline float GetW() const { return W; }
    inline void SetW(float _W) { W = _W; }

private:
    float X;
    float Y;
    float Z;
    float W;
};

void Print(const Vector4& Vector);

Vector4 operator*(float Scalar, const Vector4& Vector);

#endif