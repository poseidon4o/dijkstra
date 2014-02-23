#pragma once
#include <algorithm>
#include <functional>

using namespace std;

template <typename T>
class heap {
    T * data;
    size_t elements, index;
    function<bool(T&, T&)> comp;
public:
    heap(function<bool(T&, T&)> cmp, size_t sz = 128): comp(cmp) {
        sz = sz < 128 ? 128 : sz;
        index = 1;
        data = new T[elements = sz + 1];
    }

    ~heap() {
        delete[] data;
    }

    size_t size() {
        return index - 1;
    }

    void push(const T & el) {
        resize();
        data[index++] = el;
        up(index-1);
    }

    void pop() {
        if( index > 1 ) {
            data[1] = data[--index];
            down(1);
        }
    }

    T & top() {
        return data[1];
    }
private:
    void down(size_t idx) {
        if( idx * 2 >= index ) {
            return;
        }

        size_t left = idx * 2, right = idx * 2 + 1;
        if( right >= index ) {
            right = left;
        }

        if( comp(data[idx], data[left]) ) {
            if( comp(data[idx], data[right]) ) {
                if( comp(data[left], data[right]) ) {
                    swap(data[right], data[idx]);
                    down(right);
                } else {
                    swap(data[left], data[idx]);
                    down(left);
                }
            } else if( comp(data[right], data[idx]) ) {
                swap(data[left], data[idx]);
                down(left);
            }
        }
    }

    void up(size_t idx) {
        if( idx == 1 ) {
            return;
        }

        if( comp(data[idx/2], data[idx]) ) {
            swap(data[idx/2], data[idx]);
            up(idx/2);
        }
    }

    void resize() {
        if( index < elements ) {
            return;
        }

        T * tmp = new T[elements * 2];
        for(size_t c = 1; c < elements; ++c) {
            tmp[c] = data[c];
        }
        elements *= 2;
        delete[] data;
        data = tmp;
    }

};