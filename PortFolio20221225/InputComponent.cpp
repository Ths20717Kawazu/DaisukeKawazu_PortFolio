#pragma once
#include "InputComponent.h"
#include <stdlib.h>
#include <iostream>
//#include "input.h"


//#include "MoveComponent.h"
//#include "Actor.h"
//#include "Player.h"

//bool InputComponent::GetKeyboardPress(int key) { return (g_keyState[key] & 0x80) ? true : false;  }
//bool InputComponent::GetKeyboardTrigger(int key) { return (g_keyStateTrigger[key] & 0x80) ? true : false; }
//bool InputComponent::GetKeyboardRepeat(int key) { return (g_keyStateRepeat[key] & 0x80) ? true : false; }
//bool InputComponent::GetKeyboardRelease(int key) { return (g_keyStateRelease[key] & 0x80) ? true : false; }

InputComponent::InputComponent(Actor* Owner):MoveComponent(Owner)
{

}

InputComponent::~InputComponent() {};



void InputComponent::ProcessInput(void) 
{
	
	D3DXVECTOR2 dir(0,0);
	float posx = 0;
	//float posx2 = 0;
	if (GetKeyboardPress(DIK_LEFT)) 
	{
		posx = mOwner->GetPositionX();
		posx += 10.0f;
		mOwner->SetPositionX(posx);
	}
	else 
	{
		posx = mOwner->GetPositionX();
		posx += -1.0f;
		mOwner->SetPositionX(posx);
	}



	if (GetKeyboardPress(DIK_RIGHT))
	{
		dir.x += 10.0f;
	}
	if (GetKeyboardPress(DIK_UP))
	{
		dir.y -= 10.0f;
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		dir.y += 10.0f;
	}

	////mOwnerの現在のポジション取得し入力値を追加
	//posx = mOwner->GetPositionX();
	//posx += 10.0f;
	//mOwner->SetPositionX(posx);

};




//
//	
//// キーボードの初期化
//HRESULT InputComponent::InitKeyboard(HINSTANCE hInst, HWND hWnd) 
//{
//	HRESULT hr;
//
//	// デバイスオブジェクトを作成
//	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
//	if (FAILED(hr) || g_pDIDevKeyboard == NULL)
//	{
//		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
//		return hr;
//	}
//
//
//	// データフォーマットを設定
//	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
//	if (FAILED(hr))
//	{
//		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
//		return hr;
//	}
//
//	// 協調モードを設定（フォアグラウンド＆非排他モード）
//	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
//	if (FAILED(hr))
//	{
//		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
//		return hr;
//	}
//
//	// キーボードへのアクセス権を獲得(入力制御開始)
//	g_pDIDevKeyboard->Acquire();
//
//	return S_OK;
//}
////void    InputComponent::UninitKeyboard(void) {
////	// キーボードの終了処理
////	UninitKeyboard();
////	// パッドの終了処理
////	UninitPad();
////
////	if (g_pDInput)
////	{
////		g_pDInput->Release();
////		g_pDInput = NULL;
////	}
////};
//HRESULT InputComponent::UpdateKeyboard(void) 
//{
//	HRESULT hr;
//	BYTE keyStateOld[256];
//
//	// 前回のデータを保存
//	memcpy(keyStateOld, g_keyState, NUM_KEY_MAX);
//
//	// デバイスからデータを取得
//	hr = g_pDIDevKeyboard->GetDeviceState(sizeof(g_keyState), g_keyState);
//	if (SUCCEEDED(hr))
//	{
//		for (int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
//		{
//			g_keyStateTrigger[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & g_keyState[cnt];
//			g_keyStateRelease[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & ~g_keyState[cnt];
//			g_keyStateRepeat[cnt] = g_keyStateTrigger[cnt];
//
//			if (g_keyState[cnt])
//			{
//				g_keyStateRepeatCnt[cnt]++;
//				if (g_keyStateRepeatCnt[cnt] >= 20)
//				{
//					g_keyStateRepeat[cnt] = g_keyState[cnt];
//				}
//			}
//			else
//			{
//				g_keyStateRepeatCnt[cnt] = 0;
//				g_keyStateRepeat[cnt] = 0;
//			}
//		}
//	}
//	else
//	{
//		// キーボードへのアクセス権を取得
//		g_pDIDevKeyboard->Acquire();
//	}
//
//	return S_OK;
//}


