// 編譯提示：
// 使用以下命令進行編譯，確保鏈接 GDI 函式庫：
// gcc hello.c -o hello.exe -lgdi32

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 設定支援Unicode字符集
#define UNICODE
#define _UNICODE

// 定義按鈕顏色標識符號
#define PROP_BGCOLOR "BgColorProp"

// 定義視窗類別名稱和資源識別符
#define ID_EDIT 100
#define ID_BUTTON_0 101
#define ID_BUTTON_1 102
#define ID_BUTTON_2 103
#define ID_BUTTON_3 104
#define ID_BUTTON_4 105
#define ID_BUTTON_5 106
#define ID_BUTTON_6 107
#define ID_BUTTON_7 108
#define ID_BUTTON_8 109
#define ID_BUTTON_9 110
#define ID_BUTTON_ADD 111
#define ID_BUTTON_SUB 112
#define ID_BUTTON_MUL 113
#define ID_BUTTON_DIV 114
#define ID_BUTTON_EQ 115
#define ID_BUTTON_CLR 116

// 顏色定義
#define COLOR_BG RGB(240, 240, 240)       // 背景顏色
#define COLOR_DISPLAY RGB(230, 250, 230)  // 顯示區域背景
#define COLOR_NUMBER RGB(245, 245, 245)   // 數字按鈕背景
#define COLOR_OP RGB(230, 230, 250)       // 運算符按鈕背景
#define COLOR_EQ RGB(210, 230, 250)       // 等號按鈕背景
#define COLOR_CLR RGB(250, 220, 220)      // 清除按鈕背景

// 字型句柄
HFONT g_hFont;
HFONT g_hFontBold;

// 全域變數
HWND g_hWndEdit;
WCHAR g_buffer[256] = L"";
double g_num1 = 0.0;
int g_operation = 0; // 1:+ 2:- 3:* 4:/

// 全域變數用於保存原始的按鈕過程
typedef struct {
    WNDPROC oldProc;
    COLORREF bgColor;
} BtnData;

// 創建字型
void CreateFonts() {
    g_hFont = CreateFontW(
        20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        L"微軟正黑體");
        
    g_hFontBold = CreateFontW(
        24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        L"微軟正黑體");
}

// 自定義繪製按鈕
void DrawColorButton(HWND hwnd, HDC hdc, RECT* rect, COLORREF color) {
    FillRect(hdc, rect, CreateSolidBrush(color));
    
    // 畫邊框
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(180, 180, 180));
    SelectObject(hdc, pen);
    MoveToEx(hdc, rect->left, rect->top, NULL);
    LineTo(hdc, rect->right-1, rect->top);
    LineTo(hdc, rect->right-1, rect->bottom-1);
    LineTo(hdc, rect->left, rect->bottom-1);
    LineTo(hdc, rect->left, rect->top);
    DeleteObject(pen);
    
    // 陰影效果
    pen = CreatePen(PS_SOLID, 1, RGB(220, 220, 220));
    SelectObject(hdc, pen);
    MoveToEx(hdc, rect->left+1, rect->bottom-2, NULL);
    LineTo(hdc, rect->right-2, rect->bottom-2);
    LineTo(hdc, rect->right-2, rect->top+1);
    DeleteObject(pen);
}

// 更新顯示
void UpdateDisplay() {
    SetWindowTextW(g_hWndEdit, g_buffer);
}

// 主視窗程序
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            // 釋放字型資源
            DeleteObject(g_hFont);
            DeleteObject(g_hFontBold);
            PostQuitMessage(0);
            return 0;

        case WM_CTLCOLOREDIT:
            // 設定顯示框顏色
            if ((HWND)lParam == g_hWndEdit) {
                SetBkColor((HDC)wParam, COLOR_DISPLAY);
                return (LRESULT)CreateSolidBrush(COLOR_DISPLAY);
            }
            break;
            
        case WM_CTLCOLORBTN:
            // 設定按鈕顏色
            return (LRESULT)GetStockObject(NULL_BRUSH);
        
        case WM_COMMAND: {
            int id = LOWORD(wParam);
            
            // 數字按鈕
            if (id >= ID_BUTTON_0 && id <= ID_BUTTON_9) {
                WCHAR digit = L'0' + (id - ID_BUTTON_0);
                WCHAR str[2] = {digit, L'\0'};
                wcscat(g_buffer, str);
                UpdateDisplay();
                return 0;
            }
            
            // 運算子按鈕
            switch (id) {
                case ID_BUTTON_ADD:
                case ID_BUTTON_SUB:
                case ID_BUTTON_MUL:
                case ID_BUTTON_DIV: {
                    g_num1 = _wtof(g_buffer);
                    g_buffer[0] = L'\0';
                    UpdateDisplay();
                    
                    if (id == ID_BUTTON_ADD) g_operation = 1;
                    else if (id == ID_BUTTON_SUB) g_operation = 2;
                    else if (id == ID_BUTTON_MUL) g_operation = 3;
                    else if (id == ID_BUTTON_DIV) g_operation = 4;
                    return 0;
                }
                
                case ID_BUTTON_EQ: {
                    double num2 = _wtof(g_buffer);
                    double result = 0.0;
                    
                    switch (g_operation) {
                        case 1: result = g_num1 + num2; break;
                        case 2: result = g_num1 - num2; break;
                        case 3: result = g_num1 * num2; break;
                        case 4:
                            if (num2 != 0) {
                                result = g_num1 / num2;
                            } else {
                                MessageBoxW(hwnd, L"除數不能為零!", L"錯誤", MB_OK | MB_ICONERROR);
                                wcscpy(g_buffer, L"Error");
                                UpdateDisplay();
                                return 0;
                            }
                            break;
                    }
                    
                    swprintf(g_buffer, 255, L"%.2f", result);
                    UpdateDisplay();
                    return 0;
                }
                
                case ID_BUTTON_CLR: {
                    g_buffer[0] = L'\0';
                    UpdateDisplay();
                    return 0;
                }
            }
            break;
        }
    }
    
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

