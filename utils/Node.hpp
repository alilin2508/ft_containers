/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:13:51 by alilin            #+#    #+#             */
/*   Updated: 2021/06/21 11:28:35 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

nanespace ft
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
		Node(Node *prev, T const &data, Node *next=nullptr):
		p_prev(prev), data(data), p_next(next) {}
		Node(Node const &other):
		p_prev(other.p_prev), data(other.data), p_next(other.p_next) {}
		virtual ~Node() {}

		Node &operator=(Node const &other) {
		this->p_prev = other.p_prev;
		this->data = other.data;
		this->p_next = other.p_next;
		return (*this);
	}

	};

	class Dlist : public Node
	{
	public:

		Node *p_tail;
		Node *p_head;

		Dlist():
		p_tail(nullptr), p_head(nullptr) {}

		Dlist(Node *p_tail, Node *p_head):
		p_tail(p_tail), p_head(p_tail) {}

		template <typename T>
		void insert_after(T data) {
			Node *n = new node(data);
			n->p_next = nullptr;
			if (this->p_tail == NULL) /* Cas où notre liste est vide (pointeur vers fin de liste à  NULL) */
			{
					n->p_prev = nullptr; /* On fait pointer p_prev vers NULL */
					this->p_head = n; /* On fait pointer la tête de liste vers le nouvel élément */
					this->p_tail = n; /* On fait pointer la fin de liste vers le nouvel élément */
			}
			else /* Cas où des éléments sont déjà présents dans notre liste */
			{
					this->p_tail->p_next = n; /* On relie le dernier élément de la liste vers notre nouvel élément (début du chaînage) */
					n->p_prev = this->p_tail; /* On fait pointer p_prev vers le dernier élément de la liste */
					this->p_tail = n; /* On fait pointer la fin de liste vers notre nouvel élément (fin du chaînage: 3 étapes) */
			}
		}

		template <typename T>
		void insert_before(T data) {
			Node *n = new node(data);
			n->p_prev = nullptr;
			if (this->p_tail == NULL)
			{
					n->p_next = nullptr;
					this->p_head = n;
					this->p_tail = n;
			}
			else
			{
					this->p_head->p_prev = n;
					n->p_next = this->p_head;
					this->p_head = n;
			}
		}

		~Dlist() {
			node *p_temp = this->p_head;
			while(p_temp != nullptr)
			{
				node *p_del = p_temp;
				p_temp = p_temp->p_next;
				delete (p_del);
			}
		}
	};
}

#endif
