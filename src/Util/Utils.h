#pragma once
#include <concepts>

template <typename T>
concept RefedPtr = requires(T a) {
                     { a.owner_before(a) } -> std::convertible_to<bool>;
                   };

template <RefedPtr T, RefedPtr U>

bool is_different(T&& t, U&& u) {
  return t.owner_before(u) || u.owner_before(t);
}
