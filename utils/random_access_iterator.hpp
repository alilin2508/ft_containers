/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:13:51 by alilin            #+#    #+#             */
/*   Updated: 2021/09/13 17:28:48 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

namespace ft
{
	template<class T>
	class random_access_iterator
	{
	private:

		T* _ptr;

	public:

		typedef std::ptrdiff difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef const T* const_pointer;
		typedef const T& const_reference;
		typedef std::random_access_iterator_tag iterator_category;

		random_access_iterator() : _ptr(NULL) {}
		random_access_iterator(pointer ptr) : _ptr(ptr) {}
		random_access_iterator(random_access_iterator const &other) : _ptr(other._ptr) {}
		random_access_iterator &operator=(random_access_iterator const &other)
		{
			if (this == &other)
				return (*this);
			_ptr = other._ptr;
			return (*this);
		}
		virtual ~random_access_iterator() {}

		bool operator==(random_access_iterator const &other) const
		{
			return (this->_ptr == other._ptr);
		}

		bool operator!=(random_access_iterator const &other) const
		{
			return (this->_ptr != other._ptr);
		}

		bool operator<(random_access_iterator const &other) const
		{
			return (this->_ptr < other._ptr);
		}

		bool operator>(random_access_iterator const &other) const
		{
			return (this->_ptr > other._ptr);
		}

		bool operator<=(random_access_iterator const &other) const
		{
			return (this->_ptr <= other._ptr);
		}

		bool operator>=(random_access_iterator const &other) const
		{
			return (this->_ptr >= other._ptr);
		}

		reference operator*() const
		{
			return (*_ptr);
		}

		pointer operator->() const
		{
			return (_ptr);
		}

		random_access_iterator &operator++()
		{
			_ptr++;
			return (*this);
		}

		random_access_iterator &operator++(int)
		{
			random_access_iterator<T> tmp = *this;
			_ptr++;
			return (tmp);
		}

		random_access_iterator &operator--()
		{
			_ptr--;
			return (*this);
		}

		random_access_iterator &operator--(int)
		{
			random_access_iterator<T> tmp = *this;
			_ptr--;
			return (tmp);
		}

		random_access_iterator operator+(difference_type val) const
		{
			return (random_access_iterator<T>(_ptr + val));
		}

		difference_type operator+(random_access_iterator const &other) const
		{
			return (_ptr + other._ptr);
		}

		random_access_iterator operator-(difference_type val) const
		{
			return (random_access_iterator<T>(_ptr - val));
		}

		difference_type operator-(random_access_iterator const &other) const
		{
			return (_ptr - other._ptr);
		}

		random_access_iterator &operator+=(difference_type val)
		{
			_ptr += val;
			return (*this);
		}

		random_access_iterator &operator-=(difference_type val)
		{
			_ptr -= val;
			return (*this);
		}

		reference operator[](difference_type n) const
		{
			return *(_ptr + n);
		}
	};


	template<typename T, typename Tp>
	bool operator==(ft::random_access_iterator<T> const &_iter, ft::random_access_iterator<Tp> const &iter_) const
	{
		return (_iter->_ptr == iter_._ptr);
	}

	template<typename T, typename Tp>
	bool operator!=(ft::random_access_iterator<T> const &_iter, ft::random_access_iterator<Tp> const &iter_) const
	{
		return (_iter->_ptr != iter_._ptr);
	}

	template<typename T, typename Tp>
	bool operator<(ft::random_access_iterator<T> const &_iter, ft::random_access_iterator<Tp> const &iter_) const
	{
		return (_iter->_ptr < iter_._ptr);
	}

	template<typename T, typename Tp>
	bool operator>(ft::random_access_iterator<T> const &_iter, ft::random_access_iterator<Tp> const &iter_) const
	{
		return (_iter->_ptr > iter_._ptr);
	}

	template<typename T, typename Tp>
	bool operator<=(ft::random_access_iterator<T> const &_iter, ft::random_access_iterator<Tp> const &iter_) const
	{
		return (_iter->_ptr <= iter_._ptr);
	}

	template<typename T, typename Tp>
	bool operator>=(ft::random_access_iterator<T> const &_iter, ft::random_access_iterator<Tp> const &iter_) const
	{
		return (_iter->_ptr >= iter_._ptr);
	}

	template<typename T>
	ft::random_access_iterator<T> operator+(ft::random_access_iterator<T> const &_iter, ft::random_access_iterator<T>::difference_type val)
	{
		return (ft::random_access_iterator<T>(_iter._ptr + val));
	}

	template<typename T>
	ft::random_access_iterator<T> operator-(ft::random_access_iterator<T> const &_iter, ft::random_access_iterator<T>::difference_type val)
	{
		return (ft::random_access_iterator<T>(_iter._ptr - val));
	}
}

#endif
