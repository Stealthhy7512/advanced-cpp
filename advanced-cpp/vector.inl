#include <memory>
#include <expected>
#include <string_view>
#include <algorithm>

#include "vector.hpp"

namespace Custom {
  // Constructors and destructor
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

  // Size methods
  template <typename T>
  constexpr Vector<T>::size_type Vector<T>::size() const noexcept {
    return _size;
  }

  template <typename T>
  constexpr Vector<T>::size_type Vector<T>::capacity() const noexcept {
    return _capacity;
  }

  template <typename T>
  constexpr bool Vector<T>::empty() const noexcept {
    return _size == 0;
  }

  // Assignment operators
  template <typename T>
  constexpr Vector<T>& Vector<T>::operator=(const Vector& other) {
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
  constexpr Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
      _size = other._size;
      _capacity = other._capacity;
      _data = std::move(other._data);

      other._size = 0;
      other._capacity = 0;
    }

    return *this;
  }

  // Element retrieval
  template <typename T>
  Vector<T>::reference Vector<T>::operator[](const Vector<T>::size_type index) noexcept {
    return _data[index];
  }

  template <typename T>
  std::expected<typename Vector<T>::value_type, std::string_view> Vector<T>::at(const Vector<T>::size_type index) const {
    if (index >= _size) {
      return std::unexpected<std::string_view>("Vector index out of range.");
    }

    return _data[index];
  }

  template <typename T>
  constexpr Vector<T>::reference Vector<T>::front() noexcept {
    return _data[0];
  }

  template <typename T>
  constexpr Vector<T>::reference Vector<T>::back() noexcept {
    return _data[_size - 1];
  }

  template <typename T>
  void Vector<T>::resize() {
    Vector<T>::size_type new_capacity = _capacity ? _capacity * 2 : 1;
    std::unique_ptr<Vector<T>::value_type[]> new_data{ std::make_unique<Vector<T>::value_type[]>(new_capacity) };

    for (Vector<T>::size_type i{}; i < _size; ++i) {
      new_data[i] = std::move(_data[i]);
    }

    _data = std::move(new_data);
    _capacity = new_capacity;
  }

  // Element modifiers
  template <typename T>
  constexpr void Vector<T>::push_back(const Vector<T>::reference value) {
    if (_size == _capacity) {
      resize();
    }

    _data[_size++] = value;
  }

  template <typename T>
  constexpr void Vector<T>::push_back(T&& value) {
    if (_size == _capacity) {
      resize();
    }

    _data[_size++] = std::move(value);
  }
}
