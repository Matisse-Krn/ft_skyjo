#include "ft_skyjo/card.hpp"

#include <catch2/catch_test_macros.hpp>
#include <stdexcept>

namespace
{

constexpr ft_skyjo::CardValue minimum_card_value{
    ft_skyjo::CardValue::min_value,
};

constexpr ft_skyjo::CardValue maximum_card_value{
    ft_skyjo::CardValue::max_value,
};

constexpr ft_skyjo::Card constexpr_card{
    ft_skyjo::CardId{ft_skyjo::CardId::underlying_type{42}},
    ft_skyjo::CardValue{7},
};

static_assert(minimum_card_value.get() == -2);
static_assert(maximum_card_value.get() == 12);
static_assert(constexpr_card.id().get() == 42);
static_assert(constexpr_card.value().get() == 7);

} // namespace

TEST_CASE("card values accept the complete legal range", "[card]")
{
    for (int value = ft_skyjo::CardValue::min_value; value <= ft_skyjo::CardValue::max_value;
         ++value)
    {
        CAPTURE(value);
        CHECK_NOTHROW(ft_skyjo::CardValue{value});
    }
}

TEST_CASE("card values reject values outside the legal range", "[card]")
{
    CHECK_THROWS_AS(ft_skyjo::CardValue{-3}, std::out_of_range);
    CHECK_THROWS_AS(ft_skyjo::CardValue{13}, std::out_of_range);
}

TEST_CASE("a card preserves its identity and value", "[card]")
{
    using IdType = ft_skyjo::CardId::underlying_type;

    const ft_skyjo::Card card{
        ft_skyjo::CardId{IdType{42}},
        ft_skyjo::CardValue{7},
    };

    CHECK(card.id().get() == IdType{42});
    CHECK(card.value().get() == 7);
}

TEST_CASE("card values and identifiers have value semantics", "[card]")
{
    using IdType = ft_skyjo::CardId::underlying_type;

    CHECK(ft_skyjo::CardValue{7} == ft_skyjo::CardValue{7});
    CHECK_FALSE(ft_skyjo::CardValue{7} == ft_skyjo::CardValue{8});

    CHECK(ft_skyjo::CardId{IdType{4}} == ft_skyjo::CardId{IdType{4}});
    CHECK_FALSE(ft_skyjo::CardId{IdType{4}} == ft_skyjo::CardId{IdType{5}});
}
