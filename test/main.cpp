#include "main.hpp"

int main(int argc, char **argv)
{
    if (argc > 2)
        std::cout << "INVALID INPUT: ./ft_container or ./ft_container CONTAINER_NAME" << std::endl;
    else if (argc == 1)
    {
		test_vector();
		test_stack();
		test_map();
    }
    else if (argc == 2)
    {
        std::string container = argv[1];

        if (container == "vector")
            test_vector();
        else if (container == "stack")
            test_stack();
        else if (container == "map")
            test_map();
        else
            std::cout << "INVALID INPUT: wrong container name" << std::endl;
    }
}