// パッドの初期化
//HRESULT InputComponent::InitializePad() {
//	HRESULT		result;
//	int			i;
//
//	padCount = 0;
//	// ジョイパッドを探す
//	g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
//	// セットしたコールバック関数が、パッドを発見した数だけ呼ばれる。
//
//	for (i = 0; i < padCount; i++) {
//		// ジョイスティック用のデータ・フォーマットを設定
//		result = pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
//		if (FAILED(result))
//			return false; // データフォーマットの設定に失敗
//
//		// モードを設定（フォアグラウンド＆非排他モード）
////		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
////		if ( FAILED(result) )
////			return false; // モードの設定に失敗
//
//		// 軸の値の範囲を設定
//		// X軸、Y軸のそれぞれについて、オブジェクトが報告可能な値の範囲をセットする。
//		// (max-min)は、最大10,000(?)。(max-min)/2が中央値になる。
//		// 差を大きくすれば、アナログ値の細かな動きを捕らえられる。(パッドの性能による)
//		DIPROPRANGE				diprg;
//		ZeroMemory(&diprg, sizeof(diprg));
//		diprg.diph.dwSize = sizeof(diprg);
//		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
//		diprg.diph.dwHow = DIPH_BYOFFSET;
//		diprg.lMin = RANGE_MIN;
//		diprg.lMax = RANGE_MAX;
//		// X軸の範囲を設定
//		diprg.diph.dwObj = DIJOFS_X;
//		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
//		// Y軸の範囲を設定
//		diprg.diph.dwObj = DIJOFS_Y;
//		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
//		// 右X軸の範囲を設定
//		diprg.diph.dwObj = DIJOFS_Z;
//		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
//		// 右Y軸の範囲を設定
//		diprg.diph.dwObj = DIJOFS_RZ;
//		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//
//		// 各軸ごとに、無効のゾーン値を設定する。
//		// 無効ゾーンとは、中央からの微少なジョイスティックの動きを無視する範囲のこと。
//		// 指定する値は、10000に対する相対値(2000なら20パーセント)。
//		DIPROPDWORD				dipdw;
//		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
//		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
//		dipdw.diph.dwHow = DIPH_BYOFFSET;
//		dipdw.dwData = DEADZONE;
//		//X軸の無効ゾーンを設定
//		dipdw.diph.dwObj = DIJOFS_X;
//		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
//		//Y軸の無効ゾーンを設定
//		dipdw.diph.dwObj = DIJOFS_Y;
//		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
//		//右X軸の無効ゾーンを設定
//		dipdw.diph.dwObj = DIJOFS_Z;
//		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
//		//右Y軸の無効ゾーンを設定
//		dipdw.diph.dwObj = DIJOFS_RZ;
//		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
//
//		//ジョイスティック入力制御開始
//		pGamePad[i]->Acquire();
//	}
//
//	return true;
//}
//void	InputComponent::UpdatePad(void){
//	HRESULT			result;
//	DIJOYSTATE2		dijs;
//	int				i;
//
//	for (i = 0; i < padCount; i++)
//	{
//		DWORD lastPadState;
//		lastPadState = padState[i];
//		padState[i] = 0x00000000l;	// 初期化
//
//		result = pGamePad[i]->Poll();	// ジョイスティックにポールをかける
//		if (FAILED(result)) {
//			result = pGamePad[i]->Acquire();
//			while (result == DIERR_INPUTLOST)
//				result = pGamePad[i]->Acquire();
//		}
//
//		result = pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// デバイス状態を読み取る
//		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
//			result = pGamePad[i]->Acquire();
//			while (result == DIERR_INPUTLOST)
//				result = pGamePad[i]->Acquire();
//		}
//
//		// ３２の各ビットに意味を持たせ、ボタン押下に応じてビットをオンにする
//		//* y-axis (forward)
//		if (dijs.lY < 0)					padState[i] |= BUTTON_UP;
//		//* y-axis (backward)
//		if (dijs.lY > 0)					padState[i] |= BUTTON_DOWN;
//		//* x-axis (left)
//		if (dijs.lX < 0)					padState[i] |= BUTTON_LEFT;
//		//* x-axis (right)
//		if (dijs.lX > 0)					padState[i] |= BUTTON_RIGHT;
//		//* Ｘボタン
//		if (dijs.rgbButtons[rgbButtons_X] & 0x80)	padState[i] |= BUTTON_X;
//		//* Ａボタン
//		if (dijs.rgbButtons[rgbButtons_A] & 0x80)	padState[i] |= BUTTON_A;
//		//* Ｂボタン
//		if (dijs.rgbButtons[rgbButtons_B] & 0x80)	padState[i] |= BUTTON_B;
//		//* Ｙボタン
//		if (dijs.rgbButtons[rgbButtons_Y] & 0x80)	padState[i] |= BUTTON_Y;
//		//* Ｌボタン
//		if (dijs.rgbButtons[rgbButtons_L] & 0x80)	padState[i] |= BUTTON_L;
//		//* Ｒボタン
//		if (dijs.rgbButtons[rgbButtons_R] & 0x80)	padState[i] |= BUTTON_R;
//		//* Ｌ2ボタン
//		if (dijs.rgbButtons[rgbButtons_L2] & 0x80)	padState[i] |= BUTTON_L2;
//		//* Ｒ2ボタン
//		if (dijs.rgbButtons[rgbButtons_R2] & 0x80)	padState[i] |= BUTTON_R2;
//		//* Selectボタン
//		if (dijs.rgbButtons[rgbButtons_SELECT] & 0x80)	padState[i] |= BUTTON_SELECT;
//		//* ＳＴＡＲＴボタン
//		if (dijs.rgbButtons[rgbButtons_START] & 0x80)	padState[i] |= BUTTON_START;
//
//		padLeftStickX[i] = (float)dijs.lX / RANGE_MAX;
//		padLeftStickY[i] = (float)dijs.lY / RANGE_MAX;
//		padRightStickX[i] = (float)dijs.lZ / RANGE_MAX;
//		padRightStickY[i] = (float)dijs.lRz / RANGE_MAX;
//
//		// Trigger設定
//		padTrigger[i] = ((lastPadState ^ padState[i])	// 前回と違っていて
//			& padState[i]);					// しかも今ONのやつ
//
//	}



