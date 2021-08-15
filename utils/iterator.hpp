/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 14:15:05 by jwon              #+#    #+#             */
/*   Updated: 2021/08/15 20:40:03 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft {
  /* ITERATOR TAGS */
  struct input_iterator_tag {};
  struct output_iterator_tag : public input_iterator_tag {};
  struct forward_iterator_tag : public output_iterator_tag {};
  struct bidirectional_iterator_tag : public forward_iterator_tag {};
  struct random_access_iterator_tag : public bidirectional_iterator_tag {};

  /* STANDARD ITERATOR TRAITS */
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

  /* ITERATOR TRAITS FOR POINTER */
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

  /* ITERATOR TRAITS FOR CONST POINTER */
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

  /* ITERATOR */
  template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
  struct iterator
  {
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
  };

  /* REVERSE ITERATOR */
  template <typedef Iter>
  class reverse_iterator
  {
    private:
      Iter m_base;
      reverse_iterator();

    public:
      typedef Iter iterator_type;
      typedef typename iterator_traits<Iter>::iterator_category iterator_category
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
}

#endif