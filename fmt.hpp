#pragma once
#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#endif
#ifndef FMT_USE_WINDOWS_H
#define FMT_USE_WINDOWS_H 0
#endif

#include "fmt/bundled/format.h"
#include "fmt/bundled/ostream.h"
#include "fmt/bundled/printf.h"
#include "prettyprint.hpp"
#include <tuple>
#include <memory>

namespace sandbox {
namespace details {
template <typename... args_t>
struct args_holder
{
    std::tuple<args_t&&...> args;
};

template <int...>
struct index_tuple
{
};

template <int, typename, typename...>
struct make_indexes_impl;

template <int I, int... indexes, typename T, typename... types>
struct make_indexes_impl<I, index_tuple<indexes...>, T, types...>
{
    typedef typename make_indexes_impl<I + 1, index_tuple<indexes..., I>, types...>::type type;
};

template <int I, int... indexes>
struct make_indexes_impl<I, index_tuple<indexes...>>
{
    typedef index_tuple<indexes...> type;
};

template <typename... types>
struct make_indexes : make_indexes_impl<0, index_tuple<>, types...>
{
};

template <class... args_t, int... indexes>
std::string operator_impl(const char* format, index_tuple<indexes...>, std::tuple<args_t...>&& tup)
{
    return fmt::format(format, std::forward<args_t>(std::get<indexes>(tup))...);
}
}

template <typename... args_t>
details::args_holder<args_t...> pfmt(args_t&&... args)
{
    return {std::forward_as_tuple(std::forward<args_t>(args)...)};
}
}

template <typename... args_t>
std::string operator%(const char* format, const sandbox::details::args_holder<args_t...>& args)
{
    using namespace sandbox::details;
    return operator_impl(format, typename make_indexes<args_t...>::type(),
                         std::forward<std::tuple<args_t...>>(args.args));
}

template <typename... args_t>
std::string operator%(const std::string& format, const sandbox::details::args_holder<args_t...>& args)
{
    return format.c_str() % args;
}
