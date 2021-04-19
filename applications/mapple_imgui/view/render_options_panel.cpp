#include "3rd_party/imgui/imgui.h"

#include "fork_awesome.h"
#include "global_render_options.h"
#include "imgui_helper.hpp"
#include "line_render_options.h"
#include "points_render_options.h"
#include "state/state.h"
#include "surface_render_options.h"
#include "view/style.hpp"

#include <array>
#include <functional>
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
  ImGui::Begin("RenderOptionsWindow", nullptr,
               option_flags | ImGuiWindowFlags_NoScrollbar);

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
  ImGuiHelper::ButtonTab(tabs, selected_index);

  // detail options
  {
    ImGui::BeginChild("detailoptions", {0, 0}, false, option_flags);

    ImGui::Dummy({0, 10});
    using func = std::function<void()>;
    static std::array<func, 4> options{
        SurfaceRenderOptions::show, LineRenderOptions::show,
        PointsRenderOptions::show, GlobRenderOptions::show};
    options[selected_index]();
    ImGui::EndChild();
  }

  ImGui::End();
}
} // namespace RenderOptionsPanel