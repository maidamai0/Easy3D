#include "3rd_party/imgui/imgui.h"
#include "imgui_helper.hpp"
#include "state/state.h"
#include "view/style.hpp"
#include <string>
#include <utility>
#include <vector>

namespace RenderOptionsPanel {
void show() {
  ImGuiWindowFlags option_flags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
  const auto parent_size = ImGui::GetMainViewport()->WorkSize;
  const auto parent_pos = ImGui::GetMainViewport()->WorkPos;
  ImGui::SetNextWindowSize({AppState().RenderOptionsPanelWidth(),
                            parent_size.y - AppState().Margin() * 2});
  ImGui::SetNextWindowPos({parent_pos.x + parent_size.x -
                               AppState().RenderOptionsPanelWidth() -
                               AppState().Margin(),
                           parent_pos.y + AppState().Margin()});
  ImGui::SetNextWindowBgAlpha(0.5f);
  ImGui::Begin("RenderOptionsWindow", nullptr, option_flags);

  // title
  {
    ImGui::PushFont(style::Font(style::Font::kSize1_5X));
    ImGuiHelper::AlignedText("Render Options",
                             ImGuiHelper::Alignment::kHorizontalCenter);
    ImGui::PopFont();
  }

  // tabs
  ImGui::Dummy({0.0f, 10.f});
  static auto tabs = std::vector<std::string>{"Point", "Line", "Face"};
  static auto selected_index = 0;

  // detail options
  {
    const auto current_index = ImGuiHelper::ButtonTab(tabs, selected_index);
    selected_index = current_index;
    std::string text = tabs[current_index] + " Options";
    ImGuiHelper::AlignedText(text, ImGuiHelper::Alignment::kCenter);
  }

  ImGui::End();
}
} // namespace RenderOptionsPanel