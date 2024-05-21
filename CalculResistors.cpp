// CalculResistors.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "CalculResistors.h"

#define MAX_LOADSTRING 100
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING] = L"Резисторный калькулятор";                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING] = L"ResistorCalcClass";            // имя класса главного окна
HWND hComboBand1, hComboBand2, hComboBand3, hComboBand4, hComboBand5, hButton, hResultText, hFourBandRadio, hFiveBandRadio;
HWND hLabelBand1, hLabelBand2, hLabelBand3, hLabelBand4, hLabelBand5, hLabelPower, hComboPower;
bool isFiveBand = false;
const int NUM_COLORS = 12;

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

void SetComboBoxColor(HWND hComboBox) {
    SetWindowSubclass(hComboBox, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR) -> LRESULT {
        switch (uMsg) {
        case WM_DRAWITEM: {
            LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
            if (pDIS->itemID == -1) break; // No item to draw

            std::wstring text(256, L'\0');
            SendMessage(hWnd, CB_GETLBTEXT, pDIS->itemID, (LPARAM)text.data());
            text.resize(wcslen(text.data())); // Trim null characters

            HBRUSH hBrush;
            COLORREF textColor;

            if (text == L"Black") {
                hBrush = CreateSolidBrush(RGB(0, 0, 0));
                textColor = RGB(255, 255, 255);
            }
            else if (text == L"Brown") {
                hBrush = CreateSolidBrush(RGB(150, 75, 0));
                textColor = RGB(255, 255, 255);
            }
            else if (text == L"Red") {
                hBrush = CreateSolidBrush(RGB(255, 0, 0));
                textColor = RGB(255, 255, 255);
            }
            else if (text == L"Orange") {
                hBrush = CreateSolidBrush(RGB(255, 165, 0));
                textColor = RGB(0, 0, 0);
            }
            else if (text == L"Yellow") {
                hBrush = CreateSolidBrush(RGB(255, 255, 0));
                textColor = RGB(0, 0, 0);
            }
            else if (text == L"Green") {
                hBrush = CreateSolidBrush(RGB(0, 255, 0));
                textColor = RGB(0, 0, 0);
            }
            else if (text == L"Blue") {
                hBrush = CreateSolidBrush(RGB(0, 0, 255));
                textColor = RGB(255, 255, 255);
            }
            else if (text == L"Violet") {
                hBrush = CreateSolidBrush(RGB(238, 130, 238));
                textColor = RGB(0, 0, 0);
            }
            else if (text == L"Gray") {
                hBrush = CreateSolidBrush(RGB(169, 169, 169));
                textColor = RGB(0, 0, 0);
            }
            else if (text == L"White") {
                hBrush = CreateSolidBrush(RGB(255, 255, 255));
                textColor = RGB(0, 0, 0);
            }
            else if (text == L"Gold") {
                hBrush = CreateSolidBrush(RGB(255, 215, 0));
                textColor = RGB(0, 0, 0);
            }
            else if (text == L"Silver") {
                hBrush = CreateSolidBrush(RGB(192, 192, 192));
                textColor = RGB(0, 0, 0);
            }
            else {
                hBrush = CreateSolidBrush(RGB(255, 255, 255));
                textColor = RGB(0, 0, 0);
            }

            FillRect(pDIS->hDC, &pDIS->rcItem, hBrush);
            SetTextColor(pDIS->hDC, textColor);
            SetBkMode(pDIS->hDC, TRANSPARENT);
            DrawText(pDIS->hDC, text.c_str(), -1, &pDIS->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

            DeleteObject(hBrush);

            return TRUE;
        }
        }
        return DefSubclassProc(hWnd, uMsg, wParam, lParam);
        }, 0, 0);
}


void FillComboBox(HWND hComboBox)
{
    for (const auto& color : colors)
    {
        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)color.c_str());
    }
    SendMessage(hComboBox, CB_SETCURSEL, 0, 0); // первый элемент в 0 - Black
    
}

