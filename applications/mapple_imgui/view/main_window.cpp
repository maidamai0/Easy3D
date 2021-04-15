/**
 * Copyright (C) 2015 by Liangliang Nan (liangliang.nan@gmail.com)
 * https://3d.bk.tudelft.nl/liangliang/
 *
 * This file is part of Easy3D. If it is useful in your research/work,
 * I would be grateful if you show your appreciation by citing it:
 * ------------------------------------------------------------------
 *      Liangliang Nan.
 *      Easy3D: a lightweight, easy-to-use, and efficient C++
 *      library for processing and rendering 3D data. 2018.
 * ------------------------------------------------------------------
 * Easy3D is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 3
 * as published by the Free Software Foundation.
 *
 * Easy3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "main_window.h"

#include <iostream>

#include <easy3d/core/point_cloud.h>
#include <easy3d/core/surface_mesh.h>
#include <easy3d/renderer/camera.h>
#include <easy3d/renderer/text_renderer.h>
#include <easy3d/util/file_system.h>

#include <3rd_party/glfw/include/GLFW/glfw3.h>
#include <3rd_party/imgui/backends/imgui_impl_glfw.h>
#include <3rd_party/imgui/backends/imgui_impl_opengl3.h>
#include <3rd_party/imgui/imgui.h>
#include <3rd_party/imgui/misc/fonts/imgui_fonts_droid_sans.h>

#include "render_options_panel.h"
#include "style.hpp"

namespace easy3d {

ImGuiContext *MainWindow::context_ = nullptr;

MainWindow::MainWindow(const std::string &title /* = "Easy3D ImGui Viewer" */,
                       int samples /* = 4 */, int gl_major /* = 3 */,
                       int gl_minor /* = 2 */, bool full_screen /* = false */,
                       bool resizable /* = true */, int depth_bits /* = 24 */,
                       int stencil_bits /* = 8 */
                       )
    : Viewer(title, samples, gl_major, gl_minor, full_screen, resizable,
             depth_bits, stencil_bits),
      alpha_(0.8f), movable_(true) {
  camera()->setUpVector(vec3(0, 1, 0));
  camera()->setViewDirection(vec3(0, 0, -1));
  camera_->showEntireScene();
  set_background_color({1.0f, 1.0f, 1.0f, 1.0f});
}

void MainWindow::init() {
  Viewer::init();

  if (!context_) {
    // Setup ImGui binding
    IMGUI_CHECKVERSION();

    context_ = ImGui::CreateContext();

    const char *glsl_version = "#version 150";
    ImGui_ImplGlfw_InitForOpenGL(window_, false);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGuiIO &io = ImGui::GetIO();
    // io.WantCaptureKeyboard = true;
    io.WantTextInput = true;
    io.IniFilename = nullptr;
    style::init_style(pixel_ratio(), dpi_scaling());
  }
}

float MainWindow::pixel_ratio() {
  // Computes pixel ratio for hidpi devices
  int fbo_size[2], win_size[2];
  glfwGetFramebufferSize(window_, &fbo_size[0], &fbo_size[1]);
  glfwGetWindowSize(window_, &win_size[0], &win_size[1]);
  return static_cast<float>(fbo_size[0]) / static_cast<float>(win_size[0]);
}

void MainWindow::post_resize(int w, int h) {
  Viewer::post_resize(w, h);
  if (context_) {
    ImGui::GetIO().DisplaySize.x = float(w);
    ImGui::GetIO().DisplaySize.y = float(h);
  }
}

bool MainWindow::callback_event_cursor_pos(double x, double y) {
  if (ImGui::GetIO().WantCaptureMouse)
    return true;
  else
    return Viewer::callback_event_cursor_pos(x, y);
}

bool MainWindow::callback_event_mouse_button(int button, int action,
                                             int modifiers) {
  if (ImGui::GetIO().WantCaptureMouse)
    return true;
  else
    return Viewer::callback_event_mouse_button(button, action, modifiers);
}

bool MainWindow::callback_event_keyboard(int key, int action, int modifiers) {
  if (ImGui::GetIO().WantCaptureKeyboard)
    return true;
  else
    return Viewer::callback_event_keyboard(key, action, modifiers);
}

