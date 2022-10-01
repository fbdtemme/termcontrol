#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#endif

#include "detail/ascii.hpp"
#include "detail/color.hpp"
#include "detail/control_sequence.hpp"
#include "detail/definitions.hpp"
#include "detail/display_width.hpp"
#include "detail/fmt.hpp"
#include "detail/ostream.hpp"
#include "detail/parameters.hpp"
#include "detail/parse.hpp"
#include "detail/terminal_size.hpp"
#include "detail/text_style.hpp"

#ifdef _WIN32
#include "detail/windows.hpp"
#endif

#ifdef _WIN32
#undef WIN32_LEAN_AND_MEAN
#define NOMINMAX
#endif