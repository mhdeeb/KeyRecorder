#include<Windows.h>
#include <chrono>
#include<cmath>
#include<iostream>
#include <thread>
#include <future>
#include<string>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#define ABSX 65535 / GetSystemMetrics(SM_CXSCREEN);
#define ABSY 65535 / GetSystemMetrics(SM_CYSCREEN);
using namespace std;
using namespace std::chrono;
extern string guitext, consoleText;
extern bool MOUSE_ABSOLUTE;
extern bool KEY_REPEAT_ON_HOLD;
extern bool  CONSTANT_TIME;
extern bool  EVENT_BASED_UPDATE;
extern bool  VSYNC;
extern bool REPEAT;
extern int  CONSTANT_TIME_MSDELAY;
extern int  RECORD;
extern int  PLAY;
extern int  EXIT;
extern int  STOP;
extern int  UPDATE_INTERVAL;