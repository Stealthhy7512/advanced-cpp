#ifndef CUSTOM_VECTOR_HPP
#define CUSTOM_VECTOR_HPP

#include <memory>
#include <expected>
#include <string_view>

namespace Custom {
  template <typename T>
  class Vector {
  public:
    Vector();
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    Vector& operator=(const Vector& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;
    
    size_t size() const noexcept;
    size_t capacity() const noexcept;
    
    T operator[](const size_t index) const noexcept;
    std::expected<T, std::string_view> at(const size_t index) const;
    
    void push_back(const T& value);
    void push_back(T&& value);

    bool empty() const noexcept;

    T& front() const noexcept;
    T& back() const noexcept;

    // TODO add iterators, efficient shrinking, insert/delete etc., pop_back, push another iterator,
    // pointer types, const methods, clear, initializer list constructor, default inserted constructor
    // vector comparison
    
  private:
    size_t _size;
    size_t _capacity;
    std::unique_ptr<T[]> _data;
    
    void resize() noexcept;
  };
}

#include "vector.inl"

#endif