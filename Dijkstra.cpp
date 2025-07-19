/*
 * Dijkstra's Algorithm Practice Question
 * 
 * Problem Statement:
 * You are planning a road trip across a country with several cities. Each direct road between 
 * cities has a specific travel time (in hours). You want to find the shortest (minimum time) 
 * path from your starting city to your destination city.
 * 
 * Given:
 * - A graph representing cities and roads between them
 * - Each road has a positive travel time (weight)
 * - There are no negative weights (no time travel!)
 * - The graph is directed (you can only travel in one direction on some roads)
 * - The graph has no cycles that would create infinite loops
 * 
 * Task:
 * Implement Dijkstra's algorithm to find the shortest path (minimum total travel time)
 * from the starting city (0) to the destination city (5).
 * 
 * Also print the actual path taken (sequence of cities) from start to destination.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <utility> // for pair
#include <stack>   // for reconstructing the path
#include <algorithm>

using namespace std;

// Graph representation using adjacency list
class Graph {
private:
    int V; // Number of vertices (cities)
    vector<vector<pair<int, int>>> adj; // adjacency list: pair<destination, weight>

public:
    // Constructor
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    // Add an edge (road) from city u to city v with travel time w
    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
    }

    // TODO: Implement Dijkstra's algorithm
    void shortestPath(int src, int dest) {

        vector<int> dist(V, INT_MAX);
        vector<int> prev(V, -1);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

        dist[src] = 0;
        pq.push({0, src}); // {distance, vertices}

        while (!pq.empty()){
            int u = pq.top().second;
            pq.pop();

            for (auto [v,w] : adj[u]){
                if (dist[u] + w < dist[v]){
                    dist[v] = dist[u] + w;
                    prev[v] = u; //紀錄點
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[dest] == INT_MAX) {
            cout << "No path.\n";
            return;
        }

        // 印出最短時間
        cout << "Shortest travel time: " << dist[dest] << " hours\n";

        // 回溯路徑
        vector<int> path;
        for (int at = dest; at != -1; at = prev[at])
            path.push_back(at);
        reverse(path.begin(), path.end());

        cout << "Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
};
/*
void define_the_map(Graph& g){
    
    cout<<"Enter the edges: (u, v, w)";

}
    */
int main() {
    // Create graph with 6 cities (labeled 0 to 5)
    /*
    int v;
    cout<<"Please Enter the number of city.";
    cin>>v;
    Graph g(v);
    
    define_the_map(g); */

    Graph g(6);

    // Add roads with travel times (directed edges with weights)
    g.addEdge(0, 1, 2);  // From city 0 to city 1, travel time: 2 hours
    g.addEdge(0, 2, 4);  // From city 0 to city 2, travel time: 4 hours
    g.addEdge(1, 2, 1);  // From city 1 to city 2, travel time: 1 hour
    g.addEdge(1, 3, 7);  // From city 1 to city 3, travel time: 7 hours
    g.addEdge(2, 4, 3);  // From city 2 to city 4, travel time: 3 hours
    g.addEdge(3, 5, 1);  // From city 3 to city 5, travel time: 1 hour
    g.addEdge(4, 3, 2);  // From city 4 to city 3, travel time: 2 hours
    g.addEdge(4, 5, 5);  // From city 4 to city 5, travel time: 5 hours
    
    // Find the shortest path from city 0 (start) to city 5 (destination)
    cout << "Shortest path from city 0 to city 5:" << endl;
    g.shortestPath(0, 5);
    
    return 0;
}

/*
 * Student Task:
 * 
 * 1. Implement the shortestPath method using Dijkstra's algorithm
 * 2. Your implementation should:
 *    - Calculate the minimum travel time from src to dest
 *    - Print the sequence of cities in the shortest path
 *    - Handle edge cases (e.g., no path exists)
 * 
 * Expected output format:
 * - Shortest travel time: X hours
 * - Path: 0 -> 1 -> ... -> 5
 * 
 * Optional challenge:
 * - Modify the implementation to handle different start and destination cities as user input
 * - Visualize the graph and the shortest path
 */
