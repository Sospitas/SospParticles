#include <Windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib");
#pragma comment (lib, "d3dx9.lib");

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Global Declarations
LPDIRECT3D9 d3d; // Pointer to d3d interface
LPDIRECT3DDEVICE9 d3ddev; // Pointer to device class
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;

void initD3D(HWND hWnd);
void render_frame(void);
void cleanD3D(void);
void init_graphics(void);

// WindowProc Function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

struct CUSTOMVERTEX
{
	FLOAT x, y, z; // from D3DFVF_XYZRHW
	DWORD color; // from D3DFVF_DIFFUSE
};
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

void initD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	init_graphics();

	d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);
}

void render_frame(void)
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();
	d3ddev->SetFVF(CUSTOMFVF);

		D3DXMATRIX matView;
		D3DXMatrixLookAtLH(&matView,
			&D3DXVECTOR3(0.0f, 0.0f, 10.0f),
			&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		d3ddev->SetTransform(D3DTS_VIEW, &matView);

		D3DXMATRIX matProjection;

		D3DXMatrixPerspectiveFovLH(&matProjection,
			D3DXToRadian(45),
			(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT,
			1.0f,
			100.0f);

		d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);

		d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

		D3DXMATRIX matTranslateA;
		D3DXMATRIX matTranslateB;
		D3DXMATRIX matRotateY;
		static float index = 0.0f; index += 0.1f;

		D3DXMatrixTranslation(&matTranslateA, 0.0f, 0.0f, 2.0f);
		D3DXMatrixTranslation(&matTranslateB, 0.0f, 0.0f, -2.0f);
		D3DXMatrixRotationY(&matRotateY, index);

		d3ddev->SetTransform(D3DTS_WORLD, &(matTranslateA * matRotateY));
		d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

		d3ddev->SetTransform(D3DTS_WORLD, &(matTranslateB * matRotateY));
		d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	// do 3D rendering on the back buffer here
	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void cleanD3D(void)
{
	v_buffer->Release();
	d3ddev->Release();
	d3d->Release();
}

void init_graphics(void)
{
	// create four vertices using the CUSTOMVERTEX struct built earlier
	CUSTOMVERTEX vertices[] =
	{
		{ -3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ 0.0f, 3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ 3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0), },
	};

	d3ddev->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
							   0,
							   CUSTOMFVF,
							   D3DPOOL_MANAGED,
							   &v_buffer,
							   NULL);

	VOID* pVoid;

	v_buffer->Lock(0, sizeof(vertices), (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	v_buffer->Unlock();
}

// Entry point of the program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass1";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL,
		L"WindowClass1",
		L"Sosp Particle System",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	initD3D(hWnd);

	MSG msg;
	while (TRUE)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;

		// GAME CODE BELOW HERE
		render_frame();
	}

	cleanD3D();

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}