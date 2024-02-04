#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max(); // Define infinity as the maximum value an `int` can hold

// Function to perform Dijkstra's algorithm on a graph
void dijkstra(const vector<vector<pair<int, int>>>& graph, int source) {
    // Priority queue to store vertices that are being preprocessed.
    // This is a min-heap sorted by distance from source.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // Distance vector. dist[i] will hold the shortest distance from source to i.
    vector<int> distance(graph.size(), INF);

    // Initialize distance of source vertex to itself as 0
    distance[source] = 0;
    pq.push({0, source});

    // Looping till priority queue becomes empty (or all distances are not finalized)
    while (!pq.empty()) {
        // The first vertex in pair is the minimum distance vertex, extract it from the priority queue.
        // vertex label is stored in second of pair (it has to be done this way to keep the vertices
        // sorted distance (distance must be first item in pair)
        int dist = pq.top().first;
        int current = pq.top().second;
        pq.pop();

        // 'current' is now the shortest distance vertex that hasn't been processed yet.
        // We are done with it, so erase it from the priority queue

        // If distance of current vertex is more than the current known distance, skip it.
        if (dist > distance[current]) {
            continue;
        }

        // Otherwise, go through all adjacent vertices
        for (const auto& edge : graph[current]) {
            int next = edge.first;
            int nextDist = dist + edge.second;

            // If there is a shorter path to next through current, update distance of next
            if (nextDist < distance[next]) {
                distance[next] = nextDist;
                pq.push({nextDist, next}); // Push next vertex with updated distance to priority queue
            }
        }
    }

    // Print the shortest distances from source to all other vertices
    for (int i = 0; i < graph.size(); ++i) {
        if (distance[i] == INF) {
            cout << "Vertex " << source << " to " << i << " is unreachable." << endl;
        } else {
            cout << "Shortest distance from " << source << " to " << i << " is " << distance[i] << endl;
        }
    }
}

// Main function to take input and call the Dijkstra's algorithm function
int main() {
    int V, E, u, v, w, source;
    // Take input for number of vertices and edges
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;
    vector<vector<pair<int, int>>> graph(V); // Graph is represented as a vector of vector of pairs

    // Input edges in the format: u v w, where u is the starting vertex,
    // v is the ending vertex, and w is the weight of the edge.
    cout << "Enter edges (u v w):" << endl;
    for (int i = 0; i < E; ++i) {
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w); // Add edge to the graph
    }

    // Take input for the source vertex
    cout << "Enter source vertex: ";
    cin >> source;

    // Call Dijkstra's algorithm to find shortest paths from the source
    dijkstra(graph, source);

    return 0;
}
