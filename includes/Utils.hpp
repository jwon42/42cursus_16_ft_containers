/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 16:31:07 by jwon              #+#    #+#             */
/*   Updated: 2021/10/15 00:45:30 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	// B가 true이면 ft::enable_if::type이 생성
	// https://stackoverflow.com/questions/62012761/what-is-the-meaning-of-type-nullptr
	template <bool B, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	// integral type에는 bool, char, char16_t, char32_t, wchar_t, signed char,
	// short int, int, long ing, long long int, unsigned char, unsigned short int,
	// unsigned int, unsigned long int, unsigned long long int 가 있다.

    // 위의 integral type일 경우에만 value가 true로 세팅
    template <bool is_integral, typename T>
    struct is_integral_res
    {
        typedef T type;
        static const bool value = is_integral;
    };

    // integral type에 해당하지 않는 자료형은 false로 세팅
    template<typename>
    struct is_integral_type : public is_integral_res<false, bool> {};

    // integral type에 해당하는 자료형들은 true로 세팅
    template<>
    struct is_integral_type<bool>: public is_integral_res<true, bool> {};

    template<>
    struct is_integral_type<char>: public is_integral_res<true, char> {};

    template<>
    struct is_integral_type<signed char>: public is_integral_res<true, signed char> {};

    template<>
    struct is_integral_type<short int>: public is_integral_res<true, short int> {};

    template<>
    struct is_integral_type<int>: public is_integral_res<true, int> {};

    template<>
    struct is_integral_type<long int>: public is_integral_res<true, long int> {};

    template<>
    struct is_integral_type<long long int>: public is_integral_res<true, long long int> {};

    template<>
    struct is_integral_type<unsigned char>: public is_integral_res<true, unsigned char> {};

    template<>
    struct is_integral_type<unsigned short int>: public is_integral_res<true, unsigned short int> {};

    template<>
    struct is_integral_type<unsigned int>: public is_integral_res<true, unsigned int> {};

    template<>
    struct is_integral_type<unsigned long int>: public is_integral_res<true, unsigned long int> {};

    template<>
    struct is_integral_type<unsigned long long int>: public is_integral_res<true, unsigned long long int> {};

    template <class T>
    struct is_integral : public is_integral_type<T> {};

// bool equal
// begin1 ~ end1 사이의 구간과 begin2 이후의 구간에 있는 요소들을 1:1로 비교한다.
// 모든 요소가 일치한다면 true 리턴, 하나라도 틀리면 false 리턴.
// 두 번째 구간은 시작 위치를 지정하는 begin1 반복자만 매개변수로 받으며, 첫 번째 구간과 길이가 동일하다고 가정한다.
	template <class InputIterator1, class InputIterator2>
	static bool	equal(InputIterator1 begin1, InputIterator1 end1, InputIterator2 begin2)
	{
		while (begin1 != end1)
		{
			if (*begin1 != *begin2)
				return (false);
			begin1++;
			begin2++;
		}
		return (true);
	}

// bool lexicographical_compare
// 두 구간(begin1 ~ end1, begin2 ~ end2)의 대응되는 요소를 차례로 비교한다.
// 첫 번째 요소가 두 번째 요소보다 작으면 true 리턴, 크면 false 리턴.
// 만약 같다면 다음 요소를 같은 방식으로 비교하며 구간 끝까지 반복한다.
	template <class InputIterator1, class InputIterator2>
	static bool	lexicographical_compare(InputIterator1 begin1, InputIterator1 end1,
		InputIterator2 begin2, InputIterator2 end2)
	{
		while (begin1 != end1)
		{
			if (begin2 == end2 || *begin2 < *begin1)
				return (false);
			else if (*begin1 < *begin2)
				return (true);
			begin1++;
			begin2++;
		}
		return (begin2 != end2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	static bool	lexicographical_compare(InputIterator1 begin1, InputIterator1 end1,
		InputIterator2 begin2, InputIterator2 end2, Compare comp)
	{
		while (begin1 != end1)
		{
			if (begin2 == end2 || comp(*begin2, *begin1))
				return (false);
			else if (*begin1 < *begin2)
				return (true);
			begin1++;
			begin2++;
		}
		return (begin2 != end2);
	}

// struct pair
// T1, T2 타입을 인수로 받아 T1 타입의 first와 T2 타입의 second를 멤버변수로 정의.
// 두 개씩 짝을 이룬 데이터를 다루거나 한번에 두 개의 값을 리턴하고 싶을 때 이 구조체를 사용.
// 구조체는 값으로 복사, 대입되므로 함수의 리턴 타입으로 사용할 수 있다.
	template<class T1, class T2>
	struct pair
	{
			typedef T1		first_type;
			typedef T2		second_type;

			first_type		first;
			second_type		second;

			pair() : first(first_type()), second(second_type()) {}
			pair(const first_type& x, const second_type& y)
			: first(x), second(y) {}
			template<class U, class V>
			pair(const pair<U,V>& src) : first(src.first), second(src.second) {}
			~pair() {}

			pair& operator=(const pair& rhs)
			{
				if (this != &rhs)
				{
					first = rhs.first;
					second = rhs.second;
				}
				return (*this);
			}
	};

	template<class T1, class T2>
	bool operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template<class T1, class T2>
	bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (!(lhs == rhs));
	}

	template<class T1, class T2>
	bool operator<(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		if (lhs.first < rhs.first || lhs.second < rhs.second)
			return (true);
		return (false);
	}

	template<class T1, class T2>
	bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		if (lhs.first <= rhs.first || lhs.second <= rhs.second)
			return (true);
		return (false);
	}

	template<class T1, class T2>
	bool operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (!(lhs <= rhs));
	}

	template<class T1, class T2>
	bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (!(lhs < rhs));
	}

	template<class T1, class T2>
	ft::pair<T1,T2> make_pair(T1 t, T2 u)
	{
		return (ft::pair<T1, T2>(t, u));
	}
}


#endif