#include "menu.h"
#include "../offsets.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::RenderMenu()
{
	if (imgui_demo)
	{
		ImGui::ShowDemoWindow(&imgui_demo);
	}

	ImGui::Begin("Menu", &show_menu);

	ImGui::BeginChild("LeftMenu", ImVec2(150, 0), true);
	{
		if (ImGui::Selectable("ESP", current_tab == 0)) current_tab = 0;
		if (ImGui::Selectable("Aimbot", current_tab == 1)) current_tab = 1;
		if (ImGui::Selectable("Misc", current_tab == 2)) current_tab = 2;
	}
	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("ContentArea", ImVec2(0, 0), true);
	{
		if (current_tab == 0)
		{
			ImGui::Text("ESP Menu");
			ImGui::Checkbox("2D Box", &esp_2dbox);
			ImGui::Checkbox("Health Bar", &esp_health_bar);
		}
		else if (current_tab == 1)
		{
			ImGui::Text("Aimbot Menu");
		}
		else if (current_tab == 2)
		{
			ImGui::Text("Misc Menu");
			ImGui::Checkbox("ImGui Demo", &imgui_demo);
			ImGui::Checkbox("Debug", &debug);
		}
	}
	ImGui::EndChild();

	ImGui::End();
}

void Menu::RenderHack()
{
	Memory mem = Memory(ProcessName);

	float view_matrix[16];
	ReadProcessMemory(mem.hProcess, (BYTE*)mem.moduleBaseAddress[L"engine.dll"] + Offset::ViewMatrix, &view_matrix, sizeof(view_matrix), nullptr);


	uintptr_t entity_list = mem.moduleBaseAddress[L"server.dll"] + Offset::EntityList;
	uintptr_t local_player = mem.Read<uintptr_t>(entity_list);
	int num_of_player = 32;

	for (unsigned int i = 1; i < num_of_player; i++)
	{
		uintptr_t player = mem.Read<uintptr_t>(entity_list + Offset::EntityListNext * i);

		if (player == 0)
		{
			continue;
		}

		int health = mem.Read<int>(player + Offset::Health);
		int health_max = mem.Read<int>(player + Offset::HealthMax);

		if (health <= 1)
		{
			continue;
		}

		Vector3 pos_head = {
			mem.Read<float>(player + Offset::PositionHeadX),
			mem.Read<float>(player + Offset::PositionHeadY),
			mem.Read<float>(player + Offset::PositionHeadZ) + 30
		};

		Vector3 pos_bottom = {
			mem.Read<float>(player + Offset::PositionBottomX),
			mem.Read<float>(player + Offset::PositionBottomY),
			mem.Read<float>(player + Offset::PositionBottomZ)
		};

		Vector2 top;
		Vector2 bottom;

		if (WorldToScreen(pos_head, top, view_matrix, Overlay::screen.width, Overlay::screen.height) && WorldToScreen(pos_bottom, bottom, view_matrix, Overlay::screen.width, Overlay::screen.height))
		{
			const float h = bottom.y - top.y;
			const float w = h * 0.25f;
			const float barWidth = w * 0.3f;

			if (esp_2dbox)
			{
				ImGui::GetBackgroundDrawList()->AddRect({ top.x - w, top.y }, { bottom.x + w, bottom.y }, ImColor(255.0f, 0.0f, 0.0f), 0, 0, 2);
			}

			if (esp_health_bar)
			{
				DrawVerticalBar(top.x + w, top.y, barWidth, h, health, health_max);
			}
		}
	}

	if (debug)
	{
		ImGui::GetBackgroundDrawList()->AddRect({ 0,0 }, { (float)Overlay::screen.width, (float)Overlay::screen.height }, ImColor(255.0f, 0.0f, 0.0f), 0, 0, 2);
		ImGui::GetBackgroundDrawList()->AddLine({ 0, (float)Overlay::screen.height / 2 }, { (float)Overlay::screen.width, (float)Overlay::screen.height / 2 }, ImColor(255.0f, 0.0f, 0.0f));
		ImGui::GetBackgroundDrawList()->AddLine({ (float)Overlay::screen.width / 2, 0 }, { (float)Overlay::screen.width / 2, (float)Overlay::screen.height }, ImColor(255.0f, 0.0f, 0.0f));
	}
}

void Menu::DrawVerticalBar(float x, float y, float width, float height, int value, int max_value, ImU32 valueColor) {
	// Ensure value is between 0 and max_value
	if (value < 0) value = 0;
	if (value > max_value) value = max_value;

	// Calculate value percentage
	float valuePercentage = (float)value / (float)max_value;

	// Colors
	ImU32 borderColor = IM_COL32(255, 255, 255, 255); // White
	ImU32 backgroundColor = IM_COL32(100, 100, 100, 255); // Gray

	// Draw background
	ImVec2 p_min = ImVec2(x, y);
	ImVec2 p_max = ImVec2(x + width, y + height);
	ImGui::GetBackgroundDrawList()->AddRectFilled(p_min, p_max, backgroundColor);

	// Draw value
	float healthHeight = height * valuePercentage;
	ImVec2 value_min = ImVec2(x, y + height - healthHeight);
	ImVec2 value_max = ImVec2(x + width, y + height);
	ImGui::GetBackgroundDrawList()->AddRectFilled(value_min, value_max, valueColor);

	// Draw border
	ImGui::GetBackgroundDrawList()->AddRect(p_min, p_max, borderColor);
}