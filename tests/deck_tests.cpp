#include "ft_skyjo/deck.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <map>
#include <set>

TEST_CASE("canonical deck contains exactly 150 cards", "[deck]")
{
    const auto cards = ft_skyjo::make_canonical_deck();

    CHECK(cards.size() == ft_skyjo::canonical_deck_size);
}

TEST_CASE("canonical deck contains unique contiguous identifiers", "[deck]")
{
    using IdType = ft_skyjo::CardId::underlying_type;

    const auto cards = ft_skyjo::make_canonical_deck();
    std::set<IdType> identifiers;

    for (const ft_skyjo::Card& card : cards)
    {
        CHECK(identifiers.insert(card.id().get()).second);
    }

    REQUIRE(identifiers.size() == ft_skyjo::canonical_deck_size);

    for (std::size_t index = 0; index < ft_skyjo::canonical_deck_size; ++index)
    {
        const auto expected_id = static_cast<IdType>(index);

        CAPTURE(index);
        CHECK(identifiers.contains(expected_id));
    }
}

TEST_CASE("canonical deck follows the official value distribution", "[deck]")
{
    const auto cards = ft_skyjo::make_canonical_deck();
    std::map<int, std::size_t> counts;

    for (const ft_skyjo::Card& card : cards)
    {
        ++counts[card.value().get()];
    }

    REQUIRE(counts.size() == 15);

    CHECK(counts.at(-2) == std::size_t{5});
    CHECK(counts.at(-1) == std::size_t{10});
    CHECK(counts.at(0) == std::size_t{15});

    for (int value = 1; value <= 12; ++value)
    {
        CAPTURE(value);
        CHECK(counts.at(value) == std::size_t{10});
    }
}

TEST_CASE("canonical deck construction is deterministic", "[deck]")
{
    const auto first_deck = ft_skyjo::make_canonical_deck();
    const auto second_deck = ft_skyjo::make_canonical_deck();

    CHECK(first_deck == second_deck);
}
