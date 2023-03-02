#ifndef _MAP_HPP_
#define _MAP_HPP_

#include "../inc/pair.hpp"
#include "../inc/bidirectional_iterator.hpp"
#include "../inc/reverse_iterator.hpp"
#include "../inc/lex_compare.hpp"

namespace ft {

	/*----------*/
 /**	NODE:  */
/*----------*/

	template <class T>
 	struct TNode {

		typedef T								value_type;			
		typedef TNode*					Node;
		typedef std::size_t			size_type;
		typedef std::ptrdiff_t	difference_type;

		value_type	_data;
		Node				_left;
		Node				_right;
		Node				_parent;
		int					_height;
	
		TNode(value_type data, Node left, Node right, Node parent, size_type height)	:
		_data(data), _left(left), _right(right), _parent(parent), _height(height){}
	};

	/*---------*/
 /**	MAP:  */
/*---------*/

template <class Key, 
					class T, 
					class Compare = std::less<Key>,
		   		class Alloc = std::allocator<TNode<ft::pair<const Key, T> > >
> class map {

	public:

	/*-----------------*/
 /**	MEMBER:TYPES: */
/*-----------------*/

//	Definition																Member type
		typedef Key																key_type;
		typedef T																	mapped_type;
		typedef ft::pair<const Key, T>						value_type;
		typedef Compare														key_compare;

/** @value_compare: compares the key of objects of type map::value_type	*/
		class value_compare : public std::binary_function<value_type, value_type, bool> {
			private:
				friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}
			public:
				typedef bool 				result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				bool operator() (const value_type& lhs, const value_type& rhs) const {
					return comp(lhs.first, rhs.first);
				}
		};

		typedef Alloc																															allocator_type;
		typedef typename Alloc::pointer																						pointer;
		typedef typename Alloc::const_pointer																			const_pointer;
		typedef typename Alloc::reference																					reference;
		typedef typename Alloc::const_reference																		const_reference;
		typedef ft::TNode<value_type>																							node_type;
		typedef ft::TNode<value_type>*																						Node;		
		typedef typename Alloc::template rebind<node_type>::other									node_allocator_type;
		typedef typename ft::bidirectional_iterator<value_type, node_type>				iterator;
		typedef typename ft::bidirectional_iterator<const value_type, node_type> 	const_iterator;
		typedef typename ft::reverse_iterator<iterator>														reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>											const_reverse_iterator;
		typedef std::ptrdiff_t																										difference_type;
		typedef std::size_t																												size_type;

	private:
		Node 								_root;
		Node								_nil;
		size_type						_size;
		Compare							_comp;
		allocator_type			_alloc;
		node_allocator_type _node_alloc;

public:
 	/*---------------------*/
 /**	MEMBER:FUNCTIONS: */
/*---------------------*/

/**	CONSTRUCTOR: 	*/
		explicit map (const key_compare& comp = key_compare(), 
									const allocator_type& alloc = allocator_type()) :
		_root(NULL), _nil(NULL), _size(0), _comp(comp), _alloc(alloc) {

		_nil = _node_alloc.allocate(1);
		_node_alloc.construct(_nil, node_type(value_type(), NULL, NULL, NULL, 1));
		_root = _nil;
	}

	// range
	template <class InputIterator>
	map		(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
		 		const allocator_type& alloc = allocator_type()) :
				_size(0), _comp(comp), _alloc(alloc) {

		_nil = _node_alloc.allocate(1);
		_node_alloc.construct(_nil, node_type(value_type(), NULL, NULL, NULL, 1));
		_root = _nil;

		insert(first,last);
	}

	// copy
	map (const map& x) :
		_root(NULL),
		_nil(NULL),
		_size(0),
		_comp(x._comp),
		_alloc(x._alloc) {
		
		_nil = _node_alloc.allocate(1);
		_node_alloc.construct(_nil, node_type(value_type(), NULL, NULL, NULL, 1));
	
		_root = _nil;
		*this = x;
	}

/**	DESTRUCTOR: 	*/
	// destructor
	~map(){
		clear();
		_node_alloc.destroy(_nil);
		_node_alloc.deallocate(_nil, 1);
	}