// 建立按鈕
HWND CreateCalculatorButton(HWND hwndParent, LPCWSTR text, int x, int y, int width, int height, int id, COLORREF bgColor) {
    HWND hBtn = CreateWindowW(
        L"BUTTON",
        text,
        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,  // 改為自定義繪製
        x, y,
        width, height,
        hwndParent,
        (HMENU)(INT_PTR)id,  // 修正指針轉換
        GetModuleHandle(NULL),
        NULL
    );
    
    // 設定按鈕字型
    SendMessage(hBtn, WM_SETFONT, (WPARAM)g_hFont, TRUE);
    
    // 保存按鈕背景顏色 - 使用數字屬性而不是字串屬性
    SetWindowLongPtr(hBtn, GWLP_USERDATA, (LONG_PTR)bgColor);
    
    return hBtn;
}

// 自定義按鈕繪製函數
LRESULT CALLBACK ButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    BtnData* data = (BtnData*)GetPropA(hwnd, PROP_BGCOLOR);
    
    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            RECT rect;
            GetClientRect(hwnd, &rect);
            
            // 獲取按鈕文字
            WCHAR text[32];
            GetWindowTextW(hwnd, text, 32);
            
            // 使用結構中保存的顏色
            COLORREF bgColor = data ? data->bgColor : COLOR_NUMBER;
            
            // 繪製按鈕背景
            DrawColorButton(hwnd, hdc, &rect, bgColor);
            
            // 繪製按鈕文字
            SetBkMode(hdc, TRANSPARENT);
            SelectObject(hdc, g_hFont);
            SetTextColor(hdc, RGB(10, 10, 10));
            
            // 文字置中
            DrawTextW(hdc, text, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            
            EndPaint(hwnd, &ps);
            return 0;
        }
        
        case WM_DESTROY: {
            // 釋放資源
            if (data) {
                RemovePropA(hwnd, PROP_BGCOLOR);
                free(data);
            }
            break;
        }
    }
    
    if (data && data->oldProc) {
        return CallWindowProc(data->oldProc, hwnd, uMsg, wParam, lParam);
    } else {
        return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
}

