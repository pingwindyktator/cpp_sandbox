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
* user-defined chrono literals
* generic `std::hash` for enum types
* all commonly used std includes
* `std::bin` IO manipulator
* simple logger:
  * `LOG() << fmt::format("some value: {}", some_value);`
  * `LOG(std::cerr) << "something" << " else";`
* `osync` to make std streams thread safe:
  * `std::cout << sandbox::osync << "thread " << "safe";`
* simple thread pool

## How to use

1) `git clone` this repo next to your `main.cpp`
2) Place `include(sandbox/CMakeLists.txt)` at the end of your `CMakeLists.txt`
3) `#include "sandbox/sandbox.hpp"` and have fun!