	// Assigns new contents to the container, replacing its current content
	map& operator= (const map& x) {
		// self assignment check
		if (this == &x) { return *this; }
 		
		// previous elements are erased
		clear();
		
		// copy all elements
		_copy(_root, x._root, NULL, x._nil);
		_size = x._size;

		return *this;
	}

/**END_CONSTRUCTORTS	-----------------------------------------------------------***/


/** ITERATORS:	***/
/**iterator to begin
 * Returns an iterator to the first element in the map container;
 * Because map keeps its elements sorted, begin() points to the
 * smallest element (crescent sorting); */
	iterator begin() {
		if (empty()) {
			return iterator(_nil, _root, _nil);
		} 
		return iterator(minimum(_root), _root, _nil);
	}

	const_iterator begin() const {
		if (empty()) {
			return const_iterator(_nil, _root, _nil);
		}
		return const_iterator(minimum(_root), _root, _nil);
	}
	
/**iterator to end
 * Returns an iterator to the theoretical element that would
 * follow the last element in the container;
 * If container is empty() return begin() */
	iterator end() {
		// Returning begin() here if the container is empty will turns impossible to compare end() with find() if element was not found;
		// In the cont_iterator end() however, it is mandatory or it will return an error;
		if (empty()) { return begin(); }
		return iterator(_nil, _root, _nil);
	}

	const_iterator end() const {
		if (empty()) return begin(); 
		return const_iterator(_nil, _root, _nil);
	}
//	reverse-iterator to begin-end
		reverse_iterator rbegin() {
			return reverse_iterator(iterator(_nil, _root, _nil)); }
		const_reverse_iterator rbegin() const {
			return reverse_iterator(const_iterator(_nil, _root, _nil)); }
		reverse_iterator rend() { if (empty()) return rbegin();
			return reverse_iterator(iterator(minimum(_root), _root,_nil));	}
		const_reverse_iterator rend() const {	if (empty()) return rbegin();
			return const_reverse_iterator(const_iterator(minimum(_root), _root, _nil)); }
/**END_ITERATORS	-----------------------------------------------------------***/


/** CAPACITY:	***/

	bool empty() const { return _size == 0;	}
	size_type size() const { return _size; }
	// max_size is a public member function of std::allocator
	size_type max_size() const { return _alloc.max_size(); }
/**END_CAPACITY	-----------------------------------------------------------***/


/** ELEMENT:ACCESS:	------------------------------------------------------***/

	mapped_type& operator[] (const key_type& k) {
		/** 'k' matches the key of an element in the container */
		iterator it = find(k) ;
		if (it != end()) {	return it._node->_data.second; }

		/** 'k' does not match the key of any element in the container,
		 * the function inserts a new element with that key */
		ft::pair<iterator, bool> pair;
		pair = insert(ft::make_pair(k, mapped_type()));
		it = pair.first;
		return it._node->_data.second;
	}

	mapped_type& at (const key_type& k) {
   	/** 'k' matches the key of an element in the container */
    iterator it = find(k) ;
    if (it != end()) {      return it._node->_data.second; }
    else throw std::out_of_range("map::at: out of range");
        }

  const mapped_type& at (const key_type& k) const{
		const_iterator it = find(k) ;
    if (it != end()) { return it._node->_data.second; }
    else throw std::out_of_range("map::at: out of range");
  }


/**END_ELEMENTACCESS	-----------------------------------------------------------***/


/** MODIFIERS:	-----------------------------------------------------------***/
	// single element
	pair<iterator,bool> insert (const value_type& val) {
	/** @check: checks whether each inserted element has a key
	 * equivalent to thes one of an element already in the container
	 * if key already exists, the new element is not inserted and
	 * an iterator pointing to the the existing element is returned
	 */
		iterator it = find(val.first);
		if (it != end())
			return ft::make_pair(it, false);

		Node node = _node_alloc.allocate(1);
		_node_alloc.construct(node, node_type(val, _nil, _nil, NULL, 1));
		it = iterator(_insert(node), _root, _nil);
		balance(it._node);

		_size++;
		return ft::make_pair(it, true);
	}


	//hint
	iterator insert (iterator pos, const value_type& val) {

		if (_comp(pos._node->_data.first, val.first)) {
			Node node = _node_alloc.allocate(1);
			_node_alloc.construct(node, node_type(val, _nil, _nil, NULL, 1));
			iterator(_insert(node), _root, _nil);
			if (_size > 2) balance(pos._node);
			_size++;
			return iterator(node, _root, _nil);
		}
		return insert(val).first;
	}

