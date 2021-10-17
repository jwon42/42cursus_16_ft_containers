/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 14:52:21 by jwon              #+#    #+#             */
/*   Updated: 2021/10/16 13:41:24 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include "IteratorUtils.hpp"

namespace ft
{
	template<class T> class const_vector_iterator;

	template<class T>
	class vector_iterator
	{
		public:
			typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef ft::random_access_iterator_tag iterator_category;
			typedef value_type* pointer;
			typedef value_type& reference;

		protected:
			pointer	m_ptr;

		private:
			vector_iterator(const const_vector_iterator<T>& )
			{}

		public:
			vector_iterator(pointer ptr = NULL) : m_ptr(ptr)
			{}

			vector_iterator(const vector_iterator & rhs) : m_ptr(rhs.m_ptr)
			{}

			~vector_iterator()
			{}

			vector_iterator& operator=(const vector_iterator & it)
			{
				if (this != &it)
					this->m_ptr = it.m_ptr;
				return (*this);
			}

			bool operator==(const vector_iterator& it) const
			{
				return (this->m_ptr == it.m_ptr);
			}

			bool operator!=(const vector_iterator& it) const
			{
				return (this->m_ptr != it.m_ptr);
			}

			reference operator*() const
			{
				return (*this->m_ptr);
			}

			reference operator[](size_t n)
			{
				return (this->m_ptr[n]);
			}

			pointer operator->() const
			{
				return (this->m_ptr);
			}

			vector_iterator& operator++()
			{
				this->m_ptr++;
				return (*this);
			}

			vector_iterator operator++(int)
			{
				vector_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			vector_iterator& operator--()
			{
				this->m_ptr--;
				return (*this);
			}

			vector_iterator operator--(int)
			{
				vector_iterator tmp(*this);
				--(*this);
				return (tmp);
			}

			vector_iterator operator+(difference_type n) const
			{
				return (vector_iterator(this->m_ptr + n));
			}

			difference_type operator+(const vector_iterator& rhs) const
			{
				return (this->m_ptr + rhs.m_ptr);
			}

			vector_iterator operator-(difference_type n) const
			{
				return (vector_iterator(this->m_ptr - n));
			}

			difference_type operator-(const vector_iterator& rhs) const
			{
				return (this->m_ptr - rhs.m_ptr);
			}

			friend vector_iterator operator+(difference_type n, const vector_iterator& rhs)
			{
				return (rhs.operator+(n));
			}

			vector_iterator& operator+=(int n)
			{
				this->m_ptr += n;
				return (*this);
			}

			vector_iterator& operator-=(int n)
			{
				this->m_ptr -= n;
				return (*this);
			}

			bool operator<(const vector_iterator& rhs) const
			{
				return (this->m_ptr < rhs.m_ptr);
			}

			bool operator>(const vector_iterator& rhs) const
			{
				return (this->m_ptr > rhs.m_ptr);
			}

			bool operator<=(const vector_iterator& rhs) const
			{
				return (this->m_ptr <= rhs.m_ptr);
			}

			bool operator>=(const vector_iterator& rhs) const
			{
				return (this->m_ptr >= rhs.m_ptr);
			}
	};

	template<class T>
	class const_vector_iterator : public vector_iterator<T>
	{
		public:
			typedef T* pointer;
			typedef T const & const_reference;
			typedef T const * const_pointer;

		public:
			const_reference operator[](size_t n)
			{
				return (this->m_ptr[n]);
			}

			const_vector_iterator(pointer ptr = NULL)
			{
				this->m_ptr = ptr;
			}

			const_vector_iterator(const vector_iterator<T>& rhs)
			{
				this->m_ptr = rhs.operator->();
			}

			const_vector_iterator& operator=(const const_vector_iterator& rhs)
			{
				if (this != &rhs)
					this->m_ptr = rhs.m_ptr;
				return (*this);
			}

			bool operator<(const const_vector_iterator& rhs) const
			{
				return (this->m_ptr < rhs.m_ptr);
			}

			bool operator>(const const_vector_iterator& rhs) const
			{
				return (this->m_ptr > rhs.m_ptr);
			}

			bool operator<=(const const_vector_iterator& rhs) const
			{
				return (this->m_ptr <= rhs.m_ptr);
			}

			bool operator>=(const const_vector_iterator& rhs) const
			{
				return (this->m_ptr >= rhs.m_ptr);
			}

			const_reference operator*() const
			{
				return (*this->m_ptr);
			}

			const_pointer operator->() const
			{
				return (this->m_ptr);
			}

	};

	template<class T> class const_reverse_vector_iterator;

	template<class T>
	class reverse_vector_iterator
	{
		public:
			typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef ft::random_access_iterator_tag iterator_category;
			typedef value_type* pointer;
			typedef value_type& reference;

		protected:
			vector_iterator<T> m_base;

		private:
			reverse_vector_iterator(const const_reverse_vector_iterator<T> &)
			{}

		public:
			reverse_vector_iterator(pointer ptr = NULL)
			: m_base(vector_iterator<T>(ptr))
			{}

			explicit reverse_vector_iterator(vector_iterator<T> rhs) : m_base(--rhs)
			{}

			reverse_vector_iterator(const reverse_vector_iterator<T>& rhs)
			: m_base(rhs.m_base)
			{}

			vector_iterator<T> base() const
			{
				vector_iterator<T> tmp(m_base);
				return (++tmp);
			}

			reverse_vector_iterator& operator=(const reverse_vector_iterator& rhs)
			{
				if (this != &rhs)
					m_base = rhs.m_base;
				return (*this);
			}

			bool operator==(const reverse_vector_iterator& rhs) const
			{
				return m_base.operator==(rhs.m_base);
			}

			bool operator!=(const reverse_vector_iterator& rhs) const
			{
				return m_base.operator!=(rhs.m_base);
			}

			bool operator<(const reverse_vector_iterator& rhs) const
			{
				return m_base.operator>(rhs.m_base);
			}

			bool operator<=(const reverse_vector_iterator& rhs) const
			{
				return m_base.operator>=(rhs.m_base);
			}

			bool operator>(const reverse_vector_iterator& rhs) const
			{
				return m_base.operator<(rhs.m_base);
			}

			bool operator>=(const reverse_vector_iterator& rhs) const
			{
				return m_base.operator<=(rhs.m_base);
			}

			reference operator[](size_t n)
			{
				return m_base[-n];
			}

			reference operator*() const
			{
				return (*(vector_iterator<T>(m_base)));
			}

			pointer operator->() const
			{
				return (&this->operator*());
			}

			friend reverse_vector_iterator operator+(difference_type n, const reverse_vector_iterator& rhs)
			{
				return (rhs.operator+(n));
			}

			reverse_vector_iterator operator+(difference_type n) const
			{
				reverse_vector_iterator tmp(*this);
				tmp.m_base.operator-=(n);
				return (tmp);
			}

			difference_type operator+(const reverse_vector_iterator& rhs) const
			{
				return (rhs.base().operator-(m_base + 1));
			}

			reverse_vector_iterator operator-(difference_type n) const
			{
				reverse_vector_iterator tmp(*this);
				tmp.m_base.operator+=(n);
				return (tmp);
			}

			difference_type operator-(const reverse_vector_iterator& rhs) const
			{
				return (rhs.base().operator-(m_base + 1));
			}

			reverse_vector_iterator& operator+=(int n)
			{
				m_base.operator-=(n);
				return (*this);
			}

			reverse_vector_iterator& operator-=(int n)
			{
				m_base.operator+=(n);
				return (*this);
			}

			reverse_vector_iterator& operator++()
			{
				--m_base;
				return (*this);
			}

			reverse_vector_iterator operator++(int)
			{
				reverse_vector_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			reverse_vector_iterator& operator--()
			{
				m_base.operator++();
				return (*this);
			}

			reverse_vector_iterator operator--(int)
			{
				reverse_vector_iterator tmp(*this);
				--(*this);
				return (tmp);
			}
	};

	template<class T>
	class const_reverse_vector_iterator : public reverse_vector_iterator<T>
	{
		public:
			typedef T* pointer;
			typedef T const & const_reference;
			typedef T const * const_pointer;

			explicit const_reverse_vector_iterator(vector_iterator<T> rhs)
			{
				vector_iterator<T> tmp(rhs);
				this->m_base = --tmp;
			}

			const_reverse_vector_iterator(pointer ptr = NULL)
			{
				this->m_base = vector_iterator<T>(ptr);
			}

			const_reverse_vector_iterator(const_vector_iterator<T> & rhs)
			{
				pointer ptr = const_cast<pointer>(rhs.operator->());
				vector_iterator<T> tmp(ptr);
				this->m_base = tmp;
			}

			const_reverse_vector_iterator(const reverse_vector_iterator<T>& rhs)
			{
				this->m_base = rhs.operator->();
			}

			const_reverse_vector_iterator& operator=(const const_reverse_vector_iterator& rhs)
			{
				if (this != &rhs)
					this->m_base = rhs.m_base;
				return (*this);
			}

			const_reference operator*() const
			{
				return (*(vector_iterator<T>(this->m_base)));
			}

			const_pointer operator->() const
			{
				return (&this->operator*());
			}
	};
}

#endif
