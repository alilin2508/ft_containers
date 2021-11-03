/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:09:38 by alilin            #+#    #+#             */
/*   Updated: 2021/11/03 14:12:57 by alilin           ###   ########.fr       */
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
	class map
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
		typedef typename allocator_type::size_type size_type;

		typedef ft::RBtree<key_type, value_type, key_compare> tree_type;
		typedef Node<value_type> node_type;
		typedef Node<value_type>* node_ptr;

		// change allocator from alloc pair to alloc nodes
		// typedef typename allocator_type::template rebind<ft::Node<ft::pair<Key const, T> > >::other node_allocator_type;
		// typedef ft::RBtree< key_type, ft::pair<const Key, T>, Compare, node_allocator_type > tree_type;

		// typedef typename tree_type::node_ptr node_ptr;
		// typedef typename tree_type::node_type node_type;
		// typedef typename tree_type::size_type size_type;

		typedef ft::bidirectional_iterator<value_type, node_type> iterator;
		typedef ft::bidirectional_iterator<value_type const, node_type const> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _comp(comp), _alloc(alloc), _tree(), _size(0) {}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _comp(comp), _alloc(alloc), _tree(), _size(0)
		{
			insert(first, last);
		}
		map(const map &x): _comp(x._comp), _alloc(x._alloc), _size(0)
		{
			insert(x.begin(), x.end());
		}
		virtual ~map() {}

		map &operator=(const map &x)
		{
			if (this == &x)
				return (*this);
			if (_tree.getRoot() != NULL)
			{
				clear();
			}
			this->_comp = x._comp;
			this->_alloc = x._alloc;
			insert(x.begin(), x.end());
			return *this;
		}

		iterator begin()
		{
			return iterator(_tree.minimum(), _tree.getRoot(), _tree.getNil());
		}

		const_iterator begin() const
		{
			return const_iterator(_tree.minimum(), _tree.getRoot(), _tree.getNil());
		}

		iterator end()
		{
			if (_tree.getSize() == 0)
				return begin();
			return iterator(_tree.getNil(), _tree.getRoot(), _tree.getNil());
		}

		const_iterator end() const
		{
			if (_tree.getSize() == 0)
				return begin();
			return const_iterator(_tree.getNil(), _tree.getRoot(), _tree.getNil());
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			if (_tree.getSize() == 0)
				return rbegin();
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			if (_tree.getSize() == 0)
				return rbegin();
			return const_reverse_iterator(begin());
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
			node_ptr val = _tree.searchTreeHelper(_tree.getRoot(), k);

			if (val)
				return (val->data.second);
			else
			{
				ft::pair<iterator,bool> pr;

				pr = insert(value_type(k, mapped_type())); // insert returns a pair an first element of pair is an it
				iterator it = pr.first;
				return (it._ptr->data.second);
			}
		}

		ft::pair<iterator,bool> insert(const value_type &val)
		{
			iterator it = find(val.first);
			if (it != end())
			{
				return ft::pair<iterator,bool>(it, false);
			}
			else
			{
				std::cout << "caca5" << std::endl;
				node_ptr node = _tree.insertNode(val, _tree.getRoot());
				std::cout << "caca6" << std::endl;
				it = iterator(node, _tree.getRoot(), _tree.getNil());
				std::cout << "caca7" << std::endl;
				this->_size++;
				std::cout << "caca8" << std::endl;
				return (ft::pair<iterator,bool>(it, true));
			}
		}

		iterator insert(iterator position, const value_type &val)
		{
			node_ptr _successor = _tree.successor(position.getPtr());

			// Check if position is correct so if : position's successor > val > position
			if (_comp(get_key_from_iterator(position), get_key_from_val(val)) && _comp(get_key_from_val(val), get_key_from_val(_successor->data)))
			{
				this->_size++;
				return iterator(_tree.insertNode(val, position.getPtr()), _tree.getRoot(), _tree.getNil());
			}
			else
				return (insert(val).first); // insert(val) returns a pair of it ans bool so the pair.first returns an it
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			int i = 0;
			while (first != last)
			{
				std::cout << "check = " << i << std::endl;
				insert(*first++); // first here is a bidirectional_iterator which has an * overload so *first = first._ptr->_data which is a pair in map so a value_type
				std::cout << "i = " << i++ << std::endl;
			}
		}

		// void erase (iterator position);
		//
		// size_type erase (const key_type &k);
		//
		// void erase (iterator first, iterator last);

		iterator find(const key_type &k)
		{
			node_ptr tmp = _tree.searchTree(k);
			if (tmp == NULL)
			{
				return (end());
			}
			return iterator(tmp, _tree.getRoot(), _tree.getNil());
		}

		const_iterator find(const key_type &k) const
		{
			return const_iterator(_tree.searchTree(k), _tree.getRoot(), _tree.getNil());
		}

		void clear()
		{
			_tree.clear_helper(_tree.getRoot());
			this->_size = 0;
		}


	private:

		key_compare _comp;
		allocator_type _alloc;
		tree_type _tree;
		size_type _size;

		key_type get_key_from_val(value_type const &val) const
		{
			return (val.first);
		}

		key_type get_key_from_iterator(iterator it) const
		{
			return (it.getPtr()->data.first);
		}
	};
}

#endif
