#pragma once
#ifndef _Vector_h
#define _Vector_h

#include <cstdint>
#include <stdexcept>
#include <utility>

using namespace std::rel_ops;

namespace epl {
    
    class invalid_iterator {
    public:
        enum SeverityLevel { SEVERE, MODERATE, MILD, WARNING };
        SeverityLevel level;
        
        invalid_iterator(SeverityLevel level = SEVERE) { this->level = level; }
        virtual const char* what() const {
            switch (level) {
                case WARNING:   return "Warning"; // not used in Spring 2015
                case MILD:      return "Mild";
                case MODERATE:  return "Moderate";
                case SEVERE:    return "Severe";
                default:        return "ERROR"; // should not be used
            }
        }
    };
    
    template <typename T>
    class vector {
    public:
        friend class iterator_helper;
    private:
        T* elements; // elements points to an array of elements with certain size
        // it has type T
        
        uint64_t length;
        uint64_t capacity;
        uint64_t beginning_index;
        uint64_t end_index;
        
        uint64_t severeException;
        uint64_t moderateException;
        uint64_t mildException;
        
        uint64_t iteratorSet;
        
        static constexpr uint64_t default_capacity = 8;
        
        template <typename Z>class const_iterator_helper
        : public std::iterator<std::random_access_iterator_tag, Z>
        {
        public:
            friend vector;
            friend uint64_t vector::getSevereException();
            friend uint64_t vector::getModerateException();
            friend uint64_t vector::getMildException();
            
        private:
            const Z* ptr;
            using Same = const_iterator_helper<Z>;
            const vector<Z> *te;
            const uint64_t constFlag;
        public:
            
            Z& operator*(void) {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return ptr[0];
            }
            Same& operator++(void) {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                ++ptr;
                return *this;
            }
            
            Same& operator--(void) {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                --ptr;
                return *this;
            }
            
            bool operator==(Same const& rhs) const {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return this->ptr == rhs.ptr;
            }
            
            bool operator!=(Same const& rhs) const {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return !(*this == rhs);
            }
            
            bool operator>=(Same const& rhs) const {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return this->ptr >= rhs.ptr;
            }
            
            bool operator<=(Same const& rhs) const {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return this->ptr <= rhs.ptr;
            }
            
            bool operator>(Same const& rhs) const {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return this->ptr > rhs.ptr;
            }
            
            bool operator<(Same const& rhs) const {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return this->ptr < rhs.ptr;
            }
            
            Same operator++(int) {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                Same t{ *this }; // make a copy
                operator++(); // increment myself
                return t;
            }
            Same operator+(int32_t k) {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                Same result{};
                result.ptr = this->ptr + k;
            }
            Same operator-(int32_t k) {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                Same result{};
                result.ptr = this->ptr - k;
            }
        };
        
