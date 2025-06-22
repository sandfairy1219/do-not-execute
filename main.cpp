#include <windows.h>

int main() {
    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);

    while (1) {
        BitBlt(hdc, rand() % 5, rand() % 5, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, rand() % 5, rand() % 5, w, h, hdc, 0, 0, SRCPAINT);
        BitBlt(hdc, rand() % 5, rand() % 5, w, h, hdc, 0, 0, SRCINVERT);
        Sleep(100);
    }
}
