/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:51:15 by alilin            #+#    #+#             */
/*   Updated: 2021/10/20 15:35:01 by alilin           ###   ########.fr       */
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

		Node(value_type data, Node* parent, Node* left, Node* right,calor color): data(data), parent(parent), left(left), right(right), color(color) {}
	};

	template <class Key, class T, class Compare = std::less<Key>, >
	class RBtree
	{
	public:

		typedef T value_type;
		typedef Key key_type;
		typedef Node<value_type>* node_ptr;
		typedef Compare Key_compare;

		RBTree()
		{
			_nil = new Node;
			_nil->color = black;
			_nil->left = NULL;
			_nil->right = NULL;
			root = _nil;
		}

		node_pointer getRoot()
		{
			return (this->_root);
		}

		// find the node with the minimum key
		node_ptr minimum(node_ptr node)
		{
			while (node->left != TNULL)
				node = node->left;
			return node;
		}

		// find the node with the maximum key
		node_ptr maximum(node_ptr node)
		{
			while (node->right != TNULL)
				node = node->right;
			return node;
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

		void deleteNode(key_type key)
		{
			deleteNodeHelper(this->_root, key);
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
						z->parent->color = black;
						z->parent->parent->color = red;
						left_rotate(z->parent->parent);
					}
				}
				else // parent is gp's left child #mirror_case
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

		void rbTransplant(node_ptr u, node_ptr v) // replaces u by v
		{
			if (u->parent == NULL)
				root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		void deleteNodeHelper(node_ptr node, key_type key)
		{
			// find the node containing key
			node_ptr z = NULL;
			node_ptr x, y;
			while (node != NULL)
			{
				if (get_key_from_val(node->data) == key)
					z = node;
				if (get_key_from_val(node->data) <= key)
					node = node->right;
			 	else
					node = node->left;
			}

			if (z == NULL)
			{
				std::cout << "Couldn't find key in the tree" << std::endl;
				return;
			}

			y = z; // y saves the suppressed node's placement
			color y_og_color = y->color;
			if (z->left == NULL) // z only had 1 child whitch is the right one so so it get's replaced by it's child
			{
				x = z->right; // x saves the right child's branch
				rbTransplant(z, z->right);
			}
			else if (z->right == NULL) //mirror case
			{
				x = z->left;
				rbTransplant(z, z->left);
			}
			else // suppressed node had 2 children and is replaced by the minimum of it's right branch
			{
				y = minimum(z->right); // search for the minimum in the right child's branch
				y_og_color = y->color;
				x = y->right; // x saves the minimum's right branch
				if (y->parent == z) // the minimum is z->right
					x->parent = y;
				else
				{
					rbTransplant(y, y->right); // replaces the minimum by it's right branch
					y->right = z->right; // set the new z's right side
					y->right->parent = y;
				}
				rbTransplant(z, y); // replace z by the correct value whitch is y and maintain the tree as a good search tree
				y->left = z->left; // set the new z's left side
				y->left->parent = y;
				y->color = z->color; // we keep the old z color
			}
			delete z;
			if (y_og_color == black)
				fixDelete(x);
		}

	};
}

#endif
