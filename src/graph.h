#pragma once
#include <string>

class graph {
    size_t size;
    int ** matrix;
public:
    graph(size_t sz): size(sz) {
        matrix = new int*[size];
        for(size_t c = 0; c < size; ++c) {
            matrix[c] = new int[size];
            memset(matrix[c], 0, size);
        }
    }

    void add_edge(size_t from, size_t to, int weight) {
        if( from < size && to < size )
            matrix[from][to] = weight;
    }

    void remove_edge(size_t from, size_t to) {
        matrix[from][to] = 0;
    }

    int get_edge(size_t from, size_t to) {
        return from < size && to < size ? matrix[from][to] : 0;
    }

    size_t sz() {
        return size;
    }

    void resize(size_t new_size) {
        for(size_t c = 0; c < size; ++c) {
            delete[] matrix[c];
        }
        delete[] matrix;

        matrix = new int*[size = new_size];
        for(size_t c = 0; c < size; ++c) {
            matrix[c] = new int[size];
            memset(matrix[c], 0, size * sizeof(int));
        }
    }

};

