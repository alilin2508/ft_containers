/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:09:38 by alilin            #+#    #+#             */
/*   Updated: 2021/10/23 03:04:19 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "./utils/pair.hpp"
#include "./utils/red_black_tree.hpp"
#include "./utils/reverse_iterator.hpp"
#include "./utils/bidirectional_iterator.hpp"
// #include "./utils/enable_if.hpp"
// #include "./utils/equal.hpp"
// #include "./utils/is_integral.hpp"
// #include "./utils/lexicographical_compare.hpp"

#include <functional> // for std::less
#include <memory>

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map : public RBTree< class Key, ft::pair<const Key, T>, Compare, typename Alloc::template rebind<ft::Node<ft::pair<Key const, T> > >::other  >
	{
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::difference_type difference_type;

		typedef ft::bidirectional_iterator<value_type> iterator;
		typedef ft::bidirectional_iterator<value_type const> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	};
}

#endif
