#ifndef POLICIES_HPP
#define POLICIES_HPP

template <typename Collection>
struct SquareBracketsOperatorPolicy
{
  typedef typename Collection::value_type ValueType;
  typedef typename Collection::size_type Iterator;

  static ValueType& element(Collection& collection, const Iterator index)
  {
    return collection[index];
  }

  static Iterator begin(const Collection&)
  {
    return 0;
  }

  static Iterator end(const Collection& collection)
  {
    return collection.size();
  }
};

template <typename Collection>
struct AtMethodPolicy
{
  typedef typename Collection::value_type ValueType;
  typedef typename Collection::size_type Iterator;

  static ValueType& element(Collection& collection, const Iterator index)
  {
    return collection.at(index);
  }

  static Iterator begin(const Collection&)
  {
    return 0;
  }

  static Iterator end(const Collection& collection)
  {
    return collection.size();
  }
};

template <typename Collection>
struct IteratorPolicy
{
  typedef typename Collection::value_type ValueType;
  typedef typename Collection::iterator Iterator;

  static ValueType& element(Collection&, const Iterator& index)
  {
    return *index;
  }

  static Iterator begin(Collection& collection)
  {
    return collection.begin();
  }

  static Iterator end(Collection& collection)
  {
    return collection.end();
  }
};

#endif
