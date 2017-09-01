#include <Windows.h>
#include <stdio.h>

typedef struct tagWNDCLASS {
    UINT style;
    WNDPROC IpfnWndProc;
    int cbClsExtra;
    int cbWndExtra;
    HINSTANCE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCSTR IpszMenuName;
    LPCSTR IpszClassName;
}WNDCLASSi;


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM IParam) {

    LPDWORD dwNumberOfWrittenBytes = NULL;
    SYSTEMTIME lpTime = {0};
    char stringTime[30] = {0};

    switch (msg){
        case WM_KEYDOWN:
            if(wParam == 0x0D){
                SetWindowText(hWnd, "Enter");
                HANDLE hFile =  CreateFile("Time.bamb", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
                GetLocalTime(&lpTime);
                sprintf(stringTime, "%02d:%02d:%02d", lpTime.wHour, lpTime.wMinute, lpTime.wSecond);

                WriteFile(hFile, stringTime, sizeof(char) * 30, dwNumberOfWrittenBytes, NULL);
                CloseHandle(hFile);

            }
            return 0;
        case WM_LBUTTONDOWN:
            SetWindowText(hWnd, "Left");
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return (DefWindowProc(hWnd, msg, wParam, IParam));

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevINstance, LPSTR IpCmdLine, INT nCmdShow) {
WNDCLASSi wc = { 0 };
wc.style = 0;
wc.IpfnWndProc = WndProc;
wc.cbClsExtra = 0;
wc.cbWndExtra = 0;
wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
wc.hCursor = LoadCursor(NULL, IDC_ARROW);
wc.IpszClassName = "Sample Window Class";
wc.IpszMenuName = NULL;
wc.hInstance = hInstance;
RegisterClass(&wc);

HWND hWnd = CreateWindow("Sample Window Class", "Test", WS_OVERLAPPEDWINDOW, 0, 0, 200, 200, NULL, NULL, hInstance, NULL);
ShowWindow(hWnd, nCmdShow);

MSG msg;
while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}

}