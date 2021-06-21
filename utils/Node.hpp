/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:13:51 by alilin            #+#    #+#             */
/*   Updated: 2021/06/21 18:25:31 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

namespace ft
{
	template <typename T>
	class	Node
	{
	public:

		T data;
		Node *p_next;
		Node *p_prev;

		Node(): p_prev(nullptr), data(), p_next(nullptr) {}
		Node(T const &data):
		p_prev(nullptr), data(data), p_next(nullptr) {}
		Node(Node *prev, T const &data, Node *next):
		p_prev(prev), data(data), p_next(next) {
			prev->p_next = this;
			next->p_prev = this;
		}
		Node(Node const &other):
		p_prev(other.p_prev), data(other.data), p_next(other.p_next) {}
		virtual ~Node() {}

		Node &operator=(Node const &other) {
		this->p_prev = other.p_prev;
		this->data = other.data;
		this->p_next = other.p_next;
		return (*this);
	}

		void	insert_after(Node *node)
		{
			node->p_next = p_next;
			node->p_prev = this;
			p_next->p_prev = node;
			p_next = node;
		}

		void	insert_previous(Node *node)
		{
			node->p_next = this;
			node->p_prev = p_prev;
			p_prev->p_next = node;
			p_prev = node;
		}

		void	move_to_previous(Node *node)
		{
			node->p_prev->p_next = node->p_next;
			node->p_next->p_prev = node->p_prev;
			this->insert_previous(node);
		}

		void	swap_nodes(Node *node)
		{
			Node *temp_prev = p_prev;
			Node *temp_next = p_next;

			p_prev = node->p_prev;
			p_next = node->p_next;
			node->p_prev = temp_prev;
			node->p_next = temp_next;
		}

		void	swap_following_nodes(Node *node_next)
		{
			Node *next_next = node_next->p_next;
			Node *prev_current = p_prev;

			p_next = node_next->p_next;
			node_next->p_prev = p_prev;
			p_prev = node_next;
			node_next->p_next = this;
			next_next->p_prev = this;
			prev_current->p_next = node_next;
		}
	};
}

#endif
