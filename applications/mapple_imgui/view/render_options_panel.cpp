#include "3rd_party/imgui/imgui.h"
#include "imgui_helper.hpp"
#include "state/state.h"
#include "view/style.hpp"
#include <string>
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
  {
    std::vector<std::string> tab_names{"Point", "Line", "Face"};
    const auto tab_width =
        AppState().RenderOptionsPanelWidth() - AppState().Margin() * 10;
    const auto tab_btn_width =
        (tab_width - AppState().Margin() * 2) / tab_names.size();
    ImGui::BeginChild(
        "RenderOptionsWindow_Tab",
        {AppState().RenderOptionsPanelWidth() - AppState().Margin() * 10,
         AppState().TabHeight()},
        true, option_flags | ImGuiWindowFlags_NoScrollbar);

    ImGui::SetCursorPosX(AppState().Margin());
    for (int i = 0; i < tab_names.size(); ++i) {
      ImGui::SetCursorPosX(tab_btn_width * i);
      ImGui::Text("%s", tab_names[i].c_str());
      if (i != tab_names.size() - 1) {
        ImGui::SameLine();
      }
    }
    ImGui::EndChild();
  }

  ImGui::End();
}
} // namespace RenderOptionsPanel