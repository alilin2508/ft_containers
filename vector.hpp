/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:20:46 by alilin            #+#    #+#             */
/*   Updated: 2021/11/12 17:05:47 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "./utils/reverse_iterator.hpp"
#include "./utils/random_access_iterator.hpp"
#include "./utils/enable_if.hpp"
#include "./utils/equal.hpp"
#include "./utils/is_integral.hpp"
#include "./utils/lexicographical_compare.hpp"

#include <memory>
#include <stdexcept>
#include <limits>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;

		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::random_access_iterator<value_type const> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		explicit vector (const allocator_type &alloc = allocator_type()) : _alloc(alloc), array(NULL), _size(0), _capacity(0) {}
		explicit vector (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), array(NULL), _size(n), _capacity(n)
		{
			array = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(array + i, val);
			_size = n;
		}
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) : _alloc(alloc), array(NULL), _size(0), _capacity(0)
		{
			size_type diff = 0;
			for (InputIterator tmp = first; tmp != last; tmp++)
			{
				diff++;
			}
			_size = diff;
			_capacity = _size;
			array = _alloc.allocate(_size);
			for (int i = 0; first != last; i++, first++)
				_alloc.construct(array + i, *first);
		}

		vector (const vector &x) : _alloc(x._alloc), array(NULL), _size(x._size), _capacity(x._size)
		{
			array = _alloc.allocate(_size);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(array + i, x.array[i]);
		}

		virtual ~vector()
		{
			clear();
			if (_capacity != 0)
				_alloc.deallocate(array, _capacity);
			_capacity = 0;
		}

		vector &operator=(const vector &x)
		{
			if (this == &x)
				return (*this);
			size_type current_capacity = this->_capacity;
			this->~vector();
			this->_size = x._size;
			this->_capacity = current_capacity;
			if (x._size > this->_capacity)
				this->_capacity = x._size;
			array = _alloc.allocate(_size);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(array + i, x.array[i]);
			return (*this);
		}

		// ################ Iterators ################

		iterator begin()
		{
			return (iterator(array));
		}
		const_iterator begin() const
		{
			return (const_iterator(array));
		}

		iterator end()
		{
			if (_size == 0)
				return (begin());
			return (iterator(array + _size));
		}

		const_iterator end() const
		{
			if (_size == 0)
				return (begin());
			return (const_iterator(array + _size));
		}

		reverse_iterator rbegin()
		{
			if (_size == 0)
				return (rend());
			return (reverse_iterator(array + _size));
		}

		const_reverse_iterator rbegin() const
		{
			if (_size == 0)
				return (rend());
			return (const_reverse_iterator(array + _size));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(array));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(array));
		}

		// ################ Capacity ################

		size_type size() const
		{
			return (this->_size);
		}

		size_type max_size() const
		{
			return (_alloc.max_size());
		}

		void resize (size_type n, value_type val = value_type())
		{
			if (n < this->_size)
			{
				while (_size != n)
					pop_back();
			}
			else if (n > this->_size)
			{
				if (n > (_capacity * 2) || !_capacity)
					realloc(n);
				else if (n > _capacity)
					realloc(_capacity * 2);
				while (_size != n)
					push_back(val);
			}
		}

		size_type capacity() const
		{
			return (this->_capacity);
		}

		bool empty() const
		{
			return (_size == 0);
		}

		void reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
			if (n > _capacity)
				realloc(n);
		}

		// ################ Element access ################

		reference operator[](size_type n)
		{
			return *(array + n);
		}

		const_reference operator[](size_type n) const
		{
			return *(array + n);
		}

		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("at:: out of range index");
			return *(array + n);
		}

		const_reference at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("at:: out of range index");
			return *(array + n);
		}

		reference front()
		{
			return *(array);
		}

		const_reference front() const
		{
			return *(array);
		}

		reference back()
		{
			return *(array + _size - 1);
		}

		const_reference back() const
		{
			return *(array + _size - 1);
		}

		// ################ Modifiers ################

		template <class InputIterator>
		void assign(typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first, InputIterator last)
		{
			size_type diff = 0;
			for (InputIterator tmp = first; tmp != last; tmp++)
			{
				diff++;
			}
			if (diff > _capacity)
			{
				this->~vector();
				this->_size = 0;
				this->_capacity = diff;
				this->array = _alloc.allocate(_capacity);
				while (first != last)
					_alloc.construct(array + _size++, *first++);
			}
			else
			{
				clear();
				while (first != last)
					_alloc.construct(array + _size++, *first++);
			}
		}

		void assign(size_type n, const value_type &val)
		{
			if (n > _capacity)
			{
				this->~vector();
				this->_size = 0;
				this->_capacity = n;
				this->array = _alloc.allocate(_capacity);
				while (_size < n)
					_alloc.construct(array + _size++, val);
			}
			else
			{
				clear();
				while (_size < n)
					_alloc.construct(array + _size++, val);
			}
		}

		void push_back(const value_type &val)
		{
			if (!_capacity)
				realloc(1);
			if (_size == _capacity)
				realloc(_capacity * 2);
			_alloc.construct(array + _size, val);
			_size++;
		}

		void pop_back()
		{
			_alloc.destroy(&array[_size - 1]);
			_size--;
		}

		iterator insert(iterator position, const value_type &val)
		{
			difference_type idx = position - begin();

			insert(position, 1, val);
			return (iterator(this->begin() + idx));
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			difference_type const pos_diff = position - begin();
			difference_type const old_end_diff = end() - begin();
			iterator old_end;
			iterator new_end;

			resize(this->_size + n);
			new_end = end();
			position = begin() + pos_diff;
			old_end = begin() + old_end_diff;
			while (old_end != position)
				*--new_end = *--old_end;
			while (n-- > 0)
				*position++ = val;
		}

		template <class InputIterator>
		void insert (iterator position, typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first, InputIterator last)
		{
			size_type n = 0;
			for (InputIterator tmp = first; tmp != last; tmp++)
			{
				n++;
			}
			difference_type const pos_diff = position - begin();
			difference_type const old_end_diff = end() - begin();
			iterator old_end;
			iterator new_end;

			resize(this->_size + n);
			new_end = end();
			position = begin() + pos_diff;
			old_end = begin() + old_end_diff;
			while (old_end != position)
				*--new_end = *--old_end;
			while (first != last)
				*position++ = *first++;
		}

	iterator erase(iterator position)
	{
		_alloc.destroy(&*position);

		for (iterator pos = position; pos + 1 != end(); pos++)
		{
			_alloc.construct(&*pos, *(pos + 1));
			_alloc.destroy(&*(pos + 1));
		}
		_size--;
		return (position);
	}

	iterator erase(iterator first, iterator last)
	{
		size_type diff = 0;
		for (iterator tmp = first; tmp != last; tmp++)
		{
			diff++;
		}

		for (iterator pos = first; pos != last; pos++)
		{
			_alloc.destroy(&*pos);
		}
		for (iterator pos = first; pos + diff != end(); pos++)
		{
			_alloc.construct(&*pos, *(pos + diff));
			_alloc.destroy(&*(pos + diff));
		}
		_size -= diff;
		return (first);
	}

	void swap(vector &x)
	{
		pointer tmp = array;
		this->array = x.array;
		x.array = tmp;

		size_type tmp_size = _size;
		this->_size = x._size;
		x._size = tmp_size;

		size_type tmp_capacity = _capacity;
		this->_capacity = x._capacity;
		x._capacity = tmp_capacity;
	}

	void clear()
	{
		while (!empty())
			pop_back();
	}

	// ################ Allocator ################

	allocator_type get_allocator() const
	{
		return (_alloc);
	}

	protected:

		allocator_type _alloc;
		T* array;
		size_type _size;
		size_type _capacity;

		void realloc(size_type n)
		{
			pointer tmp = _alloc.allocate(n);
			size_type current_size = this->_size;
			for (size_type i = 0; i < this->_size; i++)
				_alloc.construct(tmp + i, this->array[i]);
			this->~vector();
			this->array = tmp;
			this->_size = current_size;
			this->_capacity = n;
		}
	};

	template <class T, class Alloc>
  bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
  bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
  bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
  bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
  bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
  bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
  void swap(vector<T,Alloc> &x, vector<T,Alloc> &y)
	{
		x.swap(y);
	}
}

#endif
