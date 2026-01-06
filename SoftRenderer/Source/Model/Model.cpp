#include "Model.h"
#include "../Rendering/Screen.h"

Model::Model()
{
    VertexBuffer = new FVertexType[3];
    IndexBuffer = new unsigned long[3];

    VertexBuffer[0].Position.SetX(6);
    VertexBuffer[0].Position.SetY(6);

    VertexBuffer[1].Position.SetX(10);
    VertexBuffer[1].Position.SetY(0);

    VertexBuffer[2].Position.SetX(15);
    VertexBuffer[2].Position.SetY(6);

    IndexBuffer[0] = 0;
    IndexBuffer[1] = 1;
    IndexBuffer[2] = 2;

    VertexNum = 3;
    IndexNum = 3;
}

Model::~Model()
{
    if (VertexBuffer) delete[] VertexBuffer;
    if (IndexBuffer) delete[] IndexBuffer;
}

bool Model::Draw(UScreen* Screen)
{
    unsigned long TriangleNum = IndexNum / 3;

    for (int i=0; i<TriangleNum; i++)
    {
        FVertexType P1 = VertexBuffer[IndexBuffer[i*3 + 0]];
        FVertexType P2 = VertexBuffer[IndexBuffer[i*3 + 1]];
        FVertexType P3 = VertexBuffer[IndexBuffer[i*3 + 2]];

        Screen->DrawLine(P1.Position, P2.Position);
        Screen->DrawLine(P2.Position, P3.Position);
        Screen->DrawLine(P3.Position, P1.Position);
    }

    return true;
}