/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:09:38 by alilin            #+#    #+#             */
/*   Updated: 2021/10/27 18:21:10 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "./utils/pair.hpp"
#include "./utils/red_black_tree.hpp"
#include "./utils/reverse_iterator.hpp"
#include "./utils/bidirectional_iterator.hpp"
// #include "./utils/enable_if.hpp"
// #include "./utils/equal.hpp"
// #include "./utils/is_integral.hpp"
// #include "./utils/lexicographical_compare.hpp"

#include <functional> // for std::less
#include <memory>

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map : public RBtree< Key, ft::pair<const Key, T>, Compare, typename Alloc::template rebind<ft::Node<ft::pair<Key const, T> > >::other  >
	{
	public:

		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::difference_type difference_type;

		// change allocator from alloc pair to alloc nodes
		typedef typename allocator_type::template rebind<ft::Node<ft::pair<Key const, T> > >::other node_allocator_type;
		typedef ft::RBtree< key_type, ft::pair<const Key, T>, Compare, node_allocator_type > tree_type;

		typedef typename tree_type::node_ptr node_ptr;
		typedef typename tree_type::node_type node_type;
		typedef typename tree_type::size_type size_type;
		// typedef typename tree_type::_alloc node_alloc;

		typedef ft::bidirectional_iterator<node_type> iterator;
		typedef ft::bidirectional_iterator<node_type const> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): tree_type(comp), alloc(alloc) {}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): tree_type(comp), alloc(alloc)
		{
			insert(first, last);
		}
		map(const map &x)
		{
			insert(x.begin(), x.end());
		}
		virtual ~map() {}

		map &operator=(const map &x)
		{
			if (this == &x)
				return (*this);
			if (this->_root != NULL)
				clear();
			tree_type::copy_helper(this->_root, x._root, NULL, x._nil);
			this->_size = x._size;
			return *this;
		}

		iterator begin()
		{
			return (iterator(tree_type::minimum(this->_root), this->_root, this->_nil));
		}

		const_iterator begin() const
		{
			return (const_iterator(tree_type::minimum(this->_root), this->_root, this->_nil));
		}

		iterator end()
		{
			if (this->_size == 0)
				return (begin());
			return (iterator(this->_nil, this->_root, this->_nil));
		}

		const_iterator end() const
		{
			if (this->_size == 0)
				return (begin());
			return (const_iterator(this->_nil, this->_root, this->_nil));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->_nil, this->_root, this->_nil));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->_nil, this->_root, this->_nil));
		}

		reverse_iterator rend()
		{
			if (this->_size == 0)
				return (rbegin());
			return (reverse_iterator(tree_type::minimum(), this->_root, this->_nil));
		}

		const_reverse_iterator rend() const
		{
			if (this->_size == 0)
				return (rbegin());
			return (const_reverse_iterator(tree_type::minimum(), this->_root, this->_nil));
		}

		bool empty() const
		{
			return (this->_size == 0);
		}

		size_type size() const
		{
			return (this->_size);
		}

		size_type max_size() const
		{
			return (this->_alloc.max_size());
		}

		mapped_type &operator[](const key_type &k)
		{
			node_ptr val = tree_type::searchTreeHelper(this->_root, k);

			if (val)
				return (val->data.second);
			else
			{
				ft::pair<iterator,bool> pr;

				pr = insert(ft::make_pair(k, mapped_type()));
				iterator it = pr.first;
				return (it._ptr->data.second);
			}
		}

		ft::pair<iterator,bool> insert(const value_type &val)
		{
			iterator it = find(val.first);

			if (it != end())
				return (ft::make_pair(it, false));
			else
			{
				node_ptr node = this->_alloc.allocate(1);
				this->_alloc.construct(node, node_type(val, NULL, this->_nil, this->_nil, red));
				it = iterator(tree_type::insertNode(node, this->_root), this->_root, this->_nil);
				this->_size++;
				return (ft::make_pair(it, true));
			}
		}

		iterator insert(iterator position, const value_type &val)
		{
			node_ptr _successor = successor(position._ptr);
			node_ptr node;

			// Check if position is correct so if : position's successor > val > position
			if (_comp(get_key_from_iterator(position), get_key_from_val(val)) && _comp(get_key_from_val(val), get_key_from_val(_successor->data)))
			{
				node = this->_alloc.allocate(1);
				this->_alloc.construct(node, node_type(val, NULL, this->_nil, this->_nil, red));
				this->_size++;
				return iterator(insertNode(node, position._ptr), this->_root, this->_nil);
			}
			else
				return (insert(val).first); // insert(val) returns a pair of it ans bool so the pair.first returns an it
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first++); // first here is a bidirectional_iterator which has an * overload so *first = first._ptr->_data which is a pair in map so a value_type
			}
		}

		// void erase (iterator position);
		//
		// size_type erase (const key_type &k);
		//
		// void erase (iterator first, iterator last);

		iterator find(const key_type &k)
		{
			return (iterator(tree_type::searchTree(k), this->_root, this->_nil));
		}

		const_iterator find(const key_type &k) const
		{
			return (const_iterator(tree_type::searchTree(k), this->_root, this->_nil));
		}

		void clear()
		{
			tree_type::clear_helper(this->_root);
		}


	private:

		allocator_type alloc;

		key_type get_key_from_val(value_type const &val) const
		{
			return (val.first);
		}

		key_type get_key_from_iterator(iterator it) const
		{
			return (it->first);
		}
	};
}

#endif
