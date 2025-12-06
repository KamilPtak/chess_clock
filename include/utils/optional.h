#pragma once

#include <new>

template <typename T> class optional {
private:
  union {
    char buffer[sizeof(T)];
    T value_storage;
  };
  bool has_value_ = false;

  T &get_value_ref() noexcept { return *reinterpret_cast<T *>(buffer); }
  const T &get_value_ref() const noexcept {
    return *reinterpret_cast<const T *>(buffer);
  }

public:
  optional() noexcept {}
  explicit optional(const T &val) { emplace(val); }
  optional(const optional &other) {
    if (other.has_value_) {
      emplace(other.get_value_ref());
    }
  }

  optional &operator=(const optional &other) {
    if (this != &other) {
      reset();
      if (other.has_value_) {
        emplace(other.get_value_ref());
      }
    }
    return *this;
  }

  ~optional() { reset(); }

  /**
   * @brief Checks if the optional contains a value.
   * @return true if a value is present, false otherwise.
   */
  bool has_value() const noexcept { return has_value_; }

  /**
   * @brief Returns the contained value.
   */
  T &value() { return get_value_ref(); }

  const T &value() const { return get_value_ref(); }

  /**
   * @brief Returns the contained value if present, otherwise returns the
   * provided default value.
   */
  T value_or(const T &default_value) const {
    if (has_value_) {
      return get_value_ref();
    } else {
      return default_value;
    }
  }

  explicit operator bool() const noexcept { return has_value_; }

  void emplace(const T &val) {
    reset();

    new (buffer) T(val);
    has_value_ = true;
  }

  void reset() noexcept {
    if (has_value_) {
      get_value_ref().~T();
      has_value_ = false;
    }
  }

  T *operator->() { return &get_value_ref(); }
  const T *operator->() const { return &get_value_ref(); }

  T &operator*() { return get_value_ref(); }
  const T &operator*() const { return get_value_ref(); }
};