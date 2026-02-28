#pragma once

#define MC __declspec(dllimport) 

#include <algorithm>          // STL general algorithms
#include <array>              // STL array container
#include <bitset>             // STL bitset container
#include <cctype>             // Character handling functions
#include <cerrno>             // C Error codes
#include <chrono>             // C++11 Time library
#include <clocale>            // C localization library
#include <cmath>              // Common mathematics functions
#include <complex>            // Complex number type
#include <condition_variable> // condition variable
#include <cstdio>             // C Standard Input/Output library
#include <cstdlib>            // C Standard General Utilities Library
#include <cstring>            // C string handling
#include <ctime>              // C Time library
#include <cwchar>             // Wide character type
#include <cwctype>            // Wide character classification
#include <deque>              // STL double ended queue container
#include <exception>          // Exception handling classes
#include <filesystem>         // STL file system
#include <forward_list>       // STL forward list container
#include <fstream>            // File stream classes
#include <functional>         // STL Function objects
#include <iomanip>            // Input/Output manipulators
#include <ios>                // Base input/output stream classes
#include <iosfwd>             // Input/Output forward declarations
#include <iostream>           // Standard Input/Output stream objects
#include <istream>            // Basic input stream classes
#include <limits>             // Numeric limits
#include <list>               // STL linear list container
#include <map>                // STL map container
#include <memory>             // STL unique_ptr, shared_ptr, weak_ptr
#include <mutex>              // STL mutual exclusion primitives
#include <numbers>            // numbers standard header
#include <optional>           // STL optional type
#include <ostream>            // Basic output stream classes
#include <queue>              // STL queue and priority_queue container
#include <random>             // C++11 Random numbers
#include <set>                // STL set and multiset container
#include <shared_mutex>       // STL shared mutual exclusion primitives
#include <sstream>            // String stream classes
#include <stack>              // STL stack container
#include <stdexcept>          // Standard exception objects
#include <streambuf>          // Stream buffer classes
#include <string>             // String class
#include <string_view>        // STL string_view type
#include <unordered_map>      // STL unordered map container
#include <unordered_set>      // STL unordered set container
#include <utility>            // STL utility components
#include <variant>            // STL variant type
#include <vector>             // STL dynamic array container
#include <future>             // STL future

// MC Deps
#include <entt/entt.hpp>
#include <gsl/gsl>
#include <glm/glm.hpp>
#include <json/json.h>

#include <amethyst/Log.hpp>

using UnknownReturn = void; // placeholder for unknown return types