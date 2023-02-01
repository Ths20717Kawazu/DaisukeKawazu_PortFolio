#pragma once
#include "main.h"
#include "input.h"
#include "Component.h"
#include "MoveComponent.h"

//↓余計なInclude
//#include "Actor.h"
//#include "Player.h"



class InputComponent :
    public MoveComponent

{
    public:
    InputComponent(class Actor* Owner);
    ~InputComponent();
	void ProcessInput(void) override;

	////	//*****************************************************************************
	////	// マクロ定義
	////	//*****************************************************************************
	//	#define	NUM_KEY_MAX			(256)
	//	// game pad用設定値
	//	#define DEADZONE		2500			// 各軸の25%を無効ゾーンとする
	//	#define RANGE_MAX		1000			// 有効範囲の最大値
	//	#define RANGE_MIN		-1000			// 有効範囲の最小値


	//	//*****************************************************************************
	//	// プロトタイプ宣言
	//	//*****************************************************************************
	//	// 
	//	//---------------------------- keyboard
		//HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
		//void UninitKeyboard(void);
		//HRESULT UpdateKeyboard(void);

		//---------------------------- game pad
		//HRESULT InitializePad(void);			// パッド初期化
		////BOOL CALLBACK SearchPadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// パッド検査コールバック
		//void UpdatePad(void);
		//void UninitPad(void);

		//BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);

	//	//*****************************************************************************
	//	// マクロ定義
	//	//*****************************************************************************

	//	// プログラム分けするときに使う
	//	#define	USE_KEYBOARD				// 宣言するとキーボードで操作可能になる
	//	#define	USE_MOUSE					// 宣言するとマウスで操作可能になる
	//	#define	USE_PAD						// 宣言するとパッドで操作可能になる


	////	/* game pad情報 */
	//	#define BUTTON_UP		0x00000001l	// 方向キー上(.IY<0)
	//	#define BUTTON_DOWN		0x00000002l	// 方向キー下(.IY>0)
	//	#define BUTTON_LEFT		0x00000004l	// 方向キー左(.IX<0)
	//	#define BUTTON_RIGHT	0x00000008l	// 方向キー右(.IX>0)

		//#define BUTTON_A		0x00000010l	// Ａボタン(.rgbButtons[0]&0x80)
		//#define BUTTON_B		0x00000020l	// Ｂボタン(.rgbButtons[1]&0x80)
		//#define BUTTON_C		0x00000040l	// Ｃボタン(.rgbButtons[2]&0x80)
		//#define BUTTON_X		0x00000080l	// Ｘボタン(.rgbButtons[3]&0x80)
		//#define BUTTON_Y		0x00000100l	// Ｙボタン(.rgbButtons[4]&0x80)
		//#define BUTTON_Z		0x00000200l	// Ｚボタン(.rgbButtons[5]&0x80)
		//#define BUTTON_L		0x00000400l	// Ｌボタン(.rgbButtons[6]&0x80)
		//#define BUTTON_R		0x00000800l	// Ｒボタン(.rgbButtons[7]&0x80)
		//#define BUTTON_START	0x00001000l	// ＳＴＡＲＴボタン(.rgbButtons[8]&0x80)
		//#define BUTTON_M		0x00002000l	// Ｍボタン(.rgbButtons[9]&0x80)

		//#define BUTTON_X		0x00000010l	// Ｘボタン(.rgbButtons[0]&0x80)
		//#define BUTTON_A		0x00000020l	// Ａボタン(.rgbButtons[1]&0x80)
		//#define BUTTON_B		0x00000040l	// Ｂボタン(.rgbButtons[2]&0x80)
		//#define BUTTON_Y		0x00000080l	// Ｙボタン(.rgbButtons[3]&0x80)
		//#define BUTTON_L		0x00000100l	// Ｌボタン(.rgbButtons[4]&0x80)
		//#define BUTTON_R		0x00000200l	// Ｒボタン(.rgbButtons[5]&0x80)
		//#define BUTTON_L2		0x00000400l	// Ｌボタン(.rgbButtons[6]&0x80)
		//#define BUTTON_R2		0x00000800l	// Ｒボタン(.rgbButtons[7]&0x80)
		//#define BUTTON_SELECT	0x00001000l	// Ｚボタン(.rgbButtons[8]&0x80)
		//#define BUTTON_START	0x00002000l	// ＳＴＡＲＴボタン(.rgbButtons[9]&0x80)

		//#define GAMEPADMAX		4			// 同時に接続するジョイパッドの最大数をセット

	//	enum {	// ボタンに対するrgbButtons[?]配列の配列番号(DirectInput上でのXYABボタン位置に合わせた)
	//		rgbButtons_X,
	//		rgbButtons_A,
	//		rgbButtons_B,
	//		rgbButtons_Y,
	//		rgbButtons_L,
	//		rgbButtons_R,
	//		rgbButtons_L2,
	//		rgbButtons_R2,
	//		rgbButtons_SELECT,
	//		rgbButtons_START,
	//	};
	//	//*****************************************************************************
	//	// 入力
	//	//*****************************************************************************
	//	HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
	//	void UninitInput(void);
	//	void UpdateInput(void);

	////	//---------------------------- keyboard
	//	bool GetKeyboardPress(int nKey);
	//	bool GetKeyboardTrigger(int nKey);
	//	bool GetKeyboardRepeat(int nKey);
	//	bool GetKeyboardRelease(int nKey);

	//	//---------------------------- game pad
		//BOOL IsButtonPressed(int padNo, DWORD button);
		//BOOL IsButtonTriggered(int padNo, DWORD button);
		//D3DXVECTOR2 GetPadLeftStick(int padNo);
		//D3DXVECTOR2 GetPadRightStick(int padNo);





	////*****************************************************************************
	//// グローバル変数
	////*****************************************************************************

	////------------------------------- keyboard
		//LPDIRECTINPUT8			g_pDInput = NULL;					// IDirectInput8インターフェースへのポインタ
		//LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// IDirectInputDevice8インターフェースへのポインタ(キーボード)
		//BYTE					g_keyState[NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
		//BYTE					g_keyStateTrigger[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
		//BYTE					g_keyStateRepeat[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
		//BYTE					g_keyStateRelease[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
		//int						g_keyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

	//	//--------------------------------- game pad

	//	//static LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = { NULL,NULL,NULL,NULL };// パッドデバイス

	//	static float	padLeftStickX[GAMEPADMAX];
	//	static float	padLeftStickY[GAMEPADMAX];
	//	static float	padRightStickX[GAMEPADMAX];
	//	static float	padRightStickY[GAMEPADMAX];
	//	static DWORD	padState[GAMEPADMAX];	// パッド情報（複数対応）
	//	static DWORD	padTrigger[GAMEPADMAX];
	//	//static int		padCount = 0;			// 検出したパッドの数




	private:
};