//};
//void	InputComponent::UninitPad(void)
//{
//	for (int i = 0; i < GAMEPADMAX; i++) {
//		if (pGamePad[i])
//		{
//			pGamePad[i]->Unacquire();
//			pGamePad[i]->Release();
//		}
//	}
//
//};
//
//BOOL CALLBACK InputComponent::SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID)
//{
//	HRESULT result;
//
//	result = g_pDInput->CreateDevice(lpddi->guidInstance, &pGamePad[padCount++], NULL);
//	return DIENUM_CONTINUE;	// 次のデバイスを列挙
//
//}
//


//============Input===============//
//
//HRESULT InputComponent::InitInput(HINSTANCE hInst, HWND hWnd)
//	{
//		HRESULT hr;
//
//		if (!g_pDInput)
//		{
//			// DirectInputオブジェクトの作成
//			hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
//				IID_IDirectInput8, (void**)&g_pDInput, NULL);
//		}
//
//		// キーボードの初期化
//		InitKeyboard(hInst, hWnd);
//
//		// パッドの初期化
//		InitializePad();
//
//		return S_OK;
//	}
//void InputComponent::UninitInput(void) {// キーボードの終了処理
//	UninitKeyboard();
//	// パッドの終了処理
//	UninitPad();
//
//	if (g_pDInput)
//	{
//		g_pDInput->Release();
//		g_pDInput = NULL;
//	}
//};
//void InputComponent::UpdateInput(void) {
//	UpdateKeyboard();
//
//	// パッドの更新
//	UpdatePad();
//};




////---------------------------- game pad
//BOOL		InputComponent::IsButtonPressed(int padNo, DWORD button) { return (button & padState[padNo]); }
//BOOL		InputComponent::IsButtonTriggered(int padNo, DWORD button) { return (button & padTrigger[padNo]); }
//D3DXVECTOR2 InputComponent::GetPadLeftStick(int padNo) {
//	D3DXVECTOR2 stick;
//	stick.x = padLeftStickX[padNo];
//	stick.y = padLeftStickY[padNo];
//
//	return stick;
//};
//D3DXVECTOR2 InputComponent::GetPadRightStick(int padNo) {
//	D3DXVECTOR2 stick;
//	stick.x = padRightStickX[padNo];
//	stick.y = padRightStickY[padNo];
//
//	return stick;
//};

