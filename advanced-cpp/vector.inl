#include <memory>
#include <expected>
#include <string_view>
#include <algorithm>
#include <stdexcept>
#include <ranges>

#include "vector.hpp"

namespace Custom {
  // Constructors and destructor
  template <typename T>
  Vector<T>::Vector() : _size(0), _capacity(0), _data(nullptr) {}

  template <typename T>
  Vector<T>::Vector(const Vector& other) : _size(other._size), _capacity(other._capacity), _data(allocate(_capacity)) {
    if (_size) {
      std::uninitialized_copy_n(other._data.get(), _size, _data.get());
    } 
  }

  template <typename T>
  Vector<T>::Vector(Vector&&) noexcept = default;

  template <typename T>
  Vector<T>::Vector(std::initializer_list<Vector<T>::value_type> ilist) : _size(ilist.size()), _capacity(ilist.size()), _data(allocate(_capacity)) {
    if (_size) {
      std::uninitialized_copy(ilist.begin(), ilist.end(), _data.get());
    }
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
  Vector<T>& Vector<T>::operator=(const Vector& other) {
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
  Vector<T>& Vector<T>::operator=(Vector&&) noexcept = default;
  
  // Element retrieval
  template <typename T>
  Vector<T>::reference Vector<T>::operator[](const Vector<T>::size_type index) noexcept {
    return _data.get()[index];
  }

  template <typename T>
  std::optional<typename Vector<T>::reference> Vector<T>::at(const Vector<T>::size_type index) const {
    if (index >= _size) {
      return std::nullopt;
    }

    return std::optional{ _data.get()[index] };
  }

  template <typename T>
  constexpr Vector<T>::reference Vector<T>::front() noexcept {
    return _data.get()[0];
  }

  template <typename T>
  constexpr Vector<T>::reference Vector<T>::back() noexcept {
    return _data.get()[_size - 1];
  }
  
  // Element modifiers
  template <typename T>
  template <typename U>
  requires std::convertible_to<U, T>
  void Vector<T>::push_back(U&& value) {
    if (_size == _capacity) {
      resize();
    }

    std::construct_at(_data.get() + _size++, std::forward<U>(value));
  }

  template <typename T>
  Vector<T>::value_type Vector<T>::pop_back() {
    if (this->empty()) {
      throw std::length_error("Vector is empty.");
    }

    Vector<T>::value_type val{ std::move(_data.get()[--_size]) };
    std::destroy_at(_data.get() + _size);

    return val;
  }

  template <typename T>
  void Vector<T>::resize() {
    Vector<T>::size_type new_capacity = _capacity ? _capacity * 2 : 1;
    auto new_storage{ allocate(new_capacity) };

    std::uninitialized_move_n(_data.get(), _size, new_storage.get());
    std::ranges::destroy_n(_data.get(), _size);

    _data = std::move(new_storage);
    _capacity = new_capacity;
  }

  template <typename T>
  std::unique_ptr<typename Vector<T>::value_type, typename Vector<T>::Deleter> Vector<T>::allocate(const typename Vector<T>::size_type n) const {
    return std::unique_ptr<Vector<T>::value_type, Vector<T>::Deleter>(
      static_cast<T*>(::operator new(sizeof(T) * n)),
      Vector<T>::Deleter{}
    );
  }
}
