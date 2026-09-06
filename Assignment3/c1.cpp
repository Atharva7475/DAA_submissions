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
        : name(n), weight(w), value(v), divisible(d), priority(p) {}

    double valuePerWeight() const {
        return value / weight;
    }
};

// Sort by priority first, then by value/weight
bool compare(const Item& a, const Item& b) {
    if (a.priority == b.priority) {
        return a.valuePerWeight() > b.valuePerWeight();
    }

    return a.priority < b.priority;
}

// Fractional Knapsack
double fractionalKnapsack(
    vector<Item>& items,
    double capacity,
    double& totalWeightCarried
) {
    // Sort items
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

    for (const auto& item : items) {

        if (capacity <= 0)
            break;

        // Divisible item
        if (item.divisible) {

            double takenWeight = min(item.weight, capacity);
            double takenValue = item.valuePerWeight() * takenWeight;

            totalValue += takenValue;
            capacity -= takenWeight;
            totalWeightCarried += takenWeight;

            cout << " - " << item.name
                 << ": " << takenWeight << " kg"
                 << ", Utility = " << takenValue
                 << ", Priority = " << item.priority
                 << ", Type = Divisible\n";
        }

        // Indivisible item
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

    // Create items
    vector<Item> items = {
        Item("Medical Kits", 10, 100, false, 1),
        Item("Food Packets", 20, 60, true, 3),
        Item("Drinking Water", 30, 90, true, 2),
        Item("Blankets", 15, 45, false, 3),
        Item("Infant Formula", 5, 50, false, 1)
    };

    double capacity;

    cout << "Enter maximum weight capacity of the boat (in kg): ";
    cin >> capacity;

    if (capacity <= 0) {
        cout << "Invalid capacity.\n";
        return 1;
    }

    double totalWeightCarried;

    double maxValue = fractionalKnapsack(
        items,
        capacity,
        totalWeightCarried
    );

    // Final report
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
