#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include <iterator>
#include <cstddef>

namespace ft
{

							/*--------------------------*/
						 /** BIDIRECTIONAL:ITERATOR: */
						/*--------------------------*/	
	template<class T, class Node_type>
	class bidirectional_iterator
	{
	public:

		typedef Node_type			value_type;
		typedef value_type*		Node;

		typedef T															 				data_type;
		typedef data_type&														reference;
		typedef const data_type&											const_reference;
		typedef data_type*														pointer;
		typedef const data_type*											const_pointer;

		typedef typename std::ptrdiff_t								difference_type;
		typedef std::bidirectional_iterator_tag				iterator_category;

		Node	_node;
		Node	_root;
		Node	_nil;

		bidirectional_iterator(Node src) { _node = src; }

public:
/** MEMBER:FUNCTIONS: */
//	Default constructor
		bidirectional_iterator() :
			_node(NULL), _root(NULL), _nil(NULL) {}

//	Initialization constructor
		bidirectional_iterator(Node node, Node root,	Node nil) :
			_node(node), _root(root), _nil(nil) {}

//	Copy constructor
		bidirectional_iterator(const bidirectional_iterator& it) :
			_node(it._node), _root(it._root), _nil(it._nil) {}

		~bidirectional_iterator() {}

		bidirectional_iterator&	operator= (const bidirectional_iterator& it) {
			if (this == &it)	return *this;
			_node = it._node;
			_root = it._root;
			_nil = it._nil;
			return *this;
		}

		template <class U>
		bidirectional_iterator&	operator= (const bidirectional_iterator<const U, Node_type>& it) {
			if (this == &it)	return *this;
			_node = it._node;
			_root = it._root;
			_nil = it._nil;
			return *this;
		}

		// Overload called when trying to copy construct a const_iterator
		operator bidirectional_iterator<const T, Node_type>() const
		{	return bidirectional_iterator<const T, Node_type>(_node, _root, _nil); }

//	Returns a copy of the base iterator '_iterator' used for underlying work
		pointer	base() const {	return _node; }

//	Deference iterator:	Returns a reference to the element pointed to by the iterator 
		reference	operator*() const { return _node->_data; }

//	Increment iterator position (pre-increment)
		bidirectional_iterator&	operator++ () { if (_node != _nil) { _node = successor(_node); } return *this; }

//	Increment iterator position (post-increment)
		bidirectional_iterator operator++ (int) { bidirectional_iterator tmp(*this);	operator++();	return tmp;	}

//	Decrement iterator position (pre-increment)
		bidirectional_iterator&	operator-- () {
			if (_node == _nil) _node = maximum(_root);
			else _node = predecessor(_node);
			return *this;
		}

//	Decrement iterator position (post-increment)
		bidirectional_iterator operator-- (int) {
			bidirectional_iterator tmp(*this);
			operator--();
			return tmp;
		}

//	Deference iterator - Returns a pointer to the element pointed to by the iterator		
		pointer	operator->() const { return &(operator*());	}

		bool operator==(const bidirectional_iterator& rhs) const { return _node == rhs._node; }
		bool operator!=(const bidirectional_iterator& rhs) const { return !(_node == rhs._node);	}

	private:

		Node	maximum(Node node) {
			while (node->_right != _nil)
				node = node->_right;
			return node;
		}

		Node	minimum(Node node) {
			while (node->_left != _nil)
				node = node->_left;
			return node;
		}

		// Get previous node in order
		Node predecessor(Node node)	{
			Node predecessor;

			// If node has a left child, it's predecessor is the maximum
			// of its left subtree
			if (node->_left != _nil)
				return maximum(node->_left);

			// If not, we need to go look for it in it's parent left side
			// The predecessor will be the first node that has its
			// left child that isn't also an ancestor of the base node
			predecessor = node->_parent;
			while (node->_parent != NULL && node == predecessor->_left)
			{
				node = predecessor;
				predecessor = predecessor->_parent;
			}

			// If node is _root then successor is NULL
			if (!predecessor)
				return _nil;
			else
				return predecessor;
		}

		// Get next node in order
		Node successor(Node node)	{
			Node successor;

			// If node has a right child, it's successor is the minimum
			// of its right subtree
			if (node->_right != _nil)
				return minimum(node->_right);

			// If not, we need to go look for it in it's parent right side
			// The successor will be the first node that has its
			// right child that isn't also an ancestor of the base node
			successor = node->_parent;
			while (node->_parent != NULL && node == successor->_right)
			{
				node = successor;
				successor = successor->_parent;
			}

			// If node is _root then successor is NULL
			if (!successor)
				return _nil;
			else
				return successor;
		}
	};
}


#endif