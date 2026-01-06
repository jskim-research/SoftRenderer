#ifndef __MODEL_H__
#define __MODEL_H__

#include "../Math/Vector.h"

class UScreen;

struct FVertexType
{
    Vector4 Position;
};

class Model
{
public:
    Model();
    virtual ~Model();
    bool Draw(UScreen* Screen);

private:
    FVertexType* VertexBuffer;
    unsigned long* IndexBuffer;

    unsigned long VertexNum;
    unsigned long IndexNum;
};

#endif