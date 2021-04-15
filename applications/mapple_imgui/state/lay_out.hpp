#pragma once

namespace state {
class Layout {
  friend class State;
  float render_options_panel_idth_ = 300;
  float margin_ = 5;
  float tab_width_ = 20;
};

} // namespace state
