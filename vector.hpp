/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:20:46 by alilin            #+#    #+#             */
/*   Updated: 2021/09/14 16:48:25 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T>>
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		// typedef typename allocator_type::difference_type difference_type;
		// typedef typename allocator_type::size_type size_type;

		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::random_access_iterator<value_type const> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		explicit vector (const allocator_type &alloc = allocator_type()) : _alloc(alloc), array(NULL), size(0), capacity(0) {}
		explicit vector (size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), array(NULL), size(n), capacity(n)
		{
			array = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(array + i, val);
			size = n;
		}
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) : _alloc(alloc), array(NULL), size(0), capacity(0)
		{
			for(iterator tmp = first; tmp != last; tmp++)
			{
				size++;
			}
			capacity = size;
			array = _alloc.allocate(size);
			for (iterator tmp = first; tmp != last; tmp++)
				_alloc.construct(array + tmp, *tmp);
		}

		vector (const vector &x) : _alloc(x._alloc), array(NULL), size(x.size), capacity(x.size)
		{
			array = _alloc.allocate(size);
			for (size_type i = 0; i < size; i++)
				_alloc.construct(array + i, x.array[i]);
		}

		virtual ~vector()
		{
			clear();
			if (capacity != 0)
				_alloc.deallocate(array, capacity);
			capacity = 0;
		}

		vector &operator=(const vector &x)
		{
			if (this == &x)
				return (*this);
			~vector();
			this->size = x.size;
			this->capacity = x.capacity;
			array = _alloc.allocate(size);
			for (size_type i = 0; i < size; i++)
				_alloc.construct(array + i, x.array[i]);
			return (*this);
		}

		// #### Iterators: ####

		iterator begin()
		{
			return (iterator(_array));
		}
		const_iterator begin() const
		{
			return (const_iterator(_array));
		}

		iterator end()
		{
			if (size == 0)
				return (begin());
			return (iterator(_array + size));
		}

		const_iterator end() const
		{
			if (size == 0)
				return (begin());
			return (const_iterator(_array + size));
		}

		reverse_iterator rbegin()
		{
			if (size == 0)
				return (rend());
			return (reverse_iterator(_array + size));
		}

		const_reverse_iterator rbegin() const
		{
			if (size == 0)
				return (rend());
			return (const_reverse_iterator(_array + size));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(_array));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(_array));
		}

		// #### Capacity: ####

		size_type size() const
		{
			return (this->size);
		}

		size_type max_size() const
		{
			return (_alloc.max_size());
		}

		void resize (size_type n, value_type val = value_type())
		{
			if (n < this->size)
			{
				while (size != n)
					pop_back();
			}
			else if (n > this->size)
			{
				while (size != n)
					push_back(val);
			}
		}

		size_type capacity() const
		{
			return (this->capacity);
		}

		bool empty() const
		{
			return (size == 0);
		}

		void reserve (size_type n)
		{
			if (n > capacity)
			{
				
			}
		}

	private:

		allocator_type _alloc;
		T* array;
		size_type size;
		size_type capacity;
	};
}

#endif
