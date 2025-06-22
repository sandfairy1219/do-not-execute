#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define PI 3.14159265358979323846

int main() {
    SetProcessDPIAware();
    srand((unsigned int)time(0));

    HDC hdc = GetDC(0);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBM = CreateCompatibleBitmap(hdc, w, h);
    SelectObject(memDC, memBM);

    BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

    int cx = w / 2;
    int cy = h / 2;

    POINT basePts[3] = {
        {0, 0},
        {w, 0},
        {0, h}
    };

    double angle = 0.0;
    double angularSpeed = 0.1;

    while (1) {
        angle += angularSpeed;
        if (angle > 2 * PI) angle -= 2 * PI;

        // 화면 크기 전체 범위에서 랜덤 움직임
        int xOffset = (rand() % (2 * w + 1)) - w; // -w ~ +w
        int yOffset = (rand() % (2 * h + 1)) - h; // -h ~ +h

        POINT pts[3];
        for (int i = 0; i < 3; i++) {
            int x = basePts[i].x - cx;
            int y = basePts[i].y - cy;
            int rx = static_cast<int>(x * cos(angle) - y * sin(angle)) + cx + xOffset;
            int ry = static_cast<int>(x * sin(angle) + y * cos(angle)) + cy + yOffset;
            pts[i].x = rx;
            pts[i].y = ry;
        }

        PlgBlt(hdc, pts, memDC, 0, 0, w, h, NULL, 0, 0);

        BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, 0, 0, SRCPAINT);
        BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, 0, 0, SRCINVERT);

        Sleep(10);
    }

    DeleteObject(memBM);
    DeleteDC(memDC);
    ReleaseDC(0, hdc);
}
