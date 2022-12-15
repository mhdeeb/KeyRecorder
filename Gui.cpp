#include "Gui.h"

string guitext, consoleText;
bool MOUSE_ABSOLUTE = 1;
bool KEY_REPEAT_ON_HOLD = 1;
bool REPEAT = 1;
bool CONSTANT_TIME = 0;
bool VSYNC = 0;
bool EVENT_BASED_UPDATE = 0;
int CONSTANT_TIME_MSDELAY = 10;
int  UPDATE_INTERVAL = 1;

void UseImGui::Init(GLFWwindow* window, const char* glsl_version) {
	this->window = window;
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void UseImGui::NewFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport();
}


void UseImGui::Update() {
	ImGui::Begin("Console", NULL, 0);
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	if (consoleText.length() > 3000)consoleText = consoleText.substr(consoleText.find('\n', consoleText.length() / 2));
	if (ImGui::GetScrollMaxY() == ImGui::GetScrollY())ImGui::SetScrollY(ImGui::GetScrollMaxY() + 50);
	ImGui::Text("%s", consoleText.c_str());
	ImGui::End();
	ImGui::Begin("Options", NULL, 0);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Checkbox("MOUSE_ABSOLUTE", &MOUSE_ABSOLUTE);
	ImGui::Checkbox("KEY_REPEAT_ON_HOLD", &KEY_REPEAT_ON_HOLD);
	ImGui::Checkbox("CONSTANT_TIME", &CONSTANT_TIME);
	ImGui::Checkbox("EVENT_BASED_UPDATE", &EVENT_BASED_UPDATE);
	ImGui::Checkbox("REPEAT", &REPEAT);
	ImGui::SliderInt("CONSTANT_TIME_DELAY (ms)", &CONSTANT_TIME_MSDELAY, 0, 1000);
	if(!EVENT_BASED_UPDATE)ImGui::SliderInt("UPDATE_INTERVAL (ms)", &UPDATE_INTERVAL, 0, 100);
	if(ImGui::Button(format("RECORD: {}", RECORD).c_str()))guitext += "sad";
	if(ImGui::Button(format("STOP: {}", STOP).c_str()));
	if(ImGui::Button(format("EXIT: {}", EXIT).c_str()));
	if(ImGui::Button(format("PLAY: {}", PLAY).c_str()));
	if(ImGui::Button(format("VSYNC: {}", VSYNC).c_str()))glfwSwapInterval(VSYNC = !VSYNC);
	ImGui::End();
	ImGui::Begin("Input:", NULL, 0);
	if (guitext.length() > 3000)guitext = guitext.substr(guitext.find('\n', guitext.length() / 2));
	if (ImGui::GetScrollMaxY() == ImGui::GetScrollY())ImGui::SetScrollY(ImGui::GetScrollMaxY()+50);
	ImGui::Text("%s", guitext.c_str());
	ImGui::End();
}

void UseImGui::Render() {

	ImGui::Render();
	static int screen_width, screen_height;
	glfwGetFramebufferSize(this->window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(this->window);
	}

}

void UseImGui::Shutdown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}