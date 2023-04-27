#ifndef LIBRARY_LOADER_HPP
#define LIBRARY_LOADER_HPP

#include <iostream>
#include <set>
#include <dlfcn.h>
#include <fstream>

class LibraryLoader{
private:
    //store the names of the loaded libraries
    std::set<std::string> loaded_libraries;

public:
    //constructors
    LibraryLoader(std::string filename){
        std::ifstream file(filename);
        if(!file)
            std::cerr << filename <<" can't be opened"<< std::endl;
        else{
            std::string lib_name;
            while(std::getline(file, lib_name))
                load_library(lib_name);
        }
    };
    //loader method
    bool load_library(std::string lib_name){
        void *dylib = dlopen(lib_name.c_str(),RTLD_NOW);
        if(dylib == nullptr)
        {
            std::cout << "cannot find library" << lib_name << std::endl;
            std::cout << dlerror();
            return false;
        }
        loaded_libraries.insert(lib_name);
        return true;
    };
    //is loaded method
    bool is_loaded(std::string lib_name){
        if(loaded_libraries.find(lib_name) != loaded_libraries.end())
            return true;
        else
            return false;
    };
    //print
    void print(){
        std::cout << "LOADED LIBRARIES:" << std::endl;
        for(auto it = loaded_libraries.begin();it!=loaded_libraries.end();it++){
            std::cout << *it << " is loaded" << std::endl;
        }
    }
};


#endif //LIBRARY_LOADER_HPP