	//range
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last) {
		while(first != last) insert(*first++);
	}

	//erase
	void erase(iterator position) {
		if (empty() || position == end()) return;
		position._node = _erase(position._node);
		if (_size > 2) balance(position._node);
		--_size;
	}

	size_type erase(const key_type& k) {
		iterator it = find(k);
		if (it == end()) return 0;
		erase(it);
		return 1;
	}

	void erase(iterator first, iterator last) {
		while(first != last) { erase(first++);	}
	}
	
	void swap(map& x) {
		Node tmp = _root;
		_root = x._root;
		x._root = tmp;

		Node nil = _nil;
		_nil = x._nil;
		x._nil = nil;

		size_type s = _size;
		_size = x._size;
		x._size = s;
	}

	void clear() { clear(_root); _root = _nil; }

	key_compare key_comp() const { return key_compare(); }
	value_compare value_comp() const { return key_compare(); }

	iterator find(const key_type& key) {
		Node node = find_node(key, _root);
		if (node)
			return iterator(node, _root, _nil);
		return end();
	}

	const_iterator find(const key_type& key) const {
		Node node = find_node(key, _root);
		if (node)
			return const_iterator(node, _root, _nil);
		return end();
	}

	size_type count(const key_type& k) const {
		if (find(k) != end()) return 1; 
		return 0;
	}

	/** Returns an iterator to the first element whose key
	 *	is greater than k */
	iterator upper_bound(const key_type& k) {
		iterator it = begin();
		iterator it_end = end();

		while (it != it_end) {
			if (_comp(k, it._node->_data.first))
				return it;
			it++;
		}
		return end();
	}

	const_iterator upper_bound(const key_type& k) const{
		const_iterator it = begin();
		const_iterator it_end = end();

		while (it != it_end) {
			if (_comp(k, it._node->_data.first))
				return it;
			it++;
		}
		return end();
	}

	iterator lower_bound(const key_type& k) {
		iterator it = begin();
		iterator it_end = end();
		while (it != it_end) {
			if (_comp(k, it._node->_data.first) || k == it._node->_data.first)
				return it;
			it++;
		}
		return end();
	}

	const_iterator lower_bound(const key_type& k) const {
		const_iterator it = begin();
		const_iterator it_end = end();

		while (it != it_end) {
			if (_comp(k, it._node->_data.first) || k == it._node->_data.first)
				return it;
			it++;
		}
		return end();
	}

	pair<const_iterator, const_iterator> equal_range (const key_type& k) const {
		return ft::make_pair(lower_bound(k), upper_bound(k));
	}
	pair<iterator, iterator> equal_range (const key_type& k) {
		return ft::make_pair(lower_bound(k), upper_bound(k));
	}
/** END_OPERATIONS	-------------------------------------------------------***/

/** ALLOCATOR:	-----------------------------------------------------------***/
	allocator_type get_allocator() const { return _alloc;	}
/** END_ALLOCATOR	---------------------------------------------------------***/
/**END_MEMBER FUNCTIONS	-----------------------------------------------------------***/

