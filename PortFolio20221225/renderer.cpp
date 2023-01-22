/*==============================================================================

   �����_�����O�Ǘ� [renderer.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "renderer.h"
#include "texture.h"
//#include "sprite.h"
#include "input.h"
#include "main.h"
#include "SpriteComponent.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			"GameWindow"		// �E�C���h�E�̃N���X��
#define WINDOW_CAPTION		"NG81_PC��"			// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")


//*********************************************************
// �\����
//*********************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
static D3D_FEATURE_LEVEL       g_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

static ID3D11Device* g_D3DDevice = NULL;
static ID3D11DeviceContext* g_ImmediateContext = NULL;
static IDXGISwapChain* g_SwapChain = NULL;
static ID3D11RenderTargetView* g_RenderTargetView = NULL;
static ID3D11DepthStencilView* g_DepthStencilView = NULL;

static ID3D11VertexShader* g_VertexShader = NULL;
static ID3D11PixelShader* g_PixelShader = NULL;
static ID3D11InputLayout* g_VertexLayout = NULL;
static ID3D11Buffer* g_ConstantBuffer = NULL;
static ID3D11Buffer* g_MaterialBuffer = NULL;

static D3DXMATRIX				g_WorldMatrix;
static D3DXMATRIX				g_ViewMatrix;
static D3DXMATRIX				g_ProjectionMatrix;

static ID3D11DepthStencilState* g_DepthStateEnable;
static ID3D11DepthStencilState* g_DepthStateDisable;
static HWND						g_hWnd;

//�Q�[���p�f�[�^
static D3DXCOLOR				g_ClearColor;			// �o�b�N�o�b�t�@�̃N���A�J���[
static char* g_PixelShaderName = (char*)"PixelShaderTexture";
//static char						*g_PixelShaderName = (char*)"PixelShaderPolygon";

Game game;


#ifdef _DEBUG
int		g_CountFPS;							// FPS�J�E���^
char	g_DebugStr[2048] = WINDOW_CAPTION;	// �f�o�b�O�����\���p

#endif

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitData(void);
void UninitData(void);

HWND GetHWND(void)
{
	return g_hWnd;
}

ID3D11Device* GetDevice(void)
{
	return g_D3DDevice;
}


ID3D11DeviceContext* GetDeviceContext(void)
{
	return g_ImmediateContext;
}


void SetDepthEnable(bool Enable)
{
	if (Enable)
		g_ImmediateContext->OMSetDepthStencilState(g_DepthStateEnable, NULL);
	else
		g_ImmediateContext->OMSetDepthStencilState(g_DepthStateDisable, NULL);

}

void SetWorldViewProjection2D(void)
{
	D3DXMATRIX worldViewProjection;

	D3DXMatrixOrthoOffCenterLH(&worldViewProjection, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0.0f, 1.0f);
	D3DXMatrixTranspose(&worldViewProjection, &worldViewProjection);

	GetDeviceContext()->UpdateSubresource(g_ConstantBuffer, 0, NULL, &worldViewProjection, 0, 0);
}


void SetWorldMatrix(D3DXMATRIX* WorldMatrix)
{
	g_WorldMatrix = *WorldMatrix;

	D3DXMATRIX worldViewProjection = g_WorldMatrix * g_ViewMatrix * g_ProjectionMatrix;
	D3DXMatrixTranspose(&worldViewProjection, &worldViewProjection);

	GetDeviceContext()->UpdateSubresource(g_ConstantBuffer, 0, NULL, &worldViewProjection, 0, 0);
}

void SetViewMatrix(D3DXMATRIX* ViewMatrix)
{
	g_ViewMatrix = *ViewMatrix;

	D3DXMATRIX worldViewProjection = g_WorldMatrix * g_ViewMatrix * g_ProjectionMatrix;
	D3DXMatrixTranspose(&worldViewProjection, &worldViewProjection);

	GetDeviceContext()->UpdateSubresource(g_ConstantBuffer, 0, NULL, &worldViewProjection, 0, 0);
}

void SetProjectionMatrix(D3DXMATRIX* ProjectionMatrix)
{
	g_ProjectionMatrix = *ProjectionMatrix;

	D3DXMATRIX worldViewProjection = g_WorldMatrix * g_ViewMatrix * g_ProjectionMatrix;
	D3DXMatrixTranspose(&worldViewProjection, &worldViewProjection);

	GetDeviceContext()->UpdateSubresource(g_ConstantBuffer, 0, NULL, &worldViewProjection, 0, 0);
}



void SetMaterial(MATERIAL Material)
{

	GetDeviceContext()->UpdateSubresource(g_MaterialBuffer, 0, NULL, &Material, 0, 0);

}



//=============================================================================
// ����������
//=============================================================================
HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;

	// �f�o�C�X�A�X���b�v�`�F�[���A�R���e�L�X�g����
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = SCREEN_WIDTH;
	sd.BufferDesc.Height = SCREEN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&g_SwapChain,
		&g_D3DDevice,
		&g_FeatureLevel,
		&g_ImmediateContext);
	if (FAILED(hr))
		return hr;


	// �����_�[�^�[�Q�b�g�r���[�����A�ݒ�
	ID3D11Texture2D* pBackBuffer = NULL;
	g_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	g_D3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_RenderTargetView);
	pBackBuffer->Release();



	//�X�e���V���p�e�N�X�`���[�쐬
	ID3D11Texture2D* depthTexture = NULL;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = sd.BufferDesc.Width;
	td.Height = sd.BufferDesc.Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc = sd.SampleDesc;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	g_D3DDevice->CreateTexture2D(&td, NULL, &depthTexture);

	//�X�e���V���^�[�Q�b�g�쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = td.Format;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags = 0;
	g_D3DDevice->CreateDepthStencilView(depthTexture, &dsvd, &g_DepthStencilView);


	g_ImmediateContext->OMSetRenderTargets(1, &g_RenderTargetView, g_DepthStencilView);


	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	g_ImmediateContext->RSSetViewports(1, &vp);



	// ���X�^���C�U�X�e�[�g�ݒ�
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.DepthClipEnable = TRUE;
	rd.MultisampleEnable = FALSE;

	ID3D11RasterizerState* rs;
	g_D3DDevice->CreateRasterizerState(&rd, &rs);

	g_ImmediateContext->RSSetState(rs);




	// �u�����h�X�e�[�g�ݒ�
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11BlendState* blendState = NULL;
	g_D3DDevice->CreateBlendState(&blendDesc, &blendState);
	g_ImmediateContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);



	// �[�x�X�e���V���X�e�[�g�ݒ�
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = FALSE;

	g_D3DDevice->CreateDepthStencilState(&depthStencilDesc, &g_DepthStateEnable);//�[�x�L���X�e�[�g

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	g_D3DDevice->CreateDepthStencilState(&depthStencilDesc, &g_DepthStateDisable);//�[�x�����X�e�[�g

	g_ImmediateContext->OMSetDepthStencilState(g_DepthStateEnable, NULL);




	// �T���v���[�X�e�[�g�ݒ�
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState = NULL;
	g_D3DDevice->CreateSamplerState(&samplerDesc, &samplerState);

	g_ImmediateContext->PSSetSamplers(0, 1, &samplerState);



	// ���_�V�F�[�_�R���p�C���E����
	ID3DBlob* pErrorBlob;
	ID3DBlob* pVSBlob = NULL;
	hr = D3DX11CompileFromFile("shader.hlsl", NULL, NULL, "VertexShaderPolygon", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, NULL, &pVSBlob, &pErrorBlob, NULL);
	if (FAILED(hr))
		MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "VS", MB_OK | MB_ICONERROR);
	{
	}

	g_D3DDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_VertexShader);

	// ���̓��C�A�E�g����
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	g_D3DDevice->CreateInputLayout(layout,
		numElements,
		pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),
		&g_VertexLayout);

	pVSBlob->Release();


	// �s�N�Z���V�F�[�_�R���p�C���E����
	ID3DBlob* pPSBlob = NULL;
	hr = D3DX11CompileFromFile("shader.hlsl", NULL, NULL, g_PixelShaderName, "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, NULL, &pPSBlob, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, (char*)pErrorBlob->GetBufferPointer(), "PS", MB_OK | MB_ICONERROR);
	}

	g_D3DDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_PixelShader);

	pPSBlob->Release();


	// �萔�o�b�t�@����
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_ConstantBuffer);
	g_ImmediateContext->VSSetConstantBuffers(0, 1, &g_ConstantBuffer);


	hBufferDesc.ByteWidth = sizeof(MATERIAL);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	g_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &g_MaterialBuffer);
	g_ImmediateContext->VSSetConstantBuffers(1, 1, &g_MaterialBuffer);




	// ���̓��C�A�E�g�ݒ�
	g_ImmediateContext->IASetInputLayout(g_VertexLayout);

	// �V�F�[�_�ݒ�
	g_ImmediateContext->VSSetShader(g_VertexShader, NULL, 0);
	g_ImmediateContext->PSSetShader(g_PixelShader, NULL, 0);


	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void UninitRenderer(void)
{
	//�e�N�X�`������͊e�A�N�^�[�̃f�X�g���N�^�Ŋe�X�J�������{����
	//UninitTexture();

	// �I�u�W�F�N�g���
	if (g_ConstantBuffer)		g_ConstantBuffer->Release();
	if (g_MaterialBuffer)		g_MaterialBuffer->Release();
	if (g_VertexLayout)		g_VertexLayout->Release();
	if (g_VertexShader)		g_VertexShader->Release();
	if (g_PixelShader)			g_PixelShader->Release();

	if (g_ImmediateContext)	g_ImmediateContext->ClearState();
	if (g_RenderTargetView)	g_RenderTargetView->Release();
	if (g_SwapChain)			g_SwapChain->Release();
	if (g_ImmediateContext)	g_ImmediateContext->Release();
	if (g_D3DDevice)			g_D3DDevice->Release();
}


//=============================================================================
// �o�b�N�o�b�t�@�N���A
//=============================================================================
void Clear(void)
{
	// �o�b�N�o�b�t�@�N���A
	float ClearColor[4] = { g_ClearColor.r, g_ClearColor.g, g_ClearColor.b, g_ClearColor.a };
	g_ImmediateContext->ClearRenderTargetView(g_RenderTargetView, ClearColor);
	g_ImmediateContext->ClearDepthStencilView(g_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void ClearColor(float r, float g, float b, float a)
{
	g_ClearColor.r = r;
	g_ClearColor.g = g;
	g_ClearColor.b = b;
	g_ClearColor.a = a;
}


//=============================================================================
// �v���[���g
//=============================================================================
void SwapBuffers(void)
{
	g_SwapChain->Present(0, 0);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	// ���Ԍv���p
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);

	int scr_width = 960;
	int scr_height = 540;

	// �E�B���h�E�̍쐬
	g_hWnd = CreateWindow(CLASS_NAME,
		WINDOW_CAPTION,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// �E�B���h�E�̍����W
		CW_USEDEFAULT,																		// �E�B���h�E�̏���W
		scr_width + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// �E�B���h�E����
		scr_height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
		NULL,
		NULL,
		hInstance,
		NULL);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if (FAILED(InitRenderer(hInstance, g_hWnd, true)))
	{
		return -1;
	}

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;


	//===============================//
	//�Q�[���̏���������
	//GameInitialize(&game);
	game.gameInit();


	//==============================//

	//InitData();

	//���͌n�̏�����
	InitInput(hInstance, g_hWnd);

	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	MSG			msg;
	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000.0f / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

#ifdef _DEBUG	// �f�o�b�O�ł̎�����FPS��\������
				wsprintf(g_DebugStr, WINDOW_CAPTION);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(g_hWnd, g_DebugStr);
#endif
				SetWorldViewProjection2D();

				//�Q�[�����[�v
				//GameLoop(&game);
				game.gameRunloop();
				dwFrameCount++;		// �����񐔂̃J�E���g�����Z
			}
		}
	}

	//�Q�[���I������
	GameUninitialize();

	timeEndPeriod(1);				// ����\��߂�

	// �I������
	//UninitData();
	UninitInput();
	UninitRenderer();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//void InitData(void)
//{
//	SpriteComponent::InitSprite();
//}
//
//void UninitData(void)
//{
//	SpriteComponent::UninitSprite();
//}

void SetDebugString(char* str)
{
	strcpy(g_DebugStr, str);
}
