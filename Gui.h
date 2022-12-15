#include"queue.h"

class UseImGui {
public:
	GLFWwindow* window;
	void Init(GLFWwindow* window, const char* glsl_version);
	void NewFrame();
	void Update();
	void Render();
	void Shutdown();
};