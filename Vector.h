#ifndef VECTOR_H
#define VECTOR_H
#include <cstring>
template <typename T>
class Vector {
private:
    T* array;
    int current_size;
    int allocated_size;

    void reallocate(int new_size) {
        T* new_array = new T[new_size];
        memcpy(new_array, array, sizeof(T) * (current_size > new_size ? new_size : current_size));
        delete[] array;
        array = new_array;
        allocated_size = new_size;
    }

public:
    Vector() : array(nullptr), current_size(0), allocated_size(0) {}

    Vector(int size, T value = T()) : array(nullptr), current_size(0), allocated_size(0) {
        if (size > 0) {
            array = new T[size];
            for (int i = 0; i < size; ++i) {
                array[i] = value;
            }
            current_size = size;
            allocated_size = size;
        }
    }
    ~Vector() { delete[] array; }

    void assign(int count, T value) {
        clear();
        resize(count, value);
    }

    void push_back(const T& value) {
        if (current_size >= allocated_size) {
            reallocate(allocated_size > 0 ? allocated_size * 2 : 1);
        }
        array[current_size++] = value;
    }

    void clear() {
        delete[] array;
        array = nullptr;
        current_size = 0;
        allocated_size = 0;
    }

    void resize(int new_size, T value = T()) {
        if (new_size > allocated_size) {
            reallocate(new_size);
        }
        if (new_size > current_size) {
            for (int i = current_size; i < new_size; ++i) {
                array[i] = value;
            }
        }
        current_size = new_size;
    }

    T& operator[](int index) {
        return array[index];
    }

    const T& operator[](int index) const {
        return array[index];
    }

    int size() const { return current_size; }

    T* begin() { return array; }
    T* end() { return array + current_size; }
   
};

#endif // VECTOR_H
