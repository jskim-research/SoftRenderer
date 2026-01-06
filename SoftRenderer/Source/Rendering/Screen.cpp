#include "Screen.h"
#include "../Math/Vector.h"

void UScreen::DrawLine(const Vector4& Start, const Vector4& End)
{
    // Brensenham 알고리즘

    // Pixel Shader Input 으로 생각
    // Start, End => 왼쪽 위 꼭짓점 (0, 0), 오른쪽 아래 꼭짓점 (W, H)
    Vector4 ClipStart;
    Vector4 ClipEnd;
    if (!ClipLine(Start, End, ClipStart, ClipEnd)) return;
    
    // ClipStart, ClipEnd 를 Screen Coordinate 로 바꿔줘야 함 (Pixel 좌표)
    // 0~0.99999... => 0 mapping
    // W 또는 H 일 땐 -1 해줘야 함 (좀 이상한거같긴한데)
    
    ClipStart.SetX(floor(ClipStart.GetX()));
    ClipStart.SetY(floor(ClipStart.GetY()));
    ClipEnd.SetX(floor(ClipEnd.GetX()));
    ClipEnd.SetY(floor(ClipEnd.GetY()));

    if (ClipStart.GetX() == W) ClipStart.SetX(W - 1);
    if (ClipStart.GetY() == H) ClipStart.SetY(H - 1);

    if (ClipEnd.GetX() == W) ClipEnd.SetX(W - 1);
    if (ClipEnd.GetY() == H) ClipEnd.SetY(H - 1);

    int X = ClipStart.GetX();
    int Y = ClipStart.GetY();
    int Dx = ClipEnd.GetX() - ClipStart.GetX();
    int Dy = ClipEnd.GetY() - ClipStart.GetY();

    int Tx = 0;
    int Ty = 0;

    if (Dx != 0) Tx = Dx / abs(Dx);
    if (Dy != 0) Ty = Dy / abs(Dy);

    int F1 = 2 * Dy * Tx;
    int F2 = 2 * Dx * Ty;
    int F = 2 * Dy * Tx - Dx * Ty;

    bool IsGradual = Dx == 0 || Dy == 0 || abs((float) Dy / Dx) <= 1;
    if (IsGradual)
    {
        F1 = 2 * Dy * Tx;
        F2 = 2 * Dx * Ty;
        F = F1 - F2 / 2;
    }
    else
    {
        F1 = 2 * Dx * Ty;
        F2 = 2 * Dy * Tx;
        F = F1 - F2 / 2;
    }

    SetPixel(X, Y, '*');
    while (X != ClipEnd.GetX() || Y != ClipEnd.GetY())
    {
        bool Det = false;

        // 1, 2, 5, 6 팔분면
        if (Tx * Ty > 0)
            Det = F < 0;
        // 3, 4, 7, 8 팔분면
        else
            Det = F > 0;

        if (Det)
        {
            F += F1;

            if (IsGradual)
                X += Tx;
            else
                Y += Ty;
        }
        else
        {
            F += F1 - F2;
            X += Tx;
            Y += Ty;
        }

        SetPixel(X, Y, '*');
    }
}

bool UScreen::ClipLine(const Vector4& V1, const Vector4& V2, Vector4& OutV1, Vector4& OutV2)
{
    // Cohen Sutherland Line Clip 알고리즘
    // V1, V2 => 왼쪽 위 꼭짓점 (0, 0), 오른쪽 아래 꼭짓점 (W, H)
    unsigned int ClipTag1 = GetClipTag(V1);
    unsigned int ClipTag2 = GetClipTag(V2);

    if (ClipTag1 & ClipTag2)
    {
        // 그리지 않아도 됨
        return false;
    }
    else
    {
        // 두 점 모두 스크린 안
        if (ClipTag1 == 0 && ClipTag2 == 0)
        {
            // Clip 필요없음
            OutV1 = V1;
            OutV2 = V2;
        }
        // 최소 한 점 스크린 밖
        else
        {
            // V1 == V2 인 경우는 두 점 모두 스크린 안이거나, 스크린 밖이면서 그리지 않아도 되는 경우일거라
            // Dx == 0 && Dy == 0 인 경우는 없으리라 판단
            float Dx = V2.GetX() - V1.GetX();
            float Dy = V2.GetY() - V1.GetY();
            Vector4 NewV1;
            Vector4 NewV2;

            if (ClipTag1 & 0x1000)
            {
                // Y >= H
                float NewX = (Dx / Dy) * (H - 1 - V1.GetY()) + V1.GetX();
                NewV1.SetX(NewX);
                NewV1.SetY(H);
            }
            else if (ClipTag1 & 0x0100)
            {
                // Y < 0
                float NewX = (Dx / Dy) * (0 - V1.GetY()) + V1.GetX();
                NewV1.SetX(NewX);
                NewV1.SetY(0);
            }
            else if (ClipTag1 & 0x0010)
            {
                // X >= W
                float NewY = (Dy / Dx) * (W - 1 - V1.GetX()) + V1.GetY();
                NewV1.SetY(NewY);
                NewV1.SetX(W);
            }
            else if (ClipTag1 & 0x0001)
            {
                // X < 0
                float NewY = (Dy / Dx) * (0 - V1.GetX()) + V1.GetY();
                NewV1.SetY(NewY);
                NewV1.SetX(0);
            }
            else
                NewV1 = V1;

            if (ClipTag2 & 0x1000)
            {
                // Y >= H
                float NewX = (Dx / Dy) * (H - 1 - V1.GetY()) + V1.GetX();
                NewV2.SetX(NewX);
                NewV2.SetY(H);
            }
            else if (ClipTag2 & 0x0100)
            {
                // Y < 0
                float NewX = (Dx / Dy) * (0 - V1.GetY()) + V1.GetX();
                NewV2.SetX(NewX);
                NewV2.SetY(0);
            }
            else if (ClipTag2 & 0x0010)
            {
                // X >= W
                float NewY = (Dy / Dx) * (W - 1 - V1.GetX()) + V1.GetY();
                NewV2.SetY(NewY);
                NewV2.SetX(W);
            }
            else if (ClipTag2 & 0x0001)
            {
                // X < 0
                float NewY = (Dy / Dx) * (0 - V1.GetX()) + V1.GetY();
                NewV2.SetY(NewY);
                NewV2.SetX(0);
            }
            else 
                NewV2 = V2;

            return ClipLine(NewV1, NewV2, OutV1, OutV2);
        }
    }

    return true;
}

unsigned int UScreen::GetClipTag(const Vector4& V)
{
    // X min, max / Y min, max 를 넘어갈 때 특정 비트를 1 로 설정
    // 비트를 통해 빠르게 공간 구분 가능
    unsigned int ClipTag = 0;

    if (V.GetX() < 0)
    {
        ClipTag |= 0x0001;
    }
    else if (V.GetX() > W)
    {
        ClipTag |= 0x0010;
    }

    if (V.GetY() < 0)
    {
        ClipTag |= 0x0100;
    }
    else if (V.GetY() > H)
    {
        ClipTag |= 0x1000;
    }

    return ClipTag;
}