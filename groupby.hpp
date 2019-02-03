#include <vector>
#include <unordered_map>
#include <utility>


template <typename KeyType, typename ValueType>
using AnonymousGroupByResult = std::unordered_map<KeyType, std::vector<ValueType>>;


template <typename Iterable, typename KeyType>
AnonymousGroupByResult<KeyType, typename Iterable::value_type>
GroupBy(KeyType Iterable::value_type::*keyExtractor, const Iterable& iterable) {
    AnonymousGroupByResult<KeyType, typename Iterable::value_type> result;
    for (const auto& value : iterable) {
        result[value.*keyExtractor].push_back(value);
    }
    return result;
}


template <typename Iterable, typename KeyType>
AnonymousGroupByResult<KeyType, typename Iterable::value_type>
GroupBy(KeyType (Iterable::value_type::*keyExtractor)() const, const Iterable& iterable) {
    AnonymousGroupByResult<KeyType, typename Iterable::value_type> result;
    for (const auto& value : iterable) {
        result[(value.*keyExtractor)()].push_back(value);
    }
    return result;
}


template <typename Iterable, typename KeyType>
AnonymousGroupByResult<KeyType, typename Iterable::value_type>
GroupBy(KeyType (*keyExtractor)(const typename Iterable::value_type&), const Iterable& iterable) {
    AnonymousGroupByResult<KeyType, typename Iterable::value_type> result;
    for (const auto& value : iterable) {
        result[keyExtractor(value)].push_back(value);
    }
    return result;
}


#define DECLARE_NAMED_GROUP_BY_RESULT(ResultClassName, GroupName, Items)            \
template <typename KeyType, typename ValueType>                                     \
class ResultClassName : public AnonymousGroupByResult<KeyType, ValueType> {         \
 public:                                                                            \
  ResultClassName(const AnonymousGroupByResult<KeyType, ValueType>& obj)            \
    : AnonymousGroupByResult<KeyType, ValueType>(obj) {}                            \
                                                                                    \
  struct NamedPair :                                                                \
      public AnonymousGroupByResult<KeyType, ValueType>::value_type {               \
    const typename AnonymousGroupByResult<KeyType, ValueType>::key_type& GroupName; \
    typename AnonymousGroupByResult<KeyType, ValueType>::mapped_type& Items;        \
    NamedPair(                                                                      \
        const typename AnonymousGroupByResult<KeyType, ValueType>::value_type& obj) \
        : AnonymousGroupByResult<KeyType, ValueType>::value_type(obj),              \
          GroupName(this->first),                                                   \
          Items(this->second)                                                       \
          {}                                                                        \
  };                                                                                \
                                                                                    \
  class NamedIterator :                                                             \
      public AnonymousGroupByResult<KeyType, ValueType>::iterator {                 \
   public:                                                                          \
    NamedIterator(                                                                  \
        const typename AnonymousGroupByResult<KeyType, ValueType>::iterator& obj)   \
        : AnonymousGroupByResult<KeyType, ValueType>::iterator(obj) {}              \
                                                                                    \
    NamedPair operator*() {                                                         \
        return NamedPair(                                                           \
            AnonymousGroupByResult<KeyType, ValueType>::iterator::operator*() );    \
    }                                                                               \
  };                                                                                \
                                                                                    \
  NamedIterator begin() {                                                           \
    return NamedIterator(                                                           \
        AnonymousGroupByResult<KeyType, ValueType>::begin());                       \
  }                                                                                 \
                                                                                    \
  NamedIterator end() {                                                             \
    return NamedIterator(                                                           \
        AnonymousGroupByResult<KeyType, ValueType>::end());                         \
  }                                                                                 \
};