void FillComboBox_accuracy(HWND hComboBox)
{
    std::vector<int> forbiddenColors = { 0, 3, 4, 9 }; // Индексы черного, оранжевого, желтого и белого цветов

    for (size_t i = 0; i < colors.size(); ++i)
    {
        if (std::find(forbiddenColors.begin(), forbiddenColors.end(), i) == forbiddenColors.end())
        {
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)colors[i].c_str());
        }
    }
    SendMessage(hComboBox, CB_SETCURSEL, 0, 0); // первый элемент в 0
    
}

void FillComboBox_1m(HWND hComboBox)
{
    std::vector<int> forbiddenColors = { 0, 10, 11 }; 

    for (size_t i = 0; i < colors.size(); ++i)
    {
        if (std::find(forbiddenColors.begin(), forbiddenColors.end(), i) == forbiddenColors.end())
        {
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)colors[i].c_str());
        }
    }
    SendMessage(hComboBox, CB_SETCURSEL, 0, 0); // первый элемент в 0
    
}

void FillComboBox_2_3m(HWND hComboBox)
{
    std::vector<int> forbiddenColors = { 10, 11 };

    for (size_t i = 0; i < colors.size(); ++i)
    {
        if (std::find(forbiddenColors.begin(), forbiddenColors.end(), i) == forbiddenColors.end())
        {
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)colors[i].c_str());
        }
    }
    SendMessage(hComboBox, CB_SETCURSEL, 0, 0); // первый элемент в 0
    SetComboBoxColor(hComboBox);
}


void UpdateComboBoxVisibility()
{
    ShowWindow(hLabelBand3, isFiveBand ? SW_SHOW : SW_HIDE);
    ShowWindow(hComboBand3, isFiveBand ? SW_SHOW : SW_HIDE);
}

void RecalculateResistance()
{
    int val1 = colorVal[SendMessage(hComboBand1, CB_GETCURSEL, 0, 0)];
    int val2 = colorVal[SendMessage(hComboBand2, CB_GETCURSEL, 0, 0)];
    int val3 = colorVal[SendMessage(hComboBand3, CB_GETCURSEL, 0, 0)];
    int multiplier = pow(10, colorVal[SendMessage(hComboBand4, CB_GETCURSEL, 0, 0)]);
    int band5 = SendMessage(hComboBand5, CB_GETCURSEL, 0, 0);
    std::wstring tolerance;

    switch (band5) {
    case 0:
        tolerance = L"1%"; // Коричневый
        break;
    case 1:
        tolerance = L"2%"; // Красный
        break;
    case 2:
        tolerance = L"0.5%"; // Зеленый
        break;
    case 3:
        tolerance = L"0.25%"; // Синий
        break;
    case 4:
        tolerance = L"0.1%"; // Фиолетовый
        break;
    case 5:
        tolerance = L"0.05%"; // Серый
        break;
    case 6:
        tolerance = L"5%"; // Золото
        break;
    case 7:
        tolerance = L"10%"; // Серебро
        break;
    default:
        tolerance = L"";
        break;
    }

    int resistance = (val1 * 10 + val2) * multiplier;
    if (isFiveBand)
    {
        resistance = (val1 * 100 + val2 * 10 + val3) * multiplier;
    }

    wchar_t resultText[256];
    swprintf_s(resultText, 256, L"Сопротивление: %d Ω ± %s", resistance, tolerance.c_str());
    SetWindowText(hResultText, resultText);
}

