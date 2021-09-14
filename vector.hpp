/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 13:20:46 by alilin            #+#    #+#             */
/*   Updated: 2021/09/14 12:26:04 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"

namespace ft
{
	template <class T, class Alloc = allocator<T>>
	class vector
	{
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::random_access_iterator<value_type const> const_iterator;

	};
}

#endif
