/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 14:11:29 by alilin            #+#    #+#             */
/*   Updated: 2021/06/21 18:38:59 by alilin           ###   ########.fr       */
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

	template <class T, class Alloc = allocator<T>>
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

		

	private:

	};
}

#endif
