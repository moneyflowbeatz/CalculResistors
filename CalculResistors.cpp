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

std::vector<std::wstring> colours = {L"Black", L"Brown", L"Red", L"Orange", L"Yellow", L"Green", L"Blue", L"Violet", L"Gray", L"White", L"Gold", L"Silver" };
std::vector<int> colorVal = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -2 };
std::vector<int> colorVal_1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
std::vector<int> colorVal_2 = { 1, 2, 5, 6, 7, 8, -1, 2 };

std::vector<COLORREF> colors = {
    RGB(0, 0, 0),         // Black 0
    RGB(139, 69, 19),     // Brown 1
    RGB(255, 0, 0),       // Red 2 
    RGB(255, 165, 0),     // Orange 3
    RGB(255, 255, 0),     // Yellow 4 
    RGB(0, 128, 0),       // Green 5 
    RGB(0, 0, 255),       // Blue 6
    RGB(128, 0, 128),     // Violet 7
    RGB(128, 128, 128),   // Gray 8
    RGB(255, 255, 255),   // White 9
    RGB(255, 215, 0),     // Gold -1
    RGB(192, 192, 192)    // Silver -2
};

std::vector<COLORREF> colors_2 = {
    RGB(139, 69, 19),     // Brown
    RGB(255, 0, 0),       // Red
    RGB(255, 165, 0),     // Orange
    RGB(255, 255, 0),     // Yellow
    RGB(0, 128, 0),       // Green
    RGB(0, 0, 255),       // Blue
    RGB(128, 0, 128),     // Violet
    RGB(128, 128, 128),   // Gray
    RGB(255, 255, 255),   // White
};

std::vector<COLORREF> colors_3 = {
    RGB(139, 69, 19),     // Brown
    RGB(255, 0, 0),       // Red
    RGB(0, 128, 0),       // Green
    RGB(0, 0, 255),       // Blue
    RGB(128, 0, 128),     // Violet
    RGB(128, 128, 128),   // Gray
    RGB(255, 215, 0),     // Gold
    RGB(192, 192, 192)    // Silver
};

class ResistorBand {
public:
    ResistorBand(COLORREF color) : color(color) {}
    void Draw(HDC hdc, int x, int y, int width, int height) const {
        HBRUSH hBrush = CreateSolidBrush(color);
        RECT rect = { x, y, x + width, y + height };
        FillRect(hdc, &rect, hBrush);
        DeleteObject(hBrush);
    }
private:
    COLORREF color;
};

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



//LRESULT CALLBACK ComboBoxProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
//{
//    switch (message)
//    {
//    case WM_DRAWITEM:
//        if (wParam == (WPARAM)0)
//        {
//            LPDRAWITEMSTRUCT pdis = (LPDRAWITEMSTRUCT)lParam;
//            if (pdis->CtlType == ODT_COMBOBOX)
//            {
//                HDC hdc = pdis->hDC;
//                RECT rect = pdis->rcItem;
//
//                // Цвет фона и текста
//                int index = (int)pdis->itemID;
//                if (index >= 0 && index < colors.size())
//                {
//                    if (pdis->itemState & ODS_SELECTED)
//                    {
//                        SetBkColor(hdc, RGB(0, 120, 215));
//                        SetTextColor(hdc, RGB(255, 255, 255));
//                    }
//                    else
//                    {
//                        SetBkColor(hdc, RGB(255, 255, 255));
//                        SetTextColor(hdc, RGB(0, 0, 0));
//                    }
//
//                    FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
//                    DrawText(hdc, colours[index].c_str(), -1, &rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
//                }
//                return TRUE;
//            }
//        }
//        break;
//
//    case WM_DESTROY:
//        RemoveWindowSubclass(hWnd, ComboBoxProc, uIdSubclass);
//        break;
//    }
//
//    return DefSubclassProc(hWnd, message, wParam, lParam);
//}

//void SetComboBoxColor(HWND hComboBox)
//{
//    SetWindowSubclass(hComboBox, ComboBoxProc, 0, 0);
//}


void FillComboBox(HWND hComboBox)
{
    for (const auto& color : colours)
    {
        SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)color.c_str());
    }
    SendMessage(hComboBox, CB_SETCURSEL, 0, 0); // первый элемент в 0 - Black
    
}

