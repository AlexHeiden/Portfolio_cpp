#ifndef FACTORIAL_CONTAINER_HPP
#define FACTORIAL_CONTAINER_HPP

#include <iterator>

class FactorialContainer
{
public:
  class const_iterator : public std::iterator<std::bidirectional_iterator_tag,
      size_t,
      std::ptrdiff_t,
      size_t*,
      size_t>
  {
  public:
    value_type operator*() const;
    const_iterator& operator++();
    const_iterator operator++(int);
    const_iterator& operator--();
    const_iterator operator--(int);
    bool operator==(const const_iterator& iterator) const;
    bool operator!=(const const_iterator& iterator) const;

  protected:
    friend FactorialContainer;
    size_t index_;
    value_type value_;
    const size_t endIndex_;

  private:
    const_iterator(const size_t index, const value_type value, const size_t endIndex);
  };

  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  FactorialContainer();
  FactorialContainer(const size_t lastElementIndex);

  const_iterator begin() const;
  const_iterator end() const;

  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

private:
  size_t lastElementIndex_;
  const_iterator::value_type endValue_;
};
#endif
