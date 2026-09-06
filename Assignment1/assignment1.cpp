#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Order {
    int orderID;
    long long timestamp;
};

// Merge two sorted parts
void merge(vector<Order>& orders, int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Order> L(n1);
    vector<Order> R(n2);

    // Copy data
    for (int i = 0; i < n1; i++)
        L[i] = orders[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = orders[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge according to timestamp
    while (i < n1 && j < n2) {

        if (L[i].timestamp <= R[j].timestamp) {
            orders[k] = L[i];
            i++;
        }
        else {
            orders[k] = R[j];
            j++;
        }

        k++;
    }

    // Copy remaining elements
    while (i < n1) {
        orders[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        orders[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort
void mergeSort(vector<Order>& orders, int left, int right) {

    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    // Sort left half
    mergeSort(orders, left, mid);

    // Sort right half
    mergeSort(orders, mid + 1, right);

    // Merge both halves
    merge(orders, left, mid, right);
}

int main() {

    int n;

    cout << "Enter number of orders: ";
    cin >> n;

    vector<Order> orders(n);

    // Input orders
    for (int i = 0; i < n; i++) {

        cout << "Enter Order ID and Timestamp: ";
        cin >> orders[i].orderID >> orders[i].timestamp;
    }

    // Sort orders
    mergeSort(orders, 0, n - 1);

    // Display sorted orders
    cout << "\nOrders sorted by timestamp:\n";

    cout << "Order ID\tTimestamp\n";

    for (const auto& order : orders) {
        cout << order.orderID << "\t\t"
             << order.timestamp << endl;
    }

    return 0;
}
