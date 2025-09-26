#include <memory>
#include <expected>
#include <string_view>
#include <algorithm>
#include <stdexcept>

#include "vector.hpp"

namespace Custom {
  // Constructors and destructor
  template <typename T>
  Vector<T>::Vector() : _size(0), _capacity(0), _data(nullptr) {}

  template <typename T>
  Vector<T>::Vector(const Vector& other) : _size(other._size), _capacity(other._capacity) {
    if (_capacity > 0) {
      _data = std::unique_ptr<T, Vector<T>::Deleter>(
        static_cast<T*>(::operator new(sizeof(T) * _capacity)), 
        Deleter{}
      );
      
      std::uninitialized_copy(other._data.get(), other._data.get() + _size, _data.get());
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
  Vector<T>::Vector(std::initializer_list<Vector<T>::value_type> ilist) : _size(ilist.size()), _capacity(ilist.size()) {
    if (_capacity > 0) {
    _data = std::unique_ptr<T, Vector<T>::Deleter>(
      static_cast<T*>(::operator new(sizeof(T) * _capacity)),
      Deleter{}
    );

    std::uninitialized_copy(ilist.begin(), ilist.end(), _data.get());
    } else {
      _data = nullptr;
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
  Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
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
  
  template <typename T>
  void Vector<T>::resize() {
    Vector<T>::size_type new_capacity = _capacity ? _capacity * 2 : 1;
    auto new_storage{ std::unique_ptr<Vector<T>::value_type, Vector<T>::Deleter>(
      static_cast<T*>(::operator new(sizeof(T)* new_capacity)),
      Deleter{}
      ) };

    std::uninitialized_move(_data.get(), _data.get() + _size, new_storage.get());
    std::destroy(_data.get(), _data.get() + _size);

    _data = std::move(new_storage);
    _capacity = new_capacity;
  }

  // Element modifiers
  template <typename T>
  template <typename U>
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

}
