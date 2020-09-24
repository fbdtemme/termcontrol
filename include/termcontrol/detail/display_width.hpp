///TODO
#pragma once
#include <string>
#include <cwchar>      /// Use operating system wcwidth, wcswidth
#include <utf8cpp/utf8.h>

namespace termcontrol {

namespace unicode {

// Convert a wide Unicode string to an UTF8 string
inline std::string utf8_encode(std::wstring_view wstr)
{
    std::string utf8line;

    if (wstr.empty()) return utf8line;

#ifdef _WIN32
    utf8::utf16to8(wstr.begin(), wstr.end(), std::back_inserter(utf8line));
#else
    utf8::utf32to8(wstr.begin(), wstr.end(), std::back_inserter(utf8line));
#endif
    return utf8line;
}

// Convert an UTF8 string to a wide Unicode String
inline std::wstring utf8_decode(std::string_view& str)
{
    std::wstring wide_line;

    if (str.empty()) return wide_line;

#ifdef _WIN32
    utf8::utf8to16(str.begin(), str.end(), std::back_inserter(wide_line));
#else
    utf8::utf8to32(str.begin(), str.end(), std::back_inserter(wide_line));
#endif
    return wide_line;
}

}

static inline int display_width(std::string_view input) {
    auto wstr = unicode::utf8_decode(input);
    return wcswidth(wstr.c_str(), wstr.size());
}

static inline int display_width(const std::wstring& input) {
    return wcswidth(input.c_str(), input.size());
}

} // namespace cliprogres