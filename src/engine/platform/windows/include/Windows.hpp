#pragma once
#include <Windows.h>
#include <windowsx.h>

#include "Client.hpp"

using namespace Toy::Engine;

namespace Toy::Platform
{
class Windows : public IClient
{
   public:
    explicit Windows(const AppArgs& args) : hwnd(NULL), hdc(NULL), args(args), is_quit(false) {}

    int Initialize() override;
    void Tick() override;
    void* GetHwnd() const noexcept override;

    const AppArgs& GetArgs() const noexcept override;

    NODISCARD bool IsQuit() const noexcept override;

    void Quit() override;

   protected:
    int CreateAppWindow() override;
    void Finalize() override;

   private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

   protected:
    HWND hwnd;
    HDC hdc;
    AppArgs args;
    bool is_quit;
};
}  // namespace Toy::Platform