#include <iostream>
#include  "Queue.h"
#include "Vector.h"
#include "Graph.h"
using namespace std;

int main() {
    int k;
    cin >> k; 

    while (k-- > 0) {
        int vertices;
        cin >> vertices;
        Graph g(vertices);
        g.processGraph(vertices);
    }

    return 0;
}
