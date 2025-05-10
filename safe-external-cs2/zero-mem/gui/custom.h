#pragma once
#include <globals/imports.h>
#include <utils/keys.h>

class UIComponents
{
public:
	ImVec2 WindowPosition = ImVec2();
	ImVec2 WindowSize = ImVec2();
	ImVec2 CursorPosition = ImVec2();

	ImColor WindowBGColor = ImColor(23, 23, 23);

	ImColor ButtonColor = ImColor(36, 36, 36, 100);
	ImColor ButtonColorHovered = ImColor(36, 36, 36, 255);
	ImColor ButtonColorActive = ImColor(36, 36, 36, 200);

	ImColor ColorEditorColor = ImColor(36, 36, 36, 100);
	ImColor ColorEditorColorHovered = ImColor(36, 36, 36, 255);
	ImColor ColorEditorColorActive = ImColor(36, 36, 36, 100);

	ImColor CheckboxColorFalse = ImColor(36, 36, 36, 100);
	ImColor CheckboxColorTrue = ImColor(36, 36, 36, 255);
	ImColor CheckboxColorHovered = ImColor(36, 36, 36, 255);
	ImColor CheckMarkColor = ImColor(255, 255, 255);

	ImColor SliderBGColor = ImColor(30, 30, 30);
	ImColor SliderGrabColor = ImColor(30, 30, 30);
	ImColor SliderGrabActiveColor = ImColor(30 - 10, 30 - 10, 30 - 4, 255);

	ImColor RadioButtonGroupColor = ImColor(23, 23, 23, 175);
	ImColor RadioButtonGroupHoverColor = ImColor(23, 23, 23, 255);
	ImColor RadioButtonGroupActiveColor = ImColor(23, 23, 23, 175);

	ImColor ComboBoxColor = ImColor(23, 23, 23, 175);
	ImColor ComboBoxHoverColor = ImColor(23, 23, 23, 255);
	ImColor ComboBoxActiveColor = ImColor(23, 23, 23, 175);

