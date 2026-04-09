#include <windows.h>
#include <stdbool.h>

bool holding = false;

void send_left_down() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}

void send_left_up() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

int main() {
    // Register F6 as a global hotkey
    RegisterHotKey(NULL, 1, 0, VK_F7);
    RegisterHotKey(NULL, 2, 0, VK_F8);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {

            if (msg.wParam == 1) { // toggle
                holding = !holding;

                if (holding) {
                    send_left_down();
                } else {
                    send_left_up();
                }
            }

            else if (msg.wParam == 2) { // exit
                send_left_up();       // always release
                PostQuitMessage(0);
            }
        }
    }

    return 0;
}
