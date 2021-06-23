/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 14:11:29 by alilin            #+#    #+#             */
/*   Updated: 2021/06/23 11:42:09 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP
#include <string>
#include <iostream>
#include "listIterator.hpp"
#include "Node.hpp"

namespace ft
{
	template <typename T, typename ptr_t>
	class ListIterator;

	template <typename T, typename ptr_t>
	class ListConstIterator;

	template <typename T, typename ptr_t>
	class ListReverseIterator;

	template <typename T, typename ptr_t>
	class ListReverseConstIterator;

	template <class T, class Alloc = std::allocator<T>>
	class list
	{
	public:

		typedef T																					value_type;
		typedef Alloc																			allocator_type;
		typedef typename allocator_type::reference 				reference;
		typedef typename allocator_type::const_reference 	const_reference;
		typedef typename allocator_type::pointer 					pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;

		typedef ft::ListIterator<T, Node<T> *> iterator;
		typedef ft::ListConstIterator<T, Node<const T> *> const_iterator;
		typedef ft::ListReverseIterator<T, Node<T> *> reverse_iterator;
		typedef ft::ListReverseConstIterator<T, Node<const T> *> const_reverse_iterator;

		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;

		explicit list(const allocator_type &alloc = allocator_type()):
		_alloc(alloc), first(nullptr), last(nullptr), n(0) {}
		explicit list(size_t n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()):
		_alloc(alloc), first(nullptr), last(nullptr), n(0) {
			size_t i = 0;

			this->init_first_elem(val);
			Node<T> *save = first;
			while (i++ < n)
			{
				Node<T> *tmp = new Node<T>(val);
				save->insert_after(tmp);
				save = tmp;
			}
			this->n = n;
		}
		template <class InputIterator>
		list (InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()):
		_alloc(alloc), first(nullptr), last(nullptr), n(0) {
			
		}
		list(const list &x);

	protected:

	void	init_first_elem(const T &val)
	{
		last = new Node<T>();
		rlast = new Node<T>();
		first = new Node<T>(rlast, last, val);
		n = 1;
	}

	private:

		allocator_type 	_alloc;
		Node<T> 				*first;
		Node<T>					*last;
		Node<T>					*rlast;
		size_t 					n;

	};
}

#endif
