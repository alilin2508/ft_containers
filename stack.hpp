/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:31:26 by alilin            #+#    #+#             */
/*   Updated: 2021/10/21 15:32:00 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:

		typedef T value_type;
		typedef Container container_type;
		typedef std::size_t size_type;

		explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}
		stack(const stack &other): c(other.c) {}
		stack &operator=(const stack &other)
		{
			c = other.c;
			return (*this);
		}
		~stack() {}

		bool empty() const
		{
			return (c.empty());
		}

		size_type size() const
		{
			return (c.size());
		}

		value_type &top()
		{
			return (c.back());
		}

		const value_type &top() const
		{
			return (c.back());
		}

		void push(const value_type &val)
		{
			return (c.push_back(val));
		}

		void pop()
		{
			return (c.pop_back());
		}

		template <class U, class ctnr>
	  friend bool operator==(const stack<U,ctnr> &lhs, const stack<U,ctnr> &rhs);

		template <class U, class ctnr>
	  friend bool operator!=(const stack<U,ctnr> &lhs, const stack<U,ctnr> &rhs);

		template <class U, class ctnr>
	  friend bool operator<(const stack<U,ctnr> &lhs, const stack<U,ctnr> &rhs);

		template <class U, class ctnr>
	  friend bool operator<=(const stack<U,ctnr> &lhs, const stack<U,ctnr> &rhs);

		template <class U, class ctnr>
	  friend bool operator>(const stack<U,ctnr> &lhs, const stack<U,ctnr> &rhs);

		template <class U, class ctnr>
	  friend bool operator>=(const stack<U,ctnr> &lhs, const stack<U,ctnr> &rhs);

	private:

		container_type c;
	};

		template <class T, class Container>
	  bool operator==(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
		{
			return (lhs.c == rhs.c);
		}

		template <class T, class Container>
	  bool operator!=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
		{
			return (lhs.c != rhs.c);
		}

		template <class T, class Container>
	  bool operator<(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
		{
			return (lhs.c < rhs.c);
		}

		template <class T, class Container>
	  bool operator<=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
		{
			return (lhs.c <= rhs.c);
		}

		template <class T, class Container>
	  bool operator>(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
		{
			return (lhs.c > rhs.c);
		}

		template <class T, class Container>
	  bool operator>=(const stack<T,Container> &lhs, const stack<T,Container> &rhs)
		{
			return (lhs.c >= rhs.c);
		}
}

#endif
