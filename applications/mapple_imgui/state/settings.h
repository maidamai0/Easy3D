#pragma once

#include <string>
namespace state {

class State;

/**
 * @brief settings of application, can only be accessd from \sa State
 *
 */
class Settings {
  friend class State;
  Settings();
  Settings(const Settings &) = delete;
  Settings(Settings &&) = delete;
  Settings &operator=(const Settings &) = delete;
  Settings &operator=(Settings &&) = delete;

  void load_from_file();

  // TODO (tonghao): make this configurable 2021-04-11
  int log_level_ = 9;
  std::string log_file_path_;
};
} // namespace state