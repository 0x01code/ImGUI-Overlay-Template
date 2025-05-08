#include "overlay/overlay.h"

int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR pCmdLine,
    int nCmdShow
)
{
    Overlay overlay;
    if (!overlay.Initialize(hInstance)) {
        return -1;
    }

    while (overlay.IsRunning()) {
        overlay.Render();
    }

    overlay.Shutdown();

    return 0;
}
