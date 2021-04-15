#pragma once

#include <3rd_party/imgui/imgui.h>
#include <string>
#include <utility>
#include <vector>

namespace ImGuiHelper {

enum class Alignment : unsigned char {
  kHorizontalCenter = 1 << 0,
  kVerticalCenter = 1 << 1,
  kCenter = kHorizontalCenter | kVerticalCenter,
};

/**
 * @brief Render text with alignment
 */
inline void AlignedText(const std::string &text, Alignment align) {
  const auto alignment = static_cast<unsigned char>(align);
  const auto text_size = ImGui::CalcTextSize(text.c_str());
  const auto wind_size = ImGui::GetWindowSize();
  if (alignment & static_cast<unsigned char>(Alignment::kHorizontalCenter)) {
    ImGui::SetCursorPosX((wind_size.x - text_size.x) * 0.5f);
  }
  if (alignment & static_cast<unsigned char>(Alignment::kVerticalCenter)) {
    ImGui::SetCursorPosY((wind_size.y - text_size.y) * 0.5f);
  }

  ImGui::Text("%s", text.c_str());
}

inline bool CheckButton(const std::string &label, bool &checked,
                        const ImVec2 &size) {
  if (checked) {
    ImGui::PushStyleColor(ImGuiCol_Button, {0.6f, 0.6f, 0.6f, 1.0f});
  } else {
    ImGui::PushStyleColor(ImGuiCol_Button, {0.5f, 0.5f, 0.0f, 1.0f});
  }
  if (ImGui::Button(label.c_str(), size)) {
    checked = !checked;
  }

  ImGui::PopStyleColor();

  return checked;
}

inline int ButtonTab(std::vector<std::pair<std::string, bool>> &tab_names) {
  const auto tab_width = ImGui::GetContentRegionAvailWidth();
  const auto tab_btn_width = tab_width / tab_names.size();
  const auto h = ImGui::CalcTextSize("Ag").y;
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, 0});
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, h);
  for (int i = 0; i < tab_names.size(); ++i) {
    CheckButton(tab_names[i].first.c_str(), tab_names[i].second,
                ImVec2{tab_btn_width, 0});
    if (i != tab_names.size() - 1) {
      ImGui::SameLine();
    }
  }
  ImGui::PopStyleVar(2);

  return 1;
}
} // namespace ImGuiHelper