/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:49:30 by jwon              #+#    #+#             */
/*   Updated: 2021/10/17 20:23:33 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include <stddef.h>
# include <iostream>

# include "../Utils.hpp"
# include "IteratorUtils.hpp"

namespace ft
{
	template<class Key, class T, class Compare, typename Node> class const_map_iterator;

	template<class Key, class T, class Compare, typename Node>
	class map_iterator
	{
		public:
		  typedef ft::bidirectional_iterator_tag iterator_category;
			typedef Key key_type;
			typedef T mapped_type;
			typedef Compare key_compare;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef ptrdiff_t difference_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			typedef Node* node_pointer;

		protected:
			node_pointer m_node;
			node_pointer m_end_node;

		private:
			map_iterator(const const_map_iterator<Key,T,Compare,Node>& ) {}

		public:
			map_iterator(node_pointer node = NULL) : m_node(node), m_end_node(node)
			{
				if (m_end_node != NULL)
				{
					while (m_end_node->parent != NULL)
						m_end_node = m_end_node->parent;
					while (m_end_node->right != NULL)
						m_end_node = m_end_node->right;
				}
			}

			map_iterator(node_pointer node, node_pointer end_node)
			: m_node(node), m_end_node(end_node)
			{}

			map_iterator(const map_iterator& rhs)
			: m_node(rhs.m_node), m_end_node(rhs.m_end_node)
			{}

			~map_iterator()
			{}

			node_pointer	get_node() const
			{
				return (m_node);
			}

			map_iterator& operator=(const map_iterator& rhs)
			{
				if (this != &rhs)
				{
					m_node = rhs.m_node;
					m_end_node = rhs.m_end_node;
				}
				return (*this);
			}

			bool operator==(const map_iterator& rhs) const
			{
				return (m_node == rhs.m_node);
			}

			bool operator!=(const map_iterator& rhs) const
			{
				return (m_node != rhs.m_node);
			}

			reference operator*() const
			{
				return (m_node->val);
			}

			pointer operator->() const
			{
				return (&(m_node->val));
			}

			map_iterator& operator++()
			{
				if (m_node == NULL)
				{
					m_node = m_end_node;
					m_end_node = NULL;
					return (*this);
				}
				else if (m_node->right != NULL)
				{
					m_node = m_node->right;
					while (m_node->left != NULL)
						m_node = m_node->left;
				}
				else
				{
					Node* origin = m_node;
					m_node = m_node->parent;
					while (m_node && m_node->right == origin)
					{
						origin = m_node;
						m_node = m_node->parent;
					}
				}
				return (*this);
			}

			map_iterator operator++(int)
			{
				map_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			map_iterator& operator--()
			{
				if (m_node == NULL)
				{
					m_node = m_end_node;
					m_end_node = NULL;
					return (*this);
				}
				else if (m_node->left != NULL)
				{
					m_node = m_node->left;
					while (m_node->right != NULL)
						m_node = m_node->right;
				}
				else
				{
					Node* origin = m_node;
					m_node = m_node->parent;
					while (m_node && m_node->left == origin)
					{
						origin = m_node;
						m_node = m_node->parent;
					}
				}
				return (*this);
			}

			map_iterator operator--(int)
			{
				map_iterator tmp(*this);
				--(*this);
				return (tmp);
			}
	};

	template<class Key, class T, class Compare, typename Node>
	class const_map_iterator : public map_iterator<Key,T,Compare,Node>
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef Compare key_compare;
			typedef ft::pair<const key_type, mapped_type>	value_type;
			typedef value_type const & const_reference;
			typedef value_type const * const_pointer;
			typedef Node* node_pointer;

			const_map_iterator(node_pointer node = NULL)
			{
				this->m_node = node;
				this->m_end_node = node;
				if (this->m_end_node != NULL)
				{
					while (this->m_end_node->parent != NULL)
						this->m_end_node = this->m_end_node->parent;
					while (this->m_end_node->right != NULL)
						this->m_end_node = this->m_end_node->right;
				}
			}

			const_map_iterator(node_pointer node, node_pointer end_node)
			{
				this->m_node = node;
				this->m_end_node = end_node;
			}

			const_map_iterator(const map_iterator<Key,T,Compare,Node>& rhs)
			{
				this->m_node = rhs.get_node();
			}

			const_map_iterator& operator=(const const_map_iterator& rhs)
			{
				if (this != &rhs)
					this->m_node = rhs.m_node;
				return (*this);
			}

			bool operator==(const const_map_iterator& rhs) const
			{
				return (this->m_node == rhs.m_node);
			}

			bool operator!=(const const_map_iterator& rhs) const
			{
				return (this->m_node != rhs.m_node);
			}

			const_reference operator*() const
			{
				return (this->m_node->val);
			}

			const_pointer operator->() const
			{
				return (&(this->m_node->val));
			}
	};

	template<class Key, class T, class Compare, typename Node> class const_reverse_map_iterator;

	template<class Key, class T, class Compare, typename Node>
	class reverse_map_iterator
	{
		public:
		  typedef ft::bidirectional_iterator_tag iterator_category;
			typedef Key key_type;
			typedef T mapped_type;
			typedef Compare key_compare;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef ptrdiff_t difference_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			typedef Node* node_pointer;

		protected:
			map_iterator<Key, T, Compare, Node> m_base;

		private:
			reverse_map_iterator(const const_reverse_map_iterator<Key, T, Compare, Node> &) {}

		public:
			explicit reverse_map_iterator(node_pointer node = NULL)
			: m_base(map_iterator<Key,T,Compare,Node>(node))
			{}

			reverse_map_iterator(node_pointer node, node_pointer end_node)
			: m_base(map_iterator<Key,T,Compare,Node>(node, end_node))
			{}

			explicit reverse_map_iterator(map_iterator<Key,T,Compare,Node> & rhs)
			{
				this->m_base = rhs;
			}

			reverse_map_iterator(const reverse_map_iterator<Key,T,Compare,Node > & rhs)
			{
				this->m_base = rhs.m_base;
			}

			node_pointer get_node() const
			{
				return (this->m_base.get_node());
			}

			map_iterator<Key,T,Compare,Node> base() const
			{
				return (this->m_base);
			}

			reverse_map_iterator& operator=(const reverse_map_iterator & rhs)
			{
				if (this != &rhs)
				{
					this->m_base = rhs.m_base;
				}
				return (*this);
			}

			bool operator==(const reverse_map_iterator & rhs) const
			{
				return (m_base == rhs.m_base);
			}

			bool operator!=(const reverse_map_iterator & rhs) const
			{
				return (m_base != rhs.m_base);
			}

			reference operator*() const
			{
				return (*(map_iterator<Key,T,Compare,Node>(this->m_base)));
			}

			pointer operator->() const
			{
				return (&this->operator*());
			}

			reverse_map_iterator& operator++()
			{
				this->m_base.operator--();

				return (*this);
			}

			reverse_map_iterator operator++(int)
			{
				reverse_map_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			reverse_map_iterator& operator--()
			{
				this->m_base.operator++();
				return (*this);
			}

			reverse_map_iterator operator--(int)
			{
				reverse_map_iterator tmp(*this);
				--(*this);
				return (tmp);
			}
	};

	template<class Key, class T, class Compare, typename Node>
	class const_reverse_map_iterator : public reverse_map_iterator<Key,T,Compare,Node>
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef Compare key_compare;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef value_type const & const_reference;
			typedef value_type const * const_pointer;
			typedef Node* node_pointer;

			explicit const_reverse_map_iterator(map_iterator<Key, T, Compare, Node> & rhs)
			{
				this->m_base = rhs.get_node();
			}

			const_reverse_map_iterator(node_pointer node = NULL)
			{
				this->m_base = map_iterator<Key,T,Compare,Node>(node);
			}

			const_reverse_map_iterator(node_pointer node, node_pointer end_node)
			{
				this->m_base = map_iterator<Key,T,Compare,Node>(node, end_node);
			}

			const_reverse_map_iterator(const_map_iterator<Key,T,Compare,Node> rhs)
			{
				this->m_base = rhs.get_node();
			}

			const_reverse_map_iterator(const reverse_map_iterator<Key,T,Compare,Node>& rhs)
			{
				this->m_base = rhs.get_node();
			}

			const_reverse_map_iterator& operator=(const const_reverse_map_iterator& rhs)
			{
				if (this != &rhs)
					this->m_base = rhs.m_base;
				return (*this);
			}

			bool operator==(const const_reverse_map_iterator& rhs) const
			{
				return (this->m_base == rhs.m_base);
			}

			bool operator!=(const const_reverse_map_iterator& rhs) const
			{
				return (this->m_base != rhs.m_base);
			}

			const_reference operator*() const
			{
				return (*(map_iterator<Key,T,Compare,Node>(this->m_base)));
			}

			const_pointer operator->() const
			{
				return (&this->operator*());
			}
	};
}

#endif