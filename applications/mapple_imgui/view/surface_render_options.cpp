#include "fork_awesome.h"
#include "imgui.h"
#include "imgui_helper.hpp"
#include <array>
#include <string>
#include <vector>

namespace SurfaceRenderOptions {
void show() {
  ImGui::Separator();

  {

    static auto index = 0;
    std::vector<const char *> items{"faces", "lines"};
    ImGuiHelper::Comb(std::string(ICON_FK_CUBE) + "    Drawables", items,
                      index);
    ImGui::Separator();
  }

  {
    static bool visible = true;
    ImGuiHelper::SwitchButton(std::string(ICON_FK_EYE) + "    Visible",
                              visible);
    ImGui::Separator();
  }

  {

    static bool phong_shading = true;
    ImGuiHelper::SwitchButton(
        std::string(ICON_FK_LIGHTBULB_O) + "    Phong Shading", phong_shading);
    ImGui::Separator();
  }

  {

    static auto index = 0;
    std::vector<const char *> items{"front", "back", "front and back"};
    ImGuiHelper::Comb(std::string(ICON_FK_SUN_O) + "    Lighting", items,
                      index);
    ImGui::Separator();
  }

  {

    static auto index = 0;
    std::vector<const char *> items{"uniform color", "scalar - f:chart"};
    ImGuiHelper::Comb(std::string(ICON_FK_FLASK) + "    Coloring", items,
                      index);
    ImGui::Separator();

    {
      ImGuiHelper::AlignedText(std::string(ICON_FK_EYEDROPPER) +
                                   "    Default Color",
                               ImGuiHelper::Alignment::kVerticalCenter);
      ImGui::SameLine();
      static ImColor font_color;
      ImGui::ColorEdit4("MyColor##default", (float *)&font_color,
                        ImGuiColorEditFlags_NoInputs |
                            ImGuiColorEditFlags_NoLabel);
      ImGui::Separator();
    }
  }

  {
    for (int i = 0; i < 10; ++i) {
      ImGuiHelper::AlignedText("Options", ImGuiHelper::Alignment::kCenter);
      ImGui::Separator();
    }
  }
}
} // namespace SurfaceRenderOptions