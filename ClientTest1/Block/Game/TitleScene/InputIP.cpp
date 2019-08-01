// プリコンパイルヘッダ ---------------
#include "../../pch.h"
// ------------------------------------
#include "InputIP.h"

using namespace std;
using namespace System;
using namespace DirectX;

InputIp::InputIp()
{
}

string InputIp::Input(string _ip)
{

	Keyboard::Keys key;

	key = InputManager::GetInstance().GetPressedKeys();

	switch (key)
	{
	case Keyboard::Keys::D1:		 _ip += "1";  break;
	case Keyboard::Keys::D2:		 _ip += "2";  break;
	case Keyboard::Keys::D3:		 _ip += "3";  break;
	case Keyboard::Keys::D4:		 _ip += "4";  break;
	case Keyboard::Keys::D5:		 _ip += "5";  break;
	case Keyboard::Keys::D6:		 _ip += "6";  break;
	case Keyboard::Keys::D7:		 _ip += "7";  break;
	case Keyboard::Keys::D8:		 _ip += "8";  break;
	case Keyboard::Keys::D9:		 _ip += "9";  break;
	case Keyboard::Keys::D0:		 _ip += "0";  break;
	case Keyboard::Keys::OemPeriod:	 _ip += ".";  break;
	case Keyboard::Keys::OemComma:	 _ip += ",";  break;
	case Keyboard::Keys::A:			 _ip += "A";  break;
	case Keyboard::Keys::B:			 _ip += "B";  break;
	case Keyboard::Keys::C:			 _ip += "C";  break;
	case Keyboard::Keys::D:			 _ip += "D";  break;
	case Keyboard::Keys::E:			 _ip += "E";  break;
	case Keyboard::Keys::F:			 _ip += "F";  break;
	case Keyboard::Keys::G:			 _ip += "G";  break;
	case Keyboard::Keys::H:			 _ip += "H";  break;
	case Keyboard::Keys::I:			 _ip += "I";  break;
	case Keyboard::Keys::J:			 _ip += "J";  break;
	case Keyboard::Keys::K:			 _ip += "K";  break;
	case Keyboard::Keys::L:			 _ip += "L";  break;
	case Keyboard::Keys::M:			 _ip += "M";  break;
	case Keyboard::Keys::N:			 _ip += "N";  break;
	case Keyboard::Keys::O:			 _ip += "O";  break;
	case Keyboard::Keys::P:			 _ip += "P";  break;
	case Keyboard::Keys::Q:			 _ip += "Q";  break;
	case Keyboard::Keys::R:			 _ip += "R";  break;
	case Keyboard::Keys::S:			 _ip += "S";  break;
	case Keyboard::Keys::T:			 _ip += "T";  break;
	case Keyboard::Keys::U:			 _ip += "U";  break;
	case Keyboard::Keys::V:			 _ip += "V";  break;
	case Keyboard::Keys::W:			 _ip += "W";  break;
	case Keyboard::Keys::X:			 _ip += "X";  break;
	case Keyboard::Keys::Y:			 _ip += "Y";  break;
	case Keyboard::Keys::Z:			 _ip += "Z";  break;
	case Keyboard::Keys::Delete:	 _ip  = "" ;  break;
	case Keyboard::Keys::Back:		 _ip  = "" ;  break;


	default:
		break;
	}

	return _ip;
}

char InputIp::Input()
{

	Keyboard::Keys keys = InputManager::GetInstance().GetPressedKeys();
	switch (keys)
	{
	case Keyboard::Keys::OemComma:	return ',';  break;	// 44
	case Keyboard::Keys::OemPeriod:	return '.';  break;	// 46
	case Keyboard::Keys::D0:		return '0';  break;	// 48
	case Keyboard::Keys::D1:		return '1';  break;	// 49
	case Keyboard::Keys::D2:		return '2';  break;	// 50
	case Keyboard::Keys::D3:		return '3';  break;	// 51
	case Keyboard::Keys::D4:		return '4';  break;	// 52
	case Keyboard::Keys::D5:		return '5';  break;	// 53
	case Keyboard::Keys::D6:		return '6';  break;	// 54
	case Keyboard::Keys::D7:		return '7';  break;	// 55
	case Keyboard::Keys::D8:		return '8';  break;	// 56
	case Keyboard::Keys::D9:		return '9';  break;	// 57

	case Keyboard::Keys::A:			return 'A';  break;	// 65
	case Keyboard::Keys::B:			return 'B';  break;	// 66
	case Keyboard::Keys::C:			return 'C';  break;	// 67
	case Keyboard::Keys::D:			return 'D';  break;	// 68
	case Keyboard::Keys::E:			return 'E';  break;	// 69
	case Keyboard::Keys::F:			return 'F';  break;	// 70
	case Keyboard::Keys::G:			return 'G';  break;	// 71
	case Keyboard::Keys::H:			return 'H';  break;	// 72
	case Keyboard::Keys::I:			return 'I';  break;	// 73
	case Keyboard::Keys::J:			return 'J';  break;	// 74
	case Keyboard::Keys::K:			return 'K';  break;	// 75
	case Keyboard::Keys::L:			return 'L';  break;	// 76
	case Keyboard::Keys::M:			return 'M';  break;	// 77
	case Keyboard::Keys::N:			return 'N';  break;	// 78
	case Keyboard::Keys::O:			return 'O';  break;	// 79
	case Keyboard::Keys::P:			return 'P';  break;	// 80
	case Keyboard::Keys::Q:			return 'Q';  break;	// 81
	case Keyboard::Keys::R:			return 'R';  break;	// 82
	case Keyboard::Keys::S:			return 'S';  break;	// 83
	case Keyboard::Keys::T:			return 'T';  break;	// 84
	case Keyboard::Keys::U:			return 'U';  break;	// 85
	case Keyboard::Keys::V:			return 'V';  break;	// 86
	case Keyboard::Keys::W:			return 'W';  break;	// 87
	case Keyboard::Keys::X:			return 'X';  break;	// 88
	case Keyboard::Keys::Y:			return 'Y';  break;	// 89
	case Keyboard::Keys::Z:			return 'Z';  break;	// 90
	case Keyboard::Keys::Delete:	return 'd';  break;	// 
	case Keyboard::Keys::Back:		return 'b';  break;	// 
	case Keyboard::Keys::Enter:		return NULL; break; //
	default:						return NULL; break;	// NULL 
	}
}
