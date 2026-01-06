#ifndef __PRINT_UTIL_H__
#define __PRINT_UTIL_H__

// 왼쪽 위 1, 1 시작
void GotoXY(int x, int y);

/*
색상	코드
검정	30
빨강	31
초록	32
노랑	33
파랑	34
보라	35
청록	36
흰색	37
*/
void SetColor(int color);
void ClearScreen();

#endif