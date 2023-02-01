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

	////mOwner�̌��݂̃|�W�V�����擾�����͒l��ǉ�
	//posx = mOwner->GetPositionX();
	//posx += 10.0f;
	//mOwner->SetPositionX(posx);

};




//
//	
//// �L�[�{�[�h�̏�����
//HRESULT InputComponent::InitKeyboard(HINSTANCE hInst, HWND hWnd) 
//{
//	HRESULT hr;
//
//	// �f�o�C�X�I�u�W�F�N�g���쐬
//	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
//	if (FAILED(hr) || g_pDIDevKeyboard == NULL)
//	{
//		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
//		return hr;
//	}
//
//
//	// �f�[�^�t�H�[�}�b�g��ݒ�
//	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
//	if (FAILED(hr))
//	{
//		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
//		return hr;
//	}
//
//	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
//	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
//	if (FAILED(hr))
//	{
//		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
//		return hr;
//	}
//
//	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
//	g_pDIDevKeyboard->Acquire();
//
//	return S_OK;
//}
////void    InputComponent::UninitKeyboard(void) {
////	// �L�[�{�[�h�̏I������
////	UninitKeyboard();
////	// �p�b�h�̏I������
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
//	// �O��̃f�[�^��ۑ�
//	memcpy(keyStateOld, g_keyState, NUM_KEY_MAX);
//
//	// �f�o�C�X����f�[�^���擾
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
//		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
//		g_pDIDevKeyboard->Acquire();
//	}
//
//	return S_OK;
//}


