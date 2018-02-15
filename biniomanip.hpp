#pragma once
#include <algorithm>
#include <climits>
#include <ios>
#include <iterator>
#include <limits>
#include <locale>
#include <stdexcept>

namespace sandbox {
template <typename Ch = char, typename Out = std::ostreambuf_iterator<Ch>>
class bin_num_put : public std::num_put<Ch, Out>
{
    typedef std::num_put<Ch, Out> base;

    typedef std::ios_base IB;

    typedef unsigned long long I;

    virtual Out do_put(Out i, IB& io, Ch const fill, unsigned long const v) const
    {
        return io.flags() & IB::basefield ? base::do_put(i, io, fill, v) : do_put(i, io, fill, I(v));
    }

    virtual Out do_put(Out const i, IB& io, Ch const fill, long long const v) const
    {
        return io.flags() & IB::basefield ? base::do_put(i, io, fill, v) : do_put(i, io, fill, I(v));
    }

    virtual Out do_put(Out i, IB& io, Ch const fill, I const v) const
    {
        IB::fmtflags const f = io.flags();
        if (f & IB::basefield)
            return base::do_put(i, io, fill, v);

        std::size_t const buf_size = sizeof(I) * CHAR_BIT * 2;
        Ch r[buf_size], *p = r + buf_size;

        {
            auto const& numpunct = std::use_facet<std::numpunct<char>>(io.getloc());

            I m                           = 1ul;
            std::streamsize group_len     = 0;
            std::string const& grouping   = numpunct.grouping();
            std::string::const_iterator g = grouping.begin();

            do
            {
                if (g != grouping.end() && group_len++ == *g)
                {
                    *--p      = numpunct.thousands_sep();
                    group_len = 1;
                    if (++g == grouping.end())
                        --g;
                }
                *--p = '0' + bool(v & m);
            } while ((m <<= 1) && v >= m);
        }

        std::streamsize const w = io.width();
        io.width(0);
        std::streamsize d = r + buf_size - p;
        if (f & IB::showbase)
            d += 2;
        IB::fmtflags const adj = f & IB::adjustfield;
        if (adj != IB::left && adj != IB::internal)
            while (w > d)
            {
                *i++ = fill;
                ++d;
            }
        if (f & IB::showbase)
        {
            *i++ = '0';
            *i++ = f & IB::uppercase ? 'B' : 'b';
        }
        if (adj == IB::internal)
            while (w > d)
            {
                *i++ = fill;
                ++d;
            }
        i = std::copy(p, r + buf_size, i);
        if (adj == IB::left)
            while (w > d)
            {
                *i++ = fill;
                ++d;
            }
        return i;
    }

    virtual Out do_put(Out const i, IB& io, Ch const fill, long const v) const
    {
        auto const w = static_cast<const unsigned long>(v);
        return io.flags() & IB::basefield ? base::do_put(i, io, fill, v) : do_put(i, io, fill, w);
    }

    // The "proper" thing to do is to add a static std::locale::id const id, but
    // that way bin_num_put does not replace the std::num_put facet in the locale.

public:
    explicit bin_num_put(std::size_t const refs = 0)
        : base(refs)
    {
    }
};

template <typename Ch, typename Tr>
std::basic_ios<Ch, Tr>& bin(std::basic_ios<Ch, Tr>& io)
{
    using T_bin_num_put = bin_num_put<Ch>;
    auto const& facet   = std::use_facet<std::num_get<char>>(io.getloc());
    if (!dynamic_cast<T_bin_num_put const*>(&facet))
    {
        std::locale loc{std::locale(), new T_bin_num_put};
        io.imbue(loc);
    }

    io.setf(std::ios_base::fmtflags(0), std::ios_base::basefield);
    return io;
}
}
