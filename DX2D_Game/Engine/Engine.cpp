#include <d3d11.h>

namespace Rendering { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }
namespace Input     { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }
namespace Sound     { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }
namespace Time      { void Procedure(HWND const, UINT const, WPARAM const, LPARAM const); }

namespace Engine
{
	LRESULT CALLBACK Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParam, LPARAM const lParam)
	{
		switch (uMessage)
		{
		case WM_APP :
		{
			Input::Procedure(hWindow, uMessage, wParam, lParam);
			Rendering::Procedure(hWindow, uMessage, wParam, lParam);
			Time::Procedure(hWindow, uMessage, wParam, lParam);

			return 0;
		}
		case WM_MOUSEWHEEL : case WM_MOUSEHWHEEL: case WM_MOUSEMOVE:
		case WM_SYSKEYDOWN : case WM_LBUTTONDOWN: case WM_LBUTTONUP:
		case WM_SYSKEYUP   : case WM_RBUTTONDOWN: case WM_RBUTTONUP:
		case WM_KEYUP      : case WM_MBUTTONDOWN: case WM_MBUTTONUP:
		case WM_KEYDOWN    : case WM_XBUTTONDOWN: case WM_XBUTTONUP:
		{
			Input::Procedure(hWindow, uMessage, wParam, lParam);

			return 0;
		}
		case WM_SIZE :
		{
			Rendering::Procedure(hWindow, uMessage, wParam, lParam);

			return 0;
		}
		case WM_CREATE:
		{
			Rendering::Procedure(hWindow, uMessage, wParam, lParam);
			Sound::Procedure(hWindow, uMessage, wParam, lParam);

			return 0;
		}
		case WM_DESTROY :
		{
			Rendering::Procedure(hWindow, uMessage, wParam, lParam);
			Sound::Procedure(hWindow, uMessage, wParam, lParam);

			PostQuitMessage(0);

			return 0;
		}
		default : 
			return DefWindowProc(hWindow, uMessage, wParam, lParam);
		}
	}
}