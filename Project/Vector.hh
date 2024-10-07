#include <iostream>

using namespace std;

//Vector de cadenas

template <typename T>
class Vector {
    private:
        T* data;
        unsigned int size;
        unsigned int capacity;
    public:
        Vector() : data(nullptr), size(0), capacity(0) {}
        Vector(unsigned int n) : data(new T[n]), size(n), capacity(n) {}
        ~Vector() { delete[] data; }
        unsigned int getSize() { return size; }
        unsigned int getCapacity() { return capacity; }
        bool empty() { return size == 0; }
        public:
        T& at(unsigned int index) {
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }

        const T& at(unsigned int index) const {
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }
        void print() {
            for (unsigned int i = 0; i < size; i++) {
                cout << data[i] << " ";
            }
            cout << endl;
        }
        void push_back(T value) {
            if (size == capacity) {
                if (capacity == 0) {
                    capacity = 1;
                } else {
                    capacity *= 2;
                }
                T* newData = new T[capacity];
                for (unsigned int i = 0; i < size; i++) {
                    newData[i] = data[i];
                }
                delete[] data;
                data = newData;
            }
            data[size] = value;
            size++;
        }
        void sort() {
            for (unsigned int i = 0; i < size; i++) {
                for (unsigned int j = 0; j < size - 1; j++) {
                    if (data[j] > data[j + 1]) {
                        T temp = data[j];
                        data[j] = data[j + 1];
                        data[j + 1] = temp;
                    }
                }
            }
        }
        void remove(unsigned int index) {
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            for (unsigned int i = index; i < size - 1; i++) {
                data[i] = data[i + 1];
            }
            size--;
        }
    private:
        void resize() {
            if (size == capacity) {
                if (capacity == 0) {
                    capacity = 1;
                } else {
                    capacity *= 2;
                }
                T* newData = new T[capacity];
                for (unsigned int i = 0; i < size; i++) {
                    newData[i] = data[i];
                }
                delete[] data;
                data = newData;
            }
        }
};