/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 14:42:45 by jwon              #+#    #+#             */
/*   Updated: 2021/10/22 20:55:54 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "Vector.hpp"

// std::stack reference
// https://www.cplusplus.com/reference/stack/stack/

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef T value_type; // stack에 요소로 저장된 개체의 형식을 나타내는 형식
			typedef Container container_type; // stack에서 조정할 기본 컨테이너를 제공하는 형식
			typedef	size_t size_type; // stack에서 요소 수를 표현할 수 있는 부호 없는 정수 형식

		protected:
			container_type c;

		public:
			// default constructor
			// 요소 없는 빈 stack 생성
			explicit stack(const container_type& ctnr = container_type())
			: c(ctnr) {}

			// destructor
			~stack() {}

			// member functions start
			bool empty(void) const // stack이 비어 있는지를 테스트
			{
				return (c.empty());
			}

			size_type size(void) const // stack에 있는 요소 수를 반환
			{
				return (c.size());
			}

			value_type& top() // stack의 맨 위에 있는 요소에 대한 참조를 반환
			{
				return (c.back());
			}

			const value_type& top() const // stack의 맨 위에 있는 요소에 대한 참조를 반환
			{
				return (c.back());
			}

			void push(const value_type& val) // stack의 맨 위에 요소를 추가
			{
				c.push_back(val);
			}

			void pop(void) // stack의 맨 위에 있는 요소를 제거
			{
				c.pop_back();
			}
			// member functions end

		private:
			// protected 멤버에 접근할 non-member 연산자들을 위한 friend 선언
			// http://tcpschool.com/cpp/cpp_encapsulation_friend

			template <class A, class B>
			friend bool	operator==(const stack<A, B> &lhs, const stack<A, B> &rhs);

			template <class A, class B>
			friend bool	operator!=(const stack<A, B> &lhs, const stack<A, B> &rhs);

			template <class A, class B>
			friend bool	operator<(const stack<A, B> &lhs, const stack<A, B> &rhs);

			template <class A, class B>
			friend bool	operator<=(const stack<A, B> &lhs, const stack<A, B> &rhs);

			template <class A, class B>
			friend bool	operator>(const stack<A, B> &lhs, const stack<A, B> &rhs);

			template <class A, class B>
			friend bool	operator>=(const stack<A, B> &lhs, const stack<A, B> &rhs);
	};

	template <class T, class Container>
	bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs.c != rhs.c);
	}

	template <class T, class Container>
	bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <class T, class Container>
	bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs.c >= rhs.c);
	}

	template <class T, class Container>
	bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return (lhs.c <= rhs.c);
	}
}

#endif