
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Road {
    int to;    // Next city
    int cost;  // Delivery cost of this road
};

const int INF = 1000000;

// Cities are numbered stage by stage: 0 = source, 9 = destination
string cityName[] = {
    "Warehouse", "Hub-A", "Hub-B", "Hub-C", "Zone-D",
    "Zone-E", "Zone-F", "Depot-G", "Depot-H", "Customer"
};

// Finds the cheapest route to the destination using Dynamic Programming
void findBestRoute(vector<vector<Road>>& graph) {
    int n = graph.size();

    vector<int> dp(n, INF);
    vector<int> next(n, -1);

    // Destination to destination costs nothing
    dp[n - 1] = 0;

    // Calculate minimum costs backwards
    for (int u = n - 2; u >= 0; u--) {
        for (Road r : graph[u]) {
            if (dp[r.to] != INF &&
                r.cost + dp[r.to] < dp[u]) {
                dp[u] = r.cost + dp[r.to];
                next[u] = r.to;
            }
        }
    }

    // Display the minimum cost table
    cout << "City          Cheapest Cost    Next City\n";
    cout << "-----------------------------------------------\n";

    for (int u = 0; u < n; u++) {
        cout << cityName[u]
             << string(14 - cityName[u].size(), ' ')
             << dp[u]
             << string(17 - to_string(dp[u]).size(), ' ')
             << (next[u] == -1 ? "-" : cityName[next[u]])
             << "\n";
    }

    // Display the optimal route
    cout << "\nBest route: ";

    for (int u = 0; u != -1; u = next[u]) {
        cout << cityName[u];

        if (next[u] != -1) {
            cout << " -> ";
        }
    }

    cout << "\nTotal cost: " << dp[0] << "\n";
}

int main() {
    vector<vector<Road>> graph(10);

    // Stage 1 -> Stage 2
    graph[0] = {{1, 4}, {2, 3}, {3, 5}};

    // Stage 2 -> Stage 3
    graph[1] = {{4, 3}, {5, 6}};
    graph[2] = {{4, 7}, {5, 2}, {6, 4}};
    graph[3] = {{5, 3}, {6, 5}};

    // Stage 3 -> Stage 4
    graph[4] = {{7, 6}, {8, 2}};
    graph[5] = {{7, 4}, {8, 5}};
    graph[6] = {{7, 3}, {8, 6}};

    // Stage 4 -> Stage 5
    graph[7] = {{9, 5}};
    graph[8] = {{9, 3}};

    // Find the cheapest route under normal conditions
    cout << "===== Normal Conditions =====\n";
    findBestRoute(graph);

    // Update road cost due to traffic
    // Hub-A -> Zone-D: cost changes from 3 to 10
    graph[1][0].cost = 10;

    // Find the cheapest route after the traffic update
    cout << "\n===== After Traffic Update =====\n";
    cout << "Hub-A -> Zone-D cost = 10\n";

    findBestRoute(graph);

    return 0;
}

