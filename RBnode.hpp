#ifndef RBNODE_HPP
# define RBNODE_HPP

//#include "utils.h"

namespace ft 
{
    template<class T>
    struct RBnode
    {
        typedef T       value_type;
        typedef Color   color_type;

        value_type  value;
        RBnode* parent;
        RBnode* left;
        RBnode* right;
        color_type color;

       //default construct - default color is RED
       RBnode() : value(), parent(NULL), left(NULL), right(NULL), color(RED) {};
       RBnode(const value_type& val, RBnode *parent = NULL, RBnode *left = NULL, RBnode* right = NULL, color_type color = RED)
            : value(val), parent(parent), left(left), right(right), color(color) { };
       RBnode(const RBnode & rhs) : value(rhs.value), parent(rhs.parent), left(rhs.left), right(rhs.right), color(rhs.color) {};
       virtual ~RBnode() {};

       RBnode& operator=( const RBnode &rhs)
       {
           if (this == &rhs)
            return (*this);
           value = rhs.value;
           parent = rhs.parent;
           left = rhs.left;
           right = rhs.right;
           color = rhs.color;
           return *this;
       }

       bool operator==(const RBnode &rhs)
       {
           if (this->value == rhs.value)
            return true;
           return false;
       }

       bool operator!=(const RBnode &rhs)
       {
           if (this->value != rhs.value)
            return true;
           return false;
       }
    };
}

#endif 