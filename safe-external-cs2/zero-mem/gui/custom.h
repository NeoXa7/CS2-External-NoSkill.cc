#pragma once
#include <globals/imports.h>
#include <utils/keys.h>
#include <gui/gifs.h>
#include <gui/particles.h>

class UIComponents
{
private:
	ImColor WindowBGColor = ImColor(5, 5, 5);
	ImColor HeaderColor = ImColor(10, 10, 10, 200);
	ImColor SideBarColor = ImColor(10, 10, 10, 200);
	ImColor FrameColor = ImColor(15, 15, 15, 200);

	ImColor VerticalButtonColor = ImColor(10, 10, 10, 0);
	ImColor VerticalButtonColorHovered = ImColor(30, 30, 30, 255);
	ImColor VerticalButtonColorActive = ImColor(45, 45, 45, 200);

	ImColor NormalButtonColor = ImColor(30, 30, 30, 255);
	ImColor NormalButtonColorHovered = ImColor(30, 30, 30, 175);
	ImColor NormalButtonColorActive = ImColor(30, 30, 30, 175);

	ImColor ColorEditorColor = ImColor(36, 36, 36, 100);
	ImColor ColorEditorColorHovered = ImColor(36, 36, 36, 255);
	ImColor ColorEditorColorActive = ImColor(36, 36, 36, 100);

	ImColor CheckboxColorFalse = ImColor(36, 36, 36, 100);
	ImColor CheckboxColorTrue = ImColor(36, 36, 36, 255);
	ImColor CheckboxColorHovered = ImColor(36, 36, 36, 255);
	ImColor CheckMarkColor = ImColor(255, 255, 255);

	ImColor SliderBGColor = ImColor(20, 20, 20, 200);
	ImColor SliderGrabColor = ImColor(255, 255, 255, 230);

	ImColor RadioButtonGroupBGColor = ImColor(23, 23, 23, 255);
	ImColor RadioButtonGroupBGHoverColor = ImColor(23, 23, 23, 255);
	ImColor RadioButtonGroupBGActiveColor = ImColor(23, 23, 23, 175);
	ImColor RadioButtonGroupCheckmarkColor = ImColor(255, 97, 116, 175);

	ImColor ComboBoxColor = ImColor(23, 23, 23, 175);
	ImColor ComboBoxHoverColor = ImColor(23, 23, 23, 255);
	ImColor ComboBoxActiveColor = ImColor(23, 23, 23, 175);

	ImColor ToggleONCircleColor = ImColor(255, 97, 116, 175);
	ImColor ToggleONBackgroundColor = ImColor(20, 20, 20, 200);
	ImColor ToggleOFFCircleColor = ImColor(255, 255, 255, 50);
	ImColor ToggleOFFBackgroundColor = ImColor(20, 20, 20, 255);

	ImColor ScrollBarGrabBGColor = ImColor(255, 255, 255, 0);
	ImColor ScrollBarGrabColor = ImColor(255, 255, 255, 50);
	ImColor ScrollBarHoverColor = ImColor(255, 255, 255, 120);
	ImColor ScrollBarActiveColor = ImColor(255, 255, 255, 50);

	float FrameTime = 0.0f;
	INT CurrentFrame = 0;

public:
	ImVec2 WindowPosition = ImVec2();
	ImVec2 WindowSize = ImVec2();
	ImVec2 CursorPosition = ImVec2();
	ImDrawList* DrawList;

	void SetStyles() {
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.0f;
		style.WindowRounding = 6.0f;
		style.ScrollbarSize = 2.0f;
		style.FrameBorderSize = 0.0f;
		style.FrameRounding = 6.0f;
		style.ChildBorderSize = 0.0f;
		style.Colors[ImGuiCol_WindowBg] = WindowBGColor;
		style.Colors[ImGuiCol_Button] = VerticalButtonColor;
		style.Colors[ImGuiCol_ButtonHovered] = VerticalButtonColorHovered;
		style.Colors[ImGuiCol_ButtonActive] = VerticalButtonColorActive;
		style.Colors[ImGuiCol_FrameBg] = FrameColor;
		style.Colors[ImGuiCol_ScrollbarBg] = ScrollBarGrabBGColor;
		style.Colors[ImGuiCol_ScrollbarGrab] = ScrollBarGrabColor;
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ScrollBarActiveColor;
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ScrollBarHoverColor;
	}

