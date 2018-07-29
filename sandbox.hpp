#pragma once

#if __cplusplus < 201103L
#error You should really use at least C++11
#endif

#include "utils.hpp"
#include "includes.hpp"

#if !defined(SANDBOX_DONT_USE_NAMESPACE)
using namespace std;
using namespace boost;
#endif
