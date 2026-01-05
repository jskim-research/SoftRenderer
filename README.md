# SoftRender

## Line Rotation

Line Rotation can be implemented using this renderer as below.

![LineRotation](./SoftRenderer/Resource/LineRotation.gif)

```cpp
while (true)
{
    float Radius = 5.0;
    int Sx = 10 + round(Radius * cos (GameTime));
    int Sy = 10 + round(Radius * sin (GameTime));

    Vector4 Start(10, 10, 0, 1);
    Vector4 End(Sx, Sy, 0, 1);

    // render
    ClearScreen();
    Screen.DrawLine(Start, End);
    Screen.Render();
    Screen.ClearBuffer();

    GotoXY(1, 1);
    this_thread::sleep_for(chrono::milliseconds((long long)(FrameTime * 1e3)));
    GameTime += FrameTime;
}
```