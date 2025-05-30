#pragma once
#include "../imgui/imgui.h"
#include "../memory/memory.h"
#include "../overlay/utils.h"
#include "../overlay/overlay.h"
#include "../vector.h"
#include "setting.h"

class Menu
{
public:
	Menu();
	~Menu();

	bool show_menu = false;

	void RenderMenu();
	void RenderHack();

	void DrawVerticalBar(float x, float y, float width, float height, int value, int max_value, ImU32 valueColor = IM_COL32(0, 255, 0, 255));
	float GetDistance3D(Vector3 src, Vector3 dst);
	Vector2 CalcAngle(Vector3 src, Vector3 dst);
private:
	int current_tab = 0;

	// Options 1
	bool esp_2dbox = true;
	bool esp_health_bar = true;

	// Options 2
	bool aimbot = true;
	float fov = 90.0f;


	// Options 3
	bool imgui_demo = false;
	bool debug = false;
};