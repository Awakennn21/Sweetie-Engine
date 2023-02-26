//#pragma once
//#include "Sweetie.h"
//#define DELAY 300
//#define FilesCount 2750
////BY1T/00033661/5
//
//struct Point
//{
//	int x, y;
//};
//
//struct KwData
//{
//	int Number[8] = {};
//	int ControlNumber;
//};
//
//struct Color
//{
//	unsigned long int r, g, b;
//};
//
//class  Workspace : public Sweetie::Application
//{
//	std::vector<Point> PointsToClick =
//	{
//		{510, 1420},		//opera
//		{1000,390},			//przejdź do wyszukiwarki
//		{1200,440},			//Pole BY1T
//		{1300,440},			//Pole z numerem
//		{1400,440},			//pole z liczbą kontrolną
//		{1700,550},			//szukaj księgi
//		{1321,1100},			//przeglądaj księgę
//		{1000,930},			//prawy przycisk na księdze
//		{1050,930 + 550},	//zapisz jako
//		//{242,679},			//nazwa jako numer
//		{1550, 1120},			//zapisz plik
//		{70,70}				//cofnij się do początku
//	};
//
//	uint32_t Iterator = 0;
//	uint32_t Step = 1;
//	std::vector<KwData> Data;
//	POINT p;
//	HDC dng;
//	COLORREF PixelColour;
//
//private:
//	void DeduceNumber(const std::string& s, int iterator)
//	{
//		int tmp[8] = { s[5] - 48,s[6] - 48, s[7] - 48, s[8] - 48, s[9] - 48, s[10] - 48, s[11] - 48, s[12] - 48 };
//		KwData k;
//		k.Number[0] = tmp[0];
//		k.Number[1] = tmp[1];
//		k.Number[2] = tmp[2];
//		k.Number[3] = tmp[3];
//		k.Number[4] = tmp[4];
//		k.Number[5] = tmp[5];
//		k.Number[6] = tmp[6];
//		k.Number[7] = tmp[7];
//		k.ControlNumber = (int)(s[14]) - 48;
//		Data.push_back(k);
//		return;
//	}
//
//	void LoadDataFromFile()
//	{
//		std::fstream In;
//		std::string tmp;
//		In.open("Ksiegi.txt", std::ios::in);
//		for (int i = 0; i < FilesCount; i++)
//		{
//			In >> tmp;
//			DeduceNumber(tmp, i);
//		}
//	}
//
//	Color CheckForColor(int CursorX, int CursorY)
//	{
//		SetProcessDPIAware();
//		long int x, y;
//
//		x = CursorX;
//		y = CursorY;
//
//		HDC hDC = GetDC(HWND_DESKTOP);
//
//		DWORD color = GetPixel(hDC, x, y);
//
//
//		unsigned long int r = GetRValue(color);
//		unsigned long int g = GetGValue(color);
//		unsigned long int b = GetBValue(color);
//
//
//		return { r,g,b };
//	}
//public:
//	Workspace()
//	{
//		LoadDataFromFile();
//		Work();
//	}
//	void Work()
//	{
//		MoveCursorAndClick(PointsToClick[Iterator]);//opera
//		Iterator++;
//		for (int i = 0; i < FilesCount; i++)
//		{
//			switch (Step)
//			{
//			case 1:
//				GetCursorPos(&p);
//				if (p.x != 0 && p.y != 0)
//				{
//					MoveCursorAndClick(PointsToClick[Iterator]);//przejdź do wyszukiwarki
//					Iterator++;
//					Step++;
//				}
//				else
//				{
//					return;
//				}
//
//			case 2:
//				GetCursorPos(&p);
//				if (p.x != 0 && p.y != 0)
//				{
//					Sleep(5000);
//					MoveCursorAndClick(PointsToClick[Iterator]);//Pole BY1T
//					InputBY1T();
//					Iterator++;
//					Step++;
//				}
//				else
//				{
//					return;
//				}
//
//			case 3:
//				GetCursorPos(&p);
//				if (p.x != 0 && p.y != 0)
//				{
//					MoveCursorAndClick(PointsToClick[Iterator]);//Pole z numerem
//					for (int j = 0; j < 8; j++)
//					{
//						InputKey(Data[i].Number[j]);
//					}
//					Iterator++;
//					Step++;
//				}
//				else
//				{
//					return;
//				}
//
//			case 4:
//				GetCursorPos(&p);
//				if (p.x != 0 && p.y != 0)
//				{
//					MoveCursorAndClick(PointsToClick[Iterator]);//pole z liczbą kontrolną
//					InputKey(Data[i].ControlNumber);
//					Iterator++;
//					Step++;
//				}
//				else
//				{
//					return;
//				}
//
//			case 5:
//				GetCursorPos(&p);
//				if (p.x != 0 && p.y != 0)
//				{
//					MoveCursorAndClick(PointsToClick[Iterator]);//szukaj księgi
//					Iterator++;
//					Step++;
//				}
//				else
//				{
//					return;
//				}
//
//			case 6:
//				GetCursorPos(&p);
//				if (p.x != 0 && p.y != 0)
//				{
//					SetCursorPos(PointsToClick[Iterator].x, PointsToClick[Iterator].y);
//					int p = PointsToClick[Iterator].y;
//					while ((CheckForColor(PointsToClick[Iterator].x, PointsToClick[Iterator].y).r > 50) && (CheckForColor(PointsToClick[Iterator].x, PointsToClick[Iterator].y).b > 50))
//					{
//						PointsToClick[Iterator].y += 1;
//						SetCursorPos(PointsToClick[Iterator].x, PointsToClick[Iterator].y);
//					}
//					MoveCursorAndClick(PointsToClick[Iterator]);//przeglądaj księgę
//					Iterator++;
//					Step++;
//					PointsToClick[Iterator].y = p;
//				}
//				else
//				{
//					return;
//				}
//
//			case 7:
//				GetCursorPos(&p);
//				if (p.x != 0 && p.y != 0)
//				{
//					MoveCursorAndClick(PointsToClick[Iterator], false);//prawy przycisk na księdze
//					Iterator++;
//					Step++;
//				}
//				else
//				{
//					return;
//				}
//
//			case 8:
//				GetCursorPos(&p);
//				if (p.x != 0 && p.y != 0)
//				{
//					MoveCursorAndClick(PointsToClick[Iterator]);//zapisz jako
//					Iterator++;
//					Step++;
//				}
//				else
//				{
//					return;
//				}
//
//			case 9://nazwa jako numer
//				GetCursorPos(&p);
//				if (p.x != 0 && p.y != 0)
//				{
//					/*MoveCursorAndClick(PointsToClick[Iterator]);
//					MoveCursorAndClick(PointsToClick[Iterator]);*/
//					InputKey(i / 1000);
//					InputKey((i % 1000) / 100);
//					InputKey((i % 100) / 10);
//					InputKey(i % 10);
//					Step++;
//				}
//				else
//				{
//					return;
//				}
//
//			case 10://zapisz plik
//				GetCursorPos(&p);
//				if (p.x != 0 && p.y != 0)
//				{
//					MoveCursorAndClick(PointsToClick[Iterator]);
//					Iterator++;
//					Step++;
//
//				}
//				else
//				{
//					return;
//				}
//
//			case 11://cofnij się do początku
//				GetCursorPos(&p);
//				if (p.x != 0 && p.y != 0)
//				{
//					MoveCursorAndClick(PointsToClick[Iterator]);
//					Sleep(DELAY);
//					MoveCursorAndClick(PointsToClick[Iterator]);
//					Sleep(DELAY);
//					MoveCursorAndClick(PointsToClick[Iterator]);
//					Step = 1;
//					Iterator = 1;
//				}
//				else
//				{
//					return;
//				}
//
//				break;
//			default:
//				return;
//			}
//		}
//	}
//
//	void Click(int x, int y, bool LMB)
//	{
//		Sleep(DELAY);
//		if (!LMB)
//		{
//			mouse_event(LMB ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);
//			mouse_event(LMB ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);
//		}
//		mouse_event(LMB ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);
//		Sleep(30);
//		if (!LMB)
//		{
//			mouse_event(LMB ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
//			mouse_event(LMB ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
//		}
//		mouse_event(LMB ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
//		Sleep(DELAY);
//	}
//
//	void MoveCursorAndClick(Point p, bool LMB = true)
//	{
//		Sleep(DELAY);
//		SetCursorPos(p.x, p.y);
//		Sleep(DELAY);
//		Click(p.x, p.y, LMB);
//	}
//
//	void InputKey(int number)
//	{
//		INPUT ip;
//		ip.type = INPUT_KEYBOARD;
//		ip.ki.wScan = 0; // hardware scan code for key
//		ip.ki.time = 0;
//		ip.ki.dwExtraInfo = 0;
//
//		// Press the "A" key
//		ip.ki.wVk = 0x30 + number; // virtual-key code for the "a" key
//		ip.ki.dwFlags = 0; // 0 for key press
//		SendInput(1, &ip, sizeof(INPUT));
//	}
//
//	void InputBY1T()
//	{
//		{
//			INPUT ip;
//			ip.type = INPUT_KEYBOARD;
//			ip.ki.wScan = 0; // hardware scan code for key
//			ip.ki.time = 0;
//			ip.ki.dwExtraInfo = 0;
//
//			// Press the "A" key
//			ip.ki.wVk = 0x42; // virtual-key code for the "a" key
//			ip.ki.dwFlags = 0; // 0 for key press
//			SendInput(1, &ip, sizeof(INPUT));
//		}
//
//
//		{
//			INPUT ip;
//			ip.type = INPUT_KEYBOARD;
//			ip.ki.wScan = 0; // hardware scan code for key
//			ip.ki.time = 0;
//			ip.ki.dwExtraInfo = 0;
//
//			// Press the "A" key
//			ip.ki.wVk = 0x59; // virtual-key code for the "a" key
//			ip.ki.dwFlags = 0; // 0 for key press
//			SendInput(1, &ip, sizeof(INPUT));
//		}
//
//		InputKey(1);
//
//		INPUT ip;
//		ip.type = INPUT_KEYBOARD;
//		ip.ki.wScan = 0; // hardware scan code for key
//		ip.ki.time = 0;
//		ip.ki.dwExtraInfo = 0;
//
//		// Press the "A" key
//		ip.ki.wVk = 0x54; // virtual-key code for the "a" key
//		ip.ki.dwFlags = 0; // 0 for key press
//		SendInput(1, &ip, sizeof(INPUT));
//	}
//
//};
//
//Sweetie::Application* Sweetie::CreateApplication()
//{
//	return new Workspace;
//}