void FillComboBox_accuracy(HWND hComboBox)
{
    std::vector<int> forbiddenColors = { 0, 3, 4, 9 }; // Индексы черного, оранжевого, желтого и белого цветов

    for (size_t i = 0; i < colours.size(); ++i)
    {
        if (std::find(forbiddenColors.begin(), forbiddenColors.end(), i) == forbiddenColors.end())
        {
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)colours[i].c_str());
        }
    }
    SendMessage(hComboBox, CB_SETCURSEL, 0, 0); // первый элемент в 0
    
}

void FillComboBox_1m(HWND hComboBox)
{
    std::vector<int> forbiddenColors = { 0, 10, 11 }; 

    for (size_t i = 0; i < colours.size(); ++i)
    {
        if (std::find(forbiddenColors.begin(), forbiddenColors.end(), i) == forbiddenColors.end())
        {
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)colours[i].c_str());
        }
    }
    SendMessage(hComboBox, CB_SETCURSEL, 0, 0); // первый элемент в 0
    
}

void FillComboBox_2_3m(HWND hComboBox)
{
    std::vector<int> forbiddenColors = { 10, 11 };

    for (size_t i = 0; i < colours.size(); ++i)
    {
        if (std::find(forbiddenColors.begin(), forbiddenColors.end(), i) == forbiddenColors.end())
        {
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)colours[i].c_str());
        }
    }
    SendMessage(hComboBox, CB_SETCURSEL, 0, 0); // первый элемент в 0
    
}


void UpdateComboBoxVisibility()
{
    ShowWindow(hLabelBand3, isFiveBand ? SW_SHOW : SW_HIDE);
    ShowWindow(hComboBand3, isFiveBand ? SW_SHOW : SW_HIDE);
}

void RecalculateResistance()
{
    // Получение значений цвета для каждой полосы
    int val1 = colorVal_1[SendMessage(hComboBand1, CB_GETCURSEL, 0, 0)];
    int val2 = colorVal[SendMessage(hComboBand2, CB_GETCURSEL, 0, 0)];
    int val3 = isFiveBand ? colorVal[SendMessage(hComboBand3, CB_GETCURSEL, 0, 0)] : 0;
    int multiplier = colorVal[SendMessage(hComboBand4, CB_GETCURSEL, 0, 0)];
    int band5 = SendMessage(hComboBand5, CB_GETCURSEL, 0, 0);
    std::wstring tolerance;

    // Определение допуска по цвету пятой полосы
    switch (band5) {
    case 0: tolerance = L"1%"; break; // Коричневый
    case 1: tolerance = L"2%"; break; // Красный
    case 2: tolerance = L"0.5%"; break; // Зеленый
    case 3: tolerance = L"0.25%"; break; // Синий
    case 4: tolerance = L"0.1%"; break; // Фиолетовый
    case 5: tolerance = L"0.05%"; break; // Серый
    case 6: tolerance = L"5%"; break; // Золото
    case 7: tolerance = L"10%"; break; // Серебро
    default: tolerance = L""; break;
    }

    // Расчет сопротивления
    double resistance = 0.0;
    if (isFiveBand) {
        resistance = (val1 * 100 + val2 * 10 + val3) * std::pow(10, multiplier);
    }
    else {
        resistance = (val1 * 10 + val2) * std::pow(10, multiplier);
    }

    // Форматирование результата
    std::wstring unit = L" Ом";
    if (resistance >= 1e9) {
        resistance /= 1e9;
        unit = L" ГОм";
    }
    else if (resistance >= 1e6) {
        resistance /= 1e6;
        unit = L" МОм";
    }
    else if (resistance >= 1e3) {
        resistance /= 1e3;
        unit = L" кОм";
    }

    // Формирование строки результата
    std::wstringstream resultStream;
    resultStream << std::fixed << std::setprecision(2) << resistance << unit << L" ± " << tolerance;
    std::wstring result = L"Сопротивление: " + resultStream.str();
    SetWindowText(hResultText, result.c_str());

    // Обновление отображения
    InvalidateRect(hResultText, NULL, TRUE);
    InvalidateRect(hComboBand1, NULL, TRUE);
    InvalidateRect(hComboBand2, NULL, TRUE);
    InvalidateRect(hComboBand3, NULL, TRUE);
    InvalidateRect(hComboBand4, NULL, TRUE);
    InvalidateRect(hComboBand5, NULL, TRUE);
}

void DrawResistor(HDC hdc, const std::vector<ResistorBand>& bands, int x, int y, int bandWidth, int bandHeight, int spacing) {
    for (size_t i = 0; i < bands.size(); ++i) {
        bands[i].Draw(hdc, x + i * (bandWidth + spacing), y, bandWidth, bandHeight);
    }
}

