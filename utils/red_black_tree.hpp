/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:51:15 by alilin            #+#    #+#             */
/*   Updated: 2021/10/19 15:43:56 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

#include <iterator>
#include <cstddef>
#include <memory>

#include "pair.hpp"
#include "reverse_iterator.hpp"
#include ""

namespace ft
{
	enum color {red, black};

	template <class T>
	struct Node
	{
		typedef	T value_type;

		struct Node* parent;
		struct Node* left;
		struct Node* right;

		value_type data;
		color color;

		// Node(value_type data, Node* parent, Node* left, Node* right,calor color): data(data), parent(parent), left(left), right(right), color(color) {}
	};

	template <class Key, class T, class Compare = std::less<Key> >
	class RBtree
	{
	public:

		typedef T value_type;
		typedef Node<value_type>* node_ptr;
		typedef Compare Key_compare;

		RBTree()
		{
			_nil = new Node;
			_nil->color = 0;
			_nil->left = NULL;
			_nil->right = NULL;
			root = _nil;
		}

		node_pointer getRoot()
		{
			return (this->_root);
		}

		void left_rotate(node_ptr x)
		{
			node_ptr y = x->right;

			x->right = y->left;
			if (y->left != _nil)
				y->left->parent = x;

			y->parent = x->parent;
			if (x->parent == NULL)
				this->_root = y;
			else if (x == x->parent->left)
				x->parent->left == y;
			else
				x->parent->right == y;
			y->left = x;
			x->parent = y;
		}

		void right_rotate(node_ptr x)
		{
			node_ptr y = x->left;

			x->left = y->right;
			if (y->right != _nil)
				y->right->parent = x;

			y->parent = x->parent;
			if (x->parent == NULL)
				this->_root = y;
			else if (x == x->parent->left)
				x->parent->left == y;
			else
				x->parent->right == y;
			y->right = x;
			x->parent = y;
		}

		void insert(Node node)
		{
		// Ordinary Binary Search Insertion
		// node->parent = nullptr;
		// node->data = key;
		// node->left = TNULL;
		// node->right = TNULL;
		// node->color = 1;
		// new node must be red

			node_ptr y = NULL;
			node_ptr x = this->root;

			while (x != _nil)
			{
				y = x;
				if (_comp(get_key_from_val(node->data), get_key_from_val(x->data)))
					x = x->left;
				else
					x = x->right;
			}
			node->parent = y;
			if (y == NULL)
				this->root = node;
			else if (_comp(get_key_from_val(node->data), get_key_from_val(y->data)))
				y->left = node;
			else
				y->right = node;
			// if new node is a root node, simply return
			if (node->parent == NULL)
			{
				node->color = black;
				return;
			}
			// if the grandparent is null, simply return
			if (node->parent->parent == NULL)
			{
				return;
			}
			// Fix the tree
			fixInsert(node);
		}

	protected:

		node_ptr _root;
		node_ptr _nil;
		Key_compare _comp;

		fixInsert(node_ptr z)
		{
			node_ptr u;
			while (z->parent->color == red)
			{
				if (z->parent == z->parent->parent->right) // parent is gp's right child
				{
					u = z->parent->parent->left; // uncle is left
					if (u->color == red) // if uncle also red
					{
						u->color = black;
						z->parent->color = black;
						z->parent->parent->color = red;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->left) // z is left child
						{
							z = z->parent;
							right_rotate(z); // new z is old parent
						}
						// case 3.2.1
						z->parent->color = black;
						z->parent->parent->color = red;
						left_rotate(z->parent->parent);
					}
				}
				else // parent is gp's left child
				{
					u = z->parent->parent->right; // uncle
					if (u->color == red)
					{
					// mirror case
						u->color = black;
						z->parent->color = black;
						z->parent->parent->color = red;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->right)
						{
							// mirror case
							z = z->parent;
							left_rotate(k);
						}
						// mirror case
						z->parent->color = black;
						z->parent->parent->color = red;
						right_rotate(k->parent->parent);
					}
				}
				if (z == root)
				{
					break;
				}
			}
			root->color = black;
		}

	};
}

#endif
