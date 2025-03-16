#include "dijkstras.h"
#include <vector>
#include <cassert>
using namespace std;


void test_all() {
    cout << "Testing dijkstra_shortest_path..." << endl;

    Graph G;
    G.numVertices = 4;
    G.resize(4);

    /** 
    0 --- (1) ---- 1 ---(2) --- 2 ---(3) ---3
    |               ----(6)--- 3
    (4)
    |
    2 

    Shortest path from 0
    1: 1 (0,1)
    2: 3 (0, 1, 2)
    3: 6 (0, 1, 2, 3)
    **/
    vector<int> previous(G.numVertices, -1);
    
    G[0].push_back(Edge(0, 1, 1));
    G[0].push_back(Edge(0, 2, 4));
    G[1].push_back(Edge(1, 2, 2));
    G[1].push_back(Edge(1, 3, 6));
    G[2].push_back(Edge(2, 3, 3));
    
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    for(int dest = 1; dest < G.numVertices; ++dest) {
        vector<int> shortest_path = extract_shortest_path(distances, previous, dest);
        cout << "Path from 0 to " << dest << "..." << endl;
        print_path(shortest_path, distances[dest]);
    }

    assert(distances[0] == 0);
    assert(distances[1] == 1);
    assert(distances[2] == 3);
    assert(distances[3] == 6);

    assert(previous[0] == -1);
    assert(previous[1] == 0);
    assert(previous[2] == 1);
    assert(previous[3] == 2);
}

int main() {
    test_all();
}