void DrawResistor(HDC hdc)
{
    int index1 = (SendMessage(hComboBand1, CB_GETCURSEL, 0, 0) < colors_2.size()) ? SendMessage(hComboBand1, CB_GETCURSEL, 0, 0) : colors_2.size() - 1;
    int index2 = (SendMessage(hComboBand2, CB_GETCURSEL, 0, 0) < colors.size()) ? SendMessage(hComboBand2, CB_GETCURSEL, 0, 0) : colors.size() - 1;
    int index3 = 0; // Default value
    if (isFiveBand) {
        index3 = (SendMessage(hComboBand3, CB_GETCURSEL, 0, 0) < colors.size()) ? SendMessage(hComboBand3, CB_GETCURSEL, 0, 0) : colors.size() - 1;
    }
    int index4 = (SendMessage(hComboBand4, CB_GETCURSEL, 0, 0) < colors.size()) ? SendMessage(hComboBand4, CB_GETCURSEL, 0, 0) : colors.size() - 1;
    int index5 = (SendMessage(hComboBand5, CB_GETCURSEL, 0, 0) < colors_3.size()) ? SendMessage(hComboBand5, CB_GETCURSEL, 0, 0) : colors_3.size() - 1;

    std::vector<ResistorBand> bands;
    bands.push_back(ResistorBand(colors_2[index1]));
    bands.push_back(ResistorBand(colors[index2]));
    if (isFiveBand) {
        bands.push_back(ResistorBand(colors[index3]));
    }
    bands.push_back(ResistorBand(colors[index4]));
    bands.push_back(ResistorBand(colors_3[index5]));
    
    int x = 150, y = 300, bandWidth = 20, bandHeight = 80, spacing = 10;
    DrawResistor(hdc, bands, x, y, bandWidth, bandHeight, spacing);
}

void DrawResistor5(HDC hdc)
{
    int index1 = (SendMessage(hComboBand1, CB_GETCURSEL, 0, 0) < colors_2.size()) ? SendMessage(hComboBand1, CB_GETCURSEL, 0, 0) : colors_2.size() - 1;
    int index2 = (SendMessage(hComboBand2, CB_GETCURSEL, 0, 0) < colors.size()) ? SendMessage(hComboBand2, CB_GETCURSEL, 0, 0) : colors.size() - 1;
    int index3 = (SendMessage(hComboBand3, CB_GETCURSEL, 0, 0) < colors.size()) ? SendMessage(hComboBand3, CB_GETCURSEL, 0, 0) : colors.size() - 1;
    int index4 = (SendMessage(hComboBand4, CB_GETCURSEL, 0, 0) < colors.size()) ? SendMessage(hComboBand4, CB_GETCURSEL, 0, 0) : colors.size() - 1;
    int index5 = (SendMessage(hComboBand5, CB_GETCURSEL, 0, 0) < colors_3.size()) ? SendMessage(hComboBand5, CB_GETCURSEL, 0, 0) : colors_3.size() - 1;

    std::vector<ResistorBand> bands;
    bands.push_back(ResistorBand(colors_2[index1]));
    bands.push_back(ResistorBand(colors[index2]));
    bands.push_back(ResistorBand(colors[index3]));
    bands.push_back(ResistorBand(colors[index4]));
    bands.push_back(ResistorBand(colors_3[index5]));

    int x = 150, y = 300, bandWidth = 20, bandHeight = 80, spacing = 10;
    DrawResistor(hdc, bands, x, y, bandWidth, bandHeight, spacing);
}

void ToggleBands(bool fiveBand)
{
    isFiveBand = fiveBand;
    UpdateComboBoxVisibility();
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
    FillComboBox_2_3m(hComboBand3);
    FillComboBox(hComboBand4);
    FillComboBox_accuracy(hComboBand5);
}

void (*FillComboBoxMethod1)(HWND) = FillComboBox_1m;
void (*FillComboBoxMethod2)(HWND) = FillComboBox_2_3m;

