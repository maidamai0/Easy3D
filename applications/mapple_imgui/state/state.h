#pragma once

#include <string>

#include "lay_out.hpp"
#include "settings.h"

#include "common/singleton.hpp"

namespace state {
class State {
  friend class Singleton<State>;
  State();
  State(const State &) = delete;
  State(State &&) = delete;
  State &operator=(const State &) = delete;
  State &operator=(State &&) = delete;

public:
  // settings
  auto LogLevel() const { return settings_.log_level_; }
  const auto &LogPath() const { return settings_.log_file_path_; }

  // layout
  auto RenderOptionsPanelWidth() const {
    return layout_.render_options_panel_idth_;
  }

  auto Margin() const { return layout_.margin_; }
  auto TabHeight() const { return layout_.tab_width_; }

private:
  Settings settings_;
  Layout layout_;
};
} // namespace state

inline auto &AppState() { return Singleton<state::State>::GetInstance(); }