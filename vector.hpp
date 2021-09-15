/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:20:46 by alilin            #+#    #+#             */
/*   Updated: 2021/09/15 15:17:28 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"

#include <memory>
#include <stdexcept>

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
			if (x.size > this->capacity)
				this->capacity = x.size;
			array = _alloc.allocate(size);
			for (size_type i = 0; i < size; i++)
				_alloc.construct(array + i, x.array[i]);
			return (*this);
		}

		// ################ Iterators ################

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

		// ################ Capacity ################

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
				if (!capacity)
					realloc(n);
				else if (n > capacity)
					realloc(n > (capacity * 2) ? n : capacity * 2);
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

		void reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("reserve:: cannot increase capacity beyond max_size");
			if (n > capacity)
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
			if (n >= size)
				throw std::out_of_range("at:: out of range index");
			return *(array + n);
		}

		const_reference at(size_type n) const
		{
			if (n >= size)
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
			return *(array + size - 1);
		}

		const_reference back() const
		{
			return *(array + size - 1);
		}

		// ################ Modifiers ################

		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			size_type diff = 0;
			for(iterator tmp = first; tmp != last; tmp++)
			{
				diff++;
			}
			if (diff > capacity)
			{
				pointer tmp = _alloc.allocate(diff);
				for (iterator i = first; i != last; i++)
					_alloc.construct(tmp + i, *i);
				~vector();
				this->array = tmp;
				this->capacity = diff;
				this->size = diff;
			}
			else
			{
				size_type current_capacity = this->capacity;
				pointer tmp = _alloc.allocate(this->capacity);
				for (iterator i = first; i != last; i++)
					_alloc.construct(tmp + i, *i);
				~vector();
				this->array = tmp;
				this->capacity = current_capacity;
				this->size = diff;
			}
		}

		void assign(size_type n, const value_type &val)
		{
			if (n > capacity)
			{
				pointer tmp = _alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(tmp + i, val);
				~vector();
				this->array = tmp;
				this->capacity = n;
				this->size = n;
			}
			else
			{
				size_type current_capacity = this->capacity;
				pointer tmp = _alloc.allocate(this->capacity);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(tmp + i, val);
				~vector();
				this->array = tmp;
				this->capacity = current_capacity;
				this->size = n;
			}
		}

		void push_back(const value_type &val)
		{
			if (empty())
				realloc(1);
			if (size == capacity)
				realloc(capacity * 2);
			_alloc.construct(array + size, val);
			size++;
		}

		void pop_back()
		{
			_alloc.destroy(&array[size - 1]);
			size--;
		}

		iterator insert(iterator position, const value_type &val)
		{
			size_type new_size = size + 1;
			iterator ret_pos = position;
			size_type new_capacity = NULL;

			if (new_size > capacity)
			{
				if (!capacity)
				{
					realloc(new_size);
					new_capacity = new_size;
				}
				else
				{
					realloc(new_size > (capacity * 2) ? n : capacity * 2);
					new_capacity = (new_size > (capacity * 2) ? n : capacity * 2);
				}
				pointer tmp = _alloc.allocate(new_capacity);
				for (iterator i = begin(); i != end(); i++)
				{
					if (i == position)
					{
						ret_pos = tmp.begin() + i;
						_alloc.construct(tmp + i++, val);
					}
					if (i != end())
							_allocator.construct(tmp + i, *i);
				}
				~vector();
				this->array = tmp;
				this->capacity = new_capacity;
				this->size = new_size;
			}
			else
			{
				size_type current_capacity = this->capacity;
				pointer tmp = _alloc.allocate(current_capacity);
				for (iterator i = begin(); i != end(); i++)
				{
					if (i == position)
						_alloc.construct(tmp + i++, val);
					if (i != end())
							_allocator.construct(tmp + i, *i);
				}
				~vector();
				this->array = tmp;
				this->capacity = current_capacity;
				this->size = new_size;
			}
			return (ret_pos);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			size_type new_size = size + n;
			size_type new_capacity = NULL;

			if (new_size > capacity)
			{
				if (!capacity)
				{
					realloc(new_size);
					new_capacity = new_size;
				}
				else
				{
					realloc(new_size > (capacity * 2) ? n : capacity * 2);
					new_capacity = (new_size > (capacity * 2) ? n : capacity * 2);
				}
				pointer tmp = _alloc.allocate(new_capacity);
				for (iterator i = begin(); i != end(); i++)
				{
					if (i == position)
					{
						for (size_type j = 0; j < n; j++)
							_alloc.construct(tmp + i++, val);
					}
					if (i != end())
						_allocator.construct(tmp + i, *i);
				}
				~vector();
				this->array = tmp;
				this->capacity = new_capacity;
				this->size = new_size;
			}
			else
			{
				size_type current_capacity = this->capacity;
				pointer tmp = _alloc.allocate(current_capacity);
				for (iterator i = begin(); i != end(); i++)
				{
					if (i == position)
					{
						for (size_type j = 0; j < n; j++)
							_alloc.construct(tmp + i++, val);
					}
					if (i != end())
						_allocator.construct(tmp + i, *i);
				}
				~vector();
				this->array = tmp;
				this->capacity = current_capacity;
				this->size = new_size;
			}
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last)
		{
			size_type diff = 0;
			for(iterator tmp = first; tmp != last; tmp++)
			{
				diff++;
			}
			size_type new_size = size + diff;
			size_type new_capacity = NULL;

			if (new_size > capacity)
			{
				if (!capacity)
				{
					realloc(new_size);
					new_capacity = new_size;
				}
				else
				{
					realloc(new_size > (capacity * 2) ? n : capacity * 2);
					new_capacity = (new_size > (capacity * 2) ? n : capacity * 2);
				}
				pointer tmp = _alloc.allocate(new_capacity);
				for (iterator i = begin(); i != end(); i++)
				{
					if (i == position)
					{
						for (iterator j = first; j != last; j++)
							_alloc.construct(tmp + i++, *j);
					}
					if (i != end())
						_allocator.construct(tmp + i, *i);
				}
				~vector();
				this->array = tmp;
				this->capacity = new_capacity;
				this->size = new_size;
			}
			else
			{
				size_type current_capacity = this->capacity;
				pointer tmp = _alloc.allocate(current_capacity);
				for (iterator i = begin(); i != end(); i++)
				{
					if (i == position)
					{
						for (iterator j = first; j != last; j++)
							_alloc.construct(tmp + i++, *j);
					}
					if (i != end())
						_allocator.construct(tmp + i, *i);
				}
				~vector();
				this->array = tmp;
				this->capacity = current_capacity;
				this->size = new_size;
			}
		}

	

	protected:

		allocator_type _alloc;
		T* array;
		size_type size;
		size_type capacity;

		void realloc(size_type n)
		{
			pointer tmp = _alloc.allocate(n);
			for (size_type i = 0; i < this->size; i++)
				_alloc.construct(tmp + i, this->array[i]);
			~vector();
			this->array = tmp;
			this->capacity = n;
		}
	};
}

#endif
