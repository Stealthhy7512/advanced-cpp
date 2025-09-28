#ifndef CUSTOM_VECTOR_HPP
#define CUSTOM_VECTOR_HPP

#include <memory>
#include <expected>
#include <string_view>
#include <optional>

namespace Custom {
  template <typename T>
  class Vector {
  public:
    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using iterator = T*;
    using const_iterator = const iterator;

    Vector();
    Vector(const Vector& other);
    Vector(Vector&&) noexcept;
    Vector(std::initializer_list<value_type> ilist);
    ~Vector();

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&&) noexcept;
    
    constexpr size_type size() const noexcept;
    constexpr size_type capacity() const noexcept;
    
    reference operator[](const size_type index) noexcept;
    std::optional<reference> at(const size_type index) const;
    
    template <typename U>
    requires std::convertible_to<U, T>
    void push_back(U&& value);
    value_type pop_back();

    constexpr bool empty() const noexcept;

    // FIXME: with reference wrapped std::expected, return unexpected on contract violation
    constexpr reference front() noexcept;
    constexpr reference back() noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;

    // TODO: add iterators, efficient shrinking, insert/delete etc., push another iterator,
    // pointer types, const methods, clear, default inserted constructor
    // vector comparison
    
  private:
    struct RawDeleter {
      void operator()(T* ptr) const noexcept {
        ::operator delete(ptr);
      }
    };
    using Deleter = RawDeleter;

    size_type _size;
    size_type _capacity;
    std::unique_ptr<T, Deleter> _data;

    void grow();
    std::unique_ptr<value_type, Deleter> allocate(size_type n) const;
  };
}

#include "vector.inl"

#endif