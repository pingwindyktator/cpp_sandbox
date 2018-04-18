# cpp_sandbox

Header-only C++ boilerplate code shipped with Boost, fmt, prettyprint. Requires at least C++11.

## Features

* `size_t get_filesize(const boost::filesystem::path& path);`
* `std::string read_file(const boost::filesystem::path& path);`
* `std::chrono::milliseconds::rep ms_since_epoch();`
* `std::string get_current_datetime_str();`
* `to_t evil_cast(from_t&& f);`
* `std::unique_ptr<T> make_unique(Args&&... args);`
* `struct identity;`
* `std::chrono::milliseconds measure_execution_time(func_t&& func, Args&&... args);`
* `benchmark_escape(void *p)` and `benchmark_clobber()` funcs to prevent optimizer ruin your performance analysis
* `type_name<T>()` to get string representation of object type
* user-defined chrono literals
* generic `std::hash` for enum types
* all commonly used std includes
* `sandbox::bin` IO manipulator
* simple logger:
  * `LOG() << fmt::format("some value: {}", some_value);`
  * `LOG(std::cerr) << "something" << " else";`
* `osync` to make std streams thread safe:
  * `std::cout << sandbox::osync << "thread " << "safe";`
* simple thread pool
* `flat_map` and `flat_set` containers: these are `std::map` and `std::set` implementations using a contiguous data structure as the underlying storage.

## How to use

1) `git clone` this repo next to your `main.cpp`
2) Place `include(cpp_sandbox/CMakeLists.txt)` at the end of your `CMakeLists.txt`
3) `#define SANDBOX_DONT_USE_NAMESPACE` if you don't want any `using namespace`
4) `#include "cpp_sandbox/sandbox.hpp"` and have fun!
