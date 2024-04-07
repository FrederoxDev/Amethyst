#pragma once

#ifdef max
#undef max
#endif // max

#include "gsl/gsl"

typedef gsl::basic_string_span<const char> string_span;