bool MainWindow::callback_event_character(unsigned int codepoint) {
  if (ImGui::GetIO().WantCaptureKeyboard)
    return true;
  else
    return Viewer::callback_event_character(codepoint);
}

bool MainWindow::callback_event_scroll(double dx, double dy) {
  if (ImGui::GetIO().WantCaptureMouse)
    return true;
  else
    return Viewer::callback_event_scroll(dx, dy);
}

void MainWindow::cleanup() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();

  ImGui::DestroyContext(context_);

  Viewer::cleanup();
}

void MainWindow::pre_draw() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  Viewer::pre_draw();
}

void MainWindow::post_draw() {
  ImGui::ShowDemoWindow();
  ImGui::ShowMetricsWindow();

  // static bool show_overlay = true;
  // if (show_overlay)
  //   draw_overlay(&show_overlay);

  static bool show_about = false;
  if (show_about) {
    ImGui::SetNextWindowPos(ImVec2(width() * 0.5f, height() * 0.5f),
                            ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::Begin("About Easy3D ImGui Viewer", &show_about,
                 ImGuiWindowFlags_NoResize);
    ImGui::Text("This viewer shows how to use ImGui for GUI creation and event "
                "handling");
    ImGui::Separator();
    ImGui::Text("\n"
                "Liangliang Nan\n"
                "liangliang.nan@gmail.com\n"
                "https://3d.bk.tudelft.nl/liangliang/\n");
    ImGui::End();
  }

  static bool show_manual = false;
  if (show_manual) {
    int w, h;
    glfwGetWindowSize(window_, &w, &h);
    ImGui::SetNextWindowPos(ImVec2(w * 0.5f, h * 0.5f), ImGuiCond_FirstUseEver,
                            ImVec2(0.5f, 0.5f));
    ImGui::Begin("Easy3D Manual", &show_manual, ImGuiWindowFlags_NoResize);
    ImGui::Text("%s", usage().c_str());
    ImGui::End();
  }

  if (ImGui::BeginMainMenuBar()) {
    draw_menu_file();

    draw_menu_view();

    if (ImGui::BeginMenu("Help")) {
      ImGui::MenuItem("Manual", nullptr, &show_manual);
      ImGui::Separator();
      ImGui::MenuItem("About", nullptr, &show_about);
      ImGui::EndMenu();
    }
    menu_height_ = ImGui::GetWindowHeight();
    ImGui::Text("Frame rate: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("GPU time (ms): %s", gpu_time_);
    float x = ImGui::GetIO().MousePos.x;
    float y = ImGui::GetIO().MousePos.y;
    ImGui::Text("Mouse Position: (%i, %i)", static_cast<int>(x),
                static_cast<int>(y));
    ImGui::EndMainMenuBar();
  }

  RenderOptionsPanel::show();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  auto texter = texter_;
  texter_ = nullptr;
  Viewer::post_draw();
  texter_ = texter;
}

void MainWindow::draw_menu_file() {

  if (ImGui::BeginMenu("File")) {
    if (ImGui::MenuItem("Open", "Ctrl+O"))
      open();
    if (ImGui::MenuItem("Save As...", "Ctrl+S"))
      save();
    ImGui::Separator();
    if (ImGui::MenuItem("Quit", "Alt+F4"))
      glfwSetWindowShouldClose(window_, GLFW_TRUE);

    ImGui::EndMenu();
  }
}

void MainWindow::draw_menu_view() {
  if (ImGui::BeginMenu("View")) {
    if (ImGui::MenuItem("Snapshot", nullptr))
      snapshot();

    ImGui::Separator();
    if (ImGui::BeginMenu("Options")) {
      ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);
      ImGui::Checkbox("Panel Movable", &movable_);
      ImGui::ColorEdit3("Background Color", (float *)background_color_,
                        ImGuiColorEditFlags_NoInputs);
      ImGui::DragFloat("Transparency", &alpha_, 0.005f, 0.0f, 1.0f, "%.1f");
      ImGui::PopItemWidth();
      ImGui::EndMenu();
    }

    ImGui::EndMenu();
  }
}
} // namespace easy3d
