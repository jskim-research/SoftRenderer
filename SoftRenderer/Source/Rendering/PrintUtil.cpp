#include "PrintUtil.h"
#include <cstdio>

// 왼쪽 위 1, 1 시작
void GotoXY(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void SetColor(int color) {
    printf("\033[%dm", color);
}

void ClearScreen() {
    printf("\033[2J\033[1;1H");
}