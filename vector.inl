#include <memory>
#include <expected>
#include <string_view>

#include "vector.hpp"

namespace Custom {
  template <typename T>
  Vector<T>::Vector() : _size(0), _capacity(0), _data(nullptr) {}

  template <typename T>
  Vector<T>::~Vector() = default;

  template <typename T>
  size_t Vector<T>::size() const noexcept {
    return _size;
  }

  template <typename T>
  T Vector<T>::operator[] (const size_t index) noexcept {
    return _data[index];
  }

  template <typename T>
  std::expected<T, std::string_view> Vector<T>::at(const size_t index) const {
    if (index >= _size) {
      return std::unexpected<std::string_view>("Vector index out of range.");
    }

    return _data[index];
  }

  template <typename T>
  void Vector<T>::resize() {
    size_t new_capacity = _capacity ? _capacity * 2 : 1;
    std::unique_ptr<T[]> new_data{ std::make_unique<T[]>(new_capacity) };

    for (size_t i{}; i < _size; ++i) {
      new_data[i] = std::move(_data[i]);
    }

    _data = std::move(new_data);
    _capacity = new_capacity;
  }

  template <typename T>
  void Vector<T>::push_back(const T& value) {
    if (_size == _capacity) {
      resize();
    }

    _data[_size++] = value;
  }

  template <typename T>
  void Vector<T>::push_back(T&& value) {
    if (_size == _capacity) {
      resize();
    }

    _data[_size++] = std::move(value);
  }
}
