/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwon <jwon@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:49:46 by jwon              #+#    #+#             */
/*   Updated: 2021/10/17 20:18:35 by jwon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "Utils.hpp"
# include "iterator/MapIterator.hpp"
# include "iterator/IteratorUtils.hpp"

// std::map reference
// https://www.cplusplus.com/reference/map/map/

namespace ft
{
	template < typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		struct Node
		{
			ft::pair<const Key, T> val;
			Node* parent;
			Node* left;
			Node* right;
			int height; // leaf 노드까지 가는 가장 긴 경로(높이)
		};

		public:
			typedef Key key_type; // 각 map 요소에 저장된 정렬 키를 나타내는 형식
			typedef T mapped_type; // 각 map 요소에 저장된 데이터를 나타내는 형식
			typedef ft::pair<const key_type, mapped_type> value_type; // map에 저장된 데이터 형식을 나타내는 형식
			typedef Compare key_compare; // map의 두 요소간 상대적 순서를 결정하는 두 정렬 키를 비교할 수 있는 함수 개체에 대한 typedef
			typedef Alloc allocator_type; // map 개체를 위한 allocator 클래스를 나타내는 형식

			typedef Node* node_ptr; // node 포인터를 나타내는 형식
			typedef typename Alloc::template rebind<Node>::other node_alloc; // node 할당자를 나타내는 형식

			typedef typename allocator_type::reference reference; // map에 저장된 요소에 대한 참조를 제공하는 형식
			typedef typename allocator_type::const_reference const_reference; // 위와 동일, 하지만 요소의 변경을 원하지 않는 경우 사용
			typedef typename allocator_type::pointer pointer; // map에 저장된 요소에 대한 포인터를 제공하는 형식
			typedef typename allocator_type::const_pointer const_pointer; // 위와 동일, 하지만 요소의 변경을 원하지 않는 경우 사용

			typedef ft::map_iterator<Key, T, Compare, Node> iterator; // map에 있는 모든 요소를 읽거나 수정할 수 있는 반복자를 제공하는 형식
			typedef ft::const_map_iterator<Key, T, Compare, Node> const_iterator; // 위와 동일, 하지만 요소의 변경을 원하지 않는 경우 사용
			typedef ft::reverse_map_iterator<Key, T, Compare, Node> reverse_iterator; // map에 있는 모든 요소를 읽거나 수정할 수 있는 역반복자를 제공하는 형식
			typedef ft::const_reverse_map_iterator<Key, T, Compare, Node> const_reverse_iterator; // 위와 동일, 하지만 요소의 변경을 원하지 않는 경우 사용

			typedef ptrdiff_t difference_type; // map 개체 내에서 두 요소 주소의 차이를 제공하는 형식
			typedef size_t size_type; // map의 요소 수를 계산하는 형식

		private:
			node_ptr m_root;
			node_ptr m_last_inserted_node;
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
			map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
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
			// map의 첫번째 요소를 가리키는 iterator 반환
			iterator begin()
			{
				return (iterator(this->smallest_node(m_root)));
			}

			const_iterator begin() const
			{
				return (const_iterator(this->smallest_node(m_root)));
			}

			// map의 마지막 요소를 가리키는 iterator 반환
			iterator end()
			{
				if (this->empty())
					return (iterator());
				return (iterator((this->biggest_node(m_root))->right, this->biggest_node(m_root)));
			}

			const_iterator end() const
			{
				if (this->empty())
					return (const_iterator());
				return (const_iterator((this->biggest_node(m_root))->right, this->biggest_node(m_root)));
			}

			// map의 첫번째 요소를 가리키는 reverse_iterator 반환
			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->biggest_node(m_root)));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->biggest_node(m_root)));
			}

			// map의 마지막 요소를 가리키는 reverse_iterator 반환
			reverse_iterator rend()
			{
				if (this->empty())
					return (reverse_iterator(m_root));
				return (reverse_iterator((this->smallest_node(m_root))->left, this->smallest_node(m_root)));
				// return (--reverse_iterator(begin().get_node()));
			}

			const_reverse_iterator rend() const
			{
				if (this->empty())
					return (const_reverse_iterator(m_root));
				Node *newnode = new Node;
				Node smallest = this->smallest_node(m_root);
				newnode->parent = smallest;
				smallest.left = newnode;
				return (const_reverse_iterator(newnode, this->smallest_node(m_root)));
				// if (this->empty())
				// 	return (const_reverse_iterator(m_root));
				// return (const_reverse_iterator((this->smallest_node(m_root))->left, this->smallest_node(m_root)));
			}

			// capacity
			// map 비어있는지 여부 체크
			bool empty() const
			{
				return (m_size == 0);
			}

			// map에 있는 요소 수를 반환
			size_type size() const
			{
				return (m_size);
			}

			// map의 최대 길이를 반환
			size_type max_size() const
			{
				return (node_alloc(m_alloc).max_size());
				// return (std::numeric_limits<difference_type>::max() / sizeof(value_type));
			}

			// element access operator
			// map에 지정된 위치의 요소에 대한 참조를 반환
			mapped_type& operator[](const key_type& k)
			{
				m_root = this->insert_node(m_root, NULL, ft::make_pair(k, mapped_type()));

				node_ptr element = m_last_inserted_node;
				m_last_inserted_node = NULL;
				return (element->val.second);
			}

			// modifiers
			// pair 구조의 요소를 map에 삽입
			ft::pair<iterator, bool> insert(const value_type& val)
			{
				size_type prev_size = this->size();

				m_root = this->insert_node(m_root, NULL, val);
				node_ptr newnode = m_last_inserted_node;
				m_last_inserted_node = NULL;
				// ((this->biggest_node(m_root))->right)->right = this->smallest_node(m_root);
				return (ft::pair<iterator, bool>(iterator(newnode), (this->size() > prev_size)));
			}

			iterator insert(iterator position, const value_type& val)
			{
				(void)position;
				return insert(val).first;
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last,
			typename ft::enable_if<true, typename InputIterator::value_type>::type* = NULL)
			{
				while (first != last)
				{
					this->insert(*first++);
				}
			}

			// map에서 position의 요소를 삭제
			void erase(iterator position)
			{
				m_root = this->delete_node(m_root, position->first);
			}

			// map에서 요소를 key로 찾아서 삭제
			size_type erase(const key_type& key)
			{
				size_type prev_size = this->size();
				m_root = this->delete_node(m_root, key);
				return ((this->size() == prev_size) ? 0 : 1);
			}

			// map에서 first부터 last까지 요소를 삭제
			void erase(iterator first, iterator last)
			{
				map temp(first, last);
				for (reverse_iterator it = temp.rbegin(); it != temp.rend(); it++)
					this->erase(it->first);
			}

			// 동일한 유형의 다른 map의 요소를 이 map의 요소로 교체
			void swap(map& x)
			{
				std::swap(m_root, x.m_root);
				std::swap(m_size, x.m_size);
				std::swap(m_compare, x.m_compare);
				std::swap(m_alloc, x.m_alloc);
			}

			// map의 모든 요소를 삭제
			void clear()
			{
				m_root = this->remove_tree(m_root);
			}

			// observer
			// key 정렬을 위해 비교 개체의 복사본을 검색
			key_compare key_comp() const
			{
				return (m_compare);
			}

			class value_compare
			{
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					value_compare(Compare c) : comp(c) {}

					bool operator()(const value_type &x, const value_type &y) const
					{
						return comp(x.first, y.first);
					}

				protected:
					key_compare comp;
			};

			value_compare value_comp() const
			{
				return (value_compare(m_compare));
			}

			// operations
			// 지정된 키와 같은 키를 가진 map 요소의 iterator를 반환
			iterator find(const key_type& k)
			{
				return (search_tree(m_root, k) ? iterator(search_tree(m_root, k)) : end());
			}

			const_iterator find(const key_type& k) const
			{
				return (search_tree(m_root, k) ? const_iterator(search_tree(m_root, k)) : end());
			}

			// 지정된 키와 일치하는 map의 요소를 반환 (multimap이 아니므로 0 아니면 1)
			size_type count(const key_type& k) const
			{
				return (search_tree(m_root, k) ? 1 : 0);
			}

			// 지정된 키보다 크거나 같은 키 값을 가진 첫번째 요소의 iterator를 반환
			iterator lower_bound(const key_type& key)
			{
				iterator lower = this->begin();

				while (lower != end())
				{
					if (this->m_compare(lower->first, key) <= 0)
						return (lower);
					++lower;
				}
				return (end());
			}

			const_iterator lower_bound(const key_type& key) const
			{
				const_iterator lower = this->begin();

				while (lower != end())
				{
					if (this->m_compare(lower->first, key) <= 0)
						return (lower);
					++lower;
				}
				return (end());
			}

			// 지정된 키보다 큰 값을 가진 첫번째 요소에 대한 iterator를 반환
			iterator upper_bound(const key_type& key)
			{
				iterator upper = this->begin();

				while (upper != end())
				{
					if (upper->first != key && this->m_compare(upper->first, key) <= 0)
						return (upper);
					++upper;
				}
				return (end());
			}

			const_iterator upper_bound(const key_type& key) const
			{
				const_iterator upper = this->begin();

				while (upper != end())
				{
					if (upper->first != key && this->m_compare(upper->first, key) <= 0)
						return (upper);
					++upper;
				}
				return (end());
			}

			// 지정된 키가 있는 모든 요소를 포함하는 범위의 경계를 반환
			ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const
			{
				pair<const_iterator, const_iterator> range;

				range.first = this->lower_bound(k);
				range.second = this->upper_bound(k);
				return (range);
			}

			ft::pair<iterator,iterator> equal_range(const key_type& k)
			{
				pair<iterator, iterator> range;

				range.first = this->lower_bound(k);
				range.second = this->upper_bound(k);
				return (range);
			}


			// allocator
			// map 생성에 필요한 할당자의 복사본을 반환
			allocator_type get_allocator() const
			{
				return (m_alloc);
			}

		private:
			int get_height(node_ptr node) const
			{
				if (node == NULL)
					return (0);
				return (node->height);
			}

			// node height 갱신
			void set_height(node_ptr node)
			{
				node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
			}

			// 균형인수(balance factor) 계산
			// 음수가 나오면 right subtree가 left subtree 보다 높고, 양수라면 반대.
			int get_balance_factor(node_ptr node) const
			{
				if (node == NULL)
					return (0);
				return (get_height(node->left) - get_height(node->right));
			}

			node_ptr left_rotate(node_ptr node)
			{
				node_ptr new_parent = node->right;

				new_parent->parent = node->parent;
				node->parent = new_parent;
				node->right = new_parent->left;
				if (new_parent->left)
					new_parent->left->parent = node;
				new_parent->left = node;
				set_height(node);
				set_height(new_parent);
				return (new_parent);
			}

			node_ptr right_rotate(node_ptr node)
			{
				node_ptr new_parent = node->left;

				new_parent->parent = node->parent;
				node->parent = new_parent;
				node->left = new_parent->right;
				if (new_parent->right)
					new_parent->right->parent = node;
				new_parent->right = node;
				set_height(node);
				set_height(new_parent);
				return (new_parent);
			}

			node_ptr left_right_rotate(node_ptr node)
			{
				node->left = this->left_rotate(node->left);
				return (this->right_rotate(node));
			}

			node_ptr right_left_rotate(node_ptr node)
			{
				node->right = this->right_rotate(node->right);
				return (this->left_rotate(node));
			}

			// node의 높이 차이가 1 이상이 되지 않도록 균형 맞추기
			node_ptr rebalance_tree(node_ptr node)
			{
				int	balance_factor = get_balance_factor(node);
				if (balance_factor > 1)
				{
					if (get_balance_factor(node->left) >= 0)
						return (this->right_rotate(node));
					else
						return (this->left_right_rotate(node));
				}
				else if (balance_factor < -1)
				{
					if (get_balance_factor(node->right) <= 0)
						return (this->left_rotate(node));
					else
						return (this->right_left_rotate(node));
				}
				return (node);
			}

			node_ptr create_node(const value_type& val, node_ptr parent)
			{
				node_ptr new_node = node_alloc(m_alloc).allocate(1);

				new_node->left = NULL;
				new_node->right = NULL;
				set_height(new_node);
				new_node->parent = parent;
				m_alloc.construct(&new_node->val, val);
				m_size++;
				m_last_inserted_node = new_node;
				return (new_node);
			}

			node_ptr insert_node(node_ptr node, node_ptr parent, const value_type& val)
			{
				if (node == NULL)
					return (create_node(val, parent));
				if (m_compare(val.first, node->val.first))
					node->left = insert_node(node->left, node, val);
				else if (m_compare(node->val.first, val.first))
					node->right = insert_node(node->right, node, val);
				else
					return (m_last_inserted_node = node);
				set_height(node);
				return(rebalance_tree(node));
			}

			// key를 이용하여 node 찾아서 리턴
			node_ptr search_tree(node_ptr node, const key_type& key) const
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

			// key를 이용하여 node 삭제 후 재정렬
			node_ptr delete_node(node_ptr node, const key_type& key)
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
						node_ptr tmp = node->left ? node->left : node->right;
						if (tmp == NULL)
							std::swap(tmp, node);
						else
						{
							m_alloc.destroy(&node->val);
							m_alloc.construct(&node->val, tmp->val);
							node->left = NULL;
							node->right = NULL;
						}
						m_alloc.destroy(&tmp->val);
						node_alloc(m_alloc).deallocate(tmp, 1);
						m_size--;
					}
					else
					{
						node_ptr tmp = this->smallest_node(node->right);
						m_alloc.destroy(&node->val);
						m_alloc.construct(&node->val, tmp->val);
						node->right = delete_node(node->right, tmp->val.first);
					}
				}
				return(rebalance_tree(node));
			}

			// 모든 node 삭제
			node_ptr remove_tree(node_ptr node)
			{
				if (node == NULL)
					return (NULL);
				if (node->left)
					remove_tree(node->left);
				if (node->right)
					remove_tree(node->right);
				node_alloc(m_alloc).deallocate(node, 1);
				m_size--;
				return (NULL);
			}

			// 트리에서 가장 작은(가장 왼쪽의) node 반환
			node_ptr smallest_node(node_ptr node) const
			{
				while (node && node->left != NULL)
					node = node->left;
				return (node);
			}

			// 트리에서 가장 큰(가장 오른쪽의) node 반환
			node_ptr biggest_node(node_ptr node) const
			{
				while (node && node->right != NULL)
					node = node->right;
				return (node);
			}
	};

	// overloads
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