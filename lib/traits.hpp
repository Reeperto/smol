#include <type_traits>

namespace smol
{

template <typename, typename = void>
struct is_specialized : std::false_type
{
};

template <typename T>
struct is_specialized<T, std::void_t<decltype(T{})>> : std::true_type
{
};

} // namespace smol
