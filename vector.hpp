#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include "random_access_iterator.hpp"
#include "type_traits.hpp"
#include "reverse_iterator.hpp"
#include "bidirectional_iterator.hpp"
#include "utils.hpp"

#include <unistd.h>	// for sleep

namespace ft
{
    template< class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            typedef T                                   value_type;
            typedef Alloc                               allocator_type;
            typedef T&                                  reference; // read write 
            typedef const T&                            const_reference; // only read 
            typedef T*                                  pointer;
            typedef const T*                            const_pointer;
            typedef random_access_iterator<T>           iterator;
            typedef random_access_iterator<const T>     const_iterator;
            typedef reverse_iterator<const_iterator>    const_reverse_iterator;
            typedef reverse_iterator<iterator>          reverse_iterator;
            typedef std::ptrdiff_t                      difference_type;
            typedef size_t                              size_type;
        
        private:
            size_type           _size;
            size_type           _capacity;
            allocator_type      _alloc;
            pointer             _array;

        private:
            void    reallocation(size_type n)
            {
                value_type *new_array = _alloc.allocate(n, &_array);
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct(&new_array[i], _array[i]);
                _alloc.deallocate(_array, _size);
                _array = new_array;
                _capacity = n; 
            }

            void    copy_vector_value(size_type n, value_type val)
            {
                while (_size < n)
                {
                    _alloc.construct(&_array[_size], val);
                    _size++;
                }
            }