private: 
//_balance() gives us the info about how many more nodes
//a branch has relatively to the opposite one
	int _balance(Node node) {	return (height(node->_left) - height(node->_right)); }

	void balance(Node node) {
//	iterate through the tree from last inserted node to _root
		while(node != NULL) {
	//	Rotate if needed

			int balance = _balance(node);

			if(balance > 1 && _balance(node->_left) > 0) { 
				node = rotateRight(node);
			}
			else if(balance < -1 && _balance(node->_right) < 1) { 
				node = rotateLeft(node);
			}
			else if(balance > 1 && _balance(node->_left) < 0) {
				node->_left = rotateLeft(node->_left);
				node = rotateRight(node);
			}
			else if ( balance < -1 && _balance(node->_right) > 0) {
				node->_right = rotateRight(node->_right);
				node = rotateLeft(node);
			}
			// re-adjust heights
			height(node, _root);
			if (node->_parent == NULL) {_root = node; }	
			node = node->_parent;
		}
	}

	void clear(const Node& node) {
		if (node == _nil) { return; }
		clear(node->_left);
		clear(node->_right);
		_node_alloc.destroy(node);
		_node_alloc.deallocate(node,1);
		_size--;
	}

	void _copy(Node& node, Node copy, Node parent, Node end) {
		/** while the node to be copied not equal its end node 
		 * 	new nodes are being added left and right
		 *	and the node parent is atualized */
		if (copy == end) node = _nil;
		else {
			node = _node_alloc.allocate(1);
			_node_alloc.construct(node, *copy);
			node->_parent = parent;
			_copy(node->_left, copy->_left, node, end);
			_copy(node->_right, copy->_right, node, end);
		}
	}

	Node _erase(Node node) {

		if (_size == 1) {
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
			_root = _nil;
  		return NULL;
		}
  /*-------------*/
 /** @new_node: */
/*-------------*/
		Node new_node = NULL;
		if (node->_left != _nil) { new_node = predecessor(node); }
		else new_node = successor(node);

  /*-------------*/
 /** @children: */
/*-------------*/
		Node child = NULL;
		if (node->_left == _nil || node->_right == _nil) {

			if (node->_left != _nil)
				child = node->_left;
			else if (node->_right != _nil)
				child = node->_right;

  /*-------------*/
 /** @no_child: */
/*-------------*/
			if (!child) {

				if (node->_parent->_left == node) {
					node->_parent->_left = _nil;
				}
				else if (node->_parent->_right == node)
					node->_parent->_right = _nil;
			}
			else { // left-side

   /*--------------*/
	/**	@one_child: */ 
 /*--------------*/
/**	@left_side: */
				if (node->_parent == NULL) {
					_root = new_node;
					new_node->_parent = NULL;
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
  				return new_node;
				}
				else if (node->_parent->_left == node) {
					node->_parent->_left = child;
					child->_parent = node->_parent;
				}
   /*--------------*/
	/**	@one_child: */
 /*--------------*/
/** @right_side:*/

				else { // right-side
					node->_parent->_right = child;
					child->_parent = node->_parent;	
				}
			}
		}

  /*-----------------*/
 /** @two_children: */
/*-----------------*/		
		else { //two childrens
			if (node->_parent == NULL) {
				Node tmp = NULL;

/**			@relink_root: */
/** 		if the deleted node was root
	* 		clean previous parent link 
				new_node was assing as _root previously	*/
				if (node->_left == new_node) {
					new_node->_parent->_left = new_node->_left;
				}
				else {
					if (new_node->_left != _nil) {
						new_node->_parent->_right = new_node->_left;
						new_node->_left->_parent = new_node->_parent;
					}
					else if (new_node->_left == _nil && new_node->_right == _nil)
						tmp = new_node->_parent;
				}
				new_node->_parent = NULL;

/**			@relink_new_node: */
//			copy node links to new node
				new_node->_left = node->_left;
				new_node->_right = node->_right;
				node->_left->_parent = new_node;
				node->_right->_parent = new_node;

				if (tmp)	tmp->_right = _nil;
			}
			else
				_erase_relink(node, new_node);
		}
	 /*----------------*/
	/**	@delete_node: */
 /*----------------*/
		_node_alloc.destroy(node);
		_node_alloc.deallocate(node, 1);
  	return new_node;
	}

	void _erase_relink(Node node, Node new_node) {
		Node tmp = new_node->_parent;

		if (node->_parent->_left == node)
			node->_parent->_left = new_node;
		else
			node->_parent->_right = new_node;
			
		if (tmp != node && new_node->_right != _nil) {
			tmp->_right = new_node->_right;
			tmp->_right->_parent = tmp;
		}
		else if (tmp != node && new_node->_left != _nil) {
			tmp->_right = new_node->_left;
			tmp->_right->_parent = tmp;
		}

		if (tmp != node) 
			new_node->_left = node->_left;
		new_node->_right = node->_right;
		if (tmp->_right == new_node)
			tmp->_right = _nil;
		else if (tmp->_left == new_node)
			tmp->_left = _nil;
		new_node->_parent = node->_parent;
		node->_right->_parent = new_node;
		node->_left->_parent = new_node;	
	}

	Node find_node(const key_type& key, Node node) const{
		while (node != _nil) {
			if (node->_data.first == key) {	return node;	}
			if (_comp(node->_data.first, key)) node = node->_right;
			else	node = node->_left;
		}
		return NULL;
	}

	Node find_parent(Node node, Node x) {
		Node parent = NULL;
		while (x != _nil) {
			parent = x;
			if (_comp(node->_data.first, x->_data.first)) {
				x = x->_left;
			}
			else {
				x = x->_right;
			}
		}
		return parent;
	}

	size_type height(Node node) {
		if (node == _nil) return 0;
		return node->_height;
	}

	void height(Node node, Node root) {
		node->_height = std::max(height(node->_left), height(node->_right)) + 1;
		root->_height = std::max(height(root->_left), height(root->_right)) + 1;
	}

	 Node _insert(Node node) {
	 	node->_parent = find_parent(node, _root);
	 	if (node->_parent == NULL)
	 		_root = node;
	 	else if(_comp(node->_data.first, node->_parent->_data.first))
	 		node->_parent->_left = node;
	 	else if(_comp(node->_parent->_data.first, node->_data.first))
	 		node->_parent->_right = node;
	 	return node;		
	 }

	Node  maximum(Node  node) const {
		while (node->_right != _nil)
			return maximum(node->_right);
		return node;
	}

	Node  minimum(Node  node) const{
		if (node->_left != _nil)
			return minimum(node->_left);
		return node;
	}

	Node  predecessor(Node  node) {

		if (node->_left != _nil)
			return maximum(node->_left);
		Node  x = node->_parent;
		while (node->_parent != _root && node == x->_left) {
			node = x;
			x = x->_parent;
		}
		if (!x)	return _nil;
		return x;
	}

	Node  successor(Node  node) {
		if (node->_right != _nil)
			return minimum(node->_right);
		Node  x = node->_parent;
		while (node->_parent != _root && node == x->_right) {
			node = x;
			x = x->_parent;
		}
		if (!x)	return _nil;
		return x;
	}

	Node rotateLeft(Node node) {

		Node root = node->_right;
		Node tmp = root->_left;
		root->_left = node;
		node->_right = tmp;
		tmp->_parent = node;
		height(node, _root);
		// if rotate-left send dir true;
		return re_link(node, root, 1);
	}

	Node rotateRight(Node node) {

		Node root = node->_left;
		Node tmp = root->_right;
		root->_right = node;
		node->_left = tmp;
		tmp->_parent = node;
		height(node, _root);
		// if rotate-right send dir false;
		return re_link(node, root, 0);
	}

	Node re_link(Node node, Node root, bool dir) {
		if (node->_parent == NULL) 
			root->_parent = NULL;
		else {
			root->_parent = node->_parent;
			if (node->_parent->_left == node)
				root->_parent->_left = root;
			else if (node->_parent->_right == node)
				root->_parent->_right = root;
		}
		node->_parent = root;
		if (dir && node->_left)
			node->_left->_parent = node;
		else if (!dir && node->_right)
			node->_right->_parent = node;
		return node;
	}

