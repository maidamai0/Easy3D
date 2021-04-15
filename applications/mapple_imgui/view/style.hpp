#pragma once

#include "3rd_party/imgui/imgui.h"
#include "view/style.hpp"
#include <3rd_party/imgui/backends/imgui_impl_opengl3.h>
#include <3rd_party/imgui/misc/fonts/imgui_fonts_droid_sans.h>

#include <unordered_map>

namespace style {
enum class Font { kDefault, kSize1_5X };

namespace details {
constexpr auto kDefauleFontSize = 15;
} // namespace details

inline auto *Font(const Font font) {
  return ImGui::GetIO().Fonts->Fonts[static_cast<int>(font)];
}

inline void reload_font(const float pixel_ratio, const float dpi_scaling) {
  ImGuiIO &io = ImGui::GetIO();
  io.Fonts->Clear();
  io.Fonts->AddFontFromMemoryCompressedTTF(
      droid_sans_compressed_data, droid_sans_compressed_size,
      details::kDefauleFontSize * dpi_scaling);
  io.Fonts->AddFontFromMemoryCompressedTTF(
      droid_sans_compressed_data, droid_sans_compressed_size,
      details::kDefauleFontSize * dpi_scaling * 1.5f);

  io.FontGlobalScale = 1.0F / pixel_ratio;

  ImGui_ImplOpenGL3_DestroyDeviceObjects();
}

inline void init_style(const float pixel_ratio, const float dpi_scaling) {
  ImGui::StyleColorsLight();
  ImGuiStyle &style = ImGui::GetStyle();
  style.FrameRounding = 5.0f;
  style.ChildRounding = 5.0f;
  style.GrabRounding = 5.0f;
  style.PopupRounding = 5.0f;
  style.ScrollbarRounding = 5.0f;
  style.TabRounding = 5.0f;
  style.WindowRounding = 5.0f;
  style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

  // load font
  reload_font(pixel_ratio, dpi_scaling);
}

} // namespace style