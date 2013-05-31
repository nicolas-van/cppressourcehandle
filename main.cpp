
#include "zais/handler.hpp"
#include <iostream>
#include <set>
#include <cassert>
#include "zais/debug_utils.hpp"
#include "zais/nullable.hpp"
#include <memory>
#include <cstdio>
#include <fstream>

using namespace std;
using namespace zais;

struct file_handler_trait;

typedef handler<file_handler_trait> file_handler_low;

struct file_handler_trait {
    typedef FILE*  value_type;

    //static const bool is_mutable = false;

    static void destroy(FILE*& v) throw() {
        if(v!=NULL)
            fclose(v);
    }
    static void construct(FILE*& v,const string& f,const string& t) {
        v=fopen(f.c_str(),t.c_str());
        if(v==NULL)
            throw file_handler_low::runtime_exception("cannot open file");
    }
};


int main(int argc,char** argv) {
    file_handler_low file("machin.txt","w");
    fprintf(file.get(),"salut le monde");

    return 0;
}