	void DrawHeader(float rounding = 0.0f, float height = 50.0f) {
		DrawList->AddRectFilled(
			ImVec2(ImGui::GetCursorScreenPos().x + 200.0f, ImGui::GetCursorScreenPos().y),
			ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetContentRegionAvail().x, ImGui::GetCursorScreenPos().y + height),
			this->HeaderColor, rounding
		);

		// horizontal line
		DrawList->AddLine(
			ImVec2(ImGui::GetCursorScreenPos().x + 200.0f, ImGui::GetCursorScreenPos().y + height),
			ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetContentRegionAvail().x, ImGui::GetCursorScreenPos().y + height),
			ImColor(255, 255, 255, 25)
		);
	}

	void DrawSideBar(float rounding = 0.0f, float width = 150.0f) {
		DrawList->AddRectFilled(
			ImVec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y),
			ImVec2(ImGui::GetCursorScreenPos().x + width, ImGui::GetCursorScreenPos().y + ImGui::GetContentRegionAvail().y + 40.0f),
			this->SideBarColor, rounding
		);

		// vertical line
		DrawList->AddLine(
			ImVec2(ImGui::GetCursorScreenPos().x + width, ImGui::GetCursorScreenPos().y),
			ImVec2(ImGui::GetCursorScreenPos().x + width, ImGui::GetCursorScreenPos().y + ImGui::GetContentRegionAvail().y + 40.0f),
			ImColor(255, 255, 255, 25)
		);

		ImGui::PushFont(RES_LOADER::FONTS::RIFIC_BOLD);
		ImGui::SetCursorPos(ImVec2(35, 15));
		ImGui::Text("NOSKILL.CC");
		ImGui::PopFont();
	}

	void DrawBorder(ImVec2 window_pos, ImVec2 window_size, float rounding = 0.0f, float thickness = 2.0f, ImColor color = ImColor(255, 255, 255, 140)) {
		DrawList->AddRect(
			{ window_pos.x - 1, window_pos.y - 1 }, { window_pos.x + window_size.x + 1, window_pos.y + window_size.y + 1 },
			color, // color
			rounding, 0, thickness
		);
	}

	// thanks CHAT-GPT :)
	void DrawVerticalButtons(std::vector<std::string> button_names, std::vector<int> button_index, int& selected_index,
		std::vector<ImTextureID> icons, float button_width = 130.0f, float button_height = 35.0f, float spacing = 2.0f)
	{
		static std::unordered_map<ImGuiID, float> hoverAnimMap;
		static std::unordered_map<ImGuiID, float> selectAnimMap;

		ImVec2 cursorPos = ImGui::GetCursorScreenPos();

		for (size_t i = 0; i < button_names.size(); ++i) {
			const char* label = button_names[i].c_str();
			ImGui::PushID(label);

			ImVec2 buttonPos = ImVec2(cursorPos.x + 10.0f, cursorPos.y + i * (button_height + spacing) + 7.0f);
			ImVec2 size = ImVec2(button_width, button_height);

			ImGui::SetCursorScreenPos(buttonPos);
			ImGui::InvisibleButton("##invisible", size);
			bool hovered = ImGui::IsItemHovered();
			bool clicked = ImGui::IsItemClicked();
			ImGuiID buttonID = ImGui::GetID(label);

			// Hover animation
			float& hoverAnim = hoverAnimMap[buttonID];
			float hoverSpeed = 6.0f * ImGui::GetIO().DeltaTime;
			hoverAnim = ImClamp(hoverAnim + (hovered ? hoverSpeed : -hoverSpeed), 0.0f, 1.0f);

			// Selection animation
			float& selectAnim = selectAnimMap[buttonID];
			float selectSpeed = 4.0f * ImGui::GetIO().DeltaTime;
			bool isSelected = (selected_index == button_index[i]);
			selectAnim = ImClamp(selectAnim + (isSelected ? selectSpeed : -selectSpeed), 0.0f, 1.0f);

			// Blend color: base → active based on selectAnim, then add hover effect
			ImVec4 baseColor = ImLerp(VerticalButtonColor.Value, VerticalButtonColorActive.Value, selectAnim);
			ImVec4 finalColor = ImLerp(baseColor, VerticalButtonColorHovered.Value, hoverAnim);
			ImColor bgColor = ImColor(finalColor);

			// Draw background
			DrawList->AddRectFilled(buttonPos, ImVec2(buttonPos.x + size.x, buttonPos.y + size.y), bgColor, 6.0f);

			// Draw icon
			float icon_size = 22.0f;
			ImVec2 iconPos = ImVec2(buttonPos.x + 10.0f, buttonPos.y + (button_height - icon_size) * 0.5f);

			int text_alpha = (int)ImLerp(100.0f, 255.0f, selectAnim); // fade from 100 to 255 alpha

			if (i < icons.size() && icons[i] != 0) {
				ImU32 iconTint = IM_COL32(255, 255, 255, text_alpha);
				DrawList->AddImage(icons[i], iconPos, ImVec2(iconPos.x + icon_size, iconPos.y + icon_size), ImVec2(0, 0), ImVec2(1, 1), iconTint);
			}

			// Draw label
			ImVec2 textSize = ImGui::CalcTextSize(label);
			ImVec2 textPos = ImVec2(
				iconPos.x + icon_size + 8.0f,
				buttonPos.y + (size.y - textSize.y) * 0.5f
			);
			DrawList->AddText(textPos, IM_COL32(255, 255, 255, text_alpha), label);

			if (clicked) {
				selected_index = button_index[i];
			}

			ImGui::PopID();
		}
	}

	// thanks CHAT-GPT :)
	bool Button(const char* label, float width, float height) {
		static std::unordered_map<ImGuiID, float> hoverAnimMap;

		std::string fullLabel(label);
		std::string visibleLabel = fullLabel.substr(0, fullLabel.find("##"));

		ImGui::PushID(label);

		ImVec2 cursor = ImGui::GetCursorScreenPos();
		ImGui::InvisibleButton(label, ImVec2(width, height));

		bool hovered = ImGui::IsItemHovered();
		bool clicked = ImGui::IsItemClicked();
		ImGuiID id = ImGui::GetID(label);

		float& anim = hoverAnimMap[id];
		float speed = 6.0f * ImGui::GetIO().DeltaTime;
		anim = ImClamp(anim + (hovered ? speed : -speed), 0.0f, 1.0f);

		ImVec4 base = ImLerp(NormalButtonColor.Value, NormalButtonColorHovered.Value, anim);
		ImColor bg = ImColor(base);

		ImDrawList* DrawList = ImGui::GetWindowDrawList(); // ✅ Correct draw list
		DrawList->AddRectFilled(cursor, ImVec2(cursor.x + width, cursor.y + height), bg, 6.0f);

		// Draw centered label text
		ImVec2 textSize = ImGui::CalcTextSize(visibleLabel.c_str());
		ImVec2 textPos = ImVec2(
			cursor.x + (width - textSize.x) * 0.5f,
			cursor.y + (height - textSize.y) * 0.5f
		);
		DrawList->AddText(textPos, IM_COL32(255, 255, 255, 255), visibleLabel.c_str());

		ImGui::PopID();
		return clicked;
	}

	void DrawProfile(const char* name, ImTextureID image, const char* license_date = "TILL: 03.10 22:41") {

		ImGui::SetCursorPos(ImVec2(20, 470));
		if(this->BeginColumn("##profile##", ImVec2(200.0f, 50.0f))) {
			ImVec2 cursor = ImGui::GetCursorScreenPos();

			float avatarSize = 40.0f;
			float radius = avatarSize / 2.0f;
			ImVec2 center = ImVec2(cursor.x + radius, cursor.y + radius);

			ImGui::GetWindowDrawList()->AddCircleFilled(center, radius, IM_COL32(20, 20, 20, 200));
			ImGui::SetCursorScreenPos(cursor);
			ImGui::Image(image, ImVec2(avatarSize, avatarSize));

			ImGui::SetCursorPos(ImVec2(45.0f, 0.0f));
			ImGui::TextColored(ImColor(255, 255, 255, 200), "%s", name);

			ImGui::SetCursorPos(ImVec2(45.0f, 20.0f));
			ImGui::TextColored(ImColor(255, 255, 255, 200), "%s", license_date);
		}

		this->EndColumn();
	}
	
	void DrawProfile2(const char* name, ImColor name_text_color, const char* license_date = "TILL: 03.10 22:41") {
		ImGui::SetCursorPos(ImVec2(20, 470));

		if (this->BeginColumn("##profile##", ImVec2(200.0f, 60.0f))) {
			// Name line with label
			ImGui::SetCursorPos(ImVec2(45.0f, 5.0f));
			ImGui::TextColored(name_text_color, "User : %s", name);

			// License expiration
			ImGui::SetCursorPos(ImVec2(3.0f, 25.0f));
			ImGui::TextColored(ImColor(255, 255, 255, 200), "Expire : %s", license_date);

			this->EndColumn();
		}
	}

	void DrawTitle(const char* name) {
		this->CenterText(name, 0.0f, ImColor(255, 255, 255, 105));
		ImGui::Dummy(ImVec2(0, 0.0f));
		ImGui::Separator();
		ImGui::Dummy(ImVec2(0, 10.0f));
	}

	// thanks CHAT-GPT :)
	bool ToggleButton(const char* label, bool* value, float width = 40.0f, float height = 20.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		std::string label_str(label);
		std::string visible_label = label_str.substr(0, label_str.find("##"));

		// Compute vertical alignment offset
		float text_height = ImGui::GetFontSize();
		float y_offset = (text_height > height) ? 0.0f : (text_height - height) * 0.5f;

		// Get current cursor pos
		ImVec2 label_pos = ImGui::GetCursorScreenPos();
		label_pos.y += 3.0f; // Adds 5 pixels of Y spacing

		// Draw the label first
		ImGui::SetCursorPosX(15.0f);
		ImGui::TextColored(ImColor(255, 255, 255, 200), visible_label.c_str());
		ImGui::SameLine();

		// Compute toggle position (right of text, vertically aligned)
		ImVec2 pos = ImVec2(label_pos.x + 190.0f, label_pos.y + y_offset + 2.0f);
		ImVec2 size = ImVec2(width, height);

		// Process input
		ImGui::SetCursorScreenPos(pos);
		ImGui::InvisibleButton((std::string(label) + "##toggle").c_str(), size);
		bool hovered = ImGui::IsItemHovered();
		bool clicked = ImGui::IsItemClicked();
		if (clicked) {
			*value = !*value;
		}

		// Animation
		ImGuiID id = ImGui::GetID(label);
		static std::unordered_map<ImGuiID, float> animationProgress;
		float& t = animationProgress[id];
		float speed = 8.0f * io.DeltaTime;
		t = ImClamp(t + ((*value ? 1.0f : 0.0f) - t) * speed, 0.0f, 1.0f);

		// Colors
		ImColor bgColor = ImLerp(ToggleOFFBackgroundColor.Value, ToggleONBackgroundColor.Value, t);
		ImColor circleColor = ImLerp(ToggleOFFCircleColor.Value, ToggleONCircleColor.Value, t);

		float bg_height = height * 0.55f; // smaller than the circle
		float bg_y = pos.y + (height - bg_height) * 0.5f;
		draw_list->AddRectFilled(
			ImVec2(pos.x + 0.0f, bg_y),
			ImVec2(pos.x + size.x - 10.0f, bg_y + bg_height),
			bgColor,
			bg_height * 0.5f
		);

		// Draw toggle circle
		float circle_radius = height * 0.35f;
		float circle_x = ImLerp(pos.x + circle_radius, pos.x + size.x - 10.0f - circle_radius, t);
		ImVec2 circle_center = ImVec2(circle_x, pos.y + size.y * 0.5f);
		draw_list->AddCircleFilled(circle_center, circle_radius, circleColor);

		return clicked;
	}

	void ColorEditor(const char* label, ImColor* color, float width = 20.0f, float height = 16.0f, float roundness = 2.0f)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.0f, 2.0f)); // Smaller padding for reduced height
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ColorEditorColor.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ColorEditorColorHovered.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ColorEditorColorActive.Value);
		ImGui::PushStyleColor(ImGuiCol_Border, ImColor(10, 10, 10, 255).Value);
		ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255, 255).Value);

		// Draw the label text
		std::string label_str(label);
		std::string visible_label = label_str.substr(0, label_str.find("##"));
		ImGui::TextUnformatted(visible_label.c_str());
		ImGui::SameLine();

		// Draw a custom color button (smaller in height)
		std::string btn_id = "##" + std::string(label) + "_colorbtn";
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.0f); // vertically center the button a bit
		ImGui::SetCursorPosX(215.0f);
		if (ImGui::ColorButton(btn_id.c_str(), *color, ImGuiColorEditFlags_NoTooltip, ImVec2(width, height))) {
			ImGui::OpenPopup((btn_id + "_picker").c_str());
		}

		if (ImGui::BeginPopup((btn_id + "_picker").c_str())) {
			ImGui::ColorPicker4("##picker", (float*)color, ImGuiColorEditFlags_NoSidePreview);
			ImGui::EndPopup();
		}

		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(5);
	}

	template <typename T>
	bool Slider(const char* title, T* value, T v_min, T v_max) {
		ImGui::PushID(title);
		this->LeaveLine();
		ImGui::TextColored(ImColor(255, 255, 255, 255), title);
		ImGui::SameLine();

		if constexpr (std::is_integral<T>::value) {
			ImGui::TextColored(ImColor(255, 255, 255, 255), "(%d)", *value);
		}
		else {
			ImGui::TextColored(ImColor(255, 255, 255, 255), "(%.1f)", *value);
		}

		ImVec2 cursor_spos = ImGui::GetCursorScreenPos();
		float width = ImGui::CalcItemWidth();
		float height = 10.0f;
		float circle_height = 20.0f;


		ImGui::InvisibleButton(title, ImVec2(width, height));
		bool is_item_active = ImGui::IsItemActive();
		bool is_item_clicked = ImGui::IsItemClicked();

		if (is_item_active) {
			float mouse_pos = ImGui::GetMousePos().x - cursor_spos.x;
			float t = ImClamp(mouse_pos / width, 0.0f, 1.0f);
			float float_value = v_min + (v_max - v_min) * t;

			if constexpr (std::is_integral<T>::value) {
				*value = static_cast<T>(float_value + 0.5f); // round to nearest int
			}
			else {
				*value = static_cast<T>(float_value);
			}

			*value = ImClamp(*value, v_min, v_max);
		}

		ImGui::GetWindowDrawList()->AddRectFilled(cursor_spos, ImVec2(cursor_spos.x + width, cursor_spos.y + height), SliderBGColor, height * 0.3f);
		float fill_width = (*value - v_min) / (float)(v_max - v_min) * width;
		ImGui::GetWindowDrawList()->AddRectFilled(
			cursor_spos,
			ImVec2(cursor_spos.x + fill_width, cursor_spos.y + height),
			IM_COL32(
				static_cast<int>(SliderGrabColor.Value.x * 255.0f),
				static_cast<int>(SliderGrabColor.Value.y * 255.0f),
				static_cast<int>(SliderGrabColor.Value.z * 255.0f),
				(ImGui::IsItemActive() ? 255.0f : 200.0f)
			),
			5.0f
		);

		ImGui::PopID();
		return is_item_clicked;
	}

	void RadioButtonGroup(const char* title, int* current_index, const char* const items[], int items_size, bool vertical = false)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::TextColored(ImColor(255, 255, 255, 200), title);

		for (int i = 0; i < items_size; ++i)
		{
			bool is_selected = (*current_index == i);
			ImGuiID id = ImGui::GetID(items[i]);

			static std::unordered_map<ImGuiID, float> anim_progress;
			float& t = anim_progress[id];
			float target = is_selected ? 1.0f : 0.0f;
			t = ImClamp(t + (target - t) * (10.0f * io.DeltaTime), 0.0f, 1.0f);

			ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
			ImVec2 text_size = ImGui::CalcTextSize(items[i]);
			ImVec2 item_size = ImVec2(18.0f + 6.0f + text_size.x, 18.0f);
			ImGui::InvisibleButton((std::string(items[i]) + "##invisible").c_str(), item_size);

			if (ImGui::IsItemClicked()) *current_index = i;

			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			ImVec2 circle_center = ImVec2(cursor_pos.x + 9.0f, cursor_pos.y + item_size.y * 0.5f);

			float outer_radius = 8.0f;
			float inner_radius = 4.0f * t;

			ImColor outer_color = ImColor(
				ImLerp(RadioButtonGroupBGColor.Value, RadioButtonGroupBGActiveColor.Value, t)
			);

			ImVec4 text_color = ImLerp(
				ImVec4(0.7f, 0.7f, 0.7f, 1.0f),
				ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
				t
			);

			ImColor inner_color = RadioButtonGroupCheckmarkColor;

			draw_list->AddCircle(circle_center, outer_radius, outer_color, 16, 1.5f);
			draw_list->AddCircleFilled(circle_center, inner_radius, inner_color);

			ImVec2 text_pos = ImVec2(circle_center.x + outer_radius + 6.0f, cursor_pos.y + (item_size.y - text_size.y) * 0.5f);
			draw_list->AddText(text_pos, ImColor(text_color), items[i]);

			if (i < items_size - 1 && !vertical)
				ImGui::SameLine();
		}
	}

	void Hotkey(int* k, const ImVec2& size_arg = ImVec2(130, 35)) {
		static std::unordered_map<int*, bool> keyStates;

		std::string label = std::string(KeyNames[*k]) + "##" + std::to_string(reinterpret_cast<uintptr_t>(k));

		// Only calculate size if the user didn't provide one
		ImVec2 final_size = size_arg;
		if (final_size.x == 0.0f) {
			// Measure the visible part only (before "##")
			ImVec2 text_size = ImGui::CalcTextSize(KeyNames[*k]);
			final_size.x = text_size.x + ImGui::GetStyle().FramePadding.x * 2;
		}
		if (final_size.y == 0.0f) {
			final_size.y = ImGui::GetFrameHeight(); // default height
		}

		if (!keyStates[k]) {
			if (this->Button(label.c_str(), final_size.x, final_size.y)) {
				keyStates[k] = true;
			}
		}
		else {
			ImGui::TextColored(ImColor(255, 255, 255, 255), "Waiting for Key...");
			Sleep(100);

			for (auto& Key : KeyCodes) {
				if (GetAsyncKeyState(Key) & 0x8000) {
					*k = Key;
					keyStates[k] = false;
					break;
				}
			}
		}
	}

	bool ComboBox(const char* label, const char* preview_value, int* currentIndex, const char* items[], int items_count, float width = 150.0f, float height = 30.0f)
	{
		static std::unordered_map<ImGuiID, float> openAnimProgress;
		static std::unordered_map<ImGuiID, bool> comboState;

		ImGui::PushID(label);

		ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255, 255).Value);
		ImGui::Text(label);
		ImGui::PopStyleColor(1);

		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImGui::InvisibleButton("##combo", ImVec2(width, height));
		ImGuiID id = ImGui::GetID(label);

		// Get draw list of the current window
		ImDrawList* drawList = ImGui::GetWindowDrawList();

		// Handle open/close toggle
		bool& isOpen = comboState[id];
		if (ImGui::IsItemClicked())
			isOpen = !isOpen;

		// Animate dropdown open progress
		float& anim = openAnimProgress[id];
		float animSpeed = 10.0f * ImGui::GetIO().DeltaTime;
		anim = ImClamp(anim + (isOpen ? animSpeed : -animSpeed), 0.0f, 1.0f);

		// Draw main combo box background
		drawList->AddRectFilled(pos, ImVec2(pos.x + width, pos.y + height), ImColor(23, 23, 23, 255), 6.0f);

		// Draw preview/selected item text
		if (preview_value)
		{
			ImVec2 textSize = ImGui::CalcTextSize(preview_value);
			drawList->AddText(ImVec2(pos.x + 10, pos.y + (height - textSize.y) * 0.5f), ImColor(255, 255, 255), preview_value);
		}

		// Draw dropdown arrow
		drawList->AddTriangleFilled(
			ImVec2(pos.x + width - 18, pos.y + height / 2 - 3),
			ImVec2(pos.x + width - 10, pos.y + height / 2 - 3),
			ImVec2(pos.x + width - 14, pos.y + height / 2 + 3),
			ImColor(255, 255, 255, 200)
		);

		// Dropdown max height (max 5 items visible)
		float maxDropdownHeight = height * ImMin(items_count, 5);
		float visibleHeight = maxDropdownHeight * anim;

		bool changed = false;

		if (visibleHeight > 0.1f)
		{
			ImVec2 dropdownPos = ImVec2(pos.x, pos.y + height);

			// Draw dropdown background with rounded corners
			drawList->AddRectFilled(dropdownPos, ImVec2(dropdownPos.x + width, dropdownPos.y + visibleHeight), ImColor(23, 23, 23, 255), 6.0f);

			// Set cursor inside dropdown area
			ImGui::SetCursorScreenPos(dropdownPos);

			ImGui::BeginChild((std::string("##dropdown") + label).c_str(), ImVec2(width, visibleHeight), true);

			// Use child window draw list for custom drawing inside dropdown
			ImDrawList* childDrawList = ImGui::GetWindowDrawList();

			for (int i = 0; i < items_count; ++i)
			{
				ImGui::PushID(i);

				ImVec2 itemPos = ImGui::GetCursorScreenPos();
				ImVec2 itemSize = ImVec2(width, height);

				ImGui::InvisibleButton("##item", itemSize);

				bool hovered = ImGui::IsItemHovered();
				bool selected = (i == *currentIndex);

				if (ImGui::IsItemClicked())
				{
					*currentIndex = i;
					isOpen = false;
					changed = true;
				}

				// Background color: highlight if hovered or selected
				ImColor bgColor;
				if (selected)
					bgColor = ImColor(70, 70, 70, 255);
				else if (hovered)
					bgColor = ImColor(50, 50, 50, 255);
				else
					bgColor = ImColor(36, 36, 36, 255);

				childDrawList->AddRectFilled(itemPos, ImVec2(itemPos.x + width, itemPos.y + height), bgColor, 6.0f);

				// Draw item text
				childDrawList->AddText(ImVec2(itemPos.x + 10, itemPos.y + (height - ImGui::GetFontSize()) * 0.5f), ImColor(255, 255, 255), items[i]);

				ImGui::PopID();
			}

			ImGui::EndChild();

			// Reset cursor pos to avoid layout issues
			ImGui::SetCursorScreenPos(ImVec2(pos.x, pos.y + height));
		}

		ImGui::PopID();

		return changed;
	}

	// ---------------------------->
	// 
	//	OLD SHITS BELOW
	//
	// ---------------------------->

	void SetLogo(ImTextureID image, ImVec2 size, float y_padding = 15.0f) {

		ImGui::SetCursorPosY(CursorPosition.y + y_padding);
		ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x / 2) - (size.x / 2));
		ImGui::Image(image, size);
		ImGui::SetCursorPos(CursorPosition);
	}

	// slightly modified version of : https://youtu.be/2B_qzPHV4MQ?t=854 (exact time line set)
	void CenterButtons(std::vector<std::string> button_names, std::vector<int> button_index, int& selected_index) {
		std::vector<ImVec2> vsizes = {};
		float total_area = 0.0f;

		const auto& styles = ImGui::GetStyle();

		// Calculate total size for centering
		for (const std::string& name : button_names) {
			ImVec2 label_size = ImGui::CalcTextSize(name.c_str(), 0, true);
			ImVec2 size = ImGui::CalcItemSize(ImVec2(), label_size.x + styles.FramePadding.x * 2.0f, label_size.y + styles.FramePadding.y * 2.0f);
			size.x += 45.5f;
			size.y += 15.0f;

			vsizes.push_back(size);
			total_area += size.x;
		}

		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (total_area / 2));

		for (size_t i = 0; i < button_names.size(); ++i) {
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 85);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);

			bool is_selected = selected_index == button_index[i];

			if (is_selected) {
				ImGui::PushStyleColor(ImGuiCol_Button, ImColor(VerticalButtonColor.Value.x, VerticalButtonColor.Value.y, VerticalButtonColor.Value.z, 255.0f).Value);
			}
			else {
				ImGui::PushStyleColor(ImGuiCol_Button, VerticalButtonColor.Value);
			}

			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, VerticalButtonColorHovered.Value);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, VerticalButtonColorActive.Value);

			if (ImGui::Button(button_names[i].c_str(), vsizes[i])) {
				selected_index = button_index[i];
			}

			ImGui::PopStyleColor(3);
			ImGui::PopStyleVar();

			if (i != button_names.size() - 1) {
				ImGui::SameLine();
			}
		}
	}

	// slightly modified version of : https://youtu.be/2B_qzPHV4MQ?t=854
	void CenterText(const char* format, const float y_padding, ImColor color) {
		const ImVec2 text_size = ImGui::CalcTextSize(format);
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (text_size.x / 2));

		if (y_padding > 0.0f)
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + y_padding);
		ImGui::TextColored(color, format);
	}

	void GradientSeperator(float seperator_height = 2.0f, float alpha = 255.0f) {
		ImVec2 p1 = ImGui::GetCursorScreenPos();
		float width = ImGui::GetWindowSize().x;

		ImVec2 p2 = ImVec2(p1.x + width, p1.y + seperator_height);

		ImGui::GetWindowDrawList()->AddRectFilledMultiColor(
			p1, p2,
			IM_COL32(255, 0, 0, static_cast<int>(alpha)),   // left: red
			IM_COL32(0, 255, 0, static_cast<int>(alpha)),   // right: green
			IM_COL32(0, 0, 255, static_cast<int>(alpha)),   // left bottom: blue
			IM_COL32(255, 255, 0, static_cast<int>(alpha))  // right bottom: yellow
		);

		ImGui::Dummy(ImVec2(0.0f, seperator_height + 2.0f));
	}

	bool BeginColumn(const char* id, ImVec2 size, int window_flag = 1) {
		ImGui::PushStyleColor(0, ImColor(247, 101, 175, 100).Value);
		return ImGui::BeginChild(id, size, window_flag);
	}

	void EndColumn() {
		ImGui::EndChild();
		ImGui::PopStyleColor();
	}

	bool BeginFrame(ImGuiID id, ImVec2 size, int window_flag = 0) {
		ImGui::PushStyleColor(ImGuiCol_Border, ImColor(255, 255, 255, 100).Value);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
		return ImGui::BeginChildFrame(id, size, window_flag);
	}

	void EndFrame() {
		ImGui::EndChildFrame();
		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
	}

	void Checkbox(const char* format, bool* value) {
		ImGui::PushStyleColor(ImGuiCol_FrameBg, CheckboxColorFalse.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, CheckboxColorHovered.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, CheckboxColorHovered.Value);
		ImGui::PushStyleColor(ImGuiCol_CheckMark, CheckMarkColor.Value);

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3.5f, 3.5f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);

		ImGui::Checkbox(format, value);

		ImGui::PopStyleColor(4);
		ImGui::PopStyleVar(2);
	}

	void ColorEditor2(const char* label, ImColor* color, float width = 190.0f, float roundness = 2.0f)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3.5f, 3.5f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ColorEditorColor.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ColorEditorColorHovered.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ColorEditorColorActive.Value);
		ImGui::PushStyleColor(ImGuiCol_Border, ImColor(10, 10, 10, 255).Value);

		ImGui::SetNextItemWidth(width);

		// Prepare to push text color
		bool active = ImGui::IsItemActive(); // still false here, so ignore
		ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255, 200).Value); // default
		ImGui::ColorEdit3(label, (float*)color);
		ImGui::PopStyleColor(); // text color

		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(4);
	}

	bool InputBoxWithPlaceholder(const char* label, const char* placeholder, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0)
	{
		ImGui::PushID(label);
		bool result = ImGui::InputText("", buf, buf_size, flags);
		if (strlen(buf) == 0 && !ImGui::IsItemActive())
		{
			ImVec2 pos = ImGui::GetItemRectMin();
			ImVec2 textPos = ImVec2(pos.x + ImGui::GetStyle().FramePadding.x,
				pos.y + ImGui::GetStyle().FramePadding.y);

			ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(150, 150, 150, 255), placeholder);
		}
		ImGui::PopID();
		return result;
	}

	void LeaveLine(int count = 1) {
		for (int i = 0; i < count; i++)
		{
			ImGui::Dummy(ImVec2());
		}
	}
};
