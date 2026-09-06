#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

struct Item {
    string name;
    double weight;
    double value;
    bool divisible;
    int priority;

    Item(string n, double w, double v, bool d, int p)
        : name(n), weight(w), value(v), divisible(d), priority(p) {
    }

    double valuePerWeight() const {
        return value / weight;
    }
};

// Sort by priority first, then value/weight
bool compare(const Item& a, const Item& b) {

    if (a.priority == b.priority) {
        return a.valuePerWeight() > b.valuePerWeight();
    }

    return a.priority < b.priority;
}

// Fractional Knapsack Function
double fractionalKnapsack(
    vector<Item>& items,
    double capacity,
    double& totalWeightCarried
) {
    // Sort items using greedy criteria
    sort(items.begin(), items.end(), compare);

    cout << "\nSorted Items (by Priority, then Value/Weight):\n";

    cout << left
         << setw(20) << "Item"
         << setw(10) << "Weight"
         << setw(10) << "Value"
         << setw(12) << "Priority"
         << setw(15) << "Value/Weight"
         << setw(15) << "Type"
         << "\n";

    cout << string(82, '-') << "\n";

    // Display sorted items
    for (const auto& item : items) {

        cout << left
             << setw(20) << item.name
             << setw(10) << item.weight
             << setw(10) << item.value
             << setw(12) << item.priority
             << setw(15) << fixed << setprecision(2)
             << item.valuePerWeight()
             << setw(15)
             << (item.divisible ? "Divisible" : "Indivisible")
             << "\n";
    }

    double totalValue = 0.0;
    totalWeightCarried = 0.0;

    cout << "\nItems selected for transport:\n";

    // Select items
    for (const auto& item : items) {

        if (capacity <= 0)
            break;

        // If item is divisible
        if (item.divisible) {

            double takenWeight = min(item.weight, capacity);

            double takenValue =
                item.valuePerWeight() * takenWeight;

            totalValue += takenValue;
            capacity -= takenWeight;
            totalWeightCarried += takenWeight;

            cout << " - " << item.name
                 << ": " << takenWeight << " kg"
                 << ", Utility = " << takenValue
                 << ", Priority = " << item.priority
                 << ", Type = Divisible\n";
        }

        // If item is indivisible
        else {

            if (item.weight <= capacity) {

                totalValue += item.value;

                capacity -= item.weight;

                totalWeightCarried += item.weight;

                cout << " - " << item.name
                     << ": " << item.weight << " kg"
                     << ", Utility = " << item.value
                     << ", Priority = " << item.priority
                     << ", Type = Indivisible\n";
            }
        }
    }

    return totalValue;
}

int main() {

    int n;

    cout << "Enter number of relief items: ";
    cin >> n;

    vector<Item> items;

    // Input item details
    for (int i = 0; i < n; ++i) {

        string name;
        double weight;
        double value;
        int divisibleInt;
        int priority;

        cout << "\nItem #" << i + 1 << ":\n";

        cout << "Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Weight (kg): ";
        cin >> weight;

        cout << "Utility Value: ";
        cin >> value;

        cout << "Is it divisible? (1 = Yes, 0 = No): ";
        cin >> divisibleInt;

        cout << "Priority (1 = High, 2 = Medium, 3 = Low): ";
        cin >> priority;

        items.emplace_back(
            name,
            weight,
            value,
            divisibleInt == 1,
            priority
        );
    }

    double capacity;

    cout << "\nEnter maximum weight capacity of the boat (in kg): ";
    cin >> capacity;

    if (capacity <= 0) {
        cout << "Invalid boat capacity.\n";
        return 1;
    }

    double totalWeightCarried;

    double maxValue =
        fractionalKnapsack(
            items,
            capacity,
            totalWeightCarried
        );

    // Final Report
    cout << "\n===== Final Report =====\n";

    cout << "Total weight carried: "
         << fixed << setprecision(2)
         << totalWeightCarried
         << " kg\n";

    cout << "Total utility value carried: "
         << fixed << setprecision(2)
         << maxValue
         << " units\n";

    return 0;
}
