#ifndef CUSTOM_VECTOR_HPP
#define CUSTOM_VECTOR_HPP

#include <memory>
#include <expected>
#include <string_view>

namespace Custom {
  template <typename T>
  class Vector {
  public:
    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;

    Vector();
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    constexpr Vector& operator=(const Vector& other);
    constexpr Vector& operator=(Vector&& other) noexcept;
    
    constexpr size_type size() const noexcept;
    constexpr size_type capacity() const noexcept;
    
    reference operator[](const size_type index) noexcept;
    std::expected<T, std::string_view> at(const size_type index) const; // change return to reference
    
    constexpr void push_back(const reference value);
    constexpr void push_back(T&& value);

    constexpr bool empty() const noexcept;

    // FIXME: with reference wrapped std::expected, return unexpected on contract violation
    constexpr reference front() noexcept;
    constexpr reference back() noexcept;

    // TODO: add iterators, efficient shrinking, insert/delete etc., pop_back, push another iterator,
    // pointer types, const methods, clear, initializer list constructor, default inserted constructor
    // vector comparison
    
  private:
    size_type _size;
    size_type _capacity;
    std::unique_ptr<T[]> _data;
    
    void resize();
  };
}

#include "vector.inl"

#endif