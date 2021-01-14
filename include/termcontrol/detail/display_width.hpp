///TODO
#pragma once
#include <string>
#include <cwchar>      /// Use operating system wcwidth, wcswidth
#include <locale>
#include <codecvt>

namespace termcontrol {

namespace unicode {

// Convert an UTF8 string to a wide Unicode String
inline std::wstring utf8_decode(const std::string& str)
{
    std::wstring wide_line;
    if (str.empty()) return wide_line;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> u8towide {};
    wide_line = u8towide.from_bytes(str);
    return wide_line;
}

}

static inline int display_width(std::string_view input) {
    auto wstr = unicode::utf8_decode(std::string(input));
    return wcswidth(wstr.c_str(), wstr.size());
}

static inline int display_width(const std::wstring& input) {
    return wcswidth(input.c_str(), input.size());
}

} // namespace cliprogres