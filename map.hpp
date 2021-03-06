/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:09:38 by alilin            #+#    #+#             */
/*   Updated: 2021/11/11 16:34:43 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "./utils/pair.hpp"
#include "./utils/red_black_tree.hpp"
#include "./utils/reverse_iterator.hpp"
#include "./utils/bidirectional_iterator.hpp"
#include "./utils/equal.hpp"
#include "./utils/lexicographical_compare.hpp"

#include <functional> // for std::less
#include <memory>

namespace ft
{
	template <class T, class Key>
	struct get_key : public std::unary_function<T, Key>
	{
		const Key &operator()(const T &x) const
		{
			return (x.first);
		}
	};

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

		typedef ft::RBtree<key_type, value_type, get_key<value_type, key_type>, key_compare> tree_type;
		typedef Node<value_type> node_type;
		typedef Node<value_type>* node_ptr;

		typedef ft::bidirectional_iterator<value_type, node_type> iterator;
		typedef ft::bidirectional_iterator<value_type const, node_type const> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		class value_compare;

		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _comp(comp), _alloc(alloc), _tree() {}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _comp(comp), _alloc(alloc), _tree()
		{
			insert(first, last);
		}
		map(const map &x): _comp(x._comp), _alloc(x._alloc)
		{
			insert(x.begin(), x.end());
		}
		~map() {}

		map &operator=(const map &x)
		{
			if (this == &x)
				return (*this);
			if (_tree.getRoot() != _tree.getNil())
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
			return iterator(_tree.getNil(), _tree.getRoot(), _tree.getNil());
		}

		const_iterator end() const
		{
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
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		bool empty() const
		{
			return (_tree.getSize() == 0);
		}

		size_type size() const
		{
			return (_tree.getSize());
		}

		size_type max_size() const
		{
			return (_tree.max_size());
		}

		mapped_type &operator[](const key_type &k)
		{
			node_ptr val = _tree.searchTree(k);

			if (val != _tree.getNil())
				return (val->data.second);
			else
			{
				_tree.insertNode(value_type(k, mapped_type())); // insert returns a pair an first element of pair is an it
				val = _tree.searchTree(k);
				return (val->data.second);
			}
		}

		ft::pair<iterator,bool> insert(const value_type &val)
		{
			iterator it = find(val.first);
			if (it != end())
			{
				return (ft::pair<iterator,bool>(it, false));
			}
			else
			{
				_tree.insertNode(val);
				it = find(val.first);
				return (ft::pair<iterator,bool>(it, true));
			}
		}

		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
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

		void erase(iterator position)
		{
			erase((*position).first); // position is a bidirectional_iterator which has an * overload so *position = position._ptr->_data so position._ptr->_data.first is the key of value_type
		}

		size_type erase(const key_type &k)
		{
			if (_tree.deleteNode(k) == true)
				return 1;
			return 0;
		}

		void erase(iterator first, iterator last)
		{
			while(first != last)
			{
				erase((*(first++)).first);
			}
		}

		void swap (map &x)
		{
			_tree.swap(x._tree);
		}

		void clear()
		{
			_tree.clear_h(_tree.getRoot());
		}

		key_compare key_comp() const
		{
			return (this->_comp);
		}

		value_compare value_comp() const
		{
			return (value_compare(this->_comp));
		}

		iterator find(const key_type &k)
		{
			node_ptr tmp = _tree.searchTree(k);
			if (tmp == _tree.getNil())
				return (end());
			return iterator(tmp, _tree.getRoot(), _tree.getNil());
		}

		const_iterator find(const key_type &k) const
		{
			node_ptr tmp = _tree.searchTree(k);
			if (tmp == _tree.getNil())
				return (end());
			return const_iterator(tmp, _tree.getRoot(), _tree.getNil());
		}

		size_type count(const key_type& k) const
		{
			const_iterator beg = this->begin();
			const_iterator end = this->end();

			while (beg != end)
			{
				if ((*(beg++)).first == k)
					return (1);
			}
			return (0);
		}

		iterator lower_bound(const key_type &k)
		{
			iterator beg = this->begin();
			iterator end = this->end();

			while (beg != end)
			{
				if (_comp((*beg).first, k) == false)
					break;
				beg++;
			}
			return (beg);
		}

		const_iterator lower_bound(const key_type& k) const
		{
			const_iterator beg = this->begin();
			const_iterator end = this->end();

			while (beg != end)
			{
				if (_comp((*beg).first, k) == false)
					break;
				beg++;
			}
			return (beg);
		}

		iterator upper_bound(const key_type& k)
		{
			iterator beg = this->begin();
			iterator end = this->end();

			while (beg != end)
			{
				if (_comp(k ,(*beg).first))
					break;
				beg++;
			}
			return (beg);
		}

		const_iterator upper_bound(const key_type& k) const
		{
			const_iterator beg = this->begin();
			const_iterator end = this->end();

			while (beg != end)
			{
				if (_comp(k, (*beg).first))
					break;
				beg++;
			}
			return (beg);
		}

		pair<const_iterator,const_iterator> equal_range(const key_type &k) const
		{
			return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
		}

		pair<iterator,iterator> equal_range(const key_type &k)
		{
			return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
		}

		allocator_type get_allocator() const
		{
			return (_alloc);
		}

	private:

		key_compare _comp;
		allocator_type _alloc;
		tree_type _tree;
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(rhs == lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	class map<Key,T,Compare,Alloc>::value_compare
	{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
  	friend class map;
	protected:
  	Compare comp;
  	value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object
	public:
  	typedef bool result_type;
  	typedef value_type first_argument_type;
  	typedef value_type second_argument_type;
  	bool operator() (const value_type& x, const value_type& y) const
  	{
    	return comp(x.first, y.first);
  	}
	};
}

#endif
