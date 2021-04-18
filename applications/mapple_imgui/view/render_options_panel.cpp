#include "3rd_party/imgui/imgui.h"

#include "fork_awesome.h"
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
  static auto tabs =
      std::vector<std::string>{"Surface", "Line", "Points", "Global"};
  static auto selected_index = 0;

  // detail options
  {
    ImGuiHelper::ButtonTab(tabs, selected_index);
    std::string text = tabs[selected_index] + " Options " + ICON_FK_COG;
    ImGuiHelper::AlignedText(text, ImGuiHelper::Alignment::kCenter);

    static bool visible = true;
    ImGuiHelper::SwitchButton("Visible", visible);
  }

  ImGui::End();
}
} // namespace RenderOptionsPanel