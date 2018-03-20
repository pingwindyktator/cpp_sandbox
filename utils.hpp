#pragma once
#include <boost/filesystem.hpp>
#include <chrono>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <sys/time.h>

#define __FUNC_NAME__ sandbox::details::func_name(__PRETTY_FUNCTION__)
#define __FILENAME__ boost::filesystem::path{__FILE__}.filename().string()

namespace sandbox {
namespace details {
inline std::string func_name(const std::string& prettyFunction)
{
    auto end    = prettyFunction.find('(');
    auto result = prettyFunction.substr(0, end);

    auto begin        = result.rfind(' ');
    result            = result.substr(begin + 1);
    end               = result.rfind("::");
    size_t last_begin = 0;
    begin             = result.find("::");

    while (begin < end)
    {
        last_begin = begin + 2;
        begin      = result.find("::", begin + 2);
    }

    return result.substr(last_begin);
}
}

inline size_t get_filesize(const boost::filesystem::path& path)
{
    std::ifstream file(path.string(), std::ios::binary | std::ios::ate | std::ios::in);
    return static_cast<size_t>(file.tellg());
}

inline std::string read_file(const boost::filesystem::path& path)
{
    std::ostringstream buf;
    std::ifstream input(path.string());
    buf << input.rdbuf();
    return buf.str();
}

inline std::chrono::milliseconds::rep ms_since_epoch()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
}

inline std::string get_current_datetime_str()
{
    timeval curTime;
    gettimeofday(&curTime, nullptr);
    auto milli = static_cast<int>(curTime.tv_usec / 1000);

    char buffer[10] = "";
    strftime(buffer, sizeof(buffer), "%H:%M:%S", localtime(&curTime.tv_sec));

    std::string milliStr;

    if (milli < 10)
        milliStr = "00" + std::to_string(milli);
    else if (milli < 100)
        milliStr = "0" + std::to_string(milli);
    else
        milliStr = std::to_string(milli);

    return buffer + (':' + milliStr);
}

template <typename to_t, typename from_t>
to_t evil_cast(from_t&& f)
{
    return *static_cast<to_t*>(reinterpret_cast<char*>(&f));
}

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

struct identity
{
    template <typename U>
    constexpr auto operator()(U&& v) const noexcept -> decltype(std::forward<U>(v))
    {
        return std::forward<U>(v);
    }
};

template <typename func_t, typename... Args>
std::chrono::milliseconds measure_execution_time(func_t&& func, Args&&... args)
{
    auto start = std::chrono::high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}
}

namespace std {
template <class E>
class hash
{
    using sfinae       = typename std::enable_if<std::is_enum<E>::value, E>::type;
    using underlying_t = typename std::underlying_type<E>::type;

public:
    size_t operator()(const E& e) const { return std::hash<underlying_t>()(static_cast<underlying_t>(e)); }
};
}

constexpr inline std::chrono::hours operator"" _h(unsigned long long i)
{
    return std::chrono::hours{i};
}

constexpr inline std::chrono::minutes operator"" _min(unsigned long long i)
{
    return std::chrono::minutes{i};
}

constexpr inline std::chrono::seconds operator"" _s(unsigned long long i)
{
    return std::chrono::seconds{i};
}

constexpr inline std::chrono::milliseconds operator"" _ms(unsigned long long i)
{
    return std::chrono::milliseconds{i};
}

constexpr inline std::chrono::microseconds operator"" _us(unsigned long long i)
{
    return std::chrono::microseconds{i};
}

constexpr inline std::chrono::nanoseconds operator"" _ns(unsigned long long i)
{
    return std::chrono::nanoseconds{i};
}