        template <typename Y>class iterator_helper
        : public std::iterator<std::random_access_iterator_tag, Y>
        {
        public:
            friend vector;
            friend uint64_t vector::getSevereException();
            friend uint64_t vector::getModerateException();
            friend uint64_t vector::getMildException();
            
        private:
            Y* ptr;
            using Same = iterator_helper<Y>;
            vector<Y> *te;
            uint64_t constFlag;
        public:
            
            iterator_helper<T>& operator=(const iterator_helper<T>& a) {	// copy assignment
                
                return *this;
            }
            
            iterator_helper() {
                ptr = nullptr;
                te = nullptr;
                constFlag = 0;
            }
            
            iterator_helper(const iterator_helper<T>& a) {
                //iterator_helper x;
                ptr = a.ptr;
                te = a.te;
                constFlag = a.constFlag;
                //return x;
            }
            
            iterator_helper(const const_iterator_helper<T>& a) {
                //iterator_helper x;
                ptr = a.ptr;
                te = a.te;
                constFlag = a.constFlag;
                //return x;
            }
            
            Y& operator*(void) {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return ptr[0];
            }
            Same& operator++(void) {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                ++ptr;
                return *this;
            }
            
            Same& operator--(void) {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                --ptr;
                return *this;
            }
            
            bool operator==(Same const& rhs) const {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return this->ptr == rhs.ptr;
            }
            
            bool operator!=(Same const& rhs) const {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return !(*this == rhs);
            }
            
            bool operator>=(Same const& rhs) const {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return this->ptr >= rhs.ptr;
            }
            
            bool operator<=(Same const& rhs) const {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return this->ptr <= rhs.ptr;
            }
            
            bool operator>(Same const& rhs) const {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return this->ptr > rhs.ptr;
            }
            
            bool operator<(Same const& rhs) const {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                return this->ptr < rhs.ptr;
            }
            
            Same operator++(int) {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                Same t{ *this }; // make a copy
                operator++(); // increment myself
                return t;
            }
            Same operator+(int32_t k) {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                Same result{};
                result.ptr = this->ptr + k;
            }
            Same operator-(int32_t k) {
                if (constFlag == 0) {
                    if (te->getSevereException() == 1) {
                        throw epl::invalid_iterator();
                    }
                    else if (te->getModerateException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MODERATE);
                    }
                    else if (te->getMildException() == 1) {
                        invalid_iterator x;
                        throw epl::invalid_iterator(x.MILD);
                    }
                }
                Same result{};
                result.ptr = this->ptr - k;
            }
        };
        
    public:
        
        using iterator = iterator_helper<T>;
        using const_iterator = const_iterator_helper<T>;
        
        iterator begin(void) {
            iterator p;
            p.ptr = elements;
            p.te = this;
            iteratorSet = 1;
            p.constFlag = 0;
            return p;
        }
        
        iterator begin(vector<T> x) {
            iterator p;
            p.ptr = x.elements;
            p.te = &x;
            x.iteratorSet = 1;
            p.constFlag = 0;
            return p;
        }
        
        const_iterator begin(void) const {
            const_iterator p;
            p.ptr = elements;
            p.constFlag = 1;
            return p;
        }
        
        const_iterator begin(vector<T> x) const {
            const_iterator p;
            p.ptr = elements;
            p.constFlag = 1;
            return p;
        }
        
        iterator end(void) {
            iterator p;
            p.ptr = elements + length;
            p.te = this;
            p.constFlag = 0;
            iteratorSet = 1;
            return p;
        }
        
        iterator end(vector<T> x) {
            iterator p;
            p.ptr = x.elements + x.length;
            p.te = &x;
            x.iteratorSet = 1;
            p.constFlag = 0;
            return p;
        }
        
        const_iterator end(void) const {
            const_iterator p;
            p.ptr = elements + length;
            p.constFlag = 1;
            return p;
        }
        
        const_iterator end(vector<T> x) const {
            const_iterator p;
            p.ptr = elements + length;
            p.constFlag = 1;
            return p;
        }
        
        uint64_t getSevereException(void) {
            return this->severeException;
        }
        
        uint64_t getModerateException(void) {
            return this->moderateException;
        }
        
        uint64_t getMildException(void) {
            return this->mildException;
        }
        
        vector(void) {
            elements = (T *)::operator new(sizeof(T)*default_capacity);
            length = 0;
            capacity = default_capacity;
            beginning_index = 0;
            end_index = 0;
            moderateException = 0;
            mildException = 0;
            severeException = 0;
        }
        explicit vector(uint64_t n);
        
        vector(const vector<T>& a);				// copy constructor
        vector<T>& operator=(const vector<T>& a) {	// copy assignment
            if (iteratorSet == 1) {
                moderateException = 1;
            }
            
            T* copy = (T *)::operator new(sizeof(T)*a.capacity); // inlined because of weird errors
            
            uint64_t i = a.beginning_index;
            while (i != a.end_index) {
                new (copy + i) T{ a.elements[i] };
                i = (i + 1) % a.capacity;
            }
            new (copy + i) T{ a.elements[i] }; // get the end_index also
            
            i = beginning_index;
            while (i != end_index) {
                (&elements[i]) -> ~T();
                i = (i + 1) % capacity;
            }
            if (length == 0)
            {
            }
            else {
                (&elements[i]) -> ~T(); // delete last_index also
            }
            ::operator delete(elements);
            
            elements = copy;
            length = a.length;
            capacity = a.capacity;
            beginning_index = a.beginning_index;
            end_index = a.end_index;
            return *this;
        }
        
