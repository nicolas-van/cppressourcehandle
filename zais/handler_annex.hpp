#ifndef HANDLER_ANNEX_HPP_INCLUDED
#define HANDLER_ANNEX_HPP_INCLUDED

namespace zais {

    namespace detail {

        /*
            Just don't care about this code.
        */

        template<bool V>
        struct is_true {};
        template<>
        struct is_true<true> {
            static void check() {}
        };

        template<typename T>
        struct is_pointer {
            typedef T pointed_type;
        };
        template<typename T>
        struct is_pointer<T*> {
            typedef T pointed_type;
            static void check() {}
        };

        template<typename T,bool B>
        struct is_mutable {
            typedef const T value_type;
        };
        template<typename T>
        struct is_mutable<T,true> {
            typedef T value_type;
        };

        template<typename T>
        struct remove_const {
            typedef T value_type;
        };
        template<typename T>
        struct remove_const<const T> {
            typedef T value_type;
        };

        template<typename T>
        struct wrapper {
            T t;
            wrapper(const T& v):t(v) {}
        };
    }

}

#endif // HANDLER_ANNEX_HPP_INCLUDED
