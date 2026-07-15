#include "ft_skyjo/deck.hpp"

#include <array>
#include <limits>

namespace ft_skyjo
{
namespace
{

struct DistributionEntry
{
    int value;
    std::size_t count;
};

constexpr std::array<DistributionEntry, 15> canonical_distribution{{
    {-2, 5},
    {-1, 10},
    {0, 15},
    {1, 10},
    {2, 10},
    {3, 10},
    {4, 10},
    {5, 10},
    {6, 10},
    {7, 10},
    {8, 10},
    {9, 10},
    {10, 10},
    {11, 10},
    {12, 10},
}};

consteval std::size_t distribution_size()
{
    std::size_t total = 0;

    for (const DistributionEntry& entry : canonical_distribution)
    {
        total += entry.count;
    }

    return total;
}

static_assert(distribution_size() == canonical_deck_size);
static_assert(canonical_deck_size > 0);
static_assert(canonical_deck_size - 1 <=
              static_cast<std::size_t>(std::numeric_limits<CardId::underlying_type>::max()));

} // namespace

std::vector<Card> make_canonical_deck()
{
    std::vector<Card> cards;
    cards.reserve(canonical_deck_size);

    for (const DistributionEntry& entry : canonical_distribution)
    {
        for (std::size_t copy_index = 0; copy_index < entry.count; ++copy_index)
        {
            const auto raw_id = static_cast<CardId::underlying_type>(cards.size());
            cards.emplace_back(CardId{raw_id}, CardValue{entry.value});
        }
    }

    return cards;
}

} // namespace ft_skyjo
