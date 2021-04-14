#include "3rd_party/imgui/imgui.h"
#include "imgui_helper.hpp"
#include "state/state.h"

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
    // ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));
    // ImGui::SetNextWindowSize({AppState().RenderOptionsPanelWidth(), 30});
    // ImGui::BeginChild("RenderOptionsWindow_title");
    ImGuiHelper::AlignedText("Options",
                             ImGuiHelper::Alignment::kHorizontalCenter);
    // ImGui::PopStyleColor();
    // ImGui::EndChild();
  }

  ImGui::End();
}
} // namespace RenderOptionsPanel