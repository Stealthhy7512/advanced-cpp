#include <memory>
#include <expected>
#include <string_view>
#include <algorithm>

#include "vector.hpp"

namespace Custom {
  template <typename T>
  Vector<T>::Vector() : _size(0), _capacity(0), _data(nullptr) {}

  template <typename T>
  Vector<T>::Vector(const Vector& other) : _size(other._size), _capacity(other._capacity) {
    if (_capacity > 0) {
      _data = std::make_unique<T[]>(_capacity);

      std::copy(other._data.get(), other._data.get() + other._size, _data.get());
    } else {
      _data = nullptr;
    }
  }

  template <typename T>
  Vector<T>::Vector(Vector&& other) noexcept : _size(other._size), _capacity(other._capacity), _data(std::move(other._data)) {
    other._size = 0;
    other._capacity = 0;
  }

  template <typename T>
  Vector<T>::~Vector() = default;

  template <typename T>
  size_t Vector<T>::size() const noexcept {
    return _size;
  }

  template <typename T>
  Vector<T>& Vector<T>::operator=(const Vector& other) noexcept {
    if (this == &other) {
      return *this;
    }

    Vector temp(other);
    std::swap(_size, temp._size);
    std::swap(_capacity, temp._capacity);
    std::swap(_data, temp._data);

    return *this;
  }

  template <typename T>
  Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
      Vector<T> temp(std::move(other));
      std::swap(*this, temp);
    }

    return *this;
  }

  template <typename T>
  T Vector<T>::operator[](const size_t index) const noexcept {
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
  bool Vector<T>::empty() const noexcept {
    return _size == 0;
  }

  template <typename T>
  T& Vector<T>::front() const noexcept {
    return _data[0];
  }

  template <typename T>
  T& Vector<T>::back() const noexcept {
    return _data[_size - 1];
  }

  template <typename T>
  void Vector<T>::resize() noexcept {
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
