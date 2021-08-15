/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 14:15:05 by jwon              #+#    #+#             */
/*   Updated: 2021/08/15 16:05:33 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>

namespace ft {
  struct input_iterator_tag {};
  struct output_iterator_tag : public input_iterator_tag {};
  struct forward_iterator_tag : public output_iterator_tag {};
  struct bidirectional_iterator_tag : public forward_iterator_tag {};
  struct random_access_iterator_tag : public bidirectional_iterator_tag {};

  template <class Category, class T, bool is_const, class Distance = std::ptrdiff_t>
  class iterator {
    public:
      typedef T value_type;
      typedef Distance difference_type;
      typedef typename std::conditional<is_const, const T*, T*>::type pointer;
      typedef typename std::conditional<is_const, const T&, T&>::type reference;
      typedef Category iterator_category;
  };

  template <typename it>
  struct iterator_traits {
    public:
      typedef typename it::value_type value_type;
      typedef typename it::difference_type difference_type;
      typedef typename it::pointer pointer;
      typedef typename it::reference reference;
      typedef typename it::iterator_category iterator_category;
  };
}

#endif