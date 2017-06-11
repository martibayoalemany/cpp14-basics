#include <type_traits>

// Workaround for a gcc 4.7 and 4.8 c++ standard change incompatibility
// https://stackoverflow.com/questions/12702103/writing-code-that-works-when-has-trivial-destructor-is-defined-instead-of-is
namespace std
{
  template<typename> struct has_trivial_destructor;
  template<typename> struct is_trivially_destructible;
}

template<typename T>
  class have_cxx11_trait_helper
  {
    template<typename T2, bool = std::is_trivially_destructible<T2>::type::value>
      static std::true_type test(int);

    template<typename T2, bool = std::has_trivial_destructor<T2>::type::value>
      static std::false_type test(...);

  public:
    typedef decltype(test<T>(0)) type;
  };

template<typename T>
  struct have_cxx11_trait : have_cxx11_trait_helper<T>::type
  { };

template<typename T>
  using is_trivially_destructible
    = typename std::conditional<have_cxx11_trait<T>::value,
                                std::is_trivially_destructible<T>,
                                std::has_trivial_destructor<T>>::type;
