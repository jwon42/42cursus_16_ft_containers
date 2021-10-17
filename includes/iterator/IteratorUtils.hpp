/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 14:15:05 by jwon              #+#    #+#             */
/*   Updated: 2021/10/14 20:50:18 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "stddef.h"
# include <memory>

namespace ft {
  // iterator tags // 반복자 종류
  struct input_iterator_tag {}; // 전진만 가능, 한에 하나만 읽기 가능
  struct output_iterator_tag {}; // 전진만 가능, 한번에 하나만 쓰기 가능
  struct forward_iterator_tag : public input_iterator_tag, output_iterator_tag {}; // 전진만 가능, 한번에 여러개 읽고 쓰기 가능
  struct bidirectional_iterator_tag : public forward_iterator_tag {}; // 전진 후진 모두 가능, 한번에 여러개 읽고 쓰기 가능
  struct random_access_iterator_tag : public bidirectional_iterator_tag {}; // 반복자를 임의 위치만큼 전진 후진 가능

  // standard iterator traits
  template <typename Iter>
  struct iterator_traits
  {
    typedef typename Iter::iterator_category iterator_category;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::difference_type difference_type;
    typedef difference_type distance_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;
  };

  // iterator traits for pointer
  template <typename T>
  struct iterator_traits<T *>
  {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef ptrdiff_t distance_type;
    typedef T *pointer;
    typedef T &reference;
  };

  // iterator traits for const pointer
  template <typename T>
  struct iterator_traits<const T *>
  {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef ptrdiff_t distance_type;
    typedef T *pointer;
    typedef T &reference;
  };

  // iterator
  template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
  struct iterator
  {
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
  };

  // reverse iterator
  template <typename Iter>
  class reverse_iterator
  {
    private:
      Iter m_base;
      reverse_iterator();

    public:
      typedef Iter iterator_type;
      typedef typename iterator_traits<Iter>::iterator_category iterator_category;
      typedef typename iterator_traits<Iter>::value_type value_type;
      typedef typename iterator_traits<Iter>::difference_type difference_type;
      typedef typename iterator_traits<Iter>::pointer pointer;
      typedef typename iterator_traits<Iter>::reference reference;

      reverse_iterator(Iter base): m_base(base)
      {}

      reverse_iterator(const reverse_iterator<Iter> &other): m_base(other.base)
      {}

      ~reverse_iterator()
      {}

      reverse_iterator<Iter> &operator=(const reverse_iterator<Iter> &other)
      {
        m_base = other.base;
        return (*this);
      }

      Iter base() const
      {
        return (m_base);
      }

      reference operator*() const
      {
        Iter iter(m_base);
        --iter;
        return (*iter);
      }

      pointer operator->() const
      {
        Iter iter(m_base);
        --iter;
        return (iter.operator->());
      }

      reverse_iterator<Iter> &operator++()
      {
        --m_base;
        return (*this);
      }

      reverse_iterator<Iter> &operator--()
      {
        ++m_base;
        return (*this);
      }

      reverse_iterator<Iter> operator++(int)
      {
        reverse_iterator<Iter> temp(m_base++);
        return (temp);
      }

      reverse_iterator<Iter> operator--(int)
      {
        reverse_iterator<Iter> temp(m_base--);
        return (temp);
      }

      reverse_iterator<Iter> &operator+=(difference_type offset)
      {
        m_base -= offset;
        return (*this);
      }

      reverse_iterator<Iter> &operator-=(difference_type offset)
      {
        m_base += offset;
        return (*this);
      }
  };

  // reverse iterator non-member functions
  template <typename Iter1, typename Iter2>
	bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
	{
		reverse_iterator<Iter> temp(it.base() - n);
		return (temp);
	}

	template <typename Iter>
	typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif