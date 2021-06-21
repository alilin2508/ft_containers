/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 14:11:29 by alilin            #+#    #+#             */
/*   Updated: 2021/06/16 12:13:07 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP
#include <string>
#include <iostream>

namespace ft
{
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
		

	private:



	};
}

#endif
