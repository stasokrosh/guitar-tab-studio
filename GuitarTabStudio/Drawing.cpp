#include "stdafx.h"
#include "Drawing.h"

void DrawLine(HDC hdc, USHORT x1, USHORT y1, USHORT x2, USHORT y2, HPEN pen) {
	HANDLE oldPen = SelectObject(hdc, pen);
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	SelectObject(hdc, oldPen);
}

void FillRectangle(HDC hdc, USHORT x, USHORT y, USHORT width, USHORT height, HBRUSH brush) {
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + width;
	rect.bottom = y + height;
	FillRect(hdc, &rect, brush);
}

void DrawRectangle(HDC hdc, USHORT x, USHORT y, USHORT width, USHORT height, HPEN pen) {
	HANDLE oldPen = SelectObject(hdc, pen);
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + width, y);
	LineTo(hdc, x + width, y + height);
	LineTo(hdc, x, y + height);
	SelectObject(hdc, oldPen);
}
