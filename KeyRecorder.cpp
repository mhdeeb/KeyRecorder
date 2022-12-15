#include"KeyRecorder.h"


int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyproc, NULL, 0);
    hHookm = SetWindowsHookEx(WH_MOUSE_LL, butproc, NULL, 0);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow *window = glfwCreateWindow(1280, 720, "KeyRecorder", NULL, NULL); //glfwGetPrimaryMonitor()
    glfwMakeContextCurrent(window);
    gladLoadGL();
    UseImGui myimgui;
    glClearColor(167 / 255., 255 / 255., 235 / 255., 1.00f);
    myimgui.Init(window, "#version 130");
    window_loop(window, &myimgui);
    myimgui.Shutdown();
    UnhookWindowsHookEx(hHook);
    UnhookWindowsHookEx(hHookm);
}
