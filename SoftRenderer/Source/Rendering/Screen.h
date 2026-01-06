#ifndef __DRAWING_H__
#define __DRAWING_H__
#include <iostream>
using namespace std;

class Vector4;

class UScreen
{
public:
    UScreen(int _W, int _H): W(_W), H(_H) 
    {
        BackBuffer = new char[H * W];
    }

    ~UScreen()
    {
        // BackBuffer 해제 필요
        // 복사는 막아놔야겠다
        delete[] BackBuffer;
    }

    void ClearBuffer()
    {
        for (int i=0; i<H*W; i++) BackBuffer[i] = ' ';
    }

    void SetPixel(int X, int Y, char C)
    {
        BackBuffer[W * Y + X] = C;
    }

    void Render()
    {
        for (int i=0; i<H; i++)
        {
            for (int j=0; j<W; j++)
            {
                cout << BackBuffer[W * i + j];
            }
            cout << endl;
        }
    }

    void DrawLine(const Vector4& Start, const Vector4& End);

private:
    bool ClipLine(const Vector4& V1, const Vector4& V2, Vector4& OutV1, Vector4& OutV2);
    unsigned int GetClipTag(const Vector4& V);
    
    
private:
    char* BackBuffer;
    int W;
    int H;
};


#endif