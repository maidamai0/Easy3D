#pragma once

#include <string>

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
  auto LogLevel() const { return settings_.log_level_; }
  const auto &LogPath() const { return settings_.log_file_path_; }

private:
  Settings settings_;
};
} // namespace state

inline auto &AppState() { return Singleton<state::State>::GetInstance(); }