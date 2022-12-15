#include"Gui.h"

MSG msg;
HHOOK hHook = NULL, hHookm = NULL;
bool keystate[256] = {0}, s1 = 0, s2 = 0, running = true;
Queue recorder((long) 1000000);
unsigned char state[256];
KillablePlayer *player;
int RECORD = 78;
int PLAY = 74;
int EXIT = 53;
int STOP = 55;

bool handle_keyboard(WPARAM &wParam, LPARAM &lParam, KBDLLHOOKSTRUCT &ckey, bool *s1, string *guitext, bool *keystate,
                     Queue *recorder) {
    bool result = 0;
    if (wParam == 256) {
        if (KEY_REPEAT_ON_HOLD || !keystate[ckey.vkCode]) {
            keystate[ckey.vkCode] = 1;
            if (*s1 && ckey.scanCode != RECORD)recorder->add(lParam, 1);
            *guitext += to_string(ckey.scanCode) + ' ' + "Pressed!\n";
        }
        if (ckey.scanCode == PLAY || ckey.scanCode == RECORD || ckey.scanCode == STOP) result = 1;
        if (player && (ckey.scanCode == PLAY || ckey.scanCode == RECORD || ckey.scanCode == STOP))player->kill();
        if (ckey.scanCode == EXIT)running = false;
    } else if (wParam == 257) {
        keystate[ckey.vkCode] = 0;
        if (ckey.scanCode == RECORD) {
            *s1 = 1 - *s1;
            if (!*s1)recorder->calcTime();
        } else if (ckey.scanCode == PLAY) {
            if (*s1) {
                recorder->calcTime();
                *s1 = 0;
            }
            player = new KillablePlayer(recorder);
        }
        if (*s1 && ckey.scanCode != RECORD)recorder->add(lParam, 1);
        *guitext += to_string(ckey.scanCode) + ' ' + "Released!\n";
        if (ckey.scanCode == PLAY || ckey.scanCode == RECORD) result = 1;
    }
    return result;
}

LRESULT CALLBACK

keyproc(int nCode, WPARAM wParam, LPARAM lParam) {
    KBDLLHOOKSTRUCT ckey = *((KBDLLHOOKSTRUCT *) lParam);
    CallNextHookEx(hHook, nCode, wParam, lParam);
    return handle_keyboard(wParam, lParam, ckey, &s1, &guitext, keystate, &recorder);
}

LRESULT CALLBACK

butproc(int nCode, WPARAM wParam, LPARAM lParam) {
    MSLLHOOKSTRUCT cbut = *((MSLLHOOKSTRUCT *) lParam);
    if (s1) { recorder.add(lParam, 0, wParam); }
    //if (wParam == 522)consoleText += format("{}\n", (signed char)HIWORD(((MSLLHOOKSTRUCT*)lParam)->mouseData));
    return CallNextHookEx(hHook, nCode, wParam, lParam);;
}

void window_loop(GLFWwindow *window, UseImGui *myimgui) {
    static BOOL bRet;
    while (!glfwWindowShouldClose(window) && running) {
        bRet = PeekMessage(&msg, NULL, 0, 0, 0);
        if (bRet == -1) {
            cout << "Error -1\n";
        } else {
            if (s1 && !s2)recorder.~Queue();
            s2 = s1;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        //glfwPollEvents();
        if (EVENT_BASED_UPDATE) glfwWaitEvents();
        else glfwWaitEventsTimeout(UPDATE_INTERVAL / 1000.);
        glClear(GL_COLOR_BUFFER_BIT);
        myimgui->NewFrame();
        myimgui->Update();
        myimgui->Render();
        glfwSwapBuffers(window);
    }
};