#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Rendering/Screen.h"
#include "Rendering/PrintUtil.h"
#include "Model/Model.h"
using namespace std;

int main() 
{
    int FPS = 10;
    float FrameTime = 1.0 / FPS;
    float GameTime = 0.0;
    Model TestModel;

    int H = 20;
    int W = 20;
    UScreen Screen(W, H);

    Screen.ClearBuffer();

    SetColor(0);

    while (true)
    {
        // input
        
        // logic

        // M V P => Screen Space 까지 왔다고 가정

        float Radius = 5.0;
        int Sx = 10 + round(Radius * cos (GameTime));
        int Sy = 10 + round(Radius * sin (GameTime));

        Vector4 Start(10, 10, 0, 1);
        Vector4 End(Sx, Sy, 0, 1);

        // render
        ClearScreen();
        Screen.DrawLine(Start, End);
        // TestModel.Draw(&Screen);
        Screen.Render();
        Screen.ClearBuffer();

        GotoXY(1, 1);
        this_thread::sleep_for(chrono::milliseconds((long long)(FrameTime * 1e3)));
        GameTime += FrameTime;
    }

    SetColor(0);
    return 0;
}