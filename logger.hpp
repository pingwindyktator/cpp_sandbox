#pragma once
#include "macroOverloading.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

namespace sandbox {
namespace details {

template <class CharT, class Traits>
class logger_helper : boost::noncopyable
{
public:
    using os_t = std::basic_ostream<CharT, Traits>;
    using ss_t = std::basic_stringstream<CharT, Traits>;

    logger_helper(os_t& os)
        : os(os)
    {
    }

    ~logger_helper()
    {
        os << get_ss().rdbuf() << '\n';
        os.flush();
    }

    ss_t& get_ss() const { return ss; }

private:
    mutable ss_t ss{};
    os_t& os;
};

template <class CharT, class Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const logger_helper<CharT, Traits>& helper)
{
    return helper.get_ss();
}
}
}

// clang-format off
#define LOG(...) VFUNC(LOG, __VA_ARGS__)
#define LOG1(os) os << sandbox::details::logger_helper<decltype(os)::char_type, decltype(os)::traits_type>{os}                   \
                    << '[' << std::setw(12) << std::left << sandbox::get_current_datetime_str() << ']'                           \
                    << '[' << __FILENAME__ << ":" << std::setw(3) << std::left << __LINE__ << ']'                                \
                    << '[' << __FUNC_NAME__ << "]\t"

#define LOG0() LOG1(std::cout)
#define BARK() { LOG(); }
// clang-format on
