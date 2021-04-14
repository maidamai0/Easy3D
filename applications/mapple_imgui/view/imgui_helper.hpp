#pragma once

#include <3rd_party/imgui/imgui.h>
#include <string>

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
} // namespace ImGuiHelper