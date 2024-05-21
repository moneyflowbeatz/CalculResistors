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

//void SetComboBoxColor(HWND hComboBox)
//{
//    SetWindowSubclass(hComboBox, [](HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR) -> LRESULT {
//        switch (uMsg)
//        {
//        case WM_DRAWITEM: {
//            LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
//            if (pDIS->itemID == -1) break; // No item to draw
//
//            std::wstring text(256, L'\0');
//            SendMessage(hWnd, CB_GETLBTEXT, pDIS->itemID, (LPARAM)text.data());
//            text.resize(wcslen(text.data())); // Trim null characters
//
//            HBRUSH hBrush = NULL;
//            COLORREF textColor = RGB(0, 0, 0);
//
//            if (text == L"Black") {
//                hBrush = CreateSolidBrush(RGB(0, 0, 0));
//                textColor = RGB(255, 255, 255);
//            }
//            else if (text == L"Brown") {
//                hBrush = CreateSolidBrush(RGB(150, 75, 0));
//                textColor = RGB(255, 255, 255);
//            }
//            else if (text == L"Red") {
//                hBrush = CreateSolidBrush(RGB(255, 0, 0));
//                textColor = RGB(255, 255, 255);
//            }
//            else if (text == L"Orange") {
//                hBrush = CreateSolidBrush(RGB(255, 165, 0));
//                textColor = RGB(0, 0, 0);
//            }
//            else if (text == L"Yellow") {
//                hBrush = CreateSolidBrush(RGB(255, 255, 0));
//                textColor = RGB(0, 0, 0);
//            }
//            else if (text == L"Green") {
//                hBrush = CreateSolidBrush(RGB(0, 255, 0));
//                textColor = RGB(0, 0, 0);
//            }
//            else if (text == L"Blue") {
//                hBrush = CreateSolidBrush(RGB(0, 0, 255));
//                textColor = RGB(255, 255, 255);
//            }
//            else if (text == L"Violet") {
//                hBrush = CreateSolidBrush(RGB(238, 130, 238));
//                textColor = RGB(0, 0, 0);
//            }
//            else if (text == L"Gray") {
//                hBrush = CreateSolidBrush(RGB(169, 169, 169));
//                textColor = RGB(0, 0, 0);
//            }
//            else if (text == L"White") {
//                hBrush = CreateSolidBrush(RGB(255, 255, 255));
//                textColor = RGB(0, 0, 0);
//            }
//            else if (text == L"Gold") {
//                hBrush = CreateSolidBrush(RGB(255, 215, 0));
//                textColor = RGB(0, 0, 0);
//            }
//            else if (text == L"Silver") {
//                hBrush = CreateSolidBrush(RGB(192, 192, 192));
//                textColor = RGB(0, 0, 0);
//            }
//
//            if (hBrush) {
//                FillRect(pDIS->hDC, &pDIS->rcItem, hBrush);
//                SetTextColor(pDIS->hDC, textColor);
//                SetBkMode(pDIS->hDC, TRANSPARENT);
//                DrawText(pDIS->hDC, text.c_str(), -1, &pDIS->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
//                DeleteObject(hBrush);
//            }
//            return TRUE;
//        }
//        }
//        return DefSubclassProc(hWnd, uMsg, wParam, lParam);
//        }, 0, 0);
//}



LRESULT CALLBACK ComboBoxProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (message)
    {
    case WM_DRAWITEM:
        if (wParam == (WPARAM)0)
        {
            LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT)lParam;
            if (pdis->CtlType == ODT_COMBOBOX)
            {
                HDC hdc = pdis->hDC;
                RECT rect = pdis->rcItem;

                // Цвет фона и текста
                int index = (int)pdis->itemID;
                if (index >= 0 && index < colors.size())
                {
                    if (pdis->itemState & ODS_SELECTED)
                    {
                        SetBkColor(hdc, RGB(0, 120, 215));
                        SetTextColor(hdc, RGB(255, 255, 255));
                    }
                    else
                    {
                        SetBkColor(hdc, RGB(255, 255, 255));
                        SetTextColor(hdc, RGB(0, 0, 0));
                    }

                    FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
                    DrawText(hdc, colors[index].c_str(), -1, &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
                }
                return TRUE;
            }
        }
        break;

    case WM_DESTROY:
        RemoveWindowSubclass(hWnd, ComboBoxProc, uIdSubclass);
        break;
    }

    return DefSubclassProc(hWnd, message, wParam, lParam);
}

