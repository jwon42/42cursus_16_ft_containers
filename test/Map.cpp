#include <iostream>
#include "main.hpp"

void test_constructor()
{
	print_header("Constructors");
	ft::map<int, int> map;
	std::map<int, int> smap;
	assert(map.empty());
	assert(smap.empty());
	check("default constructor", true);

	for (int i = 0; i < 100; i++)
	{
		map.insert(ft::make_pair(i, i));
		smap.insert(std::make_pair(i, i));
	}

	ft::map<int, int> map2(map.begin(), map.end());
	std::map<int, int> smap2(smap.begin(), smap.end());

	ft::map<int, int>::const_iterator it = map.begin();
	ft::map<int, int>::const_iterator it2 = map2.begin();
	std::map<int, int>::const_iterator sit = smap.begin();
	std::map<int, int>::const_iterator sit2 = smap2.begin();

	while (it != map.end())
	{
		assert(it->first == it2->first && it->second == it2->second);
		it++;
		it2++;
	}
	while (sit != smap.end())
	{
		assert(sit->first == sit2->first && sit->second == sit2->second);
		sit++;
		sit2++;
	}
	check("constructor with iterator", true);

	ft::map<int, int> map3(map2);
	std::map<int, int> smap3(smap2);
	assert(map2 == map3);
	assert(smap2 == smap2);
	check("copy constructor", true);
}

void test_iterators()
{
	print_header("Iterators");

    ft::map<int, int>::iterator it;
    ft::map<int, int> map;

	std::map<int, int>::iterator sit;
	std::map<int, int> smap;

    for (int i = 1000; i >= 1; i--)
	{
		map[i] = i;
		smap[i] = i;
    }

    int n = 1;
    it = map.begin();
	sit = smap.begin();
	assert(sit->first == 1);
	check("begin()", it->first == 1);
    while (it != map.end())
	{
		assert(it->first == n);
		assert(it->second == n);
		assert(sit->first == n);
		assert(sit->second == n);
		n++;
		it++;
		sit++;
    }
	assert((--smap.end())->first == 1000);
    check("end()", (--map.end())->first == 1000);

	it = --map.end();
	sit = --smap.end();
	ft::map<int, int>::reverse_iterator rit = map.rbegin();
	std::map<int, int>::reverse_iterator srit = smap.rbegin();
	assert(srit->first == 1000);
	check("rbegin()", rit->first == 1000);
	assert((--smap.rend())->first == 1);
	check("rend()", (--map.rend())->first == 1);
}

void test_modifiers()
{
	print_header("Modifiers");
	ft::map<int, int> map;
	ft::map<int, int> map2;

	for (int i = 1; i <= 100; i++)
	{
		map[i] = i;
	}

	/* insert */
	map.insert(map.begin(), ft::make_pair<int, int>(4242, 4242));
	check("insert(iterator, value)", map.find(4242) != map.end());

	/* erase */
	map.erase(42);
	check("erase()", map.size() == 100);

	/* swap */
	map.swap(map2);
	check(
		"map.swap(map2)",
		map != map2 && map2.size() == 100 && map.size() == 0
		);

	/* clear */
	map.clear();
	map2.clear();
	assert(map == map2 && map.size() == 0);
	check("map.clear() == map2.clear()", true);
}

void test_observers()
{
	print_header("Observers");
	ft::map<int, int> map;
	ft::map<int, int>::value_compare value_comp = map.value_comp();
	ft::map<int, int>::key_compare key_comp = map.key_comp();

	std::map<int, int> smap;
	std::map<int, int>::value_compare svalue_comp = smap.value_comp();
	std::map<int, int>::key_compare skey_comp = smap.key_comp();

	assert(skey_comp(1, 10));
	check("key_comp(1, 10)", key_comp(1, 10));
	assert(!skey_comp(10, 1));
	check("!key_comp(10, 1)", !key_comp(10, 1));
	assert(svalue_comp(std::make_pair<const int, int>(10, 10), std::make_pair<const int, int>(100, 100)));
	assert(value_comp(ft::make_pair<const int, int>(10, 10), ft::make_pair<const int, int>(100, 100)));
	check("value_comp(10, 100)", true);
}

void test_operations()
{
	print_header("Operators");
	ft::map<int, int> map;
	ft::map<int, int>::iterator it;

	std::map<int, int> smap;
	std::map<int, int>::iterator sit;

	for (int i = 1; i <= 100; i++)
	{
		map[i] = i;
		smap[i] = i;
	}
	/* find */
    assert(map.find(10) != map.end());
	assert(smap.find(10) != smap.end());
	check("map.find(10) != map.end()", true);
    assert(map.find(101) == map.end());
	assert(smap.find(101) == smap.end());
	check("map.find(101) = map.end()", true);

	/* count */
	assert(smap.count(10) == 1);
	check("map.count(10) == 1", map.count(10) == 1);
	assert(smap.count(101) == 0);
	check("map.count(101) == 0", map.count(101) == 0);

	/* lower bound */
	assert(smap.lower_bound(10)->first == 10);
	check("map.lower_bound(10)->first == 10", map.lower_bound(10)->first == 10);
	assert(smap.lower_bound(1000) == smap.end());
	check("map.lower_bound(1000) == map.end()", map.lower_bound(1000) == map.end());

	/* upper bound */
	assert(smap.upper_bound(10)->first == 11);
	check("map.upper_bound(10)->first == 11", map.upper_bound(10)->first == 11);
	assert(smap.upper_bound(1000) == smap.end());
	check("map.upper_bound(1000) == map.end()", map.upper_bound(1000) == map.end());

	/* equal range */
	assert(smap.equal_range(10).first == smap.lower_bound(10));
	check(
		"equal_range.first == lower_bound",
		map.equal_range(10).first == map.lower_bound(10)
		);
	assert(smap.equal_range(10).second == smap.upper_bound(10));
	check(
		"equal_range.second == upper_bound",
		map.equal_range(10).second == map.upper_bound(10)
		);
}

void test_speed()
{
	print_header("Speed");
	ft::map<int, bool> ftmap;
	std::map<int, bool> stdmap;

	clock_t ft_clock;
	clock_t std_clock;

	ft_clock = clock();
	for (int i = 0; i < 100000; i++)
	{
		ftmap[i * 10] = true;
	}
	ft_clock = clock() - ft_clock;

	std_clock = clock();
	for (int i = 0; i < 100000; i++)
	{
		stdmap[i * 10] = true;
	}
	std_clock = clock() - std_clock;

	check("insert speed test", std_clock > ft_clock);
	std::cout << "ft::map insert speed : " << ft_clock << std::endl;
	std::cout << "std::map insert speed : " << std_clock << std::endl;

	ft_clock = clock();
	for (int i = 0; i < 100000; i++)
	{
		ftmap.find(i * 10);
	}
	ft_clock = clock() - ft_clock;

	std_clock = clock();
	for (int i = 0; i < 100000; i++)
	{
		stdmap.find(i * 10);
	}
	std_clock = clock() - std_clock;

	check("find speed test", std_clock > ft_clock);
	std::cout << "ft::map find speed : " << ft_clock << std::endl;
	std::cout << "std::map find speed : " << std_clock << std::endl;
}

void test_map()
{
	print_header("map", true);
	test_constructor();
	test_iterators();
	test_modifiers();
	test_observers();
	test_operations();
	test_speed();
}
