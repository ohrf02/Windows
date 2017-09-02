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

/*The Window event handler function*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM IParam) {
    /*A pointer to a string for the get-system-directory function.*/
    LPSTR string = malloc(sizeof(char) * 255);
    switch (msg){

        /*If a key is being pressed:*/
        case WM_KEYDOWN:
            /*If the key's ascii code is 13(enter):*/
            if(wParam == 0x0D){
                /*Sets the Window's title to 'Enter' when the enter key is being pressed down.*/
                SetWindowText(hWnd, "Enter");

                /*Gets the system directory's path (the installing path of windows).*/
                GetSystemDirectory(string, 255);

                /*Shows the path of windows' installing directory.*/
                MessageBox(hWnd, string, "System", MB_OK);

            }
            return 0;

        /*If the event is the closing of this window => post a quit-message to the messages-pump*/
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