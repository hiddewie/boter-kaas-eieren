#include <windows.h>
#include "resource.h"
#include "tchar.h"

bool bDrawCircle = false;
bool bDrawCross = false;
bool Win = false, Draw = false;
bool bDraw [9];
char iDraw [9];
char user = 'X';

char sw(char user);
void reset ();
void drawX (int n, HDC hdc);
void drawO (int n, HDC hdc);
void checkWin ();
void checkDraw ();



LPCTSTR		ClsName = L"App";											// Class name
LPCTSTR		WndName = L"Boter Kaas en Eieren";							// Window title
HWND        hwnd;														// Handle to our main window

////////////////////////////////////////////////////

LRESULT CALLBACK WndProcedure(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);	

////////////////////////////////////////////////////

INT WINAPI WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, 
	int nCmdShow)
{
	MSG        Msg;														// Structure to hold messages for our WinProc
	WNDCLASSEX WndClsEx;												// Our WNDCLASSEX structure used to define a window

	for (int n=0; n<9; n++) {
		bDraw [n] = false;
		iDraw [n] = 0;
	}

	// Define our window
	WndClsEx.cbSize			 = sizeof(WNDCLASSEX);						// The size in bytes of the structure
	WndClsEx.style			 = CS_HREDRAW | CS_VREDRAW;					// Style flags: CS_HREDRAW | CS_VREDRAW redraws the window on resize
	WndClsEx.lpfnWndProc	 = WndProcedure;							// Pointer to the windows procedure
	WndClsEx.cbClsExtra		 = 0;										// Extra bytes to allocate the window class structure
	WndClsEx.cbWndExtra		 = 0;										// Extra bytes to allocate the window instance structure
	WndClsEx.hIcon			 = LoadIcon(NULL, IDI_APPLICATION);			// A handle to the window class's icon, this uses the default 
	WndClsEx.hCursor		 = LoadCursor(NULL, IDC_ARROW);				// A handle to the window class's cursor, this uses default
	WndClsEx.hbrBackground	 = (HBRUSH)GetStockObject(WHITE_BRUSH);		// A handle to the brush used to paint the background, we use white
	WndClsEx.lpszMenuName	 = MAKEINTRESOURCE(IDR_MAIN_MENU);									// Name of the menu resource if used, we dont use resources here			
	WndClsEx.lpszClassName	 = ClsName;									// Class name
	WndClsEx.hInstance		 = hInstance;								// handle to the instance that contains the WinProc for the class
	WndClsEx.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);			// A handle to the window class's small icon 

	// If register class fails, exit with error message
	if (!RegisterClassEx(&WndClsEx))
	{
		MessageBox(NULL, L"Could not register class", L"Error", NULL);

	}

	// Create the window 
	hwnd = CreateWindowEx(0,
		ClsName, WndName,								// Class name, Window title
		WS_OVERLAPPEDWINDOW,							// Window style, WS_OVERLAPPEDWINDOW allows resizing
		400, 220,											// x coord , y coord				
		317, 357,										// Width, Height
		NULL,											// Parent (if child)
		NULL,											// hMenu
		hInstance,										// Instance
		NULL);											// Additional info not needed

	// Check if window was created, if it wasn't, exit.
	if(!hwnd) 
		return FALSE;

	// Actually display the window
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Decode and treat the messages
	while(GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

////////////////////////////////////////////////////

LRESULT CALLBACK WndProcedure(HWND hwnd,				// Handle to our main window
	UINT Msg,											// Our message that needs to be processed
	WPARAM wParam,										// Extra values of message (Mouse for example might have x and y coord values)
	LPARAM lParam)										// Extra values of message (Mouse for example might have x and y coord values)
{
	HDC hdc;
	int WmID;
	PAINTSTRUCT ps;
	int iPosX = LOWORD(lParam);
	int iPosY = HIWORD(lParam);

	switch(Msg)
	{
	case WM_LBUTTONDOWN:
		{

			if (iPosX<=105) {
				if (iPosY <= 100) {
					if (!(iDraw[0])) {
						iDraw [0] = user;
						bDraw [0] = true;
						user = sw (user); 

					}
				}
				else if (iPosY > 100 && iPosY <= 200) {
					if (!(iDraw[3])) {
						iDraw [3] = user;
						bDraw [3] = true;
						user = sw (user); 
					}
				}
				else {
					if (!(iDraw[6])) {
						iDraw [6] = user;
						bDraw [6] = true;
						user = sw (user); 
					}
				}
			}
			else if (iPosX > 100 && iPosX <= 200) {
				if (iPosY <= 100) {
					if (!(iDraw[1])) {
						iDraw [1] = user;
						bDraw [1] = true;
						user = sw (user); 
					}
				}
				else if (iPosY > 100 && iPosY <= 200) {
					if (!(iDraw[4])) {
						iDraw [4] = user;
						bDraw [4] = true;
						user = sw (user); 
					}
				}
				else {
					if (!(iDraw[7])) {
						iDraw [7] = user;
						bDraw [7] = true;
						user = sw (user); 
					}
				}
			}
			else {
				if (iPosY <= 100) {
					if (!(iDraw[2])) {
						iDraw [2] = user;
						bDraw [2] = true;
						user = sw (user); 
					}
				}
				else if (iPosY > 100 && iPosY <= 200) {
					if (!(iDraw[5])) {
						iDraw [5] = user;
						bDraw [5] = true;
						user = sw (user); 
					}
				}
				else {
					if (!(iDraw[8])) {
						iDraw [8] = user;
						bDraw [8] = true;
						user = sw (user); 
					}
				}
			}


			InvalidateRect (hwnd, 0, TRUE); 

			checkWin (); 
			checkDraw ();

			if (Win) {
				user = sw (user);

				if (user == 'X') {
					int iMes = MessageBox (hwnd, L"Gefeliciteerd! Speler 'X' heeft gewonnen! Wilt u nog een keer spelen?", L"X Wint!", MB_ICONASTERISK | MB_YESNO);
					switch (iMes) {
					case IDYES:
						for (int n=0; n<9; n++) {
							iDraw [n] = 0;
							bDraw [n] = false;
						}
							
						reset ();
						
						break;
					case IDNO:
						PostQuitMessage(WM_QUIT);
						break;
					}

				}
				if (user == 'O') {
					int iMes = MessageBox (hwnd, L"Gefeliciteerd! Speler 'O' heeft gewonnen! Wilt u nog een keer spelen?", L"O Wint!", MB_ICONASTERISK | MB_YESNO);
					switch (iMes) {
					case IDYES:
						for (int n=0; n<9; n++) {
							iDraw [n] = 0;
							bDraw [n] = false;
						}
							
						reset ();
						
						break;
					case IDNO:
						PostQuitMessage(WM_QUIT);
						break;
					}

				}
			}

			if (Draw) {
				int iMes = MessageBox (hwnd, L"Jammer! Geen van de spelers heeft gewonnen... Wilt u nog een keer spelen?", L"Geen winnaar", MB_ICONASTERISK | MB_YESNO);
				switch (iMes) {
				case IDYES:
						for (int n=0; n<9; n++) {
							iDraw [n] = 0;
							bDraw [n] = false;
						}
						
						reset ();
						
						break;
					case IDNO:
						PostQuitMessage(WM_QUIT);
						break;
				}
			}
			
			InvalidateRect (hwnd, 0, TRUE);

			break;
		}
	case WM_MBUTTONDOWN:
		{
			int iPosX = LOWORD(lParam);
			int iPosY = HIWORD(lParam);

			wchar_t waCoord [20];
			wsprintf (waCoord, L"(%1d , %1d)", iPosX, iPosY);
			MessageBox (hwnd, waCoord, L"Coordinates!", MB_ICONASTERISK);

			break;
		}

	case WM_DESTROY:
		{ // If a close message is sent to the message loop
			PostQuitMessage(WM_QUIT);					// Exit
			break;
		}

	case WM_PAINT:
		{ 
			hdc = BeginPaint (hwnd, &ps);

			HPEN hPenOld3;
			HPEN hLinePen;

			hLinePen = CreatePen (PS_SOLID, 5, RGB (250,50,0));
			hPenOld3 = (HPEN) SelectObject (hdc, hLinePen);

			MoveToEx (hdc, 0,100,NULL);
			LineTo (hdc, 300,100);
			MoveToEx (hdc, 0,200,NULL);
			LineTo (hdc, 300,200);
			MoveToEx (hdc, 100,0,NULL);
			LineTo (hdc, 100,300);
			MoveToEx (hdc, 200,0,NULL);
			LineTo (hdc, 200,300);

			SelectObject (hdc, hPenOld3);
			DeleteObject (hLinePen);

			for (int n=0;n<9;n++) {
				if (iDraw [n] == 'X'){
					HPEN hPenBin;
					HPEN hXPen;

					hXPen = CreatePen (PS_SOLID, 3, RGB (0,200,0));
					hPenBin = (HPEN) SelectObject (hdc, hXPen);

					drawX(n,hdc);

					SelectObject (hdc, hPenBin);
					DeleteObject (hXPen);
				}
				else if (iDraw [n] == 'O') {
					HPEN hPenBin2;
					HPEN hOPen;

					hOPen = CreatePen (PS_SOLID, 3, RGB (0,0,200));
					hPenBin2 = (HPEN) SelectObject (hdc, hOPen);

					drawO(n,hdc);

					SelectObject (hdc, hPenBin2);
					DeleteObject (hOPen);
				}

			}
			break;
		}
	case WM_COMMAND:
		{
			int iMes;


			WmID = LOWORD(wParam);
			switch (WmID)
			{
			case IDM_RESTART:
				iMes = MessageBox (hwnd, L"Er is 'opniew starten' aangeklikt.\nWeet u zeker dat u opnieuw wil starten?", L"Opnieuw starten", MB_YESNO | MB_ICONQUESTION);
				switch (iMes) {
				case IDYES:
					for (int n=0; n<9; n++) {
						iDraw [n] = 0;
						bDraw [n] = false;
					}
					reset ();
					
					InvalidateRect (hwnd, 0, TRUE);
					break;
				case IDNO:
					break;
				}

				break;

			case IDM_EXIT:
				PostQuitMessage(WM_QUIT);					// Exit
				break;

			case IDM_ABOUT:
				MessageBox (hwnd, L"Versie: 2.1\n\n(C) Hidde Wieringa 2010", L"About", MB_OK);
				break;

			case IDM_HELP:
				MessageBox (hwnd, L"Info:\n\nSpeler 'X' begint. Klik op een leeg vakje om je teken te plaatsen.\n\
								   Als er een drie op een rij is gevonden, wordt dat automatisch weergegeven.\nSucces!", L"Help", MB_OK);
				break;
			}

		}
		break;
	default:										// Handle all other messages in a normal way
		return DefWindowProc(hwnd, Msg, wParam, lParam);
	}
	return 0;
}

char sw (char user) {
	if (user == 'X')
		return 'O';
	else if (user == 'O')
		return 'X';
}

void drawX (int n, HDC hdc) {
	switch (n) {
	case 0:
		MoveToEx (hdc, 10,10,NULL);
		LineTo (hdc, 90,90);
		MoveToEx (hdc, 90,10,NULL);
		LineTo (hdc, 10,90);
		break;
	case 1:
		MoveToEx (hdc, 110,10,NULL);
		LineTo (hdc, 190,90);
		MoveToEx (hdc, 190,10,NULL);
		LineTo (hdc, 110,90);
		break;
	case 2:
		MoveToEx (hdc, 210,10,NULL);
		LineTo (hdc, 290,90);
		MoveToEx (hdc, 290,10,NULL);
		LineTo (hdc, 210,90);
		break;
	case 3:
		MoveToEx (hdc, 10,110,NULL);
		LineTo (hdc, 90,190);
		MoveToEx (hdc, 90,110,NULL);
		LineTo (hdc, 10,190);
		break;
	case 4:
		MoveToEx (hdc, 110,110,NULL);
		LineTo (hdc, 190,190);
		MoveToEx (hdc, 190,110,NULL);
		LineTo (hdc, 110,190);
		break;
	case 5:
		MoveToEx (hdc, 210,110,NULL);
		LineTo (hdc, 290,190);
		MoveToEx (hdc, 290,110,NULL);
		LineTo (hdc, 210,190);
		break;
	case 6:
		MoveToEx (hdc, 10,210,NULL);
		LineTo (hdc, 90,290);
		MoveToEx (hdc, 90,210,NULL);
		LineTo (hdc, 10,290);
		break;
	case 7:
		MoveToEx (hdc, 110,210,NULL);
		LineTo (hdc, 190,290);
		MoveToEx (hdc, 190,210,NULL);
		LineTo (hdc, 110,290);
		break;
	case 8:
		MoveToEx (hdc, 210,210,NULL);
		LineTo (hdc, 290,290);
		MoveToEx (hdc, 290,210,NULL);
		LineTo (hdc, 210,290);
		break;
	}

}

void drawO (int n, HDC hdc) {
	switch (n) {
	case 0:
		Arc (hdc, 10,10,90,90,0,0,0,0);
		break;
	case 1:
		Arc (hdc, 110,10,190,90 ,0,0,0,0);
		break;
	case 2:
		Arc (hdc, 210,10,290,90,0,0,0,0);
		break;
	case 3:
		Arc (hdc, 10,110,90,190,0,0,0,0);
		break;
	case 4:
		Arc (hdc, 110,110,190,190,0,0,0,0);
		break;
	case 5:
		Arc (hdc, 210,110,290,190,0,0,0,0);
		break;
	case 6:
		Arc (hdc, 10,210,90,290,0,0,0,0);
		break;
	case 7:
		Arc (hdc, 110,210,190,290,0,0,0,0);
		break;
	case 8:
		Arc (hdc, 210,210,290,290,0,0,0,0);
		break;
	}

}


void checkWin () {
	if ((iDraw [0] == 'X' && iDraw [1] == 'X' && iDraw [2] == 'X') || 
		(iDraw [3] == 'X' && iDraw [4] == 'X' && iDraw [5] == 'X') ||
		(iDraw [6] == 'X' && iDraw [7] == 'X' && iDraw [8] == 'X') ||

		(iDraw [0] == 'X' && iDraw [3] == 'X' && iDraw [6] == 'X') ||
		(iDraw [1] == 'X' && iDraw [4] == 'X' && iDraw [7] == 'X') ||
		(iDraw [2] == 'X' && iDraw [5] == 'X' && iDraw [8] == 'X') ||

		(iDraw [0] == 'X' && iDraw [4] == 'X' && iDraw [8] == 'X') ||
		(iDraw [2] == 'X' && iDraw [4] == 'X' && iDraw [6] == 'X')
		) {
			Win = true;
	}
	if ((iDraw [0] == 'O' && iDraw [1] == 'O' && iDraw [2] == 'O') || 
		(iDraw [3] == 'O' && iDraw [4] == 'O' && iDraw [5] == 'O') ||
		(iDraw [6] == 'O' && iDraw [7] == 'O' && iDraw [8] == 'O') ||

		(iDraw [0] == 'O' && iDraw [3] == 'O' && iDraw [6] == 'O') ||
		(iDraw [1] == 'O' && iDraw [4] == 'O' && iDraw [7] == 'O') ||
		(iDraw [2] == 'O' && iDraw [5] == 'O' && iDraw [8] == 'O') ||

		(iDraw [0] == 'O' && iDraw [4] == 'O' && iDraw [8] == 'O') ||
		(iDraw [2] == 'O' && iDraw [4] == 'O' && iDraw [6] == 'O')
		) {
			Win = true;
	}
}

void checkDraw () {

	if ((iDraw[0]) && 
		(iDraw[1]) &&
		(iDraw[2]) &&
		(iDraw[3]) &&
		(iDraw[4]) &&
		(iDraw[5]) &&
		(iDraw[6]) &&
		(iDraw[7]) &&
		(iDraw[8])
		) {

		Draw = true;
	}
}

void reset () {

	user = 'X';
	Win = false;
	Draw = false;

}