void SetComboBoxColor(HWND hComboBox)
{
    SetWindowSubclass(hComboBox, ComboBoxProc, 0, 0);
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
    int val3 = isFiveBand ? colorVal[SendMessage(hComboBand3, CB_GETCURSEL, 0, 0)] : 0;
    int multiplier = colorVal[SendMessage(hComboBand4, CB_GETCURSEL, 0, 0)];
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
        resistance = (val1 * 100 + val2 * 10 + val3) * pow(10, multiplier);
    }
    else
    {
        resistance = (val1 * 10 + val2) * pow(10, multiplier);
    }

    std::wstring result = L"Сопротивление: " + std::to_wstring(resistance) + L" Ом ± " + tolerance;
    SetWindowText(hResultText, result.c_str());
    InvalidateRect(hResultText, NULL, TRUE);
    InvalidateRect(hComboBand1, NULL, TRUE);
    InvalidateRect(hComboBand2, NULL, TRUE);
    InvalidateRect(hComboBand3, NULL, TRUE);
    InvalidateRect(hComboBand4, NULL, TRUE);
    InvalidateRect(hComboBand5, NULL, TRUE);
}



void DrawResistor(HDC hdc, RECT& rect)
{
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    int resistorWidth = width / 3;
    int resistorHeight = height / 8;
    int startX = (width - resistorWidth) / 2;
    int startY = (height - resistorHeight) / 2;

    // Рисуем резистор
    Rectangle(hdc, startX, startY, startX + resistorWidth, startY + resistorHeight);

    // Рисуем полосы
    int numBands = isFiveBand ? 5 : 4;
    int bandWidth = resistorWidth / (numBands + 1);
    int bandHeight = resistorHeight;

    HBRUSH hBrush;
    for (int i = 0; i < numBands; ++i)
    {
        int colorIndex;
        switch (i)
        {
        case 0:
            colorIndex = SendMessage(hComboBand1, CB_GETCURSEL, 0, 0);
            break;
        case 1:
            colorIndex = SendMessage(hComboBand2, CB_GETCURSEL, 0, 0);
            break;
        case 2:
            colorIndex = isFiveBand ? SendMessage(hComboBand3, CB_GETCURSEL, 0, 0) : SendMessage(hComboBand4, CB_GETCURSEL, 0, 0);
            break;
        case 3:
            colorIndex = SendMessage(hComboBand4, CB_GETCURSEL, 0, 0);
            break;
        case 4:
            colorIndex = SendMessage(hComboBand5, CB_GETCURSEL, 0, 0);
            break;
        default:
            colorIndex = 0;
            break;
        }

        COLORREF color;
        switch (colorIndex)
        {
        case 0: color = RGB(0, 0, 0); break;              // Черный
        case 1: color = RGB(139, 69, 19); break;          // Коричневый
        case 2: color = RGB(255, 0, 0); break;            // Красный
        case 3: color = RGB(255, 165, 0); break;          // Оранжевый
        case 4: color = RGB(255, 255, 0); break;          // Желтый
        case 5: color = RGB(0, 128, 0); break;            // Зеленый
        case 6: color = RGB(0, 0, 255); break;            // Синий
        case 7: color = RGB(238, 130, 238); break;        // Фиолетовый
        case 8: color = RGB(128, 128, 128); break;        // Серый
        case 9: color = RGB(255, 255, 255); break;        // Белый
        case 10: color = RGB(255, 215, 0); break;         // Золотой
        case 11: color = RGB(192, 192, 192); break;       // Серебряный
        default: color = RGB(0, 0, 0); break;             // Черный по умолчанию
        }

        hBrush = CreateSolidBrush(color);
        SelectObject(hdc, hBrush);

        RECT bandRect;
        bandRect.left = startX + (i + 1) * bandWidth - (bandWidth / 2);
        bandRect.top = startY;
        bandRect.right = bandRect.left + bandWidth;
        bandRect.bottom = startY + bandHeight;

        FillRect(hdc, &bandRect, hBrush);
        DeleteObject(hBrush);
    }
}

