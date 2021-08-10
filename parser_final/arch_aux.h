#ifndef ARCH_AUX_H
#define ARCH_AUX_H
#include <vector>

using namespace std;

template <class T>
bool content(T t, vector<T> cont){
    for (int i = 0; i < cont.size(); i++){
        if (cont[i] == t)
            return true;
    }
    return false;
}

#endif