        vector(vector<T>&& a);						// move constructor
        vector<T>& operator=(vector<T>&& a);		// move assignment
        
        template<typename... Args>
        void emplace_back(Args&&... args) {
            if (iteratorSet == 1) {
                severeException = 1;
            }
            if (length == capacity || (beginning_index == 0 && end_index == (capacity - 1)) ||
                ((beginning_index > 0) && (beginning_index - 1) == end_index))
            {
                if (capacity == 0)
                {
                    T* newElements = (T *)::operator new(sizeof(T) * 8);
                    capacity = 8;
                    if (newElements == NULL)
                        throw std::out_of_range{ "memory allocation failure" };
                    if (elements != NULL)
                    {
                        uint64_t i = beginning_index;
                        while (i != end_index) {
                            (&elements[i]) -> ~T();
                            i = (i + 1) % capacity;
                        }
                        if (length == 0)
                        {
                        }
                        else {
                            (&elements[i]) -> ~T(); // delete last_index also
                        }
                        ::operator delete(elements);
                    }
                    beginning_index = 0;
                    end_index = 0;
                    length = 1;
                    new(newElements + end_index) T{ std::forward<Args>(args)... };
                    elements = newElements;
                }
                else
                {
                    uint64_t i;
                    T* newElements = (T *)::operator new(sizeof(T) * 2 * capacity);
                    new(newElements + length) T{ std::forward<Args>(args)... };
                    
                    if (newElements == NULL)
                        throw std::out_of_range{ "memory allocation failure" };
                    
                    uint64_t j = 0;
                    i = beginning_index;
                    while (i != end_index) {
                        new (newElements + j) T{ std::forward<Args>(args)... };
                        i = (i + 1) % capacity;
                        ++j;
                    }
                    new (newElements + j) T{ std::forward<Args>(args)... };
                    
                    if (elements != NULL)
                    {
                        uint64_t q = beginning_index;
                        while (q != end_index) {
                            (&elements[q]) -> ~T();
                            q = (q + 1) % capacity;
                        }
                        if (length == 0)
                        {
                        }
                        else {
                            (&elements[q]) -> ~T(); // delete last_index also
                        }
                        ::operator delete(elements);
                    }
                    capacity = 2 * capacity;
                    beginning_index = 0;
                    length++;
                    end_index = beginning_index + length - 1;
                    elements = newElements;
                }
            }
            else if ((beginning_index == 0) && (end_index == 0) && length == 0) {
                new(elements + beginning_index) T{ std::forward<Args>(args)... };
                length++;
            }
            else if ((beginning_index == 0) && (end_index == 0) && length == 1) {
                end_index++;
                new(elements + end_index) T{ std::forward<Args>(args)... };
                length++;
            }
            else
            {
                end_index = (end_index + 1) % capacity;
                new(elements + end_index) T{ std::forward<Args>(args)... };
                length++;
            }
        }
        
        // Member template constructor for (3)
        template <typename It>
        vector(It begin, It end) : vector() {
            while (begin != end) {
                this->push_back(*begin);
                ++begin;
            }
        }
        
        // Alternate Vector initialization
        vector(std::initializer_list<int> list) : vector(list.begin(), list.end())
        {
            
        }
        
        ~vector() { // destructor
            uint64_t i = beginning_index;
            while (i != end_index) {
                (&elements[i]) -> ~T();
                i = (i + 1) % capacity;
            }
            if (length == 0) {
            }
            else {
                (&elements[i]) -> ~T(); // delete last_index also
            }
            ::operator delete(elements);
        }
        
