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
//

inline std::string strip_control_sequences(std::string_view text)
{
    std::string out;
    auto inserter = std::back_inserter(out);

    auto match = ctre::search<escape_seq_regex>(text.begin(), text.end());
    auto prev = text.begin();

    while (match) {
        auto m = match.get<0>();
        std::copy(prev, m.begin(), inserter);
        match = ctre::search<escape_seq_regex>(m.end(), text.end());
        prev = m.end();
    }
    std::copy(prev, text.end(), inserter);
    return out;
}

inline std::wstring strip_control_sequences(std::wstring_view text)
{
    std::wstring out;
    auto inserter = std::back_inserter(out);

    auto match = ctre::search<escape_seq_regex>(text.begin(), text.end());
    auto prev = text.begin();

    while (match) {
        auto m = match.get<0>();
        std::copy(prev, m.begin(), inserter);
        match = ctre::search<escape_seq_regex>(m.end(), text.end());
        prev = m.end();
    }
    std::copy(prev, text.end(), inserter);
    return out;
}
//
//


}