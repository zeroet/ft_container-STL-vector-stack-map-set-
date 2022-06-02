#pragma once

#include "bidirectional_iterator.hpp"
#include "RBnode.hpp"
#include "reverse_iterator.hpp"
#include <iostream>
#include "utils.hpp"
#include "type_traits.hpp"
#include <memory>

namespace ft
{

template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class set
{   
   public:
			typedef T											key_type;
			typedef T											value_type;
			typedef Compare										key_compare;
			typedef Compare										value_compare;
			typedef Alloc										allocator_type;
            typedef RBnode<T>                                   node_type;
            typedef typename allocator_type::template rebind<node_type>::other node_alloc_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			poiner;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef const_bidirectional_iterator<const T, node_type*> iterator;
			typedef const_bidirectional_iterator<const T, node_type*> const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;
    
    
     private:
        key_compare                     _comp;
        allocator_type                  _alloc; 
        size_type                       _size;
        node_alloc_type                 _node_alloc;
        node_type*                      _meta_node;
    

    public:

    explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
        : _comp(comp), _alloc(alloc), _size(0), _node_alloc(node_alloc_type()), _meta_node(NULL) 
    {
        _meta_node = _node_alloc.allocate(1);
        _node_alloc.construct(_meta_node, node_type());
    }
        
    template<class InputIterator>
    set(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) 
        : _comp(comp),_alloc(alloc), _size(0), _meta_node(NULL) 
    { 
        _meta_node = _node_alloc.allocate(1);
        _node_alloc.construct(_meta_node, node_type());
        insert(first, last); 
    }   
        
    set(const set &other) : _comp(other._comp), _alloc(other._alloc), _size(0) 
    {
        _meta_node = _node_alloc.allocate(1);
        _node_alloc.construct(_meta_node, node_type());
        copyTree(other.getRoot());
    }
       
    ~set () 
    { 
        clear_tree();
        if(_meta_node != NULL)
        {
            _node_alloc.destroy(_meta_node);
            _node_alloc.deallocate(_meta_node, 1);
        } 
    }

    set &operator=(const set &other)
    {
        this->clear_tree();
        this->_comp = other._comp;
        this->_alloc = other._alloc;
        this->_node_alloc = other._node_alloc;
        copyTree(other.getRoot());
        this->_size = other._size;
        return *this;   
    }

    void    clear()
    {
        deleteTree(getRoot());
        setRoot(NULL);
        this->_size = 0;
    }

    void clear_tree()
    {
        deleteTree(getRoot());
        setRoot(NULL);
        this->_size = 0;
    }

    void deleteTree(node_type* node)
    {
        if (node != NULL)
        {
            deleteTree(node->left);
            deleteTree(node->right);
            _node_alloc.destroy(node);
            _node_alloc.deallocate(node, 1);
        }
            
    }

    void copyTree(node_type* node)
    {
        if (node != NULL)
        {
            insertValue(node->value);
            copyTree(node->left);
            copyTree(node->right);
        }
    }

    node_type* successor(node_type* node) const
    {
        if (node == NULL)
            return (node);
        while (node->left != NULL)
            node = node->left;
        return (node);
    }

    void    swap(set &x)
    {
        node_alloc_type temp_alloc_type = this->_node_alloc;
        key_compare temp_key_compare = this->_comp;
        size_type temp_size = this->_size;
        node_type *temp_root = this->_meta_node;

        this->_node_alloc = x._node_alloc;
        this->_comp = x._comp;
        this->_size = x._size;
        this->_meta_node = x._meta_node;

        x._node_alloc = temp_alloc_type;
        x._comp = temp_key_compare;
        x._size = temp_size;
        x._meta_node = temp_root;
        return;
    }

    iterator begin() { return iterator(minValueNode(_meta_node)); }
    const_iterator begin() const { return const_iterator(minValueNode(_meta_node)); }
    iterator end() { return iterator(_meta_node); }
    const_iterator end() const { return const_iterator(_meta_node); }
    reverse_iterator rbegin() { return reverse_iterator(end()--); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()--); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
        
    bool    empty() const { return this->_size == 0; }
    size_type size() const { return this->_size; }
    size_type max_size() const { return _node_alloc.max_size(); }
    allocator_type get_allocator() const { return this->_node_alloc; }

    node_type* minValueNode(node_type* node) const
    {
        if (node == NULL)
            return node;
        while (node->left != NULL)
            node = node->left;
        return node;
    }

    node_type*    getRoot(void) const
    {
        return (_meta_node->left);
    }

    void    setRoot(node_type* node) const
    {
        _meta_node->left = node;
        _meta_node->right = node;
        if (node != NULL)
            node->parent = _meta_node;
    }

    key_compare key_comp() const
    {
        return (this->_comp);
    }

    value_compare value_comp() const
    {
        return (value_compare(key_compare()));
    }

    size_type count(const key_type &k) const
    {
        const_iterator tmp = this->find(k);
        if (tmp == this->end())
            return (0);
        return (1);
    }

    iterator lower_bound(const key_type &k)
    {
        iterator it1 = begin();
        iterator it2 = end();

        while (it1 != it2)
        {
            if (_comp(*it1, k) == false)
                break;
            ++it1;
        }
        return it1;
    }

    const_iterator lower_bound(const key_type &k) const
    {
        const_iterator it1 = begin();
        const_iterator it2 = end();

        while (it1 != it2)
        {
            if (_comp(*it1, k) == false)
                break;
            ++it1;
        }
        return it1;
    }

    iterator upper_bound(const key_type &k)
    {
        iterator it1 = begin();
        iterator it2 = end();

        while (it1 != it2)
        {
            if (_comp(k, *it1) == true)
                break;
            ++it1;
        }
        return it1;
    }

    const_iterator upper_bound(const key_type &k) const
    {
        const_iterator it1 = begin();
        const_iterator it2 = end();

        while (it1 != it2)
        {
            if (_comp(k, *it1) == true)
                break;
            ++it1;
        }
        return it1;
    }

    pair<iterator,iterator> equal_range (const key_type& val)
    {
        return ft::make_pair<iterator, iterator>(lower_bound(val), upper_bound(val));
    }

    pair<const_iterator, const_iterator> equal_range(const key_type& val) const
    {
        return ft::make_pair<const_iterator, const_iterator>(lower_bound(val), upper_bound(val));
    }

    iterator find(const key_type &k)
    {
        node_type* tmp;

        tmp = getRoot();
        while (tmp != NULL)
        {
            if (!_comp(tmp->value, k) && !_comp(k, tmp->value))
                break;
            else if (_comp(tmp->value, k))
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        if (tmp == NULL)
            return _meta_node;
        return (tmp);
    } 
        
    const_iterator find(const key_type &k) const
    {
        node_type* tmp;

        tmp = getRoot();
        while (tmp != NULL)
        {
            if (!_comp(tmp->value, k) && !_comp(k, tmp->value))
                break;
            else if (_comp(tmp->value, k))
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        if (tmp == NULL)
            return _meta_node;
        return (tmp);
    }
   pair<iterator, bool> insert(const value_type &val)
	{
		return (insertValue(val));
	}

	iterator insert (iterator position, const value_type& val)
	{
		(void)position;
		return (insertValue(val).first);
	}

	template <class InputIterator>
	void insert(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
	{
		while (first != last)
		{
			this->insert(*first);
			++first;
		}
	} 
    
    void        erase(iterator position)
    {
        deleteValue(*position);
    }

    size_type erase(const key_type& k)
    {
        return deleteValue(k);
    }

    void        erase(iterator first, iterator last)
    {
        for(iterator it = first; it !=last; )
            erase(it++);
    }

private:
        
        
    pair<iterator, bool> insertValue(const value_type &val)
    {
        node_type* node = _node_alloc.allocate(1);
        _node_alloc.construct(node, node_type(val));
        pair<iterator, bool> ret = insertNode(node);

        if (ret.second == false)
        {
            _node_alloc.destroy(node);
            _node_alloc.deallocate(node, 1);
        }
        else
        { 
            this->_size++;
            fixAfterInsert(node);
        }
        return (ret);
    }

        
    pair<iterator, bool> insertNode(node_type* node)
    {
        node_type* tmp = getRoot();
        node_type* parent;

        if (tmp == NULL)
        {
            setRoot(node);
            return (ft::make_pair(iterator(node), true));
        }
        while (tmp)
        {
            if (_comp(tmp->value, node->value))
            {
                parent = tmp;
                tmp = tmp->right;
            }
            else if(_comp(node->value, tmp->value))
            {
                parent = tmp;
                tmp = tmp->left;
            }
            else
                return (ft::make_pair(iterator(tmp), false));
        }
        if (_comp(parent->value, node->value))
        {
            parent->right = node;
            node->parent = parent;
        }
        else
        {
            parent->left = node;
            node->parent = parent;
        }
        return (ft::make_pair(iterator(node), true));
    }
           
    void fixAfterInsert(node_type* node)
    {
        node_type* parent;
        node_type* grandparent;
        node_type* uncle;
        // red red violation
        while (node != getRoot() && getColor(node) == RED && getColor(getParent(node)) == RED)
        {
            parent = getParent(node);
            grandparent = getGrandparent(node);
            uncle = getUncle(node);

            if (getColor(uncle) == RED)
            {
                insertCase1(node);
            }
            else if (grandparent->left == parent)
            {
                if (parent->right == node)
                    insertCase2(node, parent);
                insertCase3(node, parent, grandparent);   
            }
            else if (grandparent->right == parent)
            {
                if (parent->left == node)
                    insertCase2(node, parent);
                insertCase3(node, parent, grandparent);
            }
        }
        setColor(getRoot(), BLACK);
    }

            // case(uncle is red) : change color parent && uncle red to black and give black color to grandparent
            // if grandparent is root, change color red to black 
            // else go to case 2 || 3
    void    insertCase1(node_type* &node)
    {
        setColor(getParent(node), BLACK);
        setColor(getUncle(node), BLACK);
        setColor(getGrandparent(node), RED);
        node = getGrandparent(node);
    }

    // case 2  -> case 3 
    void    insertCase2(node_type* &node, node_type* &parent)
    {
        if (parent == getGrandparent(node)->left)
        {
            rotateLeft(parent);
            node = parent;
            parent = getParent(node);
        }
        else if (parent == getGrandparent(node)->right)
        {
            rotateRight(parent);
            node = parent;
            parent = getParent(node);
        }
    }

    // case3 : if z is left enfant node, p[z] to black, p[p[z]] to red
    // p[p[z]] right-rotation 
    void    insertCase3(node_type* & node, node_type* parent, node_type* grandparent)
    {
        if (parent == grandparent->left)
            rotateRight(grandparent);
        else if (parent == grandparent->right)
            rotateLeft(grandparent);
        std::swap(parent->color, grandparent->color);
        node = parent;
    }

            void    rotateLeft(node_type* &node)
            {
                node_type* rightChild;

                rightChild = node->right; // set y
                if (rightChild == NULL) // protection if case child node is NULL 0.1%
                    return ;
                node->right = rightChild->left; // Turn y's left subtree into x's right subtree
                if (node->right != NULL)
                    node->right->parent = node;
                rightChild->parent = node->parent;  // Link x's parent to y
                if (getParent(node) == NULL) // case: node is root node 
                    setRoot(rightChild);
				else if (node == node->parent->left)
					node->parent->left = rightChild;
				else
					node->parent->right = rightChild;
				rightChild->left = node; //put x on y's left
				node->parent = rightChild;
            }

            void    rotateRight(node_type* &node)
            {
                node_type* leftChild;

                leftChild = node->left;
                if(leftChild == NULL)
                    return ;
                node->left = leftChild->right;
                if (node->left != NULL)
                    node->left->parent = node;
                leftChild->parent = node->parent;
                if (getParent(node) == NULL)
                    setRoot(leftChild);
                else if (node == node->parent->right)
                    node->parent->right = leftChild;
                else
                    node->parent->left = leftChild;
                leftChild->right = node;
                node->parent =leftChild;
            }

              
        size_type deleteValue(const key_type &val)
            {
                node_type* target = deleteNode(getRoot(), val);
                if (target == NULL)
                    return (0);
                fixAfterDelete(target);
                this->_size--;
                return (1);
            }

            node_type* deleteNode(node_type* node, const key_type &val)
            {
                if (node == NULL)
                    return (node);
                // find delete position
                if (_comp(node->value, val))
                    return (deleteNode(node->right, val));
                if (_comp(val, node->value))
                    return (deleteNode(node->left, val));
                // easy case: delete node have one enfant node, new link and delete
                if (node->left == NULL || node->right == NULL)
                    return (node);
                // else : tree Successor(z) 
                node_type* tmp = successor(node->right);
                // --- Target Trnasplant ---
                // if target have left enfant or NIL
                // else target have right enfant or NIL
                // RB-Transplant (T,z,y)
                if (tmp->parent == node) // tmp = node->left case
                {
                    if (node->parent && node->parent->left == node)
                        node->parent->left = tmp;
                    if (node->parent && node->parent->right == node)
                        node->parent->right = tmp;
                    tmp->left = node->left;
                    node->left->parent = tmp;
                    node->left = NULL;
                    tmp->parent = node->parent;
                    node->parent = tmp;
                    node->right = tmp->right;
                    tmp->right = node;
                    std::swap(tmp->color, node->color);
                }
                //RB-Transplant (T,y,y.right)
                else // else : tmp is successor  node->right->left->left......left == NULL
                { 
                    if(node->parent && node->parent->left == node)
                        node->parent->left = tmp;
                    if(node->parent && node->parent->right == node)
                        node->parent->right = tmp;
                    if (tmp->parent->left == tmp)
                        tmp->parent->left = node;
                    if (tmp->parent->right == tmp)
                        tmp->parent->right = node;
                    node_type* tmp2 = tmp->parent;
                    node->right->parent =tmp;
                    tmp->parent = node->parent;
                    node->parent = tmp2;
                    tmp->left = node->left;
					node->left->parent = tmp;
					node->left = NULL;
					node_type* tmp3 = tmp->right;
					tmp->right = node->right;
					node->right = tmp3;
					std::swap(tmp->color, node->color);
				}
				return (deleteNode(tmp->right, val));
            }

            void    fixAfterDelete(node_type* node)
            {
                if (node == NULL)
                    return ;
                if (node == getRoot()) // if root node is red case 
                {
                    deleteRootCase(node);
                    return ;
                }
                //  if x node is black or son of x node is black, go to next case 
                //  else we can delete node.
                if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED)
                {
                    deleteRedCase(node);
                    return ;
                } 
                node_type* w = NULL;
                node_type* p = NULL;
                node_type* tmp = node;
                // z  == z->parent->left is 1234 // z == z->parent->right is 5678 case
                // case1 : w node is RED
                // case2 : w node is Black && son of w is also Black
                // case3 : w node is Black && left son is Red
                // case4 : w node is Black && right son is Red 
                
                //                                  (6)   (5,7,8) 
                // case 1 -> 2                 case 2 -> case 1 (return case 1)     case 3 -> 4          case 4
                //        -> 3 -> 4                   -> 3 -> 4
                //        -> 4                        -> 4
                setColor(tmp, DBLACK);
				while (tmp != getRoot() && getColor(tmp) == DBLACK)
				{
					p = tmp->parent;
					w = (tmp == p->left) ? p->right : p->left;
					if (getColor(w) == RED)
						deleteCase1(w, p); 
					else if (getColor(w->left) == BLACK && getColor(w->right) == BLACK)
						deleteCase2(w, p, tmp);
					else
					{
						if ((tmp == p->left && getColor(w->right) == BLACK)
						|| (tmp == p->right && getColor(w->left) == BLACK))
							deleteCase3(w, p);
						deleteCase4(w, p);
						break;
					}
				}
				if (node == node->parent->left)
					node->parent->left = NULL;
				else
					node->parent->right = NULL;
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
				setColor(getRoot(), BLACK);
            }

            void    deleteRootCase(node_type* root)
            {
                if (root->right)
                    setRoot(root->right);
                else
                    setRoot(root->left);
                _node_alloc.destroy(root);
                _node_alloc.deallocate(root, 1);
                setColor(getRoot(), BLACK);
                return ;
                
            }
            
            void    deleteRedCase(node_type* &node)
            {
                node_type* child = node->left != NULL ? node->left : node->right;
                if (node == node->parent->left)
                    node->parent->left = child;
                else
                    node->parent->right = child;
                if (child != NULL)
                    child->parent = node->parent;
                setColor(child, BLACK);
                _node_alloc.destroy(node);
                _node_alloc.deallocate(node, 1);
            }


            // x & p DOUBLE Black but w is RED & son of w is Black case
            // rotate p and change color
            // x node have still dblack  go to case 2 or 3
            void    deleteCase1(node_type* &w, node_type* &p)
            {
                if (w == p->right)
                    rotateLeft(p);
                if (w == p->left)
                    rotateRight(p);
                setColor(w, BLACK);
                setColor(p, RED);
            }
            
            // x node is dblack // w node is Black && (left&right)son of w is all black node
            // give black x to p && w to p  =>  if p was R -> p is B   Else p was B double B up up
            // if prev case was case 1 => p node is Red (clear) 
            void deleteCase2(node_type* w, node_type* p, node_type* &node)
            {
                setColor(w, RED);
                if (getColor(p) == RED)
                    setColor(p, BLACK);
                else
                    setColor(p, DBLACK);
                node = p;
            }


            // w is RED && w->left is RED
            // rightRotate(w) - > case4 
            void deleteCase3(node_type* &w, node_type* &p)
            {
                if (w == p->right)
                {
                    rotateRight(w);
                    setColor(w->left, BLACK);
                    setColor(w, RED);
                    w = p->right;
                }
                if (w == p->left)
                {
                    rotateLeft(w);
                    setColor(w->right, BLACK);
                    setColor(w, RED);
                    w = p->left;
                }
            }


            // w is Black w->right is RED
            // p[x] leftrotate
            // delete BB -> B
            void deleteCase4(node_type* &w, node_type* &p)
            {
                if (w == p->right)
                {
                    rotateLeft(p);
                    setColor(w, getColor(p));
                    setColor(p, BLACK);
                    setColor(w->right, BLACK);
                }
                if (w == p->left)
                {
                    rotateRight(p);
                    setColor(w, getColor(p));
                    setColor(p, BLACK);
                    setColor(w->left, BLACK);
                }
            }

         node_type* getParent(node_type* node) const
            {
                if (node == NULL)
                    return (NULL);
                if (node->parent == this->_meta_node)
                    return (NULL);
                return (node->parent);
            }

            node_type* getGrandparent(node_type* node)
            {
                node_type* pr = getParent(node);

                if (pr == NULL)
                    return (NULL);
                return getParent(pr);
            }

            node_type* getUncle(node_type* node)
            {
                node_type* pr = getParent(node);

                if (pr == NULL)
                    return NULL;
                return getSibling(pr);
            }

            node_type* getSibling(node_type* node)
            {
                node_type* pr = getParent(node);

                if (pr == NULL)
                    return (NULL);
                if (node == pr->left)
                    return (pr->right);
                return (pr->left);
            }

            Color getColor(node_type* node)
            {
                if (node == NULL)
                    return (BLACK);
                return (node->color);
            }

            void setColor(node_type* node, Color color)
            {
                if (node == NULL)
                    return ;
                node->color = color;
            }
};

template <class T, class Compare, class Alloc>
bool operator==(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Compare, class Alloc>
bool operator!=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return !(lhs == rhs);
}

template <class T, class Compare, class Alloc>
bool operator<(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Compare, class Alloc>
bool operator<=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return (lhs < rhs || lhs == rhs);
}

template <class T, class Compare, class Alloc>
bool operator>(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return rhs < lhs;
}

template <class T, class Compare, class Alloc>
bool operator>=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return (lhs > rhs || lhs == rhs);
}

template <class T, class Compare, class Alloc>
void swap(set<T, Compare, Alloc> &x, set<T, Compare, Alloc> &y)
{
    x.swap(y);
}

}