#include "stdafx.h"
#include "Drawing.h"

void DrawLine(HDC hdc, SHORT x1, SHORT y1, SHORT x2, SHORT y2, HPEN pen) {
	HANDLE oldPen = SelectObject(hdc, pen);
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	SelectObject(hdc, oldPen);
}

void FillRectangle(HDC hdc, SHORT x, SHORT y, SHORT width, SHORT height, HBRUSH brush) {
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + width;
	rect.bottom = y + height;
	FillRect(hdc, &rect, brush);
}

void DrawRectangle(HDC hdc, SHORT x, SHORT y, SHORT width, SHORT height, HPEN pen) {
	HANDLE oldPen = SelectObject(hdc, pen);
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + width, y);
	LineTo(hdc, x + width, y + height);
	LineTo(hdc, x, y + height);
	LineTo(hdc, x, y);
	SelectObject(hdc, oldPen);
}
