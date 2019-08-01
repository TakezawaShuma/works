#pragma once
#include "../InputManager.h"

#ifndef KEYCODE
#define KEYCODE

#define DIK_ESCAPE	Escape			// Escape
#define DIK_F1		F1 				// F1 
#define DIK_F2		F2 				// F2 
#define DIK_F3		F3 				// F3 
#define DIK_F4		F4 				// F4 
#define DIK_F5		F5 				// F5 
#define DIK_F6		F6 				// F6 
#define DIK_F7		F7 				// F7 
#define DIK_F8		F8 				// F8 
#define DIK_F9		F9 				// F9 
#define DIK_F10		F10				// F10

#define DIK_1		D1				// 1
#define DIK_2		D2				// 2
#define DIK_3		D3				// 3
#define DIK_4		D4				// 4
#define DIK_5		D5				// 5
#define DIK_6		D6				// 6
#define DIK_7		D7				// 7
#define DIK_8		D8				// 8
#define DIK_9		D9				// 9
#define DIK_0		D0				// 0

#define DIK_Q		Q				// Q
#define DIK_W		W				// W
#define DIK_E		E				// E
#define DIK_R		R				// R
#define DIK_T		T				// T
#define DIK_Y		Y				// Y
#define DIK_U		U				// U
#define DIK_I		I				// I
#define DIK_O		O				// O
#define DIK_P		P				// P
#define DIK_A		A				// A
#define DIK_S		S				// S
#define DIK_D		D				// D
#define DIK_F		F				// F
#define DIK_G		G				// G
#define DIK_H		H				// H
#define DIK_J		J				// J
#define DIK_K		K				// K
#define DIK_L		L				// L
#define DIK_Z		Z				// Z
#define DIK_X		X				// X
#define DIK_C		C				// C
#define DIK_V		V				// V
#define DIK_B		B				// B
#define DIK_N		N				// N
#define DIK_M		M				// M

#define DIK_SPACE	Space			// Space
#define DIK_BACK	Back			// BackSpace
#define DIK_DELETE	Delete			// Delete
#define DIK_ENTER	Enter			// Enter

#define DIK_LContol	LeftControl		// LCtrl
#define DIK_RContol	RightControl	// RCtrl
#define DIK_LSHIFT	LeftShift		// LShift
#define DIK_RSHIFT	RightShift		// RShift
#define DIK_COMMA	OemComma		// ,
#define DIK_PERIOD	OemPeriod		// .

#define DIK_UP		Up				// Up
#define DIK_DOWN	Down			// Down
#define DIK_LEFT	Left			// Left
#define DIK_RIGHT	Right			// Right

#endif // !KEYCODE

class InputIp
{
public:
	InputIp();
	std::string Input(std::string _ip);
	char Input();
private:

};
