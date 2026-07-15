#include "ft_skyjo/version.hpp"

#include <iostream>

int main()
{
    std::cout << ft_skyjo::project_name() << " " << ft_skyjo::project_version() << '\n';
    return 0;
}