        public:
            //constructor
            //default(1)
            explicit vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _array(NULL) { }
            //fill(2)
            explicit vector(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
            : _size(n), _capacity(n), _alloc(alloc), _array(NULL)
            {
                _array = _alloc.allocate(n);
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(&_array[i], val);
               // std::cout << "first val " << val << " My Vector 0 index item" << std::endl;
            }
            //range(3) !true ??? 
            template<class InputIterator>
            vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
            const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _array(NULL)
            {
                /*difference_type n = last - first;
                _size = _capacity = n;
                _array = _alloc.allocate(_size);
                for (size_type i = 0; i < _size; ++i, ++first)
                    _alloc.construct(&_array[i], *first);*/
                InputIterator tmp(first);
			    while (tmp++ != last)
				    this->_size++;
    			this->set_capacity(this->get_size());
                //As requested, allocated in one call
    			this->_array = _alloc.allocate(this->get_size()); //get_capacity()

    			for (int i = 0; first != last; ++first, ++i)
    				_alloc.construct(&this->_array[i], *first);
            }
            
            //copy(4)
            vector (const vector& x) : _size(x._size), _capacity(x._size), _alloc(x._alloc), _array(NULL)
            {
	       
               this->_array = _alloc.allocate(this->_capacity);
               size_type i = 0;
               while (i < this->get_size())
               {
                   _alloc.construct(&_array[i], x._array[i]);
                   i++;
              	}
               return ;
            }
            //operator=
            vector& operator=(const vector& x)
            {
                if (x == *this)
                    return *this;
                this->clear();
                this->insert(this->end(), x.begin(), x.end());
                return *this;
            }

            //destructor
            ~vector() { 
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(&_array[i]);
                _alloc.deallocate(_array, _size); }

            //iterator
            iterator begin() { return iterator(&_array[0]); }
            
            const_iterator begin() const { return const_iterator(&_array[0]); }

            iterator end() { return iterator(&_array[_size]); }

            const_iterator end() const { return const_iterator(&_array[_size]); }

            reverse_iterator rbegin() { return reverse_iterator(end()); }
            const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

            reverse_iterator rend() { return reverse_iterator(begin()); }
            const_reverse_iterator rend() const { return const_reference(begin()); }

            //setter getter
            void    set_pointer(pointer ptr)
            {
                this->_array = ptr; 
            }

            void    set_size(size_type n)
            {
                this->_size = n;
            }

            void    set_capacity(size_type n)
            {
                this->_capacity = n;
            }

            size_type get_size() const
            {
                return (this->_size);
            }

            size_type capacity() const
            {
                return (this->_capacity);
            }

            //alocator 
            allocator_type get_allocator() const
            {
                return (this->_alloc);
            }
            
            size_type size() const
            {
                return (this->_size);
            }

            size_type max_size() const
            {
                size_type ret = this->_alloc.max_size();
                return (ret);
            }

            void reserve (size_type n)
            {
                if (n > this->max_size())
			        throw std::length_error("vector::reserve");
                if (n > this->_capacity)
                {
                    pointer nptr = _alloc.allocate(n);
                    int start = 0;
                    int end = this->get_size();
                    while (start < end)
                    {
                        _alloc.construct(&nptr[start], this->_array[start]);
                        _alloc.destroy(&this->_array[start]);
                        start++;
                    }
                    this->_alloc.deallocate(this->_array, this->_capacity);
                    set_pointer(nptr);
                    set_capacity(n);
                }
            }

            void    resize(size_type n, value_type val = value_type())
            {

                if (n > this->capacity())
                {
                    if (n <= this->_size * 2)
                        reserve(this->_size * 2);
                    else
                        reserve(n);
                }
                size_type i = this->get_size();
                while (i < n)
                {
                    this->_alloc.construct(&_array[i], val);
                    i++;
                }
                i = n;
                while (i < this->get_size())
                {
                    _alloc.destroy(&_array[i]);
                    i++;
                }
                this->set_size(n);
            }

            bool empty() const
            {
                if (this->size() != 0)
                    return (false);
                return (true);
            }

            reference operator[] (size_type n)
            {
                reference ref = this->_array[n];
                return ref;
            }

            const_reference operator[] (size_type n) const
            {
                const_reference ref = this->_array[n];
                return ref;
            }

            const_reference at (size_type n) const
            {
                if (n >= this->_size)
                    throw std::out_of_range("out of range");
                const_reference ref = this->_array[n];
                return ref;
            }
            
            reference at (size_type n)
            {
                if (n >= this->_size)
                    throw std::out_of_range("out of range");
                reference ref = this->_array[n];
                return ref;
            }
     
            const_reference front() const
            {
                const_reference ref = *(this->_array);
                return ref;
            }

            reference front()
            {
                reference ref = *(this->_array);
                return ref;
            }

            reference back()
            {
                reference ref = this->_array[_size - 1];
                return ref;
            }

            const_reference back() const
            {
                const_reference ref = this->_array[_size - 1];
                return ref;
            }
            

            //assign range   last -first  type InputIterator for bidirectional
            template <class InputIterator>
	        void assign(
				InputIterator first, 
				InputIterator last, 
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0 )
            {
		        size_type n = 0;
			    size_type i = 0;
			    InputIterator it(first);
			    while (it != last)
		    	{
		    		n++;
	    			it++;
    			}
	    		if (!n)
	    			return ;
       			i = 0;
	    		for(size_type j = 0;j < _size;j++)
			    	_alloc.destroy(&_array[j]);
			    
                if (n > _capacity)
		    	{
		    		size_type	_tmp_capacity = _capacity;
	    			if (n <= _size * 2)
	    				_capacity = _size * 2;
	    			else
	    				_capacity = n;
	    			_alloc.deallocate(_array, _tmp_capacity);
	    			_array = _alloc.allocate(_capacity);
	    		}
			    _size = n;
	    		i = 0;
    			while (first != last)
    			{
    				this->_alloc.construct(&_array[i], *first);
    				first++;
    				i++;
    			}
            }

            //assign fill
            void assign (size_type n, const value_type& val)
            {
                 if (n > _capacity)
                    reallocation(n);
                _size = n;
                for (size_type i = 0; i < n; i++)
                    _alloc.construct(&_array[i], val);
            }


            void pop_back()
            {
                _alloc.destroy(&_array[--this->_size]);
            }

            void push_back (const value_type& val)
            {
                if (this->_size == capacity())
                {
                    if (!_size)
                        reserve(1);
                    else
                        reserve(capacity() * 2);
                }
                _alloc.construct(&_array[this->_size], val);
                this->_size++;
            }

            // single element
            iterator insert(iterator position, const value_type& val)
            {
                difference_type diff = position.get_ptr() - this->_array;
			    insert(position, 1, val);
			    return iterator(begin() + diff);
            }

            //fill
            void insert(iterator position, size_type n, const value_type &val)
            {
		    if (!n)
			    return ;
                size_type begin_to_pos = 0;
			    size_type pos_to_end = 0;
			    size_type i = 0;
			    iterator it = begin();
			    while (it != position)
			    {
			    	begin_to_pos++;
				    it++;
			    }
			    while (it != this->end())
		    	{
		    		pos_to_end++;
	    			it++;
    			}
    			if (this->_size + n > this->_capacity)
	    		{
	    			if (this->_size + n <= this->_size * 2)
	    				reserve(this->_size * 2);
	    			else
	    				reserve(this->_size + n);
	    		}
	    		while (i < pos_to_end)
	    		{
	    			this->_alloc.construct(&_array[begin_to_pos + n + pos_to_end - i - 1], _array[begin_to_pos + pos_to_end - i - 1]);
	    			this->_alloc.destroy(&_array[begin_to_pos + pos_to_end - i - 1]);
	    			i++;
	    		}
	    		i = 0;
	    		while (i < n)
	    		{
	    			this->_alloc.construct(&_array[begin_to_pos + i], val);
	    			i++;
	    		}
	    		this->set_size(this->get_size() + n);
           }

            
            //range
            template <class InputIterator>
		    void insert(iterator position, 
				InputIterator first, 
				InputIterator last, 
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
	    	{
	    		size_type n = 0;
	    		size_type begin_to_pos = 0;
	    		size_type pos_to_end = 0;
	    		InputIterator Init = first;

    			while (Init != last)
    			{
    				Init++;
    				n++;
    			}
    			iterator it = this->begin();
    			while (it != position)
    			{
    				begin_to_pos++;
    				it++;
    			}
    			while (it != this->end())
    			{
    				pos_to_end++;
    				it++;
    			}
    			if (this->_size + n > this->_capacity)
    			{
    				if (this->_size + n < this->_capacity * 2)
    					reserve(this->_capacity * 2);
    				else
    					reserve(this->_size + n);
    			}
    			size_type i = 0;
    			while (i < pos_to_end)
    			{
    				this->_alloc.construct(&_array[begin_to_pos + n + pos_to_end - i - 1], _array[begin_to_pos + pos_to_end - i - 1]);
    				this->_alloc.destroy(&_array[begin_to_pos + pos_to_end - i - 1]);
    				i++;
    			}
    			Init = first;
    			i = 0;
    			while (i < n)
    			{
    				this->_alloc.construct(&_array[begin_to_pos + i], *Init);
    				Init++;
    				i++;
    			}
    			this->set_size(this->get_size() + n);
    		}

            //erase - An iterator pointing to the new location of the element that followed 
            //        the last element erased by the function call. 
            // simple
            iterator erase (iterator position)
            {
		        return erase(position, position + 1);
            }
            // range
            iterator erase (iterator first, iterator last)
            {
		        if (empty())
			        return last;
                difference_type n = last - first;
	    	    iterator	ret(first);
		        while (last != end())
			        *(first++) = *(last)++;
		        while (n--)
			        pop_back();
		        return ret;
            }
            
            void swap(vector &x)
            {
		        std::swap(_array, x._array);
		        std::swap(_size, x._size);
		        std::swap(_capacity, x._capacity);
            }

            void clear()
            {
        		for(size_type i = 0;i < _size; i++)
        			_alloc.destroy(&_array[i]);
                this->_size = 0;
            }

     };

    // Non-member function 
    template<class T, class Alloc>
    bool operator== (const vector<T, Alloc>&lhs, const vector<T,Alloc>& rhs)
    {
	    if (lhs.size() != rhs.size())
            return (false);
        typename ft::vector<T>::const_iterator first1 = lhs.begin();
        typename ft::vector<T>::const_iterator first2 = rhs.begin();
        while (first1 != lhs.end())
        {
            if (first2 == rhs.end() || *first1 != *first2)
                return (false);
            ++first1;
            ++first2;
        }
        return (true);
    }

    template<class T, class Alloc>
    bool operator != (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }

    template<class T, class Alloc>
    bool operator <=(const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs)
    {
        bool res1 = lhs < rhs;
        bool res2 = lhs == rhs;
        return (res1 || res2);
    }

    // lhs size small case  " < " 
    template<class T, class Alloc>
    bool operator < (const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    
    template<class T, class Alloc>
    bool operator > (const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs)
    {
        bool res = rhs < lhs;
        return res;
    }

    template<class T, class Alloc>
    bool operator >= (const vector<T, Alloc>&lhs, const vector<T, Alloc>&rhs)
    {
        bool res1 = lhs > rhs;
        bool res2 = lhs == rhs;
        return( res1 || res2);
    }

    template<class T, class Alloc>
    void swap(vector<T, Alloc> &x, vector<T, Alloc>&y)
    {
        x.swap(y);
    }

}

#endif