void CreateControls(HWND hWnd)
{
    // Creating UI controls with positioning

    int margin = 10;
    int labelWidth = 100;
    int comboWidth = 150;
    int height = 25;
    int top = margin;
    int left = margin;

    hFourBandRadio = CreateWindow(L"BUTTON", L"4 кольца", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
        left, top, labelWidth, height, hWnd, (HMENU)ID_FOURBANDRADIO, hInst, NULL);
    SendMessage(hFourBandRadio, BM_SETCHECK, BST_CHECKED, 0);

    left += labelWidth + margin;

    hFiveBandRadio = CreateWindow(L"BUTTON", L"5 колец", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
        left, top, labelWidth, height, hWnd, (HMENU)ID_FIVEBANDRADIO, hInst, NULL);

    left = margin;
    top += height + margin;

    hLabelBand1 = CreateWindow(L"STATIC", L"Номинал:", WS_VISIBLE | WS_CHILD,
        left, top, labelWidth, height, hWnd, NULL, hInst, NULL);

    left += labelWidth + margin;

    hComboBand1 = CreateWindow(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
        left, top, comboWidth, height * 10, hWnd, (HMENU)IDC_COMBO1, hInst, NULL);
   // FillComboBox_1m(hComboBand1);

   

    left = margin;
    top += height + margin;

    hLabelBand2 = CreateWindow(L"STATIC", L"Номинал:", WS_VISIBLE | WS_CHILD,
        left, top, labelWidth, height, hWnd, NULL, hInst, NULL);

    left += labelWidth + margin;

    hComboBand2 = CreateWindow(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
        left, top, comboWidth, height * 10, hWnd, (HMENU)IDC_COMBO2, hInst, NULL);
    // FillComboBox_2_3m(hComboBand2);
    

    left = margin;
    top += height + margin;
    
        hLabelBand3 = CreateWindow(L"STATIC", L"Номинал:", WS_VISIBLE | WS_CHILD,
            left, top, labelWidth, height, hWnd, NULL, hInst, NULL);

        left += labelWidth + margin;


        hComboBand3 = CreateWindow(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
            left, top, comboWidth, height * 10, hWnd, (HMENU)IDC_COMBO3, hInst, NULL);
        UpdateComboBoxVisibility();
        // FillComboBox_2_3m(hComboBand3);

        left = margin;
        top += height + margin;
    
    hLabelBand4 = CreateWindow(L"STATIC", L"Множитель:", WS_VISIBLE | WS_CHILD,
        left, top, labelWidth, height, hWnd, NULL, hInst, NULL);

    left += labelWidth + margin;

    hComboBand4 = CreateWindow(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
        left, top, comboWidth, height * 10, hWnd, (HMENU)IDC_COMBO4, hInst, NULL);

    // FillComboBox(hComboBand4);

    left = margin;
    top += height + margin;

    hLabelBand5 = CreateWindow(L"STATIC", L"Точность:", WS_VISIBLE | WS_CHILD,
        left, top, labelWidth, height, hWnd, NULL, hInst, NULL);

    left += labelWidth + margin;

    hComboBand5 = CreateWindow(L"COMBOBOX", NULL, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
        left, top, comboWidth, height * 10, hWnd, (HMENU)IDC_COMBO5, hInst, NULL);

    // FillComboBox_accuracy(hComboBand5);

    left = margin;
    top += height + margin;

    /*hButton = CreateWindow(L"BUTTON", L"Calculate", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        left, top, labelWidth, height, hWnd, (HMENU)IDC_BUTTON, hInst, NULL);*/

    left += labelWidth + margin;

    hResultText = CreateWindow(L"STATIC", L"", WS_VISIBLE | WS_CHILD,
        left, top, comboWidth * 2, height, hWnd, NULL, hInst, NULL);

    FillComboBoxMethod1(hComboBand1);
    FillComboBoxMethod2(hComboBand2);
    if (isFiveBand) {
        FillComboBoxMethod2(hComboBand3);
    }
    FillComboBox(hComboBand4);
    FillComboBox_accuracy(hComboBand5);
}


void OnComboBoxChange(HWND hWnd)
{
    // Пересчитать сопротивление
    RecalculateResistance();

    // Обновить отображение резистора
    InvalidateRect(hWnd, NULL, TRUE);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        CreateControls(hWnd);
        break;
    
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        if (isFiveBand) 
            DrawResistor5(hdc);
        else
            DrawResistor(hdc);
        EndPaint(hWnd, &ps);
    }
    break;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case ID_FOURBANDRADIO:
            isFiveBand = false;
            UpdateComboBoxVisibility();
            
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        case ID_FIVEBANDRADIO:
            isFiveBand = true;
            UpdateComboBoxVisibility();
            FillComboBoxMethod2(hComboBand3);
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                switch (LOWORD(wParam))
                {
                case IDC_COMBO1:
                case IDC_COMBO2:
                case IDC_COMBO3:
                case IDC_COMBO4:
                case IDC_COMBO5:
                    OnComboBoxChange(hWnd);
                    break;
                }
            }
            else if (LOWORD(wParam) == IDC_BUTTON)
            {
                RecalculateResistance();
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
