/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:20:14 by alilin            #+#    #+#             */
/*   Updated: 2021/10/22 17:07:51 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

#include <iterator>
#include <cstddef>

#include "iterator_traits.hpp"
#include "red_black_tree.hpp"

namespace ft
{
	template<class Node>
	class bidirectional_iterator
	{
	protected:

		Node _root;
		Node _nil;
		Node *_ptr;

	public:

		typedef std::ptrdiff_t difference_type;
		typedef Node value_type;
		typedef Node* node_ptr;
		typedef Node::value_type data_type;

		typedef data_type* pointer;
		typedef data_type& reference;
		typedef const data_type* const_pointer;
		typedef const data_type& const_reference;
		typedef std::bidirectional_iterator_tag iterator_category;

		bidirectional_iterator() : _ptr(NULL), _root(NULL), _nil(NULL) {}
		bidirectional_iterator(node_ptr ptr, node_ptr root, node_ptr nil) : _ptr(ptr), , _root(root), _nil(nil){}
		bidirectional_iterator(bidirectional_iterator const &lhs) : _ptr(lhs._ptr), _root(lhs._root), _nil(lhs._nil) {}
		bidirectional_iterator &operator=(bidirectional_iterator const &lhs)
		{
			if (this == &lhs)
				return (*this);
			_ptr = lhs._ptr;
			_root = lhs._root;
			_nil = lhs._nil;
			return (*this);
		}
		virtual ~bidirectional_iterator() {}

		// Overload called when trying to copy construct a const_iterator
		// based on an iterator
		operator bidirectional_iterator<value_type const>() const
		{
			return bidirectional_iterator<value_type const>(_ptr, _root, _nil);
		}

		template<class Iterator>
		friend bool operator==(ft::bidirectional_iterator<Iterator> const &lhs, ft::bidirectional_iterator<Iterator> const &rhs);

		template<class Iterator>
		friend bool operator!=(ft::bidirectional_iterator<Iterator> const &lhs, ft::bidirectional_iterator<Iterator> const &rhs);

		template<class Iterator, class Iter>
		friend bool operator==(ft::random_access_iterator<Iterator> const &lhs, ft::random_access_iterator<Iter> const &rhs);

		template<class Iterator, class Iter>
		friend bool operator!=(ft::random_access_iterator<Iterator> const &lhs, ft::random_access_iterator<Iter> const &rhs);

		reference operator*() const
		{
			return (ptr->data);
		}

		pointer operator->() const
		{
			return (&(operator*()));
		}

		bidirectional_iterator &operator++()
		{
			_ptr++;
			return (*this);
		}

		bidirectional_iterator operator++(int)
		{
			bidirectional_iterator<T> tmp(*this);
			_ptr++;
			return (tmp);
		}

		bidirectional_iterator &operator--()
		{
			_ptr--;
			return (*this);
		}

		bidirectional_iterator operator--(int)
		{
			bidirectional_iterator<T> tmp(*this);
			_ptr--;
			return (tmp);
		}

	};

	template<class Iterator>
	bool operator==(ft::bidirectional_iterator<Iterator> const &lhs, ft::bidirectional_iterator<Iterator> const &rhs)
	{
		return (lhs._ptr == rhs._ptr);
	}

	template<class Iterator>
	bool operator!=(ft::bidirectional_iterator<Iterator> const &lhs, ft::bidirectional_iterator<Iterator> const &rhs)
	{
		return (lhs._ptr != rhs._ptr);
	}

	template<class Iterator, class Iter>
	bool operator==(ft::random_access_iterator<Iterator> const &lhs, ft::random_access_iterator<Iter> const &rhs)
	{
		return (lhs._ptr == rhs._ptr);
	}

	template<class Iterator, class Iter>
	bool operator!=(ft::random_access_iterator<Iterator> const &lhs, ft::random_access_iterator<Iter> const &rhs)
	{
		return (lhs._ptr != rhs._ptr);
	}
}

#endif
