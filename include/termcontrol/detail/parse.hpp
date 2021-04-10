#pragma once
#include <ctre.hpp>
#include <ctll.hpp>
#include <algorithm>

inline constexpr auto escape_seq_regex = ctll::fixed_string {
        "(?:" "\x1B" "[@-Z\\-_]|[" "\x80" "-" "\x9A" "\x9C" "-" "\x9F" "]"
        "|(?:" "\x1B" "\\[|" "\x9B" ")[0-?]*[ -/]*[@-~])"};

namespace termcontrol {

/// Return the cumulative length of escape sequences contained in `text`.
constexpr auto total_control_sequences_length(std::string_view text) -> std::size_t
{
    std::size_t size = 0;
    auto match = ctre::search<escape_seq_regex>(text);
    while (match) {
        auto m = match.get<0>();
        size += m.size();
        match = ctre::search<escape_seq_regex>(m.end(), text.end());
    }
    return size;
}

template <typename CharT>
inline std::basic_string<CharT> strip_control_sequences(std::basic_string_view<CharT> text)
{
    std::basic_string<CharT> out;
    auto inserter = std::back_inserter(out);

    auto match = ctre::search<escape_seq_regex>(text.begin(), text.end());
    auto prev = text.begin();

    while (match) {
        auto m = match.template get<0>();
        std::copy(prev, m.begin(), inserter);
        match = ctre::search<escape_seq_regex>(m.end(), text.end());
        prev = m.end();
    }
    std::copy(prev, text.end(), inserter);
    return out;
}

inline auto strip_control_sequences(std::string_view text)
{
    return strip_control_sequences<char>(text);
}

inline auto strip_control_sequences(std::wstring_view text)
{
    return strip_control_sequences<wchar_t>(text);
}

inline auto strip_control_sequences(std::u8string_view text)
{
   return strip_control_sequences<char8_t>(text);
}

inline auto strip_control_sequences(std::u16string_view text)
{
    return strip_control_sequences<char16_t>(text);
}

inline auto strip_control_sequences(std::u32string_view text)
{
    return strip_control_sequences<char32_t>(text);
}

}