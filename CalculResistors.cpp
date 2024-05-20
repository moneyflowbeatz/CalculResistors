// CalculResistors.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "CalculResistors.h"

#define MAX_LOADSTRING 100
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING] = L"Резисторный калькулятор";                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING] = L"ResistorCalcClass";            // имя класса главного окна
HWND hComboBand1, hComboBand2, hComboBand3, hComboBand4, hComboBand5, hButton, hResultText;
HWND hLabelBand1, hLabelBand2, hLabelBand3, hLabelBand4, hLabelBand5;
bool isFiveBand = false;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

std::vector<std::wstring> colors = {L"Black", L"Brown", L"Red", L"Orange", L"Yellow", L"Green", L"Blue", L"Violet", L"Gray", L"White", L"Gold", L"Silver" };
std::vector<int> colorVal = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -2 };

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CALCULRESISTORS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CALCULRESISTORS));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CALCULRESISTORS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CALCULRESISTORS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void FillComboBox(HWND hComboBox)
{
    for (const auto& color : colors)
    {
        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)color.c_str());
    }
    SendMessage(hComboBox, CB_SETCURSEL, 0, 0); // первый элемент в 0 - Black
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            // radio buttons
            HWND hFourBandRadio = CreateWindowW(L"BUTTON", L"4 кольцевой", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                400, 10, 120, 30, hWnd, (HMENU)2, hInst, nullptr);
            SendMessage(hFourBandRadio, BM_SETCHECK, BST_CHECKED, 0);

            HWND hFiveBandRadio = CreateWindowW(L"BUTTON", L"5 кольцевой", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                400, 40, 120, 30, hWnd, (HMENU)3, hInst, nullptr);

            // comboboxes & labels
            hLabelBand1 = CreateWindowW(L"STATIC", L"Кольцо 1 (номинал): ", WS_VISIBLE | WS_CHILD,
                10, 10, 150, 20, hWnd, nullptr, hInst, nullptr);
            hComboBand1 = CreateWindowW(L"COMBOBOX", nullptr, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
                150, 10, 150, 200, hWnd, nullptr, hInst, nullptr);
            FillComboBox(hComboBand1);

            hLabelBand2 = CreateWindowW(L"STATIC", L"Кольцо 2 (номинал): ", WS_VISIBLE | WS_CHILD,
                10, 40, 150, 20, hWnd, nullptr, hInst, nullptr);
            hComboBand2 = CreateWindowW(L"COMBOBOX", nullptr, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
                150, 40, 150, 200, hWnd, nullptr, hInst, nullptr);
            FillComboBox(hComboBand2);

            hLabelBand3 = CreateWindowW(L"STATIC", L"Кольцо 3 (номинал): ", WS_VISIBLE | WS_CHILD,
                10, 70, 150, 20, hWnd, nullptr, hInst, nullptr);
            hComboBand3 = CreateWindowW(L"COMBOBOX", nullptr, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
                150, 70, 150, 200, hWnd, nullptr, hInst, nullptr);
            FillComboBox(hComboBand3);
            ShowWindow(hComboBand3, SW_HIDE); // по умолчанию скрыл
            ShowWindow(hLabelBand3, SW_HIDE); // по умолчанию скрыл

            hLabelBand4 = CreateWindowW(L"STATIC", L"Кольцо (множитель): ", WS_VISIBLE | WS_CHILD,
                10, 100, 150, 20, hWnd, nullptr, hInst, nullptr);
            hComboBand4 = CreateWindowW(L"COMBOBOX", nullptr, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
                150, 100, 150, 200, hWnd, nullptr, hInst, nullptr);
            FillComboBox(hComboBand4);

            hLabelBand5 = CreateWindowW(L"STATIC", L"Кольцо (точность): ", WS_VISIBLE | WS_CHILD,
                10, 130, 150, 20, hWnd, nullptr, hInst, nullptr);
            hComboBand5 = CreateWindowW(L"COMBOBOX", nullptr, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
                150, 130, 150, 200, hWnd, nullptr, hInst, nullptr);
            FillComboBox(hComboBand5);
            

            // button for calculate
            hButton = CreateWindowW(L"BUTTON", L"Рассчитать", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                10, 160, 150, 30, hWnd, (HMENU)1, hInst, nullptr);

            // result
            hResultText = CreateWindowW(L"STATIC", L"", WS_VISIBLE | WS_CHILD,
                10, 200, 350, 20, hWnd, nullptr, hInst, nullptr);
        }
    case WM_COMMAND:
        {
            if (LOWORD(wParam) == 2 || LOWORD(wParam) == 3) {
                if (LOWORD(wParam) == 2) {
                    isFiveBand == false;
                    ShowWindow(hLabelBand3, SW_HIDE);
                    ShowWindow(hComboBand3, SW_HIDE);

                    
                }
                else
                {
                    isFiveBand == true;
                    ShowWindow(hLabelBand3, SW_SHOW);
                    ShowWindow(hComboBand3, SW_SHOW);

                    
                    
                }

            }
            if (LOWORD(wParam) == 1)
            {
                int band1 = colorVal[SendMessage(hComboBand1, CB_GETCURSEL, 0, 0)];
                int band2 = colorVal[SendMessage(hComboBand2, CB_GETCURSEL, 0, 0)];
                int band3 = colorVal[SendMessage(hComboBand3, CB_GETCURSEL, 0, 0)];
                int band4 = colorVal[SendMessage(hComboBand4, CB_GETCURSEL, 0, 0)];
                int band5 = colorVal[SendMessage(hComboBand5, CB_GETCURSEL, 0, 0)];

                double resistance = 0.0; // сопротивление резистора

                if (isFiveBand)
                    resistance = (band1 * 100 + band2 * 10 + band3) * pow(10, band4); // значение трех цифр * множитель
                else
                    resistance = (band1 * 10 + band2) * pow(10, band3); // значение двух цифр * множитель

                std::wstring result = L"Сопротивление: " + std::to_wstring(resistance) + L"Ом";
                SetWindowText(hResultText, result.c_str());
                
            }

            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
