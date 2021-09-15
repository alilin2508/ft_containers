/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 11:48:51 by alilin            #+#    #+#             */
/*   Updated: 2021/09/15 16:31:48 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template<class Iter>
	class reverse_iterator
	{
	public:

		typedef Iter iterator_type;
		typedef typename iterator_traits<Iter>::iterator_category iterator_category;
		typedef typename iterator_traits<Iter>::value_type value_type;
		typedef typename iterator_traits<Iter>::difference_type difference_type;
		typedef typename iterator_traits<Iter>::pointer pointer;
		typedef typename iterator_traits<Iter>::reference reference;

		reverse_iterator() : _iter(iterator_type()) {}
		explicit reverse_iterator(iterator_type it) : _iter(it) {}
		template<class Iterator>
		reverse_iterator(reverse_iterator<Iterator> const &rev_it) : _iter(rev_it.base()) {}
		reverse_iterator &operator=(reverse_iterator const &lhs)
		{
			if (this == &lhs)
				return (*this);
			_iter = lhs._iter;
			return (*this);
		}
		virtual ~reverse_iterator() {}

		iterator_type base() const
		{
			return _iter;
		}

		reference operator*() const
		{
			Iter tmp(_iter);
			return (*--tmp);
		}

		reverse_iterator operator+(difference_type n) const
		{
			return (reverse_iterator<Iter>(_iter - n));
		}

		reverse_iterator &operator++()
		{
			_iter--;
			return (*this);
		}

		reverse_iterator &operator++(int)
		{
			reverse_iterator<Iter> tmp(*this);
			_iter--;
			return (tmp);
		}

		reverse_iterator &operator+=(difference_type n)
		{
			_iter -= n;
			return (*this);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return (reverse_iterator<Iter>(_iter + n));
		}

		reverse_iterator &operator--()
		{
			_iter++;
			return (*this);
		}

		reverse_iterator &operator--(int)
		{
			reverse_iterator<Iter> tmp(*this);
			_iter++;
			return (tmp);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			_iter += n;
			return (*this);
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type n) const
		{
			return _iter[-n -1];
		}

	protected:

		iterator_type _iter;
	};

	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator!= (const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator, class Iter>
	bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iter> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it)
	{
		return (rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
}

#endif