public:
	void tree_printHelper(Node _root, std::string indent, bool last) {
		if (_root != _nil) {
			std::cout << indent;
			if (last) {
				std::cout<<"R----";
				indent += "    ";
			} else {
				std::cout << "L----";
				indent += "|    ";
			}
			std::cout << _root->_data.first;
			std::cout << " (" << _root->_height << ") " << std::endl;
			tree_printHelper(_root->_left, indent, false);
			tree_printHelper(_root->_right, indent, true);
		}
	}

	void tree_print() {
		if (_root) {
			tree_printHelper(_root, "", true);
		}
	}
}; //end MAP

	/*-----------------------------------*/
 /**	NON:MEMBER:FUNCTION:OVERLOADS:	*/
/*-----------------------------------*/

		template <class Key, class T, class Compare, class Alloc> 
		bool operator == (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
			if (lhs.size() == rhs.size())
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			return false;
		}

		template <class Key, class T, class Compare, class Alloc> 
		bool operator != (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
			return !(lhs	==	rhs); }
		
		// lexicographical_compare compares the elements sequentially (checking both a<b and b<a)
		template <class Key, class T, class Compare, class Alloc> 
		bool operator <	(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { 
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
	
		template <class Key, class T, class Compare, class Alloc> 
		bool operator <=	(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { 
			return !(lhs > rhs); }
	
		template <class Key, class T, class Compare, class Alloc> 
		bool operator >	(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { 
			return rhs < lhs; }
	
		template <class Key, class T, class Compare, class Alloc> 
		bool operator >=	(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { 
			return !(lhs < rhs); }
}

#endif
