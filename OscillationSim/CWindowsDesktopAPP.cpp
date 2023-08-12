// CWindowsDesktopAPP.cpp : Defines the entry point for the application.
//

#include "OscillationSim.h"



#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HANDLE g_hOutput = 0;                           
double startTime;
double lastRunTime;
double runTime;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
void                timerProc(HWND, WPARAM);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Setting(HWND, UINT, WPARAM, LPARAM);

//void                printSizeOnCMD(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,         
    _In_opt_ HINSTANCE hPrevInstance,  
    _In_ LPWSTR    lpCmdLine,          
    _In_ int       nCmdShow)           
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    //AllocConsole();     
    g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);    

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CWINDOWSDESKTOPAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance); 

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))    
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CWINDOWSDESKTOPAPP));  

    MSG msg;

    // Main message loop:   
    while (GetMessage(&msg, nullptr, 0, 0))
    {
    
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg); 
            DispatchMessage(&msg);  
        }
    }

    return (int)msg.wParam;
}













//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;     
    wcex.cbClsExtra = 0;   
    wcex.cbWndExtra = 0;    
    wcex.hInstance = hInstance;   
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CWINDOWSDESKTOPAPP)); 
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);  
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW); 
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CWINDOWSDESKTOPAPP); 
    wcex.lpszClassName = szWindowClass;   
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);     
}


//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowEx(NULL, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);   



    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);  
    UpdateWindow(hWnd);         


    return TRUE;
}

void timerProc(HWND hWnd, WPARAM wParam) {                                          
    RECT rect1 = {0};
    SetRect(&rect1, 0, 0, COOR_WIDTH, COOR_HEIGHT);
    InvalidateRect(hWnd, &rect1, TRUE);

    //InvalidateRect(hWnd, NULL, TRUE);

}





//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        //case IDM_ABOUT:
        //    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
        //    break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_CREATE:
        //SetTimer(hWnd, 1, 1, NULL);
        DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Setting);

        break;

    case WM_TIMER:
        timerProc(hWnd, wParam);
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        lastRunTime = runTime;
        runTime = (double)clock();
        updateGraph(startTime, runTime, lastRunTime);
        paintGraph(hWnd,hdc);
        Sleep(1);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_SIZE:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for dialogBox.
INT_PTR CALLBACK Setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        
        if (LOWORD(wParam) == IDOK)
        {
           
           
            TCHAR szBuf[256];
            GetDlgItemText(hDlg, IDC_EDIT1, szBuf, 256);
            double p_length = _tcstod(szBuf,NULL);
            GetDlgItemText(hDlg, IDC_EDIT2, szBuf, 256);
            double g_input = _tcstod(szBuf, NULL);
            GetDlgItemText(hDlg, IDC_EDIT3, szBuf, 256);
            double p_angle = _tcstod(szBuf, NULL);
            GetDlgItemText(hDlg, IDC_EDIT4, szBuf, 256);
            double i_scale_x = _tcstod(szBuf, NULL);
            GetDlgItemText(hDlg, IDC_EDIT5, szBuf, 256);
            double i_scale_y = _tcstod(szBuf, NULL);
            GetDlgItemText(hDlg, IDC_EDIT6, szBuf, 256);
            double i_zoom = _tcstod(szBuf, NULL);


            startTime = (double)clock();
            lastRunTime = (double)clock();
            runTime = (double)clock();
            osc_init(p_length,g_input,p_angle,i_scale_x,i_scale_y,i_zoom);
            //osc_init(OSC_LENGTH, G_ACC, OSC_MAXANGLE_DEG, SCALE_X, SCALE_Y,ZOOM);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    case WM_SHOWWINDOW: 
    {
        char szBuffer[32];
        sprintf_s(szBuffer, "%f", OSC_LENGTH);
        SetDlgItemTextA(hDlg, IDC_EDIT1, szBuffer);
        sprintf_s(szBuffer, "%f", G_ACC);
        SetDlgItemTextA(hDlg, IDC_EDIT2, szBuffer);
        sprintf_s(szBuffer, "%f", OSC_MAXANGLE_DEG);
        SetDlgItemTextA(hDlg, IDC_EDIT3, szBuffer);
        sprintf_s(szBuffer, "%f", SCALE_X);
        SetDlgItemTextA(hDlg, IDC_EDIT4, szBuffer);
        sprintf_s(szBuffer, "%f", SCALE_Y);
        SetDlgItemTextA(hDlg, IDC_EDIT5, szBuffer);
        sprintf_s(szBuffer, "%f", SCALE_Y);
        SetDlgItemTextA(hDlg, IDC_EDIT5, szBuffer);
        sprintf_s(szBuffer, "%f", ZOOM);
        SetDlgItemTextA(hDlg, IDC_EDIT6, szBuffer);
        break;
    }  
    }
    return (INT_PTR)FALSE;
}






// Message handler for about box.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}



