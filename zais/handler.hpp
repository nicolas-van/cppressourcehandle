
#ifndef CLIW_HANDLER_HPP_INCLUDED
#define CLIW_HANDLER_HPP_INCLUDED

#if !defined(HANDLER_PROVIDE_EXCEPTIONS)
#define HANDLER_PROVIDE_EXCEPTIONS 1
#endif

#if HANDLER_PROVIDE_EXCEPTIONS!=0
#include <stdexcept>
#endif

#include "handler_annex.hpp"

namespace zais {

    /*
    Exemple :

    struct xxx_handler_trait;
    typedef zais::handler<xxx_handler_trait> xxx_handler;
    struct xxx_handler_trait {
        typedef xxx value_type;

        // The destructor must always be defined
        static void destroy(value_type& v) throw() {

        }

        // The default constructor is facultative
        //static void construct(value_type& v) {}

        // The copy constructor is facultative
        //static void construct(value_type& v,const value_type& v) {}

        // You can define as many constructors as you want
        //static void construct(value_type& v,int x) {}
        //static void construct(value_type& v,float x) {}

        // The assignment operator is facultative
        //static void assign(value_type& v,const value_type& o) {}
    };

    */

    template <class TR>
    class handler {
        public:
        typedef typename detail::remove_const<typename TR::value_type>::value_type value_type;
        typedef typename TR::value_type public_type;
        typedef TR trait_type;
#if HANDLER_PROVIDE_EXCEPTIONS!=0
        class runtime_exception : public std::runtime_error {
            public:
            explicit runtime_exception(const std::string&  __arg):std::runtime_error(__arg) {};
        };
        class logic_exception : public std::logic_error {
            public:
            explicit logic_exception(const std::string&  __arg):std::logic_error(__arg) {};
        };
#endif
        private:
        value_type value;
        public:
        /**
            Construct by initializing with an existing value when
            using handler(wrap(value)).
            Does not use trait_type::construct(value_type&,const value_type&).
        */
        handler(const detail::wrapper<value_type>& w):value(w.t) {}

        /**
            Assign a new value when using handler = wrap(value).
            Does not use trait_type::assign(value_type&,const value_type&).
        */
        handler& operator=(const detail::wrapper<value_type>& w) {
            trait_type::destroy(value);
            value = w.t;
            return *this;
        }

        /**
            Constructor with no argument.
        */
        handler() {
            trait_type::construct(value);
        };
        /**
            Constructor with 1 argument.
        */
        template<class A1>
        handler(A1 a1) {
            trait_type::construct(value,a1);
        }
        /**
            Constructor with 2 arguments.
        */
        template<class A1,class A2>
        handler(A1 a1,A2 a2) {
            trait_type::construct(value,a1,a2);
        }
        /**
            Constructor with 3 arguments.
        */
        template<class A1,class A2,class A3>
        handler(A1 a1,A2 a2,A3 a3) {
            trait_type::construct(value,a1,a2,a3);
        }
        /**
            Constructor with 4 arguments.
        */
        template<class A1,class A2,class A3,class A4>
        handler(A1 a1,A2 a2,A3 a3,A4 a4) {
            trait_type::construct(value,a1,a2,a3,a4);
        }
        /**
            Constructor with 5 arguments.
        */
        template<class A1,class A2,class A3,class A4,class A5>
        handler(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5) {
            trait_type::construct(value,a1,a2,a3,a4,a5);
        }
        /**
            Constructor with 6 arguments.
        */
        template<class A1,class A2,class A3,class A4,class A5,class A6>
        handler(A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6) {
            trait_type::construct(value,a1,a2,a3,a4,a5,a6);
        }

        /**
            Return the value.
        */
        const value_type& get() const {
            return value;
        }
        /**
            Return the value. The return is a non-const reference only when
            trait_type::is_mutable is true.
        */
        public_type&
        get() {
            return value;
        }

        /**
            Return the data pointed by the value.
            The value must be a pointer.
        */
        typename detail::is_pointer<value_type>::pointed_type& operator * () const {
            detail::is_pointer<value_type>::check();
            return *value;
        }
        /**
            Return the data pointed by the value.
            The value must be a pointer.
        */
        value_type operator -> () const {
            detail::is_pointer<value_type>::check();
            return value;
        }

        /**
            Construct a handler by copying another handler.
            trait_type::construct(value_type&,const value_type&) must be defined.
        */
        handler(const handler& o) : handler(o.get()) {}
        /**
            Assign a new value to this handler by copying
            another value.
            trait_type::assign must be defined.
        */
        handler& operator = (const value_type& e) {
            value_type tmp = value;
            trait_type::assign(value,e);
            trait_type::destroy(tmp);
            return *this;
        }
        /**
            Assign a new value to this handler by copying the value
            of another handler.
            trait_type::assign must be defined.
        */
        handler& operator = (const handler& o) {
            return ((*this) = o.get());
        }

        /**
            Destroy the handler.
        */
        ~handler() {
            trait_type::destroy(value);
        }
    };

    /**
        This function should only be used when its return is sent
        to the constructor or the assignement operator of a handler.
    */
    template<typename T>
    detail::wrapper<T> handle(const T& t) {
        return detail::wrapper<T>(t);
    }

}


#endif // CLIW_HANDLER_HPP_INCLUDED

