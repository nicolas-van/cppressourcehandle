#ifndef DEBUG_UTILS_HPP_INCLUDED
#define DEBUG_UTILS_HPP_INCLUDED

#if !defined(DEBUG_UTILS_DEBUG_MODE)
#if defined(NDEBUG)
#define DEBUG_UTILS_DEBUG_MODE 0
#else
#define DEBUG_UTILS_DEBUG_MODE 1
#endif
#endif

#if DEBUG_UTILS_DEBUG_MODE==0
#define DEBUG_ACTION(x)	((void)0)
#else
#define DEBUG_ACTION(x) (x)
#endif

#include <stdexcept>
#include <iostream>

namespace zais {
    class assertion_error : public std::logic_error {
        std::string _verif;
        std::string _file;
        unsigned int _line;
        public:
        assertion_error(const std::string& st)
        :logic_error(st),_line(0) {}
        assertion_error(const std::string& st,const std::string& v,const std::string& f,unsigned int l)
        :logic_error(st),_verif(v),_file(f),_line(l) {}
        const std::string& verification() const {
            return _verif;
        }
        const std::string& file() const {
            return _file;
        }
        unsigned int line() const {
            return _line;
        }
        ~assertion_error() throw() {}
    };
    std::ostream& operator << (std::ostream& str,const assertion_error& er) {
        str << std::endl;
        str << "Assertion error" << std::endl;
        str << "===============" << std::endl;
        str << "Failed on: " << er.verification() << std::endl;
        str << "Message: " << er.what() << std::endl;
        str << "File: " << er.file() << std::endl;
        str << "Line: " << er.line() << std::endl;
        str << std::endl;
        return str;
    }
}

#define DEBUG_ASSERT(e,y) DEBUG_ACTION( (e)?(void)0:(throw zais::assertion_error(y,#e,__FILE__, __LINE__)) )

#endif // DEBUG_UTILS_HPP_INCLUDED