void HandleComboBoxChange(HWND hComboBox)
{
    if (hComboBox == hComboBand1 || hComboBox == hComboBand2 || hComboBox == hComboBand3 || hComboBox == hComboBand4 || hComboBox == hComboBand5)
    {
        RecalculateResistance();
        InvalidateRect(GetParent(hComboBox), NULL, TRUE); // Обновление окна при изменении значений
    }
}

void InitializeBands()
{
    FillComboBox_1m(hComboBand1);
    FillComboBox_2_3m(hComboBand2);
    if (isFiveBand)
    {
        FillComboBox_2_3m(hComboBand3);
    }
    FillComboBox(hComboBand4);
    FillComboBox_accuracy(hComboBand5);
}






LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        hComboBand1 = CreateWindow(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE, 10, 140, 100, 200, hWnd, NULL, hInst, NULL);
        hComboBand2 = CreateWindow(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE, 120, 140, 100, 200, hWnd, NULL, hInst, NULL);
        hComboBand3 = CreateWindow(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE, 230, 140, 100, 200, hWnd, NULL, hInst, NULL);
        hComboBand4 = CreateWindow(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE, 340, 140, 100, 200, hWnd, NULL, hInst, NULL);
        hComboBand5 = CreateWindow(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE, 450, 140, 100, 200, hWnd, NULL, hInst, NULL);

        hButton = CreateWindow(L"BUTTON", L"Рассчитать", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 560, 140, 100, 25, hWnd, (HMENU)1, hInst, NULL);
        hResultText = CreateWindow(L"STATIC", L"", WS_CHILD | WS_VISIBLE, 10, 50, 300, 25, hWnd, NULL, hInst, NULL);

        hFourBandRadio = CreateWindow(L"BUTTON", L"4 полосы", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 10, 10, 100, 25, hWnd, (HMENU)2, hInst, NULL);
        hFiveBandRadio = CreateWindow(L"BUTTON", L"5 полос", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 120, 10, 100, 25, hWnd, (HMENU)3, hInst, NULL);

        SendMessage(hFourBandRadio, BM_SETCHECK, BST_CHECKED, 0);
        isFiveBand = false;

        hLabelBand1 = CreateWindow(L"STATIC", L"1-я полоса", WS_CHILD | WS_VISIBLE, 10, 110, 100, 25, hWnd, NULL, hInst, NULL);
        hLabelBand2 = CreateWindow(L"STATIC", L"2-я полоса", WS_CHILD | WS_VISIBLE, 120, 110, 100, 25, hWnd, NULL, hInst, NULL);
        hLabelBand3 = CreateWindow(L"STATIC", L"3-я полоса", WS_CHILD | WS_VISIBLE, 230, 110, 100, 25, hWnd, NULL, hInst, NULL);
        hLabelBand4 = CreateWindow(L"STATIC", L"Множитель", WS_CHILD | WS_VISIBLE, 340, 110, 100, 25, hWnd, NULL, hInst, NULL);
        hLabelBand5 = CreateWindow(L"STATIC", L"Допуск", WS_CHILD | WS_VISIBLE, 450, 110, 100, 25, hWnd, NULL, hInst, NULL);

        UpdateComboBoxVisibility();

        // Заполняем комбобоксы
        InitializeBands();

        // Подписываемся на изменение выбранного элемента в комбобоксах
        SendMessage(hComboBand1, CB_SETCURSEL, 0, 0);
        SendMessage(hComboBand2, CB_SETCURSEL, 0, 0);
        SendMessage(hComboBand4, CB_SETCURSEL, 0, 0);
        SendMessage(hComboBand5, CB_SETCURSEL, 0, 0);

        SetComboBoxColor(hComboBand1);
        SetComboBoxColor(hComboBand2);
        SetComboBoxColor(hComboBand4);
        SetComboBoxColor(hComboBand5);

        if (isFiveBand) {
            SetComboBoxColor(hComboBand3);
        }

        RecalculateResistance();
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case 1:
            RecalculateResistance();
            break;
        case 2:
            isFiveBand = false;
            UpdateComboBoxVisibility();
            InitializeBands();
            RecalculateResistance();
            break;
        case 3:
            isFiveBand = true;
            UpdateComboBoxVisibility();
            InitializeBands();
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

        RECT rect;
        GetClientRect(hWnd, &rect);
        DrawResistor(hdc, rect);

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