// 子類化按鈕
void SubclassButton(HWND hBtn, COLORREF bgColor) {
    // 創建存儲數據的結構
    BtnData* data = (BtnData*)malloc(sizeof(BtnData));
    if (data) {
        data->oldProc = (WNDPROC)SetWindowLongPtr(hBtn, GWLP_WNDPROC, (LONG_PTR)ButtonProc);
        data->bgColor = bgColor;
        
        // 存儲指向數據的指針
        SetPropA(hBtn, PROP_BGCOLOR, (HANDLE)data);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 創建字型
    CreateFonts();
    
    // 註冊視窗類別
    const WCHAR CLASS_NAME[] = L"Calculator";
    
    WNDCLASSW wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(COLOR_BG);
    
    RegisterClassW(&wc);
    
    // 建立主視窗
    HWND hwnd = CreateWindowW(
        CLASS_NAME,
        L"美化計算機",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        320, 420,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    
    if (hwnd == NULL) {
        return 0;
    }
    
    // 建立輸入/顯示欄位
    g_hWndEdit = CreateWindowW(
        L"EDIT",
        L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_RIGHT | ES_READONLY,
        20, 20,
        280, 40,
        hwnd,
        (HMENU)ID_EDIT,
        hInstance,
        NULL
    );
    
    // 設定顯示框字型
    SendMessage(g_hWndEdit, WM_SETFONT, (WPARAM)g_hFontBold, TRUE);
    
    // 按鈕大小和間距
    const int BTN_WIDTH = 60;
    const int BTN_HEIGHT = 50;
    const int GAP = 10;
    int baseX = 20;
    int baseY = 80;
    
    // 建立數字按鈕 (0-9)
    HWND hBtn;
    hBtn = CreateCalculatorButton(hwnd, L"7", baseX, baseY, BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_7, COLOR_NUMBER);
    SubclassButton(hBtn, COLOR_NUMBER);
    
    hBtn = CreateCalculatorButton(hwnd, L"8", baseX + BTN_WIDTH + GAP, baseY, BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_8, COLOR_NUMBER);
    SubclassButton(hBtn, COLOR_NUMBER);
    
    hBtn = CreateCalculatorButton(hwnd, L"9", baseX + 2 * (BTN_WIDTH + GAP), baseY, BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_9, COLOR_NUMBER);
    SubclassButton(hBtn, COLOR_NUMBER);
    
    hBtn = CreateCalculatorButton(hwnd, L"4", baseX, baseY + BTN_HEIGHT + GAP, BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_4, COLOR_NUMBER);
    SubclassButton(hBtn, COLOR_NUMBER);
    
    hBtn = CreateCalculatorButton(hwnd, L"5", baseX + BTN_WIDTH + GAP, baseY + BTN_HEIGHT + GAP, BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_5, COLOR_NUMBER);
    SubclassButton(hBtn, COLOR_NUMBER);
    
    hBtn = CreateCalculatorButton(hwnd, L"6", baseX + 2 * (BTN_WIDTH + GAP), baseY + BTN_HEIGHT + GAP, BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_6, COLOR_NUMBER);
    SubclassButton(hBtn, COLOR_NUMBER);
    
    hBtn = CreateCalculatorButton(hwnd, L"1", baseX, baseY + 2 * (BTN_HEIGHT + GAP), BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_1, COLOR_NUMBER);
    SubclassButton(hBtn, COLOR_NUMBER);
    
    hBtn = CreateCalculatorButton(hwnd, L"2", baseX + BTN_WIDTH + GAP, baseY + 2 * (BTN_HEIGHT + GAP), BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_2, COLOR_NUMBER);
    SubclassButton(hBtn, COLOR_NUMBER);
    
    hBtn = CreateCalculatorButton(hwnd, L"3", baseX + 2 * (BTN_WIDTH + GAP), baseY + 2 * (BTN_HEIGHT + GAP), BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_3, COLOR_NUMBER);
    SubclassButton(hBtn, COLOR_NUMBER);
    
    hBtn = CreateCalculatorButton(hwnd, L"0", baseX, baseY + 3 * (BTN_HEIGHT + GAP), BTN_WIDTH * 2 + GAP, BTN_HEIGHT, ID_BUTTON_0, COLOR_NUMBER);
    SubclassButton(hBtn, COLOR_NUMBER);
    
    // 建立運算符按鈕
    hBtn = CreateCalculatorButton(hwnd, L"+", baseX + 3 * (BTN_WIDTH + GAP), baseY, BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_ADD, COLOR_OP);
    SubclassButton(hBtn, COLOR_OP);
    
    hBtn = CreateCalculatorButton(hwnd, L"-", baseX + 3 * (BTN_WIDTH + GAP), baseY + BTN_HEIGHT + GAP, BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_SUB, COLOR_OP);
    SubclassButton(hBtn, COLOR_OP);
    
    hBtn = CreateCalculatorButton(hwnd, L"×", baseX + 3 * (BTN_WIDTH + GAP), baseY + 2 * (BTN_HEIGHT + GAP), BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_MUL, COLOR_OP);
    SubclassButton(hBtn, COLOR_OP);
    
    hBtn = CreateCalculatorButton(hwnd, L"÷", baseX + 3 * (BTN_WIDTH + GAP), baseY + 3 * (BTN_HEIGHT + GAP), BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_DIV, COLOR_OP);
    SubclassButton(hBtn, COLOR_OP);
    
    // 建立等號和清除按鈕
    hBtn = CreateCalculatorButton(hwnd, L"C", baseX + 2 * (BTN_WIDTH + GAP), baseY + 3 * (BTN_HEIGHT + GAP), BTN_WIDTH, BTN_HEIGHT, ID_BUTTON_CLR, COLOR_CLR);
    SubclassButton(hBtn, COLOR_CLR);
    
    hBtn = CreateCalculatorButton(hwnd, L"=", baseX, baseY + 4 * (BTN_HEIGHT + GAP), BTN_WIDTH * 4 + GAP * 3, BTN_HEIGHT, ID_BUTTON_EQ, COLOR_EQ);
    SubclassButton(hBtn, COLOR_EQ);
    
    // 顯示視窗
    ShowWindow(hwnd, nCmdShow);
    
    // 消息迴圈
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}