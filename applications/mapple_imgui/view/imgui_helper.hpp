#pragma once

#include <3rd_party/imgui/imgui.h>
#include <algorithm>
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

inline bool CheckButton(const std::string &label, bool checked,
                        const ImVec2 &size) {
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                        ImGui::GetStyle().Colors[ImGuiCol_TabUnfocusedActive]);
  if (checked) {
    ImGui::PushStyleColor(ImGuiCol_Button,
                          ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
  } else {
    ImGui::PushStyleColor(ImGuiCol_Button,
                          ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive]);
  }
  if (ImGui::Button(label.c_str(), size)) {
    checked = !checked;
  }

  ImGui::PopStyleColor(2);

  return checked;
}

inline int ButtonTab(std::vector<std::string> &tabs, int &index) {
  auto checked = 1 << index;
  std::string tab_names;
  std::for_each(tabs.begin(), tabs.end(),
                [&tab_names](const auto item) { tab_names += item; });
  const auto tab_width = ImGui::GetContentRegionAvailWidth();
  const auto tab_btn_width = tab_width / tabs.size();
  const auto h = ImGui::CalcTextSize(tab_names.c_str()).y;
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, 0});
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, h);
  ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, h);

  ImGui::PushStyleColor(ImGuiCol_ChildBg,
                        ImGui::GetStyle().Colors[ImGuiCol_TitleBgActive]);
  ImGui::BeginChild(tab_names.c_str(),
                    {tab_width, h + ImGui::GetStyle().FramePadding.y * 2},
                    false,
                    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |
                        ImGuiWindowFlags_NoResize);

  for (int i = 0; i < tabs.size(); ++i) {
    auto &tab = tabs[i];

    // if current tab is checkd, uncheck otheres
    if (CheckButton(tab.c_str(), checked & (1 << i),
                    ImVec2{tab_btn_width, 0})) {
      checked = 0;
      checked = 1 << i;
    }

    if (i != tabs.size() - 1) {
      ImGui::SameLine();
    }
  }
  ImGui::PopStyleColor();
  ImGui::PopStyleVar(3);
  ImGui::EndChild();

  index = 0;
  while (checked / 2) {
    checked = checked / 2;
    ++index;
  }

  return index;
}
} // namespace ImGuiHelper