#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <stdexcept>


namespace ft
{
    template< class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            typedef T           value_type;
            typedef Alloc       allocator_type;
            typedef T&          reference; // read write 
            typedef const T&    const_reference; // only read 
            typedef T*          pointer;
            typedef const T*    const_pointer;
            typedef size_t      size_type;

        private:
            size_type           _size;
            size_type           _capacity;
            allocator_type      _alloc;
            pointer             _array;
        
        public:
            //constructor
            //default(1)
            explicit vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc), _array(NULL) { }
            //fill(2)
            explicit vector(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type())
            : _size(n), _capacity(n), _alloc(alloc)
            {
                _array = _alloc.allocate(n);
                for (size_type i = 0; i < _size; i++)
                    _alloc.construct(&_array[i], val);
               // std::cout << "first val " << val << " My Vector 0 index item" << std::endl;
            }
            //range(3)
            //template<class InputIterator>
            //vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
            // {

            // }
            
            //copy(4)
            vector (const vector& x)
            {
                _size = x._size;
                _capacity = x._capacity;
                _alloc = x._alloc;
                _array = _alloc.allocate(_size, &x._array);
                for (size_type i = 0; i < _size; i++)
                    _alloc.constructor(&_array[i], x._array[i]);
            }
            //operator=
            vector& operator=(const vector& x)
            {
                if (this != &x)
                {
                    if (this->_size < x.get_size())
                    {
                        this->reserve(x.get_size());
                        set_size(x.get_size());
                    }
                    else  // this vector size is smaller then x
                    {
                        size_t i = 0;
                        while(i < this->_size)
                            _alloc.destroy(&_array[i++]);
                        set_size(x._size);
                        i = 0;
                        while (i < this->_size)
                        { 
                            _alloc.construct(&_array[i], x._array[i]);
                            i++;
                        }
                    }
                }
                return *this;
            }

            //destructor
            ~vector() { _alloc.deallocate(_array, _size); }

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
            

            //capacity
            size_type size() const
            {
                return (this->_size);
            }

            size_type max_size() const
            {
                size_t ret = this->_alloc.max_size();
                return (ret);
            }

            void reserve (size_type n)
            {
                if (n > max_size())
                    throw std::length_error("out of length");
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
                    if (n < this->capacity() * 2)
                        reserve(this->capacity() * 2);
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
                if (n > this->_size)
                    throw std::out_of_range("out of range");
                const_reference ref = this->_array[n];
                return ref;
            }
            
            reference at (size_type n)
            {
                if (n > this->_size)
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

            void pop_back()
            {
                _alloc.destroy(this->_array[--this->_size]);
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

            void swap (vector& x)
            {
               if (*this == x) 
                return ;

                
            }

     };

}

#endif
