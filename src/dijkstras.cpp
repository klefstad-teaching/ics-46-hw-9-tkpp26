#include "dijkstras.h"
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// Source : https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/#
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numV = G.numVertices;
    vector<int> distances(numV, INF);
    vector<bool> visited(numV, false);
    distances[source] = 0;
    previous[source] = -1; // acts as a stopping condition when calling extract_shortest_path or -1?

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap; // pair<vertex, weight>
    minHeap.push({source, 0}); // push source node to minHeap

    while(!minHeap.empty()) {
        int u = minHeap.top().first;
        minHeap.pop();

        if(visited[u])
            continue;
        else
            visited[u] = true;

        // G is an adjacency list so G[u] is a list of edges connected to u
        for (Edge edge : G[u]) {
            int v = edge.dst; 
            int weight = edge.weight;
            // Update shortest path to v from source
            // Update the previous node 
            // THINK : why is !visited[v] necessary?
            if(distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]}); 
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    // Handle edge case : If path from source to dest doesn't exist
    if (distances[destination] == INF)
        return vector<int>();

    // If only one node
    if (previous[destination] == -1) 
        return {destination};

    // If path of more than one exists
    stack<int> shortest_stack;
    int curr = destination;

    while(curr != -1) {
        shortest_stack.push(curr);
        curr = previous[curr]; // go back one up
    }

    // pop from stack and return path -- ensure order from source to dest
    vector<int> shortest_path;
    while(!shortest_stack.empty()) {
        shortest_path.push_back(shortest_stack.top());
        shortest_stack.pop();
    }

    return shortest_path;
}
// total indicates the total weight of the path
void print_path(const vector<int>& v, int total) {
    size_t path_length = v.size();

    for(size_t i = 0; i < path_length; ++i ){
        cout << v[i] << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}
void error(string msg) {
    cout << "Error: " + msg << endl;
}