// �p�b�h�̏�����
//HRESULT InputComponent::InitializePad() {
//	HRESULT		result;
//	int			i;
//
//	padCount = 0;
//	// �W���C�p�b�h��T��
//	g_pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, (LPDIENUMDEVICESCALLBACK)SearchGamePadCallback, NULL, DIEDFL_ATTACHEDONLY);
//	// �Z�b�g�����R�[���o�b�N�֐����A�p�b�h�𔭌������������Ă΂��B
//
//	for (i = 0; i < padCount; i++) {
//		// �W���C�X�e�B�b�N�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
//		result = pGamePad[i]->SetDataFormat(&c_dfDIJoystick);
//		if (FAILED(result))
//			return false; // �f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s
//
//		// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
////		result = pGamePad[i]->SetCooperativeLevel(hWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
////		if ( FAILED(result) )
////			return false; // ���[�h�̐ݒ�Ɏ��s
//
//		// ���̒l�͈̔͂�ݒ�
//		// X���AY���̂��ꂼ��ɂ��āA�I�u�W�F�N�g���񍐉\�Ȓl�͈̔͂��Z�b�g����B
//		// (max-min)�́A�ő�10,000(?)�B(max-min)/2�������l�ɂȂ�B
//		// ����傫������΁A�A�i���O�l�ׂ̍��ȓ�����߂炦����B(�p�b�h�̐��\�ɂ��)
//		DIPROPRANGE				diprg;
//		ZeroMemory(&diprg, sizeof(diprg));
//		diprg.diph.dwSize = sizeof(diprg);
//		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
//		diprg.diph.dwHow = DIPH_BYOFFSET;
//		diprg.lMin = RANGE_MIN;
//		diprg.lMax = RANGE_MAX;
//		// X���͈̔͂�ݒ�
//		diprg.diph.dwObj = DIJOFS_X;
//		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
//		// Y���͈̔͂�ݒ�
//		diprg.diph.dwObj = DIJOFS_Y;
//		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
//		// �EX���͈̔͂�ݒ�
//		diprg.diph.dwObj = DIJOFS_Z;
//		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
//		// �EY���͈̔͂�ݒ�
//		diprg.diph.dwObj = DIJOFS_RZ;
//		pGamePad[i]->SetProperty(DIPROP_RANGE, &diprg.diph);
//
//
//		// �e�����ƂɁA�����̃]�[���l��ݒ肷��B
//		// �����]�[���Ƃ́A��������̔����ȃW���C�X�e�B�b�N�̓����𖳎�����͈͂̂��ƁB
//		// �w�肷��l�́A10000�ɑ΂��鑊�Βl(2000�Ȃ�20�p�[�Z���g)�B
//		DIPROPDWORD				dipdw;
//		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
//		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
//		dipdw.diph.dwHow = DIPH_BYOFFSET;
//		dipdw.dwData = DEADZONE;
//		//X���̖����]�[����ݒ�
//		dipdw.diph.dwObj = DIJOFS_X;
//		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
//		//Y���̖����]�[����ݒ�
//		dipdw.diph.dwObj = DIJOFS_Y;
//		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
//		//�EX���̖����]�[����ݒ�
//		dipdw.diph.dwObj = DIJOFS_Z;
//		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
//		//�EY���̖����]�[����ݒ�
//		dipdw.diph.dwObj = DIJOFS_RZ;
//		pGamePad[i]->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
//
//		//�W���C�X�e�B�b�N���͐���J�n
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
//		padState[i] = 0x00000000l;	// ������
//
//		result = pGamePad[i]->Poll();	// �W���C�X�e�B�b�N�Ƀ|�[����������
//		if (FAILED(result)) {
//			result = pGamePad[i]->Acquire();
//			while (result == DIERR_INPUTLOST)
//				result = pGamePad[i]->Acquire();
//		}
//
//		result = pGamePad[i]->GetDeviceState(sizeof(DIJOYSTATE), &dijs);	// �f�o�C�X��Ԃ�ǂݎ��
//		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
//			result = pGamePad[i]->Acquire();
//			while (result == DIERR_INPUTLOST)
//				result = pGamePad[i]->Acquire();
//		}
//
//		// �R�Q�̊e�r�b�g�ɈӖ����������A�{�^�������ɉ����ăr�b�g���I���ɂ���
//		//* y-axis (forward)
//		if (dijs.lY < 0)					padState[i] |= BUTTON_UP;
//		//* y-axis (backward)
//		if (dijs.lY > 0)					padState[i] |= BUTTON_DOWN;
//		//* x-axis (left)
//		if (dijs.lX < 0)					padState[i] |= BUTTON_LEFT;
//		//* x-axis (right)
//		if (dijs.lX > 0)					padState[i] |= BUTTON_RIGHT;
//		//* �w�{�^��
//		if (dijs.rgbButtons[rgbButtons_X] & 0x80)	padState[i] |= BUTTON_X;
//		//* �`�{�^��
//		if (dijs.rgbButtons[rgbButtons_A] & 0x80)	padState[i] |= BUTTON_A;
//		//* �a�{�^��
//		if (dijs.rgbButtons[rgbButtons_B] & 0x80)	padState[i] |= BUTTON_B;
//		//* �x�{�^��
//		if (dijs.rgbButtons[rgbButtons_Y] & 0x80)	padState[i] |= BUTTON_Y;
//		//* �k�{�^��
//		if (dijs.rgbButtons[rgbButtons_L] & 0x80)	padState[i] |= BUTTON_L;
//		//* �q�{�^��
//		if (dijs.rgbButtons[rgbButtons_R] & 0x80)	padState[i] |= BUTTON_R;
//		//* �k2�{�^��
//		if (dijs.rgbButtons[rgbButtons_L2] & 0x80)	padState[i] |= BUTTON_L2;
//		//* �q2�{�^��
//		if (dijs.rgbButtons[rgbButtons_R2] & 0x80)	padState[i] |= BUTTON_R2;
//		//* Select�{�^��
//		if (dijs.rgbButtons[rgbButtons_SELECT] & 0x80)	padState[i] |= BUTTON_SELECT;
//		//* �r�s�`�q�s�{�^��
//		if (dijs.rgbButtons[rgbButtons_START] & 0x80)	padState[i] |= BUTTON_START;
//
//		padLeftStickX[i] = (float)dijs.lX / RANGE_MAX;
//		padLeftStickY[i] = (float)dijs.lY / RANGE_MAX;
//		padRightStickX[i] = (float)dijs.lZ / RANGE_MAX;
//		padRightStickY[i] = (float)dijs.lRz / RANGE_MAX;
//
//		// Trigger�ݒ�
//		padTrigger[i] = ((lastPadState ^ padState[i])	// �O��ƈ���Ă���
//			& padState[i]);					// ��������ON�̂��
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
//	return DIENUM_CONTINUE;	// ���̃f�o�C�X���
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
//			// DirectInput�I�u�W�F�N�g�̍쐬
//			hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
//				IID_IDirectInput8, (void**)&g_pDInput, NULL);
//		}
//
//		// �L�[�{�[�h�̏�����
//		InitKeyboard(hInst, hWnd);
//
//		// �p�b�h�̏�����
//		InitializePad();
//
//		return S_OK;
//	}
//void InputComponent::UninitInput(void) {// �L�[�{�[�h�̏I������
//	UninitKeyboard();
//	// �p�b�h�̏I������
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
//	// �p�b�h�̍X�V
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

