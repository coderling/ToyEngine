#include "Windows.hpp"
#include <CStringTool.hpp>

using namespace Toy::Platform;

int Windows::Initialize()
{
    int ret = CreateAppWindow();
    if (ret != 0)
        {
            Quit();
            return ret;
        }

    return 0;
}

void Windows::Quit() { is_quit = true; }

int Windows::CreateAppWindow()
{
    HINSTANCE instance = GetModuleHandle(NULL);

    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = instance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    const auto& w_name = Str2Wstr(args.app_name);
    wc.lpszClassName = w_name.c_str();

    if (!RegisterClassEx(&wc))
        {
            return -1;
        }

    int add_height = GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER);

    int add_width = GetSystemMetrics(SM_CXFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER);

    hwnd = CreateWindowEx(0, wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,  // window position x
                          CW_USEDEFAULT,  // window position y
                          args.screen_width + add_width, args.screen_height + add_height, NULL, NULL, instance, this);

    DWORD error = GetLastError();
    if (error != 0)
        {
            LPWSTR error_message = NULL;
            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error,
                          MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), error_message, 0, NULL);

            MessageBox(NULL, error_message, L"提示", MB_OK);
            return -1;
        }
    hdc = GetDC(hwnd);
    ShowWindow(hwnd, SW_SHOW);
    return 0;
}

void Windows::Finalize() { ReleaseDC(hwnd, hdc); }

void Windows::Tick()
{
    MSG msg;

    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // translate msg right format
            TranslateMessage(&msg);

            // send msg to windproc
            DispatchMessage(&msg);
        }
}

void* Windows::GetHwnd() const noexcept { return hwnd; }

const AppArgs& Windows::GetArgs() const noexcept { return args; }

LRESULT CALLBACK Windows::WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    LRESULT result = 0;
    Windows* p_this;

    if (message == WM_NCCREATE)
        {
            p_this = static_cast<Windows*>(reinterpret_cast<CREATESTRUCT*>(lparam)->lpCreateParams);
            SetLastError(0);
            // 创建窗口的时候保存，WinApp类实例指针，以便后面获取
            if (!SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(p_this)))
                {
                    if (GetLastError() != 0) return FALSE;
                }
        }
    else
        {
            p_this = reinterpret_cast<Windows*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

    LRESULT ret = 0;
    switch (message)
        {
                case WM_CHAR: {
                    // 0-127 asci 字符输入
                }
                break;
                case WM_KEYUP: {
                    // any keyup
                }
                break;
                case WM_KEYDOWN: {
                    // any keydown
                }
                break;
                case WM_LBUTTONDOWN: {
                    // mouse left button down
                }
                break;
                case WM_LBUTTONUP: {
                    // mouse left button up
                }
                break;
                case WM_RBUTTONDOWN: {
                    // mouse right button down
                }
                break;
                case WM_RBUTTONUP: {
                    // mouse right button up
                }
                break;
                case WM_MOUSEMOVE: {
                    // mouse on move
                }
                break;
                case WM_DESTROY: {
                    PostQuitMessage(0);
                    p_this->Quit();
                }
                break;
            default:
                // default handle
                ret = DefWindowProc(hwnd, message, wparam, lparam);
                break;
        }

    return ret;
}