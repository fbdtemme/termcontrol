#pragma once
#include <type_traits>
#include <concepts>

namespace termcontrol::detail {

template <typename T>
concept character_type = std::regular<T> &&
    requires (T t) { typename std::char_traits<T>::char_type; };

}

