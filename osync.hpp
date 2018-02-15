#pragma once
#include <mutex>
#include <ostream>
#include <boost/core/noncopyable.hpp>

#define osync details::osync_impl<std::mutex>{}

namespace sandbox {
namespace details {
template <typename mutex_t>
class osync_impl : boost::noncopyable
{
public:
    osync_impl() { mtx.lock(); }

    ~osync_impl() { mtx.unlock(); }

private:
    static mutex_t mtx;
};

template <typename mutex_t>
mutex_t osync_impl<mutex_t>::mtx{};

template<class CharT, class Traits, typename mutex_t>
std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &os, const osync_impl<mutex_t> &)
{
    return os;
}
}
}
