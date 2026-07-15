#pragma once

#include <string_view>

namespace ft_skyjo {

[[nodiscard]] std::string_view project_name() noexcept;
[[nodiscard]] std::string_view project_version() noexcept;

} // namespace ft_skyjo
