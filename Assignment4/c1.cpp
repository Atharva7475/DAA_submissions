#include <bits/stdc++.h>
using namespace std;

// Dijkstra's Algorithm
void dijkstra(
    int source,
    vector<vector<pair<int, int>>>& graph,
    vector<int>& dist
) {
    int V = graph.size();

    // Initialize distances
    dist.assign(V, INT_MAX);

    dist[source] = 0;

    // Min-priority queue
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    pq.push({0, source});

    while (!pq.empty()) {

        int d = pq.top().first;
        int u = pq.top().second;

        pq.pop();

        // Ignore outdated distance
        if (d > dist[u])
            continue;

        // Check all adjacent vertices
        for (auto& edge : graph[u]) {

            int v = edge.first;
            int w = edge.second;

            // Relaxation
            if (dist[v] > dist[u] + w) {

                dist[v] = dist[u] + w;

                pq.push({dist[v], v});
            }
        }
    }
}

int main() {

    int V, E;

    cout << "Enter number of intersections (vertices): ";
    cin >> V;

    cout << "Enter number of roads (edges): ";
    cin >> E;

    // Create graph
    vector<vector<pair<int, int>>> graph(V);

    cout << "Enter edges (u v w):\n";
    cout << "u = starting node, v = ending node, w = travel time\n";

    for (int i = 0; i < E; i++) {

        int u, v, w;

        cin >> u >> v >> w;

        // Undirected graph
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int source;

    cout << "Enter ambulance start location (source): ";
    cin >> source;

    int H;

    cout << "Enter number of hospitals: ";
    cin >> H;

    vector<int> hospitals(H);

    cout << "Enter hospital nodes: ";

    for (int i = 0; i < H; i++) {
        cin >> hospitals[i];
    }

    // Run Dijkstra
    vector<int> dist;

    dijkstra(source, graph, dist);

    // Find nearest hospital
    int minTime = INT_MAX;
    int nearestHospital = -1;

    for (int h : hospitals) {

        if (dist[h] < minTime) {

            minTime = dist[h];

            nearestHospital = h;
        }
    }

    // Display result
    if (nearestHospital == -1 || minTime == INT_MAX) {

        cout << "No hospital reachable.\n";
    }
    else {

        cout << "\n===== Result =====\n";

        cout << "Nearest hospital is at node "
             << nearestHospital
             << " with travel time "
             << minTime
             << " minutes.\n";
    }

    return 0;
}
