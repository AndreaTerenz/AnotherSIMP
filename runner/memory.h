#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

template<typename T>
class Memory
{
public:
    Memory() : Memory(0) {}
    Memory(unsigned int s) : size(s), locations(new T[s]) { }
    ~Memory() { delete [] locations; }

    unsigned int get_size() { return size; }

    bool set_value_at(T val, unsigned int pos) {
        if (pos < size) {
            locations[pos] = val;
            return true;
        }

        return false;
    }

    T* get_value_at(unsigned int pos) {
        if (pos < size) {
            T* output = new T(locations[pos]);
            //std::cout<<pos<<" "<<*output<<"\t";
            return output;
        }

        return nullptr;
    }

private:
    unsigned int size;
    T* locations = nullptr;
};

#endif // MEMORY_H