	void SetStyles() {
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowBorderSize = 0.0f;
		style.WindowRounding = 0.0f;
		style.ScrollbarSize = 2.0f;
		style.FrameRounding = 5.0f;
		style.FrameBorderSize = 1.0f;
		style.FrameRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg] = WindowBGColor;
		style.Colors[ImGuiCol_Border] = ImColor(91, 60, 160, 0);
		style.Colors[ImGuiCol_Button] = ButtonColor;
		style.Colors[ImGuiCol_ButtonHovered] = ButtonColorHovered;
		style.Colors[ImGuiCol_ButtonActive] = ButtonColorActive;
		style.Colors[ImGuiCol_FrameBg] = ImColor(28, 28, 28, 100);
		style.Colors[ImGuiCol_FrameBgHovered] = ImColor(255, 255, 255);
		style.Colors[ImGuiCol_FrameBgActive] = ImColor(255, 255, 255);
	}

	void LeaveLine(int count = 1) {
		for (int i = 0; i < count; i++)
		{
			ImGui::Dummy(ImVec2());
		}
	}

	void DrawBorder(ImVec2 window_pos, ImVec2 window_size, float rounding = 0.0f, float thickness = 2.0f, ImColor color = ImColor(255, 255, 255, 140)) {
		ImGui::GetBackgroundDrawList()->AddRect(
			{ window_pos.x - 1, window_pos.y - 1 }, { window_pos.x + window_size.x + 1, window_pos.y + window_size.y + 1 },
			color, // color
			rounding, 0, thickness
		);
	}

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
				ImGui::PushStyleColor(ImGuiCol_Button, ImColor(ButtonColor.Value.x, ButtonColor.Value.y, ButtonColor.Value.z, 255.0f).Value);
			}
			else {
				ImGui::PushStyleColor(ImGuiCol_Button, ButtonColor.Value);
			}

			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ButtonColorHovered.Value);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ButtonColorActive.Value);

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
		ImGui::PushStyleColor(ImGuiCol_Border, ImColor(247, 101, 175, 100).Value);
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

	void ColorEditor(const char* label, ImColor* color, float width = 50.0f, float roundness = 2.0f) {
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3.5f, 3.5f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ColorEditorColor.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ColorEditorColorHovered.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ColorEditorColorActive.Value);
		ImGui::PushStyleColor(ImGuiCol_Border, ImColor(10, 10, 10, 255).Value);

		ImGui::SetNextItemWidth(width);
		ImGui::ColorEdit3(label, (float*)color, ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoBorder);

		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(4);
	}

	void ColorEditor2(const char* label, ImColor* color, float width = 200.0f, float roundness = 2.0f) {
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness);
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3.5f, 3.5f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ColorEditorColor.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ColorEditorColorHovered.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ColorEditorColorActive.Value);
		ImGui::PushStyleColor(ImGuiCol_Border, ImColor(10, 10, 10, 255).Value);

		ImGui::SetNextItemWidth(width);
		ImGui::ColorEdit3(label, (float*)color);

		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(4);
	}

	template <typename T>
	bool Slider(const char* title, T* value, T v_min, T v_max, ImColor color = ImColor(255, 0, 0), float alpha = 255) {
		ImGui::PushID(title);
		this->LeaveLine();
		ImGui::Text(title);
		ImGui::SameLine();

		if constexpr (std::is_integral<T>::value) {
			ImGui::Text("(%d)", *value);
		}
		else {
			ImGui::Text("(%.1f)", *value);
		}

		ImVec2 cursor_spos = ImGui::GetCursorScreenPos();
		float width = ImGui::CalcItemWidth();
		float height = 10.0f;
		float circle_height = 20.0f;

		ImU32 slider_bg_color = ImGui::GetColorU32(ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
		ImU32 slider_start_color = ImGui::GetColorU32(ImVec4(0.0f, 0.1f, 0.0f, 1.0f));
		ImU32 slider_end_color = ImGui::GetColorU32(ImVec4(0.0f, 0.5f, 1.0f, 1.0f));
		ImU32 slider_grab_color = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

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

		ImGui::GetWindowDrawList()->AddRectFilled(cursor_spos, ImVec2(cursor_spos.x + width, cursor_spos.y + height), slider_bg_color, height * 0.3f);
		float fill_width = (*value - v_min) / (float)(v_max - v_min) * width;
		ImGui::GetWindowDrawList()->AddRectFilled(
			cursor_spos,
			ImVec2(cursor_spos.x + fill_width, cursor_spos.y + height),
			IM_COL32(
				static_cast<int>(color.Value.x * 255.0f),
				static_cast<int>(color.Value.y * 255.0f),
				static_cast<int>(color.Value.z * 255.0f),
				static_cast<int>(alpha)
			),
			5.0f
		);

		ImGui::PopID();
		return is_item_clicked;
	}

	void RadioButtonGroup(const char* title, int* current_index, const char* const items[], int items_size)
	{
		ImGui::Text(title);

		for (int i = 0; i < items_size; ++i)
		{
			bool is_selected = (*current_index == i);

			ImGui::PushStyleColor(ImGuiCol_FrameBg, RadioButtonGroupColor.Value);
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, RadioButtonGroupHoverColor.Value);
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, RadioButtonGroupActiveColor.Value);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
			if (is_selected) ImGui::PushStyleColor(ImGuiCol_CheckMark, ImColor(255, 255, 255, 255).Value);

			if (ImGui::RadioButton(items[i], is_selected)) *current_index = i;

			ImGui::PopStyleColor(is_selected ? 4 : 3);
			ImGui::PopStyleVar(1);

			if (i < items_size - 1) ImGui::SameLine();
		}
	}

	void Hotkey(int* k, const ImVec2& size_arg = ImVec2(0, 0)) {
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
			if (ImGui::Button(label.c_str(), final_size)) {
				keyStates[k] = true;
			}
		}
		else {
			ImGui::Text("Waiting for Key...");
			Sleep(20);

			for (auto& Key : KeyCodes) {
				if (GetAsyncKeyState(Key) & 0x8000) {
					*k = Key;
					keyStates[k] = false;
					break;
				}
			}
		}
	}

	bool ComboBox(const char* label, const char* combo_items, int* current_index, const char* items[], int items_size, float roundness = 3.0f, float width = 200.0f)
	{
		ImGui::Text(label);
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ComboBoxColor.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ComboBoxActiveColor.Value);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ComboBoxHoverColor.Value);

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, roundness);

		ImGui::SetNextItemWidth(width);
		bool is_open = ImGui::BeginCombo("##", combo_items);

		if (is_open)
		{
			for (int i = 0; i < items_size; ++i)
			{
				bool is_selected = (i == *current_index);
				if (is_selected)
				{
					ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 215, 0).Value);
				}

				if (ImGui::Selectable(items[i], is_selected))
				{
					*current_index = i;
				}

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}

				if (is_selected)
				{
					ImGui::PopStyleColor();
				}
			}
			ImGui::EndCombo();
		}

		ImGui::PopStyleVar(1);
		ImGui::PopStyleColor(3);

		return is_open;
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
};