void HandleComboBoxChange(HWND hComboBox)
{
    RecalculateResistance();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            // radio buttons
            hFourBandRadio = CreateWindowW(L"BUTTON", L"4 кольцевой", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                400, 10, 120, 30, hWnd, (HMENU)2, hInst, nullptr);
            SendMessage(hFourBandRadio, BM_SETCHECK, BST_CHECKED, 0);

            hFiveBandRadio = CreateWindowW(L"BUTTON", L"5 кольцевой", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                400, 40, 120, 30, hWnd, (HMENU)3, hInst, nullptr);

            // comboboxes & labels
            hLabelBand1 = CreateWindowW(L"STATIC", L"Кольцо 1 (номинал): ", WS_VISIBLE | WS_CHILD,
                10, 10, 150, 20, hWnd, nullptr, hInst, nullptr);
            hComboBand1 = CreateWindowW(L"COMBOBOX", nullptr, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
                150, 10, 150, 200, hWnd, nullptr, hInst, nullptr);
            FillComboBox_1m(hComboBand1);
            SetComboBoxColor(hComboBand1);

            hLabelBand2 = CreateWindowW(L"STATIC", L"Кольцо 2 (номинал): ", WS_VISIBLE | WS_CHILD,
                10, 40, 150, 20, hWnd, nullptr, hInst, nullptr);
            hComboBand2 = CreateWindowW(L"COMBOBOX", nullptr, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
                150, 40, 150, 200, hWnd, nullptr, hInst, nullptr);
            FillComboBox_2_3m(hComboBand2);
            SetComboBoxColor(hComboBand2);

            hLabelBand3 = CreateWindowW(L"STATIC", L"Кольцо 3 (номинал): ", WS_VISIBLE | WS_CHILD,
                10, 70, 150, 20, hWnd, nullptr, hInst, nullptr);
            hComboBand3 = CreateWindowW(L"COMBOBOX", nullptr, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
                150, 70, 150, 200, hWnd, nullptr, hInst, nullptr);
            FillComboBox_2_3m(hComboBand3);
            SetComboBoxColor(hComboBand3);
            ShowWindow(hComboBand3, SW_HIDE); // по умолчанию скрыл
            ShowWindow(hLabelBand3, SW_HIDE); // по умолчанию скрыл

            hLabelBand4 = CreateWindowW(L"STATIC", L"Кольцо (множитель): ", WS_VISIBLE | WS_CHILD,
                10, 100, 150, 20, hWnd, nullptr, hInst, nullptr);
            hComboBand4 = CreateWindowW(L"COMBOBOX", nullptr, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
                150, 100, 150, 200, hWnd, nullptr, hInst, nullptr);
            FillComboBox(hComboBand4);
            SetComboBoxColor(hComboBand4);

            hLabelBand5 = CreateWindowW(L"STATIC", L"Кольцо (точность): ", WS_VISIBLE | WS_CHILD,
                10, 130, 150, 20, hWnd, nullptr, hInst, nullptr);
            hComboBand5 = CreateWindowW(L"COMBOBOX", nullptr, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
                150, 130, 150, 200, hWnd, nullptr, hInst, nullptr);
            FillComboBox_accuracy(hComboBand5);
            SetComboBoxColor(hComboBand5);
            
            // мощность
            hLabelPower = CreateWindowW(L"STATIC", L"Мощность (Вт):", WS_VISIBLE | WS_CHILD,
                10, 160, 100, 20, hWnd, nullptr, hInst, nullptr);
            hComboPower = CreateWindowW(L"COMBOBOX", nullptr, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
                150, 160, 150, 200, hWnd, nullptr, hInst, nullptr);

            // button for calculate
            /*hButton = CreateWindowW(L"BUTTON", L"Рассчитать", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                10, 200, 150, 30, hWnd, (HMENU)1, hInst, nullptr);*/

            // result
            hResultText = CreateWindowW(L"STATIC", L"", WS_VISIBLE | WS_CHILD,
                10, 240, 350, 40, hWnd, nullptr, hInst, nullptr);


            
            SendMessage(hComboPower, CB_ADDSTRING, 0, (LPARAM)L"0.125");
            SendMessage(hComboPower, CB_ADDSTRING, 0, (LPARAM)L"0.25");
            SendMessage(hComboPower, CB_ADDSTRING, 0, (LPARAM)L"0.5");
            SendMessage(hComboPower, CB_ADDSTRING, 0, (LPARAM)L"1");
            SendMessage(hComboPower, CB_ADDSTRING, 0, (LPARAM)L"2");
            SendMessage(hComboPower, CB_ADDSTRING, 0, (LPARAM)L"5");
            SendMessage(hComboPower, CB_SETCURSEL, 0, 0); //
        }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);

            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                HWND hComboBox = (HWND)lParam;
                HandleComboBoxChange(hComboBox);
            }

            switch (wmId)
            {
            case 1:
                RecalculateResistance();
                break;
            case 2:
                isFiveBand = false;
                UpdateComboBoxVisibility();
                RecalculateResistance();
                break;
            case 3:
                isFiveBand = true;
                UpdateComboBoxVisibility();
                RecalculateResistance();
                break;
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
