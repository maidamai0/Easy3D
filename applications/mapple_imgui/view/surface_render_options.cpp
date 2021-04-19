#include "fork_awesome.h"
#include "imgui.h"
#include "imgui_helper.hpp"

namespace SurfaceRenderOptions {
void show() {
  ImGui::Separator();

  {
    static bool visible = true;
    ImGuiHelper::SwitchButton(std::string(ICON_FK_EYE) + "    Visible",
                              visible);
    ImGui::Separator();
  }

  for (int i = 0; i < 1000; ++i) {
    ImGuiHelper::AlignedText("Surface settings",
                             ImGuiHelper::Alignment::kCenter);
    ImGui::Separator();
  }
}
} // namespace SurfaceRenderOptions