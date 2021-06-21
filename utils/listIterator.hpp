/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 10:19:05 by alilin            #+#    #+#             */
/*   Updated: 2021/06/21 18:25:29 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTITERATOR_HPP
# define LISTITERATOR_HPP

#include "node.hpp"
#include "list.hpp"

namespace ft
{
	template <typename T>
	class Node;

	template <typename T, typename ptr_t>
	class ListIterator
	{
	public:

		typedef T         value_type;
		typedef ptrdiff_t  difference_type;
		typedef const T*   pointer;
		typedef const T& reference;
		typedef std::bidirectional_iterator_tag  iterator_category;

		ListIterator(): ptr(0) {}
		ListIterator(ptr_t ptr): ptr(ptr) {}
		ListIterator(const ListIterator &rhs) : ptr(rhs.ptr) {}
		ListIterator &operator=(ListIterator const &rhs)
		{
			ptr = rhs.ptr;
			return (*this);
		}
		ListIterator &operator++(void) {
			if (ptr && ptr->p_next)
				ptr = ptr->p_next;
			return *this;
		}
		ListIterator operator++(T) {
			ListIterator tmp(*this);
			++(*this);
			return (tmp);
		}
		ListIterator &operator--(void) {
			if (ptr && ptr->p_prev)
				ptr = ptr->p_prev;
			return *this;
		}
		ListIterator operator--(T) {
			ListIterator tmp(*this);
			--(*this);
			return (tmp);
		}
		bool operator==(const ListIterator &rhs) const {
			return (ptr == rhs.ptr);
		}
		bool operator!=(const ListIterator &rhs) const {
			return (ptr != rhs.ptr);
		}
		bool operator==(const ptr_t rhs) const {
			return (ptr == rhs);
		}
		bool operator!=(const ptr_t rhs) const {
			return (ptr != rhs);
		}
		T& operator*() {
			return (*ptr.data);
		}
		T* operator->() {
			return (&ptr.data);
		}

	protected:

		ptr_t getPtr(void) const {
			return (ptr);
		}

	private:

		ptr_t ptr;
	};

	template <typename T, typename ptr_t>
	class ListConstIterator : protected class ListIterator<T, Node<T> *>
	{
	public:

		typedef const T         value_type;
		typedef ptrdiff_t  difference_type;
		typedef const T*   pointer;
		typedef const T& reference;
		typedef std::bidirectional_iterator_tag  iterator_category;

		ListConstIterator(): ptr(0) {}
		ListConstIterator(ptr_t ptr): ptr(ptr) {}
		ListConstIterator(const ListConstIterator &rhs) : ptr(rhs.ptr) {}
		ListConstIterator(const ListIterator<T, Node<T> *> &rhs) : ptr(reinterpret_cast<ft::Node<const T> *>(reinterpret_cast< const ListConstIterator &>(rhs).getPtr())) {}
		ListConstIterator &operator=(ListConstIterator const &rhs)
		{
			ptr = rhs.ptr;
			return (*this);
		}
		ListConstIterator &operator++(void) {
			if (ptr && ptr->p_next)
				ptr = ptr->p_next;
			return *this;
		}
		ListConstIterator operator++(int) {
			ListConstIterator tmp(*this);
			++(*this);
			return (tmp);
		}
		ListConstIterator &operator--(void) {
			if (ptr && ptr->p_prev)
				ptr = ptr->p_prev;
			return *this;
		}
		ListConstIterator operator--(int) {
			ListConstIterator tmp(*this);
			--(*this);
			return (tmp);
		}
		bool operator==(const ListConstIterator &rhs) const {
			return (ptr == rhs.ptr);
		}
		bool operator!=(const ListConstIterator &rhs) const {
			return (ptr != rhs.ptr);
		}
		bool operator==(const ptr_t rhs) const {
			return (ptr == rhs);
		}
		bool operator!=(const ptr_t rhs) const {
			return (ptr != rhs);
		}
		T& operator*() {
			return (*ptr.data);
		}
		T* operator->() {
			return (&ptr.data);
		}

	private:

		ptr_t ptr;
	};

	template <typename T, typename ptr_t>
	class ListReverseIterator
	{
	public:

		typedef T         value_type;
		typedef ptrdiff_t  difference_type;
		typedef const T*   pointer;
		typedef const T& reference;
		typedef std::bidirectional_iterator_tag  iterator_category;

		ListReverseIterator(): ptr(0) {}
		ListReverseIterator(ptr_t ptr): ptr(ptr) {}
		ListReverseIterator(const ListReverseIterator &rhs) : ptr(rhs.ptr) {}
		ListReverseIterator &operator=(ListReverseIterator const &rhs)
		{
			ptr = rhs.ptr;
			return (*this);
		}
		ListReverseIterator &operator++(void) {
			if (ptr && ptr->p_prev)
				ptr = ptr->p_prev;
			return *this;
		}
		ListReverseIterator operator++(T) {
			ListReverseIterator tmp(*this);
			--(*this);
			return (tmp);
		}
		ListReverseIterator &operator--(void) {
			if (ptr && ptr->p_next)
				ptr = ptr->p_next;
			return *this;
		}
		ListReverseIterator operator--(T) {
			ListReverseIterator tmp(*this);
			++(*this);
			return (tmp);
		}
		bool operator==(const ListReverseIterator &rhs) const {
			return (ptr == rhs.ptr);
		}
		bool operator!=(const ListReverseIterator &rhs) const {
			return (ptr != rhs.ptr);
		}
		bool operator==(const ptr_t rhs) const {
			return (ptr == rhs);
		}
		bool operator!=(const ptr_t rhs) const {
			return (ptr != rhs);
		}
		T& operator*() {
			return (*ptr.data);
		}
		T* operator->() {
			return (&ptr.data);
		}

	protected:

		ptr_t getPtr(void) const {
			return (ptr);
		}

	private:

		ptr_t ptr;
	};

	template <typename T, typename ptr_t>
	class ListReverseConstIterator : protected class ListReverseIterator<T, Node<T> *>
	{
	public:

		typedef const T         value_type;
		typedef ptrdiff_t  difference_type;
		typedef const T*   pointer;
		typedef const T& reference;
		typedef std::bidirectional_iterator_tag  iterator_category;

		ListReverseConstIterator(): ptr(0) {}
		ListReverseConstIterator(ptr_t ptr): ptr(ptr) {}
		ListReverseConstIterator(const ListReverseConstIterator &rhs) : ptr(rhs.ptr) {}
		ListReverseConstIterator(const ListReverseIterator<T, Node<T> *> &rhs) : ptr(reinterpret_cast<ft::Node<const T> *>(reinterpret_cast<const ListReverseConstIterator &>(rhs).getPtr())) {}
		ListReverseConstIterator &operator=(ListReverseConstIterator const &rhs)
		{
			ptr = rhs.ptr;
			return (*this);
		}
		ListReverseConstIterator &operator++(void) {
			if (ptr && ptr->p_prev)
				ptr = ptr->p_prev;
			return *this;
		}
		ListReverseConstIterator operator++(T) {
			ListReverseConstIterator tmp(*this);
			--(*this);
			return (tmp);
		}
		ListReverseConstIterator &operator--(void) {
			if (ptr && ptr->p_next)
				ptr = ptr->p_next;
			return *this;
		}
		ListReverseConstIterator operator--(T) {
			ListReverseConstIterator tmp(*this);
			++(*this);
			return (tmp);
		}
		bool operator==(const ListReverseConstIterator &rhs) const {
			return (ptr == rhs.ptr);
		}
		bool operator!=(const ListReverseConstIterator &rhs) const {
			return (ptr != rhs.ptr);
		}
		bool operator==(const ptr_t rhs) const {
			return (ptr == rhs);
		}
		bool operator!=(const ptr_t rhs) const {
			return (ptr != rhs);
		}
		T& operator*() {
			return (*ptr.data);
		}
		T* operator->() {
			return (&ptr.data);
		}

	private:

		ptr_t ptr;
	};
}

#endif
