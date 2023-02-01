#pragma once
#include "main.h"
#include "input.h"
#include "Component.h"
#include "MoveComponent.h"

//���]�v��Include
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
	////	// �}�N����`
	////	//*****************************************************************************
	//	#define	NUM_KEY_MAX			(256)
	//	// game pad�p�ݒ�l
	//	#define DEADZONE		2500			// �e����25%�𖳌��]�[���Ƃ���
	//	#define RANGE_MAX		1000			// �L���͈͂̍ő�l
	//	#define RANGE_MIN		-1000			// �L���͈͂̍ŏ��l


	//	//*****************************************************************************
	//	// �v���g�^�C�v�錾
	//	//*****************************************************************************
	//	// 
	//	//---------------------------- keyboard
		//HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
		//void UninitKeyboard(void);
		//HRESULT UpdateKeyboard(void);

		//---------------------------- game pad
		//HRESULT InitializePad(void);			// �p�b�h������
		////BOOL CALLBACK SearchPadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// �p�b�h�����R�[���o�b�N
		//void UpdatePad(void);
		//void UninitPad(void);

		//BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);

	//	//*****************************************************************************
	//	// �}�N����`
	//	//*****************************************************************************

	//	// �v���O������������Ƃ��Ɏg��
	//	#define	USE_KEYBOARD				// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
	//	#define	USE_MOUSE					// �錾����ƃ}�E�X�ő���\�ɂȂ�
	//	#define	USE_PAD						// �錾����ƃp�b�h�ő���\�ɂȂ�


	////	/* game pad��� */
	//	#define BUTTON_UP		0x00000001l	// �����L�[��(.IY<0)
	//	#define BUTTON_DOWN		0x00000002l	// �����L�[��(.IY>0)
	//	#define BUTTON_LEFT		0x00000004l	// �����L�[��(.IX<0)
	//	#define BUTTON_RIGHT	0x00000008l	// �����L�[�E(.IX>0)

		//#define BUTTON_A		0x00000010l	// �`�{�^��(.rgbButtons[0]&0x80)
		//#define BUTTON_B		0x00000020l	// �a�{�^��(.rgbButtons[1]&0x80)
		//#define BUTTON_C		0x00000040l	// �b�{�^��(.rgbButtons[2]&0x80)
		//#define BUTTON_X		0x00000080l	// �w�{�^��(.rgbButtons[3]&0x80)
		//#define BUTTON_Y		0x00000100l	// �x�{�^��(.rgbButtons[4]&0x80)
		//#define BUTTON_Z		0x00000200l	// �y�{�^��(.rgbButtons[5]&0x80)
		//#define BUTTON_L		0x00000400l	// �k�{�^��(.rgbButtons[6]&0x80)
		//#define BUTTON_R		0x00000800l	// �q�{�^��(.rgbButtons[7]&0x80)
		//#define BUTTON_START	0x00001000l	// �r�s�`�q�s�{�^��(.rgbButtons[8]&0x80)
		//#define BUTTON_M		0x00002000l	// �l�{�^��(.rgbButtons[9]&0x80)

		//#define BUTTON_X		0x00000010l	// �w�{�^��(.rgbButtons[0]&0x80)
		//#define BUTTON_A		0x00000020l	// �`�{�^��(.rgbButtons[1]&0x80)
		//#define BUTTON_B		0x00000040l	// �a�{�^��(.rgbButtons[2]&0x80)
		//#define BUTTON_Y		0x00000080l	// �x�{�^��(.rgbButtons[3]&0x80)
		//#define BUTTON_L		0x00000100l	// �k�{�^��(.rgbButtons[4]&0x80)
		//#define BUTTON_R		0x00000200l	// �q�{�^��(.rgbButtons[5]&0x80)
		//#define BUTTON_L2		0x00000400l	// �k�{�^��(.rgbButtons[6]&0x80)
		//#define BUTTON_R2		0x00000800l	// �q�{�^��(.rgbButtons[7]&0x80)
		//#define BUTTON_SELECT	0x00001000l	// �y�{�^��(.rgbButtons[8]&0x80)
		//#define BUTTON_START	0x00002000l	// �r�s�`�q�s�{�^��(.rgbButtons[9]&0x80)

		//#define GAMEPADMAX		4			// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g

	//	enum {	// �{�^���ɑ΂���rgbButtons[?]�z��̔z��ԍ�(DirectInput��ł�XYAB�{�^���ʒu�ɍ��킹��)
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
	//	// ����
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
	//// �O���[�o���ϐ�
	////*****************************************************************************

	////------------------------------- keyboard
		//LPDIRECTINPUT8			g_pDInput = NULL;					// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
		//LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
		//BYTE					g_keyState[NUM_KEY_MAX];			// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		//BYTE					g_keyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		//BYTE					g_keyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		//BYTE					g_keyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
		//int						g_keyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

	//	//--------------------------------- game pad

	//	//static LPDIRECTINPUTDEVICE8	pGamePad[GAMEPADMAX] = { NULL,NULL,NULL,NULL };// �p�b�h�f�o�C�X

	//	static float	padLeftStickX[GAMEPADMAX];
	//	static float	padLeftStickY[GAMEPADMAX];
	//	static float	padRightStickX[GAMEPADMAX];
	//	static float	padRightStickY[GAMEPADMAX];
	//	static DWORD	padState[GAMEPADMAX];	// �p�b�h���i�����Ή��j
	//	static DWORD	padTrigger[GAMEPADMAX];
	//	//static int		padCount = 0;			// ���o�����p�b�h�̐�




	private:
};
