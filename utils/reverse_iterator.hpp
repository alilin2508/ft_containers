/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:48:51 by alilin            #+#    #+#             */
/*   Updated: 2021/09/13 17:50:31 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template<class Iter>
	class reverse_Iterator
	{
	private:

		iterator_type _iter;
	public:

		typedef Iter iterator_type;
		typedef typename iterator_traits<Iter>::iterator_category iterator_category;
		typedef typename iterator_traits<Iter>::value_type value_type;
		typedef typename iterator_traits<Iter>::difference_type difference_type;
		typedef typename iterator_traits<Iter>::pointer pointer;
		typedef typename iterator_traits<Iter>::reference reference;

		reverse_iterator() : _iter(iterator_type()) {}
		reverse_iterator(iterator_type it) : _iter(it) {}
		template<class Iterator>
		reverse_iterator(reverse_iterator<Iterator> const &rev_it) : _iter(rev_it.base()) {}
		reverse_iterator &operator=(reverse_iterator const &other)
		{
			if (this == &other)
				return (*this);
			_iter = other._iter;
			return (*this);
		}
		virtual ~reverse_iterator() {}


		reference operator*() const
		{
			Iter tmp(_iter);
			return (*--tmp);
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reverse_iterator &operator++()
		{
			_iter--;
			return (*this);
		}

		reverse_iterator &operator++(int)
		{
			reverse_iterator<Iter> tmp = *this;
			_iter--;
			return (tmp);
		}

		reverse_iterator &operator--()
		{
			_iter++;
			return (*this);
		}

		reverse_iterator &operator--(int)
		{
			reverse_iterator<Iter> tmp = *this;
			_iter++;
			return (tmp);
		}

		reverse_iterator operator+(difference_type val) const
		{
			return (reverse_iterator<Iter>(_iter - val));
		}

		difference_type operator+(reverse_iterator const &other) const
		{
			return (_iter - other._iter);
		}

		reverse_iterator operator-(difference_type val) const
		{
			return (reverse_iterator<Iter>(_iter + val));
		}

		difference_type operator-(reverse_iterator const &other) const
		{
			return (_iter + other._iter);
		}

		reverse_iterator &operator+=(difference_type val)
		{
			_iter -= val;
			return (*this);
		}

		reverse_iterator &operator-=(difference_type val)
		{
			_iter += val;
			return (*this);
		}

		reference operator[](difference_type n) const
		{
			return _iter[-n -1];
		}

		iterator_type base() const
		{
			return _iter;
		}
	};


	template<typename T, typename Tp>
	bool operator==(ft::reverse_iterator<T> const &iter, ft::reverse_iterator<Tp> const &iter_) const
	{
		return (iter->_iter == iter_._iter);
	}

	template<typename T, typename Tp>
	bool operator!=(ft::reverse_iterator<T> const &iter, ft::reverse_iterator<Tp> const &iter_) const
	{
		return (iter->_iter != iter_._iter);
	}

	template<typename T, typename Tp>
	bool operator<(ft::reverse_iterator<T> const &iter, ft::reverse_iterator<Tp> const &iter_) const
	{
		return (iter->_iter < iter_._iter);
	}

	template<typename T, typename Tp>
	bool operator>(ft::reverse_iterator<T> const &iter, ft::reverse_iterator<Tp> const &iter_) const
	{
		return (iter->_iter > iter_._iter);
	}

	template<typename T, typename Tp>
	bool operator<=(ft::reverse_iterator<T> const &iter, ft::reverse_iterator<Tp> const &iter_) const
	{
		return (iter->_iter <= iter_._iter);
	}

	template<typename T, typename Tp>
	bool operator>=(ft::reverse_iterator<T> const &iter, ft::reverse_iterator<Tp> const &iter_) const
	{
		return (iter->_iter >= iter_._iter);
	}

	template<typename T>
	ft::reverse_iterator<T> operator+(ft::reverse_iterator<T> const &iter, ft::reverse_iterator<T>::difference_type val)
	{
		return (ft::reverse_iterator<T>(iter._iter + val));
	}

	template<typename T>
	ft::reverse_iterator<T> operator-(ft::reverse_iterator<T> const &iter, ft::reverse_iterator<T>::difference_type val)
	{
		return (ft::reverse_iterator<T>(iter._iter - val));
	}
}

#endif