        uint64_t size(void) const { return length; }
        
        T& operator[](uint64_t k);
        const T& operator[](uint64_t k) const;
        
        void push_front(const T& a);
        void push_front(T&& a);
        
        void push_back(T&& a);
        void push_back(const T& a);
        
        void pop_back(void);
        void pop_front(void);
    };
    
    template <typename T>
    vector<T>::vector(uint64_t n)
    {
        if (n < 0) throw std::out_of_range{ "Can't have negative" };
        if (n == 0) {
            elements = (T *)::operator new(sizeof(T)*default_capacity);
            // new (elements) T{};
            length = 0;
            capacity = default_capacity;
            beginning_index = 0;
            end_index = 0;
            moderateException = 0;
            mildException = 0;
            severeException = 0;
        }
        else if (n > 0) {
            elements = (T *)::operator new(sizeof(T)*n);
            for (uint64_t i = 0; i < n; ++i) {
                new (elements + i) T{};
            }
            length = n;
            capacity = n;
            beginning_index = 0;
            end_index = n - 1;
            moderateException = 0;
            mildException = 0;
            severeException = 0;
        }
    }
    
    // copy constructor
    template <typename T>
    vector<T>::vector(const vector<T>& a)
    {
        if (iteratorSet == 1) {
            mildException = 1;
        }
        capacity = a.capacity;
        length = a.length;
        beginning_index = a.beginning_index;
        end_index = a.end_index;
        
        elements = (T *)::operator new(sizeof(T)*a.capacity);
        
        uint64_t i = a.beginning_index;
        while (i != a.end_index) {
            new (elements + i) T{ a.elements[i] };
            i = (i + 1) % a.capacity;
        }
        if (a.length == 0) {
        }
        else {
            new (elements + i) T{ a.elements[i] }; // get the end_index also
        }
    }
    
    // move constructor
    template <typename T>
    vector<T>::vector(vector<T>&& a)
    : elements(a.elements)
    , length(a.length)
    , capacity(a.capacity)
    , beginning_index(a.beginning_index)
    , end_index(a.end_index)
    , moderateException(a.moderateException)
    , mildException(a.mildException)
    , severeException(a.severeException)
    {
        if (iteratorSet == 1) {
            mildException = 1;
            a.mildException = 1;
        }
        // copy data
        elements = a.elements;
        length = a.length;
        capacity = a.capacity;
        beginning_index = a.beginning_index;
        end_index = a.end_index;
        
        // release data
        a.elements = nullptr;
        a.length = 0;
        a.capacity = 0;
        a.beginning_index = 0;
        a.end_index = 0;
    }
    
    // move assignment
    template <typename T>
    vector<T>& vector<T>::operator=(vector<T>&& a)
    {
        if (iteratorSet == 1) {
            moderateException = 1;
            a.moderateException = 1;
        }
        if (this != &a) {
            if (elements != NULL) {
                uint64_t i = beginning_index;
                while (i != end_index) {
                    (&elements[i]) -> ~T();
                    i = (i + 1) % capacity;
                }
                if (length == 0)
                {
                }
                else {
                    (&elements[i]) -> ~T(); // delete last_index also
                }
                ::operator delete(elements);
            }
            elements = a.elements;
            capacity = a.capacity;
            length = a.length;
            beginning_index = a.beginning_index;
            end_index = a.end_index;
            
            // release data pointer
            a.elements = nullptr;
            a.capacity = 0;
            a.length = 0;
            a.beginning_index = 0;
            a.end_index = 0;
        }
        return *this;
    }
    
    // What's the difference, ????
    template <typename T>
    T& vector<T>::operator[](uint64_t k)
    {
        if (iteratorSet == 1) {
            severeException = 1;
        }
        if (k < 0 || size() <= k)
            throw std::out_of_range{ "vector::operator[]" }; // fix me ???
        uint64_t temp = (k + beginning_index) % capacity;
        
        return elements[temp];//???::possibly a bug
    }
    
    template <typename T>
    const T& vector<T>::operator[](uint64_t k)  const
    {
        if (k < 0 || size() <= k)
            throw std::out_of_range{ "vector::operator[]" }; // fix me ???
        uint64_t temp = (k + beginning_index) % capacity;
        
        return elements[temp];//???::possibly a bug
    }
    
    template <typename T>
    void vector<T>::push_back(const T& a) {
        if (iteratorSet == 1) {
            severeException = 1;
        }
        if (length == capacity || (beginning_index == 0 && end_index == (capacity - 1)) ||
            ((beginning_index > 0) && (beginning_index - 1) == end_index))
        {
            if (capacity == 0)
            {
                T* newElements = (T *)::operator new(sizeof(T) * 8);
                capacity = 8;
                if (newElements == NULL)
                    throw std::out_of_range{ "memory allocation failure" };
                if (elements != NULL)
                {
                    uint64_t i = beginning_index;
                    while (i != end_index) {
                        (&elements[i]) -> ~T();
                        i = (i + 1) % capacity;
                    }
                    if (length == 0)
                    {
                    }
                    else {
                        (&elements[i]) -> ~T(); // delete last_index also
                    }
                    ::operator delete(elements);
                }
                beginning_index = 0;
                end_index = 0;
                length = 1;
                new(newElements + end_index) T{ std::move(a) };
                elements = newElements;
            }
            else
            {
                uint64_t i;
                T* newElements = (T *)::operator new(sizeof(T) * 2 * capacity);
                
                new(newElements + length) T{ std::move(a) };
                
                if (newElements == NULL)
                    throw std::out_of_range{ "memory allocation failure" };
                
                uint64_t j = 0;
                i = beginning_index;
                while (i != end_index) {
                    new (newElements + j) T{ std::move(elements[i]) };
                    i = (i + 1) % capacity;
                    ++j;
                }
                new (newElements + j) T{ std::move(elements[i]) };
                
                if (elements != NULL)
                {
                    uint64_t q = beginning_index;
                    while (q != end_index) {
                        (&elements[q]) -> ~T();
                        q = (q + 1) % capacity;
                    }
                    if (length == 0)
                    {
                    }
                    else {
                        (&elements[q]) -> ~T(); // delete last_index also
                    }
                    ::operator delete(elements);
                }
                capacity = 2 * capacity;
                beginning_index = 0;
                length++;
                end_index = beginning_index + length - 1;
                elements = newElements;
            }
        }
        else if ((beginning_index == 0) && (end_index == 0) && length == 0) {
            new(elements + beginning_index) T{ (a) };
            length++;
        }
        else if ((beginning_index == 0) && (end_index == 0) && length == 1) {
            end_index++;
            new(elements + end_index) T{ (a) };
            length++;
        }
        else
        {
            end_index = (end_index + 1) % capacity;
            new(elements + end_index) T{ (a) };
            length++;
        }
    }
    
    template <typename T>
    void vector<T>::push_front(const T& a) {
        if (iteratorSet == 1) {
            severeException = 1;
        }
        if (length == capacity || (beginning_index==0 && end_index==(capacity-1)) ||
            ((beginning_index > 0) && (beginning_index-1)==end_index))
        {
            if (capacity == 0)
            {
                T* newElements = (T *)::operator new(sizeof(T) * 8);
                capacity = 8;
                if (newElements == NULL)
                    throw std::out_of_range{ "memory allocation failure" };
                if (elements != NULL)
                {
                    uint64_t i = beginning_index;
                    while (i != end_index) {
                        (&elements[i]) -> ~T();
                        i = (i + 1) % capacity;
                    }
                    if (length == 0)
                    {
                    }
                    else {
                        (&elements[i]) -> ~T(); // delete last_index also
                    }
                    ::operator delete(elements);
                }
                beginning_index = 0;
                end_index = 0;
                length = 1;
                new(newElements + end_index) T{ std::move(a) };
                elements = newElements;
            }
            else
            {
                uint64_t r;
                T* newElements = (T *)::operator new(sizeof(T) * 2 * capacity);
                new(newElements) T{ (a) };
                
                if (newElements == NULL)
                    throw std::out_of_range{ "memory allocation failure" };
                
                uint64_t j = 1;
                r = beginning_index;
                while (r != end_index) {
                    new (newElements + j) T{ std::move(elements[r]) };
                    r = (r + 1) % capacity;
                    ++j;
                }
                new (newElements + j) T{ std::move(elements[r]) };
                
                if (elements != NULL)
                {
                    uint64_t q = beginning_index;
                    while (q != end_index) {
                        (&elements[q]) -> ~T();
                        q = (q + 1) % capacity;
                    }
                    if (length == 0)
                    {
                    }
                    else {
                        (&elements[q]) -> ~T(); // delete last_index also
                    }
                    ::operator delete(elements);
                }
                capacity = 2 * capacity;
                beginning_index = 0;
                length++;
                end_index = beginning_index + length - 1;
                elements = newElements;
            }
        }
        else if ((beginning_index == 0) && (end_index == 0) && length == 0) {
            new(elements + beginning_index) T{ a };
            length++;
        }
        else if ((beginning_index == 0) && (end_index == 0) && length == 1) {
            beginning_index = capacity - 1;
            new(elements + beginning_index) T{ a };
            length++;
        }
        else {
            if (beginning_index == 0) {
                beginning_index = capacity - 1; // Possible bug: could be negative
            }
            else {
                --beginning_index;
            }
            new(elements + beginning_index) T{ a };
            length++;
        }
    }
    
    template <typename T>
    void vector<T>::push_front(T&& a) {
        if (iteratorSet == 1) {
            severeException = 1;
        }
        if (length == capacity || (beginning_index == 0 && end_index == (capacity - 1)) ||
            ((beginning_index > 0) && (beginning_index - 1) == end_index))
        {
            if (capacity == 0)
            {
                T* newElements = (T *)::operator new(sizeof(T) * 8);
                capacity = 8;
                if (newElements == NULL)
                    throw std::out_of_range{ "memory allocation failure" };
                if (elements != NULL)
                {
                    uint64_t i = beginning_index;
                    while (i != end_index) {
                        (&elements[i]) -> ~T();
                        i = (i + 1) % capacity;
                    }
                    if (length == 0)
                    {
                    }
                    else {
                        (&elements[i]) -> ~T(); // delete last_index also
                    }
                    ::operator delete(elements);
                }
                beginning_index = 0;
                end_index = 0;
                length = 1;
                new(newElements + end_index) T{ std::move(a) };
                elements = newElements;
            }
            else
            {
                uint64_t i;
                T* newElements = (T *)::operator new(sizeof(T) * 2 * capacity);
                new(newElements) T{ std::move(a) };
                
                if (newElements == NULL)
                    throw std::out_of_range{ "memory allocation failure" };
                
                uint64_t j = 1;
                i = beginning_index;
                while (i != end_index) {
                    new (newElements + j) T{ std::move(elements[i]) };
                    i = (i + 1) % capacity;
                    ++j;
                }
                new (newElements + j) T{ std::move(elements[i]) };
                
                if (elements != NULL)
                {
                    uint64_t q = beginning_index;
                    while (q != end_index) {
                        (&elements[q]) -> ~T();
                        q = (q + 1) % capacity;
                    }
                    if (length == 0)
                    {
                    }
                    else {
                        (&elements[q]) -> ~T(); // delete last_index also
                    }
                    ::operator delete(elements);
                }
                capacity = 2 * capacity;
                beginning_index = 0;
                length++;
                end_index = beginning_index + length - 1;
                elements = newElements;
            }
        }
        else if ((beginning_index == 0) && (end_index == 0) && length == 0) {
            new(elements + beginning_index) T{ std::move(a) };
            length++;
        }
        else if ((beginning_index == 0) && (end_index == 0) && length == 1) {
            beginning_index = capacity - 1;
            new(elements + beginning_index) T{ std::move(a) };
            length++;
        }
        else {
            if ((beginning_index) == 0) {
                beginning_index = capacity - 1;
            }
            else {
                --beginning_index;
            }
            new(elements + beginning_index) T{ std::move(a) };
            length++;
        }
    }
    
    template <typename T>
    void vector<T>::push_back(T&& a) {
        if (iteratorSet == 1) {
            severeException = 1;
        }
        if (length == capacity || (beginning_index == 0 && end_index == (capacity - 1)) ||
            ((beginning_index > 0) && (beginning_index - 1) == end_index))
        {
            if (capacity == 0)
            {
                T* newElements = (T *)::operator new(sizeof(T) * 8);
                capacity = 8;
                if (newElements == NULL)
                    throw std::out_of_range{ "memory allocation failure" };
                if (elements != NULL)
                {
                    uint64_t i = beginning_index;
                    while (i != end_index) {
                        (&elements[i]) -> ~T();
                        i = (i + 1) % capacity;
                    }
                    if (length == 0)
                    {
                    }
                    else {
                        (&elements[i]) -> ~T(); // delete last_index also
                    }
                    ::operator delete(elements);
                }
                beginning_index = 0;
                end_index = 0;
                length = 1;
                new(newElements + end_index) T{ std::move(a) };
                elements = newElements;
            }
            else
            {
                uint64_t i;
                T* newElements = (T *)::operator new(sizeof(T) * 2 * capacity);
                new(newElements + length) T{ std::move(a) };
                
                if (newElements == NULL)
                    throw std::out_of_range{ "memory allocation failure" };
                
                uint64_t j = 0;
                i = beginning_index;
                while (i != end_index) {
                    new (newElements + j) T{ std::move(elements[i]) };
                    i = (i + 1) % capacity;
                    ++j;
                }
                new (newElements + j) T{ std::move(elements[i]) };
                
                if (elements != NULL)
                {
                    uint64_t q = beginning_index;
                    while (q != end_index) {
                        (&elements[q]) -> ~T();
                        q = (q + 1) % capacity;
                    }
                    if (length == 0)
                    {
                    }
                    else {
                        (&elements[q]) -> ~T(); // delete last_index also
                    }
                    ::operator delete(elements);
                }
                capacity = 2 * capacity;
                beginning_index = 0;
                length++;
                end_index = beginning_index + length - 1;
                elements = newElements;
            }
        }
        else if ((beginning_index == 0) && (end_index == 0) && length == 0) {
            new(elements + beginning_index) T{ std::move(a) };
            length++;
        }
        else if ((beginning_index == 0) && (end_index == 0) && length == 1) {
            end_index++;
            new(elements + end_index) T{ std::move(a) };
            length++;
        }
        else
        {
            end_index = (end_index + 1) % capacity;
            new(elements + end_index) T{ std::move(a) };
            length++;
        }
    }
    
    template <typename T>
    void vector<T>::pop_back(void) {
        if (iteratorSet == 1 && length <= 1) {
            severeException = 1;
        }
        else if (iteratorSet == 1) {
            mildException = 1;
        }
        if (length == 0)
            throw std::out_of_range{ "Array is empty" };
        else
        {
            elements[end_index].~T();
            if (end_index == 0) {
                end_index = (capacity - 1);
            }
            else {
                --end_index;
            }
            length--;
        }
    }
    
    template <typename T>
    void vector<T>::pop_front(void) {
        if (iteratorSet == 1 && length <= 1) {
            severeException = 1;
        }
        else if (iteratorSet == 1) {
            mildException = 1;
        }
        if (length == 0)
            throw std::out_of_range{ "Array is empty" };
        else
        {
            elements[beginning_index].~T();
            beginning_index = (beginning_index + 1) % capacity;
            --length;
        }
    }
    
    using std::begin;
}

#endif /* _Vector_h */
