#include "heap.h"
#include "graph.h"
#include <iostream>
#include <map>
#include <limits>

using namespace std;

void input(graph & gr) {
    cout << "Graph size = " << gr.sz() << endl;
    size_t count;
    cout << "Edge count: ";
    cin >> count;
    gr.resize(count);

    while(count--) {
        size_t from, to;
        int weight;
        cout << "from: ";
        cin >> from;

        cout << "to: ";
        cin >> to;

        cout << "weight: ";
        cin >> weight;

        gr.add_edge(from, to, weight);
    }
}

typedef pair<int, size_t> wpair;

void dijkstra(graph & gr, size_t start) {

    int * weights = new int[gr.sz()];
    for(size_t c = 0; c < gr.sz(); ++c) {
        weights[c] = INT_MAX;
    }
    weights[start] = 0;

    heap<wpair> hp([](wpair & l, wpair & r) -> bool {
        return l.first < r.first;
    });

    hp.push(wpair(0, start));

    while( hp.size() ) {
        wpair curr = hp.top();
        hp.pop();
        for(size_t c = 0; c < gr.sz(); ++c) {
            if( gr.get_edge(curr.second, c) ) {
                if( weights[c] > curr.first + gr.get_edge(curr.second, c) ) {
                    weights[c] = curr.first + gr.get_edge(curr.second, c);
					hp.push(wpair(weights[c], c));
                }
            }
        }
    }

    for(size_t c = 0; c < gr.sz(); ++c) {
        cout << "Distance from gr[" << start << "] to gr[" << c << "] = " << weights[c] << endl;
    }
}

int main() {

    size_t size;
    cout << "Node count = ";
    cin >> size;
    graph gr(size);
    input(gr);

    size_t start;
    cout << "Start: ";
    cin >> start;

    dijkstra(gr, start);
    cin.get();cin.get();cin.get();
    return 0;
}

