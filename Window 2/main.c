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

    /*A pointer to a double-word, a string and a system-time variable for the time-function*/
    LPDWORD dwNumberOfWrittenBytes = NULL;
    SYSTEMTIME lpTime = {0};
    char stringTime[30] = {0};

    switch (msg){
        /*If the event is a key-down:*/
        case WM_KEYDOWN:
            /*If the key's ascii code is 13(enter):*/
            if(wParam == 0x0D){
                /*Creates a handle to the time-file(Time.bamb).*/
                HANDLE hFile =  CreateFile("Time.bamb", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);

                /*Gets the local time of the system*/
                GetLocalTime(&lpTime);

                /*Sets the string with the current time*/
                sprintf(stringTime, "%02d:%02d:%02d", lpTime.wHour, lpTime.wMinute, lpTime.wSecond);

                /*Writes the time to the time-file*/
                WriteFile(hFile, stringTime, sizeof(char) * 30, dwNumberOfWrittenBytes, NULL);

                /*Closes the file-handle*/
                CloseHandle(hFile);
            }
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