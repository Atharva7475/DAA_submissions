#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Movie {
    string title;
    float rating;
    int release_year;
    int popularity;

    void display() const {
        cout << title << " | Rating: " << rating
             << " | Year: " << release_year
             << " | Popularity: " << popularity << endl;
    }
};

// QuickSort with comparator function pointer
void quickSort(vector<Movie> &movies, int low, int high, bool (*compare)(const Movie &, const Movie &)) {
    if (low < high) {
        int pivotIndex = low;
        Movie pivot = movies[high];
        for (int i = low; i < high; i++) {
            if (compare(movies[i], pivot)) {
                swap(movies[i], movies[pivotIndex]);
                pivotIndex++;
            }
        }
        swap(movies[pivotIndex], movies[high]);
        quickSort(movies, low, pivotIndex - 1, compare);
        quickSort(movies, pivotIndex + 1, high, compare);
    }
}

// Comparators
bool compareByRating(const Movie &a, const Movie &b) {
    return a.rating < b.rating;
}
bool compareByYear(const Movie &a, const Movie &b) {
    return a.release_year < b.release_year;
}
bool compareByPopularity(const Movie &a, const Movie &b) {
    return a.popularity < b.popularity;
}

// Random movie generator
vector<Movie> generateMovies(int n) {
    vector<Movie> movies;
    for (int i = 0; i < n; i++) {
        Movie m;
        m.title = "Movie " + to_string(i + 1);
        m.rating = static_cast<float>(rand() % 90 + 10) / 10.0f; // 1.0 to 10.0
        m.release_year = rand() % 45 + 1980; // 1980 to 2024
        m.popularity = rand() % 1000000 + 1000; // 1,000 to 1,000,000
        movies.push_back(m);
    }
    return movies;
}

int main() {
    srand(time(0));
    int num_movies = 100000;
    vector<Movie> movies = generateMovies(num_movies);

    cout << "Sort movies by (rating/year/popularity): ";
    string sort_by;
    cin >> sort_by;

    bool (*compare)(const Movie &, const Movie &);
    if (sort_by == "rating")
        compare = compareByRating;
    else if (sort_by == "year")
        compare = compareByYear;
    else if (sort_by == "popularity")
        compare = compareByPopularity;
    else {
        cout << "Invalid choice. Defaulting to rating.\n";
        compare = compareByRating;
    }

    auto start = high_resolution_clock::now();
    quickSort(movies, 0, movies.size() - 1, compare);
    auto end = high_resolution_clock::now();
    duration<double> diff = end - start;

    // Show top 10 in descending order
    cout << "\nTop 10 movies by " << sort_by << ":\n";
    for (int i = num_movies - 1; i >= num_movies - 10; --i) {
        movies[i].display();
    }

    cout << "\nSorted " << num_movies << " movies in " << diff.count() << " seconds.\n";

    return 0;
}

