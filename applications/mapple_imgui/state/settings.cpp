#pragma once

#include "settings.h"
#include "common/log.hpp"

namespace state {
Settings::Settings() { load_from_file(); }

void Settings::load_from_file(){
    // TODO (tonghao): complete this 2021-04-11
};
} // namespace state
