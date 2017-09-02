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

    /*The counter of the mouse's clicks.*/
    static int count = 0;
    char countString[5];

    switch (msg){
        /*If the event is the left key of the mouse is being pressed*/
        case WM_LBUTTONDOWN:
            count ++;
            return 0;

        /*If the event is the right key of the mouse is being pressed*/
        case WM_RBUTTONDOWN:
            /*Sets the title of this window to the mouse's clicks count*/
            sprintf(countString, "%d", count);
            SetWindowText(hWnd, countString);

            /*Reset the counter*/
            count = 0;

            return 0;
        /*If the event is the closing of this window => send a closing message tp the messages-pump*/
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            break;
    }
    return (DefWindowProc(hWnd, msg, wParam, IParam));

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevINstance, LPSTR IpCmdLine, INT nCmdShow) {
    WNDCLASSi wc = {0};
    wc.style = 0;
    wc.IpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(GRAY_BRUSH);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.IpszClassName = "Sample Window Class";
    wc.IpszMenuName = NULL;
    wc.hInstance = hInstance;
    RegisterClass(&wc);

    HWND hWnd = CreateWindow("Sample Window Class", "Test", WS_OVERLAPPEDWINDOW, 0, 0, 200, 200, NULL, NULL, hInstance,
                             NULL);
    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

}