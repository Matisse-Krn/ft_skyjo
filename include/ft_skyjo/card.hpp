#pragma once

#include <cstdint>
#include <stdexcept>

namespace ft_skyjo
{

class CardValue
{
  public:
    static constexpr int min_value = -2;
    static constexpr int max_value = 12;

    [[nodiscard]] static constexpr bool is_valid(int value) noexcept
    {
        return value >= min_value && value <= max_value;
    }

    constexpr explicit CardValue(int value) : value_(value)
    {
        if (!is_valid(value))
        {
            throw std::out_of_range{"card value must be between -2 and 12"};
        }
    }

    [[nodiscard]] constexpr int get() const noexcept
    {
        return value_;
    }

    friend constexpr bool operator==(const CardValue&, const CardValue&) noexcept = default;

  private:
    int value_;
};

class CardId
{
  public:
    using underlying_type = std::uint16_t;

    constexpr explicit CardId(underlying_type value) noexcept : value_(value)
    {
    }

    [[nodiscard]] constexpr underlying_type get() const noexcept
    {
        return value_;
    }

    friend constexpr bool operator==(const CardId&, const CardId&) noexcept = default;

  private:
    underlying_type value_;
};

class Card
{
  public:
    constexpr Card(CardId id, CardValue value) noexcept : id_(id), value_(value)
    {
    }

    [[nodiscard]] constexpr CardId id() const noexcept
    {
        return id_;
    }

    [[nodiscard]] constexpr CardValue value() const noexcept
    {
        return value_;
    }

    friend constexpr bool operator==(const Card&, const Card&) noexcept = default;

  private:
    CardId id_;
    CardValue value_;
};

} // namespace ft_skyjo
