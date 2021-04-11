#pragma once

/**
 * @brief Ceate a Singleton
 * ```cpp
 * class S {
 * friend class Singleton<S>;
 };
 * ```
 * @tparam T
 */
template <typename T> class Singleton {
public:
  static T &GetInstance() {
    static T instance{};
    return instance;
  }
};