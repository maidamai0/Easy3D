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

#pragma once

#include <easy3d/viewer/viewer.h>

// A very good tutorial for imgui:
// https://eliasdaler.github.io/using-imgui-with-sfml-pt1/
// https://eliasdaler.github.io/using-imgui-with-sfml-pt2/

struct ImGuiContext;

namespace easy3d {

class MainWindow : public Viewer {
public:
  MainWindow();

protected:
  // imgui plugins
  void init() override;

  // draw the widgets
  void pre_draw() override;

  //  the widgets
  void post_draw() override;

  void cleanup() override;

  void post_resize(int w, int h) override;

  bool callback_event_cursor_pos(double x, double y) override;
  bool callback_event_mouse_button(int button, int action,
                                   int modifiers) override;
  bool callback_event_keyboard(int key, int action, int modifiers) override;
  bool callback_event_character(unsigned int codepoint) override;
  bool callback_event_scroll(double dx, double dy) override;

  void draw_menu_file();
  void draw_menu_view();

private:
  // Ratio between the framebuffer size and the window size.
  // May be different from the DPI scaling!
  float pixel_ratio();

  float widget_scaling() { return dpi_scaling() / pixel_ratio(); }

private:
  // Single global context by default, but can be overridden by the user
  static ImGuiContext *context_;

  // Global variables for all the windows
  float alpha_;
  bool movable_;
  float menu_height_;
};

} // namespace easy3d