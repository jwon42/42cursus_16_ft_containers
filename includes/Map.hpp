/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:49:46 by jwon              #+#    #+#             */
/*   Updated: 2021/09/04 03:36:08 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "Utils.hpp"
# include "MapIterator.hpp"
# include "Iterator.hpp"

// std::map reference
// https://www.cplusplus.com/reference/map/map/

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		struct Node
		{
			ft::pair<const Key, T> val;
			Node* parent;
			Node* left;
			Node* right;
			int height;
		};

		public:
			typedef Key key_type; // 각 map 요소에 저장된 정렬 키를 나타내는 형식
			typedef T mapped_type; // 각 map 요소에 저장된 데이터를 나타내는 형식
			typedef ft::pair<const key_type, mapped_type> value_type; // map에 저장된 데이터 형식을 나타내는 형식
			typedef Compare key_compare; // map의 두 요소간 상대적 순서를 결정하는 두 정렬 키를 비교할 수 있는 함수 개체에 대한 typedef
			typedef Alloc allocator_type; // map 개체를 위한 allocator 클래스를 나타내는 형식

			typedef Node* node_pointer; // node 포인터를 나타내는 형식
			typedef typename Alloc::template rebind<Node>::other node_allocator; // node 할당자를 나타내는 형식

			typedef typename allocator_type::reference reference; // map에 저장된 요소에 대한 참조를 제공하는 형식
			typedef typename allocator_type::const_reference const_reference; // 위와 동일, 하지만 요소의 변경을 원하지 않는 경우 사용
			typedef typename allocator_type::pointer pointer; // map에 저장된 요소에 대한 포인터를 제공하는 형식
			typedef typename allocator_type::const_pointer const_pointer; // 위와 동일, 하지만 요소의 변경을 원하지 않는 경우 사용

			typedef map_iterator<Key, T, Compare, Node> iterator; // map에 있는 모든 요소를 읽거나 수정할 수 있는 반복자를 제공하는 형식
			typedef const_map_iterator<Key, T, Compare, Node> const_iterator; // 위와 동일, 하지만 요소의 변경을 원하지 않는 경우 사용
			typedef reverse_map_iterator<Key, T, Compare, Node> reverse_iterator; // map에 있는 모든 요소를 읽거나 수정할 수 있는 역반복자를 제공하는 형식
			typedef const_reverse_map_iterator<Key, T, Compare, Node> const_reverse_iterator; // 위와 동일, 하지만 요소의 변경을 원하지 않는 경우 사용

			typedef ptrdiff_t difference_type; // map 개체 내에서 두 요소 주소의 차이를 제공하는 형식
			typedef size_t size_type; // map의 요소 수를 계산하는 형식

		private:
			node_pointer m_root;
			node_pointer m_last_inserted_node;
			size_type m_size;
			key_compare m_compare;
			allocator_type m_alloc;

		public:
			// default constructor (1)
			// 요소 없는 빈 map 생성
			explicit map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			: m_root(NULL), m_last_inserted_node(NULL), m_size(0), m_compare(comp), m_alloc(alloc) {}

			// constructor overloading (2)
			// iterator가 지정한 구간(first~last)의 요소를 복사하여 map 생성
			template <class InputIterator>
			map(typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first,
				InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			: m_root(NULL), m_last_inserted_node(NULL), m_size(0), m_compare(comp), m_alloc(alloc)
			{
				while (first != last)
					this->insert(*first++);
			}

			// constructor overloading (3)
			// 복사생성자, map x의 요소를 그대로 복사
			map(const map& x)
			: m_root(NULL), m_last_inserted_node(NULL), m_size(0), m_compare(key_compare()), m_alloc(allocator_type())
			{
				for (const_iterator it = x.begin(); it != x.end(); it++)
					this->insert(*it);
			}

			// destructor
			~map()
			{
				this->clear();
			}

			// asign operator
			map& operator=(const map& x)
			{
				map tmp(x);
				this->swap(tmp);
				return (*this);
			}

			// iterators
			iterator begin()
			{
				return (iterator(this->min_node(m_root)));
			}

			const_iterator begin() const
			{
				return (const_iterator(this->min_node(m_root)));
			}

			iterator end()
			{
				if (this->empty())
					return (iterator());
				return (iterator((this->max_node(m_root))->right,
					this->max_node(m_root)));
			}

			const_iterator end() const
			{
				if (this->empty())
					return (iterator());
				return (const_iterator((this->max_node(m_root))->right,
					this->max_node(m_root)));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->max_node(m_root)));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->max_node(m_root)));
			}

			reverse_iterator rend()
			{
				if (this->empty())
					return (reverse_iterator(m_root));
				return (reverse_iterator((this->min_node(m_root))->left,
					this->min_node(m_root)));
			}

			const_reverse_iterator rend() const
			{
				if (this->empty())
					return (const_reverse_iterator(m_root));
				return (const_reverse_iterator((this->min_node(m_root))->left,
					this->min_node(m_root)));
			}

			// capacity
			bool empty() const
			{
				return (m_size == 0);
			}

			size_type size() const
			{
				return (m_size);
			}

			size_type max_size() const
			{
				return (node_allocator(m_alloc).max_size());
			}

			// element access operator
			mapped_type& operator[](const key_type& k)
			{
				m_root = this->insert_node(m_root, NULL, ft::make_pair(k, mapped_type()));

				node_pointer element = m_last_inserted_node;
				m_last_inserted_node = NULL;
				return (element->val.second);
			}

			// modifiers
			pair<iterator,bool> insert(const value_type& val)
			{
				size_type prev_size = this->size();

				m_root = this->insert_node(m_root, NULL, val);
				node_pointer newnode = m_last_inserted_node;
				m_last_inserted_node = NULL;
				return (ft::pair<iterator, bool>(iterator(newnode),
					(this->size() > prev_size)));
			}

			iterator insert(iterator position, const value_type& val)
			{
				(void)position;
				return insert(val).first;
			}

			template <class InputIterator>
			void insert(typename ft::enable_if<!std::numeric_limits<InputIterator>
				::is_integer, InputIterator>::type first, InputIterator last)
			{
				while (first != last)
					this->insert(*first++);
			}

			void erase(iterator position)
			{
				m_root = this->delete_node(m_root, position->first);
			}

			size_type erase(const key_type& k)
			{
				size_type prev_size = this->size();
				m_root = this->delete_node(m_root, k);

				return ((this->size() == prev_size) ? 0 : 1);
			}

			void erase(iterator first, iterator last)
			{
				map tmp(first, last);
				for (reverse_iterator it = tmp.rbegin(); it != tmp.rend(); ++it)
					this->erase(it->first);
			}

			void swap(map& x)
			{
				swap(m_root, x.m_root);
				swap(m_size, x.m_size);
				swap(m_compare, x.m_compare);
				swap(m_alloc, x.m_alloc);
			}

			void clear()
			{
				m_root = this->clear_tree(m_root);
				m_size = 0;
			}

			// observer
			key_compare key_comp() const
			{
				return (m_compare);
			}

			class value_compare
			{
				// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
				friend class map;
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

				bool operator()(const value_type &x, const value_type &y) const
				{
					return comp(x.first, y.first);
				}

				protected:
					key_compare comp;
					value_compare(Compare c) : comp(c) {}
			};

			value_compare value_comp() const
			{
				return (value_compare(m_compare));
			}

			// operations
			iterator find(const key_type& k)
			{
				return (search_tree(m_root, k) ? iterator(search_tree(m_root, k)) : end());
			}

			const_iterator find(const key_type& k) const
			{
				return (search_tree(m_root, k) ? const_iterator(search_tree(m_root, k)) : end());
			}

			size_type count(const key_type& k) const
			{
				return (search_tree(m_root, k) ? 1 : 0);
			}

			iterator lower_bound(const key_type& k)
			{
				iterator lower = this->begin();
				iterator end = this->end();
				while (lower != end && m_compare(lower->first, k))
					lower++;
				return (lower);
			}

			const_iterator lower_bound(const key_type& k) const
			{
				const_iterator lower = this->begin();
				const_iterator end = this->end();
				while (lower != end && m_compare(lower->first, k))
					lower++;
				return (lower);
			}

			iterator upper_bound(const key_type& k)
			{
				iterator upper = this->begin();
				iterator end = this->end();
				while (upper != end && !m_compare(k, upper->first))
					upper++;
				return (upper);
			}

			const_iterator upper_bound(const key_type& k) const
			{
				const_iterator upper = this->begin();
				const_iterator end = this->end();
				while (upper != end && !m_compare(k, upper->first))
					upper++;
				return (upper);
			}

			pair<const_iterator,const_iterator> equal_range(const key_type& k) const
			{
				pair<const_iterator, const_iterator> range;

				range.first = this->lower_bound(k);
				range.second = this->upper_bound(k);
				return (range);
			}

			pair<iterator,iterator> equal_range(const key_type& k)
			{
				pair<iterator, iterator> range;

				range.first = this->lower_bound(k);
				range.second = this->upper_bound(k);
				return (range);
			}


			// allocator
			allocator_type get_allocator() const
			{
				return (m_alloc);
			}

		private:
			template<class X>
			void swap(X& x1, X& x2)
			{
				X tmp = x2;
				x2 = x1;
				x1 = tmp;
			}

			int		get_height(node_pointer node) const
			{
				if (node != NULL)
					return (node->height);
				return (0);
			}

			int		get_balance(node_pointer node) const
			{
				if (node == NULL)
					return (0);
				return (get_height(node->left) - get_height(node->right));
			}

			node_pointer	left_rotate(node_pointer node)
			{
				node_pointer	new_parent;

				new_parent = node->right;				// new_parent = Q;
				new_parent->parent = node->parent;		// Q->parent = P->parent;
				node->parent = new_parent;				// P->parent = Q;
				node->right = new_parent->left;			// P->right = B;
				if (new_parent->left)					// if (Q->left)
					new_parent->left->parent = node;	//	   B->parent = P;
				new_parent->left = node;				// Q->left = P;
				node->height = 1 + std::max(get_height(node->left), get_height(node->right));
				new_parent->height = 1 + std::max(get_height(new_parent->left), get_height(new_parent->right));
				return (new_parent);
			}

			node_pointer	right_rotate(node_pointer node)
			{
				node_pointer	new_parent;

				new_parent = node->left;				// new_parent = P;
				new_parent->parent = node->parent;		// P->parent = Q->parent;
				node->parent = new_parent;				// Q->parent = P;
				node->left = new_parent->right;			// Q->left = B;
				if (new_parent->right)					// if (P->right)
					new_parent->right->parent = node;	//     B->parent = Q;
				new_parent->right = node;				// P->right = Q;
				node->height = 1 + std::max(get_height(node->left), get_height(node->right));
				new_parent->height = 1 + std::max(get_height(new_parent->left), get_height(new_parent->right));
				return (new_parent);
			}

			node_pointer	left_right_rotate(node_pointer node)
			{
				node->left = this->left_rotate(node->left);
				return (this->right_rotate(node));
			}

			node_pointer	right_left_rotate(node_pointer node)
			{
				node->right = this->right_rotate(node->right);
				return (this->left_rotate(node));
			}

			node_pointer	balance_tree(node_pointer node)
			{
				int	factor = get_balance(node);
				if (factor == 2)
				{
					if (get_balance(node->left) >= 0)
						return (this->right_rotate(node));
					else
						return (this->left_right_rotate(node));
				}
				else if (factor == -2)
				{
					if (get_balance(node->right) <= 0)
						return (this->left_rotate(node));
					else
						return (this->right_left_rotate(node));
				}
				return (node);
			}

			node_pointer	create_node(const value_type& val, node_pointer parent)
			{
				node_pointer	new_node = node_allocator(m_alloc).allocate(1);

				new_node->left = NULL;
				new_node->right = NULL;
				new_node->height = 1;
				new_node->parent = parent;
				m_alloc.construct(&new_node->val, val);

				m_size++;

				m_last_inserted_node = new_node;
				return (new_node);
			}

			node_pointer	insert_node(node_pointer node, node_pointer parent, const value_type& val)
			{
				if (node == NULL)
					return (create_node(val, parent));

				if (m_compare(val.first, node->val.first))
					node->left = insert_node(node->left, node, val);
				else if (m_compare(node->val.first, val.first))
					node->right = insert_node(node->right, node, val);
				else
					return (m_last_inserted_node = node);

				node->height = 1 + std::max(get_height(node->left), get_height(node->right));

				return(balance_tree(node));
			}

			node_pointer	delete_node(node_pointer node, const key_type& key)
			{
				if (node == NULL)
					return (NULL);

				if (m_compare(key, node->val.first))
					node->left = delete_node(node->left, key);
				else if (m_compare(node->val.first, key))
					node->right = delete_node(node->right, key);
				else
				{
					if ((node->left == NULL) || (node->right == NULL))
					{
						node_pointer tmp = node->left ? node->left : node->right;
						if (tmp == NULL)
							swap(tmp, node);
						else
						{
							m_alloc.destroy(&node->val);
							m_alloc.construct(&node->val, tmp->val);
							node->left = NULL;
							node->right = NULL;
						}
						m_alloc.destroy(&tmp->val);
						node_allocator(m_alloc).deallocate(tmp, 1);
						this->m_size--;
					}
					else
					{
						node_pointer tmp = this->min_node(node->right);
						m_alloc.destroy(&node->val);
						m_alloc.construct(&node->val, tmp->val);
						node->right = delete_node(node->right, tmp->val.first);
					}
				}

				return(balance_tree(node));
			}

			node_pointer	clear_tree(node_pointer node)
			{
				if (!node)
					return (NULL);
				if (node->left)
					clear_tree(node->left);
				if (node->right)
					clear_tree(node->right);
				m_alloc.destroy(&node->val);
				node_allocator(m_alloc).deallocate(node, 1);
				m_size--;
				return (NULL);
			}

			node_pointer	search_tree(node_pointer node, const key_type& key) const
			{
				if (node == NULL)
					return (NULL);
				if (!m_compare(node->val.first, key) && !m_compare(key, node->val.first))
					return (node);
				if (m_compare(key, node->val.first))
					return (search_tree(node->left, key));
				else if (m_compare(node->val.first, key))
					return (search_tree(node->right, key));
				return (NULL);
			}

			node_pointer	min_node(node_pointer node) const
			{
				while (node && node->left != NULL)
					node = node->left;
				return (node);
			}

			node_pointer	max_node(node_pointer node) const
			{
				while (node && node->right != NULL)
					node = node->right;
				return (node);
			}
	};

	// overload
	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
			rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs,
		const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y)
	{
		x.swap(y);
	}
}

#endif