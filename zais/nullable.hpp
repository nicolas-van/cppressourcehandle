#ifndef NULLABLE_HPP_INCLUDED
#define NULLABLE_HPP_INCLUDED

#include "debug_utils.hpp"

namespace zais {

    template<typename T>
    class nullable {
        public:
        typedef T value_type;

        private:
        bool _valid;
        char _data[sizeof(value_type)];

        value_type& _get() {
            return *reinterpret_cast<value_type*>(_data);
        }

        const value_type& _get() const {
            return *reinterpret_cast<const value_type*>(_data);
        }
        public:

        nullable():_valid(false) {};

        value_type& get() {
            DEBUG_ASSERT(!null(),"trying to access value while it is null");
            return _get();
        }

        const value_type& get() const {
            DEBUG_ASSERT(!null(),"trying to access value while it is null");
            return _get();
        }

        bool null() const {
            return !_valid;
        }

        void destroy() {
            if(_valid) {
                _get().~value_type();
                _valid = false;
            }
        }

        void construct() {
            if(_valid) {
                _get().~value_type();
            } else
                _valid=true;
            ::new(&_get()) value_type();
        }
        template <class T1>
        void construct(T1 t1) {
            if(_valid) {
                _get().~value_type();
            } else
                _valid=true;
            ::new(&_get()) value_type(t1);
        }
        template <class T1,class T2>
        void construct(T1 t1,T2 t2) {
            if(_valid) {
                _get().~value_type();
            } else
                _valid=true;
            ::new(&_get()) value_type(t1,t2);
        }
        template <class T1,class T2,class T3>
        void construct(T1 t1,T2 t2,T3 t3) {
            if(_valid) {
                _get().~value_type();
            } else
                _valid=true;
            ::new(&_get()) value_type(t1,t2,t3);
        }
        template <class T1,class T2,class T3,class T4>
        void construct(T1 t1,T2 t2,T3 t3,T4 t4) {
            if(_valid) {
                _get().~value_type();
            } else
                _valid=true;
            ::new(&_get()) value_type(t1,t2,t3,t4);
        }
        template <class T1,class T2,class T3,class T4,class T5>
        void construct(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5) {
            if(_valid) {
                _get().~value_type();
            } else
                _valid=true;
            ::new(&_get()) value_type(t1,t2,t3,t4,t5);
        }
        template <class T1,class T2,class T3,class T4,class T5,class T6>
        void construct(T1 t1,T2 t2,T3 t3,T4 t4,T5 t5,T6 t6) {
            if(_valid) {
                _get().~value_type();
            } else
                _valid=true;
            ::new(&_get()) value_type(t1,t2,t3,t4,t5,t6);
        }

        nullable(const nullable& o) {
            if(o._valid) {
                _valid=true;
                ::new(&_get()) value_type(o._get());
            } else {
                _valid=false;
            }
        }

        nullable& operator = (const nullable& o) {
            if(o._valid) {
                _valid=true;
                if(_valid) {
                    _get()=o._get();
                } else {
                    ::new(&_get()) value_type(o._get());
                }
            } else {
                if(_valid) {
                    _get().~value_type();
                    _valid = false;
                }
            }
            return *this;
        }

        nullable(const value_type& v):_valid(true) {
            ::new(&_get()) value_type(v);
        }

        nullable& operator = (const value_type& v) {
            if(_valid) {
                _get()=v;
            } else {
                _valid=true;
                ::new(&_get()) value_type(v);
            }
            return *this;
        }

        ~nullable() {
            if(_valid) {
                _get().~value_type();
            }
        }

    };

}

#endif // NULLABLE_HPP_INCLUDED
