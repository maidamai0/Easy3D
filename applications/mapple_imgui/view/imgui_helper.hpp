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
  const auto wind_size = ImGui::GetContentRegionAvail();
  if (alignment & static_cast<unsigned char>(Alignment::kHorizontalCenter)) {
    ImGui::SetCursorPosX((wind_size.x - text_size.x) * 0.5f);
  }
  if (alignment & static_cast<unsigned char>(Alignment::kVerticalCenter)) {
    ImGui::AlignTextToFramePadding();
  }

  ImGui::TextUnformatted(text.c_str());
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

inline void SwitchButton(std::string &&label, bool &checked) {
  float height = ImGui::GetFrameHeight();
  float width = height * 1.55f;
  float radius = height * 0.50f;
  const auto frame_width = ImGui::GetContentRegionAvailWidth();

  {
    // ImGui::PushFont(style::Font(style::Font::kSize1_5X));
    AlignedText(label.c_str(), Alignment::kVerticalCenter);
    // ImGui::PopFont();
  }
  ImGui::SameLine();

  ImGui::SetCursorPosX(frame_width - width);
  ImVec2 pos = ImGui::GetCursorScreenPos();
  if (ImGui::InvisibleButton(label.c_str(), ImVec2(width, height)))
    checked = !checked;
  ImU32 col_bg;
  if (checked) {
    col_bg = ImColor(ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
  } else {
    col_bg = ImColor(ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
  }
  ImDrawList *draw_list = ImGui::GetWindowDrawList();
  draw_list->AddRectFilled(pos, ImVec2(pos.x + width, pos.y + height), col_bg,
                           radius);
  draw_list->AddCircleFilled(
      ImVec2(checked ? (pos.x + width - radius) : (pos.x + radius),
             pos.y + radius),
      radius - 1.5f, IM_COL32_WHITE);
}

inline void Comb(std::string &&label, const std::vector<const char *> &items,
                 int &index) {
  const auto p_w = ImGui::GetContentRegionAvailWidth();
  ImGuiHelper::AlignedText(label.c_str(),
                           ImGuiHelper::Alignment::kVerticalCenter);
  ImGui::SameLine();
  ImGui::SetCursorPosX(p_w - 150.0f - ImGui::GetStyle().FramePadding.x);
  ImGui::SetNextItemWidth(150.0f);
  ImGui::Combo(label.c_str(), &index, items.data(), items.size());
}

} // namespace ImGuiHelper