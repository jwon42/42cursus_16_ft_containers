#include "../includes/main.hpp"

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

    // ft::vector<int> v(5, 2);
    // // v.push_back(1111);
    // // v.push_back(2222);
    // // v.push_back(3333);
    // // v.push_back(4444);
    // // v.push_back(5555);
    // std::cout << "vector v size : " << v.size() << std::endl;
    // std::cout << "vector v capacity : " << v.capacity() << std::endl;
    // // v.resize(9, 0000);


    // ft::vector<int>::iterator iter;
    // for (iter = v.begin(); iter != v.end(); iter++)
    //     std::cout << *iter << std::endl;
    // std::cout << "vector v size : " << v.size() << std::endl;
    // std::cout << "vector v capacity : " << v.capacity() << std::endl;

    // ft::vector<int> v2(v);
    // ft::vector<int>::iterator iter2;
    // for (iter2 = v2.begin(); iter2 != v2.end(); iter2++)
    //     std::cout << *iter2 << std::endl;
    // std::cout << "vector v2 size : " << v2.size() << std::endl;
    // std::cout << "vector v2 capacity : " << v2.capacity() << std::endl;

    // std::cout << "std::max(NULL, NULL) : " << std::max(NULL, NULL) << std::endl;

    // ft::map<int, int> m1;
	// std::map<int, int> m2;
    // std::cout << "map m1 size : " << m1.size() << std::endl;
    // std::cout << "map m2 size : " << m2.size() << std::endl;
    // std::cout << "map m1 max_size : " << m1.max_size() << std::endl;
    // std::cout << "map m2 max_size : " << m2.max_size() << std::endl;
    // for (int i = 0; i < 100; i++)
	// {
	// 	m1.insert(ft::make_pair(i, i));
	// 	m2.insert(std::make_pair(i, i));
	// }
    // std::cout << "map m1 size : " << m1.size() << std::endl;
    // std::cout << "map m2 size : " << m2.size() << std::endl;
    // std::cout << "map m1 max_size : " << m1.max_size() << std::endl;
    // std::cout << "map m2 max_size : " << m2.max_size() << std::endl;
}
