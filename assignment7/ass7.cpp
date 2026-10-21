
#include <bits/stdc++.h>
using namespace std;

int main() {

    // List of subjects
    vector<string> subjects = {
        "DAA", "AIML", "SPM", "EAC", "MDM-3"
    };

    // Colour name represents the exam slot
    vector<string> colourName = {
        "Blue", "Orange", "Green", "Red", "Purple",
        "Yellow", "Pink", "Brown", "Grey", "Cyan"
    };

    int n = subjects.size();
    int m;

    // Create graph
    vector<vector<int>> graph(n);

    cout << "Subjects:\n";

    for (int i = 0; i < n; i++) {
        cout << i << " - " << subjects[i] << "\n";
    }

    // Input number of conflicts
    cout << "\nEnter number of conflicts: ";
    cin >> m;

    cout << "Enter conflicting pairs (u v):\n";

    for (int i = 0; i < m; i++) {

        int u, v;
        cin >> u >> v;

        if (u < 0 || u >= n ||
            v < 0 || v >= n ||
            u == v) {

            cout << "Invalid conflict!\n";
            return 1;
        }

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // --------------------------------------------------
    // GREEDY GRAPH COLOURING
    // --------------------------------------------------

    vector<int> slot(n, -1);

    for (int u = 0; u < n; u++) {

        vector<bool> used(n + 1, false);

        // Check colours used by already coloured neighbours
        for (int v : graph[u]) {

            if (slot[v] != -1) {
                used[slot[v]] = true;
            }
        }

        // Find the smallest available colour
        int c = 0;

        while (used[c]) {
            c++;
        }

        slot[u] = c;
    }

    // Number of exam slots required
    int totalSlots =
        *max_element(slot.begin(), slot.end()) + 1;

    // --------------------------------------------------
    // DISPLAY GRAPH COLOURING RESULT
    // --------------------------------------------------

    cout << "\n----- GRAPH COLOURING RESULT -----\n";

    cout << left
         << setw(10) << "Vertex"
         << setw(10) << "Course"
         << setw(10) << "Colour#"
         << setw(10) << "Colour"
         << "Exam slot\n";

    cout << "--------------------------------------------------\n";

    for (int i = 0; i < n; i++) {

        string cname;

        if (slot[i] < (int)colourName.size()) {
            cname = colourName[slot[i]];
        }
        else {
            cname = "C" + to_string(slot[i] + 1);
        }

        cout << left
             << setw(10) << i
             << setw(10) << subjects[i]
             << setw(10) << slot[i] + 1
             << setw(10) << cname
             << "Slot " << slot[i] + 1
             << "\n";
    }

    cout << "\nColours used (chromatic number found): "
         << totalSlots << "\n";

    // --------------------------------------------------
    // VERIFY COLOURING
    // --------------------------------------------------

    bool valid = true;

    for (int u = 0; u < n; u++) {

        for (int v : graph[u]) {

            if (slot[u] == slot[v]) {
                valid = false;
            }
        }
    }

    cout << "Colouring check: "
         << (valid
             ? "VALID (no adjacent vertices share a colour)"
             : "INVALID")
         << "\n";

    // --------------------------------------------------
    // ROOM INFORMATION
    // --------------------------------------------------

    int roomCount;

    cout << "\nEnter number of rooms: ";
    cin >> roomCount;

    vector<int> capacity(roomCount);

    cout << "Enter capacity of each room:\n";

    for (int &c : capacity) {
        cin >> c;
    }

    // --------------------------------------------------
    // STUDENT COUNT
    // --------------------------------------------------

    vector<int> students(n);

    cout << "\nEnter student count for "
         << "DAA, AIML, SPM, EAC, MDM-3:\n";

    for (int &s : students) {
        cin >> s;
    }

    // --------------------------------------------------
    // GENERATE EXAM TIMETABLE
    // --------------------------------------------------

    cout << "\n----- EXAM TIMETABLE -----\n";

    for (int t = 0; t < totalSlots; t++) {

        string cname;

        if (t < (int)colourName.size()) {
            cname = colourName[t];
        }
        else {
            cname = "C" + to_string(t + 1);
        }

        cout << "\nSlot " << t + 1
             << " (" << cname << "):\n";

        // Track rooms already assigned in this slot
        vector<bool> occupied(roomCount, false);

        // Process every subject
        for (int i = 0; i < n; i++) {

            if (slot[i] != t) {
                continue;
            }

            int chosen = -1;

            // Find the smallest suitable room
            for (int r = 0; r < roomCount; r++) {

                if (!occupied[r] &&
                    capacity[r] >= students[i] &&
                    (chosen == -1 ||
                     capacity[r] < capacity[chosen])) {

                    chosen = r;
                }
            }

            cout << subjects[i]
                 << " (" << students[i]
                 << " students) - ";

            if (chosen == -1) {

                cout << "NO SUITABLE ROOM\n";

            }
            else {

                occupied[chosen] = true;

                cout << "Room "
                     << chosen + 1
                     << " (Capacity: "
                     << capacity[chosen]
                     << ")\n";
            }
        }
    }

    // --------------------------------------------------
    // FINAL RESULT
    // --------------------------------------------------

    cout << "\nTotal exam slots: "
         << totalSlots
         << "\n";

    return 0;
}

