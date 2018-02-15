#pragma once

#include "bignum.hpp"
#include "biniomanip.hpp"
#include "fmt.hpp"
#include "logger.hpp"
#include "macroOverloading.hpp"
#include "osync.hpp"
#include "prettyprint.hpp"
#include "simple_thread_pool.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fcntl.h>
#include <fstream>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <limits>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <numeric>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unistd.h>
#include <unordered_map>
#include <utility>
#include <vector>

#if defined(unix) || defined(__unix) || defined(__unix__)
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#endif

#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/io/ios_state.hpp>