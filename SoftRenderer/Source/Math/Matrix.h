#ifndef __MATRIX_H__
#define __MATRIX_H__

// 전방 선언 등으로 바꾸는게 좋음
// 현재는 구현 편의로 헤더에 구현을 몰아서 쓰고 있어서 이렇게 함
#include "Vector.h"

/*

행렬
- 하나의 벡터 공간을 다른 벡터 공간으로 변환 (새로운 벡터 공간도 Basis Vector 의 선형 결합 구조 유지)
- 변환 과정에서 선형 함수만 사용하므로 선형 변환

Affine Space
- 이동 변환의 경우 원점을 벗어나므로 선형성 위배
    - 이를 해결하기 위해 이동 변환을 위한 새로운 축을 제안 => 해당 축이 이동에 대한 연결 고리가 됨
    - 해당 축에서 w = 1 인 곳이 Affine Space

Affine Transform
- 새로운 축의 변화 (이동) 도 고려한 변환

*/

class Matrix4
{
public:
    Matrix4() {}

    Matrix4(Vector4 _Column1, Vector4 _Column2, Vector4 _Column3, Vector4 _Column4):
        Column1(_Column1), Column2(_Column2), Column3(_Column3), Column4(_Column4)
    {}

    Vector4 Multiply(const Vector4& Vector)
    {
        Vector4 Result;

        Result = Result.Add(Column1.Multiply(Vector.GetX()));
        Result = Result.Add(Column2.Multiply(Vector.GetY()));
        Result = Result.Add(Column3.Multiply(Vector.GetZ()));
        Result = Result.Add(Column4.Multiply(Vector.GetW()));

        return Result;
    }

private:
    Vector4 Column1;
    Vector4 Column2;
    Vector4 Column3;
    Vector4 Column4;
};

#endif