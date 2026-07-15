#include "ft_skyjo/version.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("project metadata is available", "[smoke]")
{
    CHECK(ft_skyjo::project_name() == "ft_skyjo");
    CHECK(ft_skyjo::project_version() == "0.1.0");
}
