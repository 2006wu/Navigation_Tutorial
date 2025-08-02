/*
 * A* Algorithm Practice Question
 * 
 * Problem Statement:
 * You are planning a road trip across a country with several cities. Each direct road between 
 * cities has a specific travel time (in hours). You also know the straight-line distance from
 * each city to the destination (as the crow flies), which can be used as a heuristic.
 * You want to find the shortest (minimum time) path from your starting city to your destination city.
 * 
 * Given:
 * - A graph representing cities and roads between them
 * - Each road has a positive travel time (weight)
 * - There are no negative weights (no time travel!)
 * - The graph is directed (you can only travel in one direction on some roads)
 * - The graph has no cycles that would create infinite loops
 * - For each city, you know the straight-line distance to the destination (heuristic)
 * 
 * Task:
 * Implement the A* algorithm to find the shortest path (minimum total travel time)
 * from the starting city (0) to the destination city (5).
 * 
 * Also print the actual path taken (sequence of cities) from start to destination.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility> // for pair
#include <stack>   // for reconstructing the path
#include <climits>

using namespace std;

// Graph representation using adjacency list
class Graph {
private:
    int V; // Number of vertices (cities)
    vector<vector<pair<int, int>>> adj; // adjacency list: pair<destination, weight>
    vector<int> heuristic; // heuristic values (estimated distance to destination)

public:
    // Constructor
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
        heuristic.resize(V);
    }

    // Add an edge (road) from city u to city v with travel time w
    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
    }

    // Set heuristic value for a city (estimated distance to destination)
    void setHeuristic(int city, int h) {
        heuristic[city] = h;
    }

    // TODO: Implement A* algorithm
    void aStarSearch(int src, int dest) {
        // Your implementation goes here
        // 1. Create a priority queue for vertices being processed
        // 2. Create arrays for g_score (actual distance from start)
        //    and f_score (g_score + heuristic)
        // 3. Initialize all g_scores as INFINITE and src g_score as 0
        // 4. Process vertices in order of their f_score (not just distance)
        // 5. Reconstruct and print the shortest path from src to dest

        using pii = pair<int, int>; // typedef pair<int, int> pii; 把最小的城市放在前面 <fScore, city>
        priority_queue<pii, vector<pii>, greater<pii>> Set;

        vector<int> gScore(V, INT_MAX);
        vector<int> fScore(V, INT_MAX);
        vector<int> From(V, -1); // notes every vertices where are you from

        gScore[src] = 0;
        fScore[src] = heuristic[src];

        Set.push({fScore[src], src});

        while(!Set.empty()){
            int current = Set.top().second;
            Set.pop();

            if (current == dest){ // find destination, backtrack the path
                stack<int> path;
                int temp = dest;
                while (temp != -1){
                    path.push(temp);
                    temp = From[temp];
                }

                cout << "Shortest travel time " << gScore[dest] << " hours." << endl;
                cout << "Path: ";
                while (!path.empty()){
                    cout << path.top();
                    path.pop();
                    if (!path.empty()){
                        cout << " -> ";
                    }
                }
                cout << endl;
                return;
            }

            for (auto neighborPair : adj[current]){
                int neighbor = neighborPair.first;
                int weight = neighborPair.second;

                int temp_gScore = gScore[current] + weight;

                if (temp_gScore < gScore[neighbor]){
                    From[neighbor] = current;
                    gScore[neighbor] = temp_gScore;
                    fScore[neighbor] = temp_gScore + heuristic[neighbor];
                    Set.push({fScore[neighbor], neighbor});
                }
            }
        }

        cout << "No path exists from " << src << " to " << dest << "." << endl;
    }
};

int main() {
    // Create graph with 6 cities (labeled 0 to 5)
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
    
    // Set heuristic values (straight-line distance to destination city 5)
    g.setHeuristic(0, 10);  // Estimated distance from city 0 to destination
    g.setHeuristic(1, 8);   // Estimated distance from city 1 to destination
    g.setHeuristic(2, 6);   // Estimated distance from city 2 to destination
    g.setHeuristic(3, 1);   // Estimated distance from city 3 to destination
    g.setHeuristic(4, 4);   // Estimated distance from city 4 to destination
    g.setHeuristic(5, 0);   // Destination city (distance to itself is 0)
    
    // Find the shortest path from city 0 (start) to city 5 (destination)
    cout << "A* search from city 0 to city 5:" << endl;
    g.aStarSearch(0, 5);
    
    return 0;
}

/*
 * Student Task:
 * 
 * 1. Implement the aStarSearch method using the A* algorithm
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
 * - Compare the performance of A* with Dijkstra's algorithm on the same graph
 * - Experiment with different heuristic values and observe how they affect the search
 */
