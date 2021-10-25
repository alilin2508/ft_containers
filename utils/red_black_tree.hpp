/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alilin <alilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:51:15 by alilin            #+#    #+#             */
/*   Updated: 2021/10/25 17:55:46 by alilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

#include <iterator>
#include <cstddef>
#include <memory>
#include <iostream>

#include "pair.hpp"
#include "reverse_iterator.hpp"

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
		color _color;

		Node(value_type data, Node* parent, Node* left, Node* right, color clr): parent(parent), left(left), right(right), data(data), _color(clr) {}
	};

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<Node<T> > >
	class RBtree
	{
	public:

		typedef T value_type;
		typedef Key key_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;

		typedef Node<value_type> node_type;
		typedef Node<value_type>* node_ptr;

		typedef std::size_t size_type;


		RBtree(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _root(NULL), _nil(NULL), _comp(comp), _alloc(alloc), _size(0)
		{
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, node_type(value_type(), NULL, NULL, NULL, black));
			_root = _nil;
		}

		RBtree(const RBtree &other): _root(NULL), _nil(NULL), _comp(other._comp), _alloc(other._alloc), _size(0)
		{
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, node_type(value_type(), NULL, NULL, NULL, black));
			_root = _nil;
			*this = other;
		}

		virtual ~RBtree()
		{
			clear_helper(_root);
			_root = _nil;
			_alloc.destroy(_nil);
			_alloc.deallocate(_nil, 1);
		}

		node_ptr getRoot()
		{
			return (this->_root);
		}

		// find the node with the minimum key
		node_ptr minimum(node_ptr node) const
		{
			while (node->left != _nil)
				node = node->left;
			return node;
		}

		// find the node with the maximum key
		node_ptr maximum(node_ptr node) const
		{
			while (node->right != _nil)
				node = node->right;
			return node;
		}

		void left_rotate(node_ptr x)
		{
			node_ptr y = x->right; // y saves x's right branch

			x->right = y->left; // x's new right child is y's old left child
			if (y->left != _nil) // if y->left isn't NULL
				y->left->parent = x;

			y->parent = x->parent; // y is new x so it takes old x's parent
			if (x->parent == NULL)
				this->_root = y;
			else if (x == x->parent->left) // if x was it's parent's left child, y becomes it's new parent's left child
				x->parent->left == y;
			else
				x->parent->right == y; // mirror case
			y->left = x;
			x->parent = y;
		}

		void right_rotate(node_ptr x) // mirror case
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

		node_ptr insertNode(node_ptr node)
		{
		// init with those values
		// node->parent = nullptr;
		// node->data = key;
		// node->left = TNULL;
		// node->right = TNULL;
		// node->color = red;
		// new node must be red

			node_ptr y = NULL;
			node_ptr x = this->root;

			while (x != _nil) // find node's natural placement
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
			else if (_comp(get_key_from_val(node->data), get_key_from_val(y->data))) // place the new node at it's right placement
				y->left = node;
			else
				y->right = node;
			// if new node is a root node, simply return
			if (node->parent == NULL)
			{
				node->_color = black;
				return;
			}
			// if the grandparent is null, simply return
			if (node->parent->parent == NULL)
			{
				return;
			}
			// Fix the tree colors
			fixInsert(node);
			return (node);
		}

		void deleteNode(key_type key)
		{
			deleteNodeHelper(this->_root, key);
		}

		// search the tree for the key k and return the corresponding node
		node_ptr searchTree(key_type k)
		{
			return searchTreeHelper(this->_root, k);
		}

		// find the successor of a given node
		node_ptr successor(node_ptr x)
		{
			// if the right subtree is not null the successor is the leftmost node in the sright subtree
			if (x->right != _nil)
			{
				return minimum(x->right);
			}
			// else it is the lowest ancestor of x whose left child is also an ancestor of x
			node_ptr y = x->parent;
			while (y != _nil && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		// find the predecessor of a given node
		node_ptr predecessor(node_ptr x)
		{
			// if the left subtree is not null the predecessor is the rightmost node in the left subtree
			if (x->left != _nil)
			{
				return maximum(x->left);
			}
			node_ptr y = x->parent;
			while (y != _nil && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

	protected:

		node_ptr _root;
		node_ptr _nil;
		key_compare _comp;
		allocator_type _alloc;
		size_type _size;

		virtual	key_type get_key_from_val(value_type const& val) const = 0;

		void fixInsert(node_ptr z)
		{
			node_ptr u;
			while (z->parent->_color == red)
			{
				if (z->parent == z->parent->parent->right) // parent is gp's right child
				{
					u = z->parent->parent->left; // uncle is left
					if (u->_color == red) // if uncle also red
					{
						u->_color = black;
						z->parent->_color = black;
						z->parent->parent->_color = red;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->left) // z is left child
						{
							z = z->parent;
							right_rotate(z); // new z is old parent
						}
						z->parent->_color = black;
						z->parent->parent->_color = red;
						left_rotate(z->parent->parent);
					}
				}
				else // parent is gp's left child #mirror_case
				{
					u = z->parent->parent->right; // uncle
					if (u->_color == red)
					{
					// mirror case
						u->_color = black;
						z->parent->_color = black;
						z->parent->parent->_color = red;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->right)
						{
							// mirror case
							z = z->parent;
							left_rotate(z);
						}
						// mirror case
						z->parent->_color = black;
						z->parent->parent->_color = red;
						right_rotate(z->parent->parent);
					}
				}
				if (z == _root)
				{
					break;
				}
			}
			_root->_color = black; // root is black
		}

		void rbTransplant(node_ptr u, node_ptr v) // replaces u by v
		{
			if (u->parent == NULL)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		// fix the rb tree modified by the delete operation
		void fixDelete(node_ptr x)
		{
			node_ptr w;
			while (x != this->_root && x->_color == black)
			{
				if (x == x->parent->left) // if x is the left child
				{
					w = x->parent->right; // w is x's right brother
					if (w->_color == red)
					{
						w->_color = black;
						x->parent->_color = red;
						leftRotate(x->parent); // new parent is w, old parent p became w's left child, p is still x's parent and x->parent->right bacame old w->left
						w = x->parent->right;
					}

					if (w->left->_color == black && w->right->_color == black)
					{
						w->_color = red;
						x = x->parent;
					}
					else // at least one child is red
					{
						if (w->right->_color == black) // left child is red
						{
							w->left->_color = black;
							w->_color = red;
							rightRotate(x);
							w = x->parent->right;
						}
						w->_color = x->parent->_color;
						x->parent->_color = black;
						w->right->_color = black;
						leftRotate(x->parent);
						x = _root;
					}
				}
				else // mirror case
				{
					w = x->parent->left;
					if (w->_color == red)
					{
						w->_color = black;
						x->parent->_color = red;
						rightRotate(x->parent);
						w = x->parent->left;
					}

					if (w->left->_color == black && w->right->_color == black)
					{
						w->_color = red;
						x = x->parent;
					}
					else
					{
						if (w->left->_color == black)
						{
							w->right->_color = black;
							w->_color = red;
							leftRotate(x);
							w = x->parent->left;
						}
						w->_color = x->parent->_color;
						x->parent->_color = black;
						w->left->_color = black;
						rightRotate(x->parent);
						x = _root;
					}
				}
			}
			x->_color = black; // root is black
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
			color y_og_color = y->_color;
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
				y_og_color = y->_color;
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
				y->_color = z->_color; // we keep the old z color
			}
			_alloc.destroy(z);
			_alloc.deallocate(z, 1);
			_size--;
			if (y_og_color == black) // fix the lost black color on x
				fixDelete(x);
		}

		void clear_helper(node_ptr const &node)
		{
			// Base case of recursion
			if (node == _nil)
				return;

			// Clear all nodes to the left and right of it
			clear_helper(node->left);
			clear_helper(node->right);

			// Clear the node itself
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);

			_size--;
		}

		node_ptr searchTreeHelper(node_ptr node, key_type key)
		{
			if (node == _nil || key == get_key_from_val(node->data))
				return node;
			if (key < node->data)
				return searchTreeHelper(node->left, key);
			return searchTreeHelper(node->right, key);
		}

		void copy_helper(node_ptr &lhs, node_ptr rhs, node_ptr parent, node_ptr nil_rhs)
		{
			if (rhs == nil_rhs)
			{
				lhs = _nil;
				return;
			}
			lhs = _alloc.allocate(1);
			_alloc.construct(lhs, *rhs);
			// Parent is the previously created node pased as argument
			lhs->parent = parent;
			copy_helper(lhs->left, rhs->left, lhs, nil_rhs);
			copy_helper(lhs->right, rhs->right, lhs, nil_rhs);
		}
	};
}

#endif
