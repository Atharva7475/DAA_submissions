
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

struct Node {
    vector<vector<int>> mat;
    vector<int> path;
    int bound;
};

struct Compare {
    bool operator()(const Node &a, const Node &b) const {
        return a.bound > b.bound;
    }
};

int reduceMatrix(vector<vector<int>> &a) {
    int n = a.size();
    int reduction = 0;

    // Row reduction
    for (int i = 0; i < n; i++) {
        int mn = *min_element(a[i].begin(), a[i].end());

        if (mn == INF)
            continue;

        reduction += mn;

        for (int j = 0; j < n; j++) {
            if (a[i][j] != INF)
                a[i][j] -= mn;
        }
    }

    // Column reduction
    for (int j = 0; j < n; j++) {
        int mn = INF;

        for (int i = 0; i < n; i++)
            mn = min(mn, a[i][j]);

        if (mn == INF)
            continue;

        reduction += mn;

        for (int i = 0; i < n; i++) {
            if (a[i][j] != INF)
                a[i][j] -= mn;
        }
    }

    return reduction;
}

int main() {
    int n;

    cout << "Enter number of cities: ";
    cin >> n;

    if (n < 2)
        return 0;

    vector<vector<int>> cost(n, vector<int>(n));

    cout << "Enter cost matrix (0 for no road):\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];

            if (i == j || cost[i][j] <= 0)
                cost[i][j] = INF;
        }
    }

    // Initialize root node
    Node root{cost, {0}, 0};
    root.bound = reduceMatrix(root.mat);

    priority_queue<Node, vector<Node>, Compare> pq;
    pq.push(root);

    int best = INF;
    vector<int> answer;

    // Branch and Bound
    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.bound >= best)
            continue;

        int u = cur.path.back();

        // Check if all cities have been visited
        if ((int)cur.path.size() == n) {
            if (cost[u][0] == INF)
                continue;

            int total = cost[u][0];

            for (int k = 1; k < n; k++) {
                total += cost[cur.path[k - 1]][cur.path[k]];
            }

            if (total < best) {
                best = total;
                answer = cur.path;
            }

            continue;
        }

        // Explore unvisited cities
        for (int v = 1; v < n; v++) {
            if (find(cur.path.begin(), cur.path.end(), v)
                != cur.path.end())
                continue;

            if (cur.mat[u][v] == INF)
                continue;

            Node child = cur;
            child.path.push_back(v);

            child.bound += cur.mat[u][v];

            // Remove the outgoing edges from current city
            for (int j = 0; j < n; j++)
                child.mat[u][j] = INF;

            // Remove incoming edges to the next city
            for (int i = 0; i < n; i++)
                child.mat[i][v] = INF;

            // Prevent returning to the source before visiting all cities
            if ((int)child.path.size() < n)
                child.mat[v][0] = INF;

            child.bound += reduceMatrix(child.mat);

            if (child.bound < best)
                pq.push(child);
        }
    }

    // Display the result
    if (best == INF) {
        cout << "No possible tour\n";
    } else {
        cout << "\nMinimum cost: " << best << "\n";
        cout << "Route: ";

        for (int v : answer)
            cout << v << " -> ";

        cout << "0\n";
    }

    return 0;
}

