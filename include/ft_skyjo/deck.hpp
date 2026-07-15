#pragma once

#include "ft_skyjo/card.hpp"

#include <cstddef>
#include <vector>

namespace ft_skyjo
{

inline constexpr std::size_t canonical_deck_size = 150;

[[nodiscard]] std::vector<Card> make_canonical_deck();

} // namespace ft_skyjo
