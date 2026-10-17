#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // Create list of goats
    list<Goat> trip;

    // Main menu loop
    do {
        int choice = main_menu();

        if (choice == 1) {
            add_goat(trip, names, colors);
        }
        else if (choice == 2) {
            delete_goat(trip);
        }
        else if (choice == 3) {
            display_trip(trip);
        }
        
        

        again = (choice != 4);
    }
    while (again);




    return 0;
}

// ***** FUNCTION DEFINITIONS *****

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice --> ";

    int choice;
    cin >> choice;

    while (choice < 1 || choice > 4) {
        cout << endl;
        cout << "Invalid choice. Try again: ";
        cin >> choice;
    }
    return choice;
}

void add_goat(list<Goat> &trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES];
    int age = rand() % (MAX_AGE + 1);
    string color = colors[rand() % SZ_COLORS];

    Goat newGoat(name, age, color);

    trip.push_back(newGoat);
}

void display_trip(list<Goat> trip) {
    int count = 1;

    for (const Goat& goat : trip) {
        cout << "[" << count << "]" << goat.get_name()
             << " (" << goat.get_age() << ", "
             << goat.get_color() << ")" << endl;

        count++;
    }
}

int select_goat(list<Goat> trip) {
    display_trip(trip);

    int choice;
    cout << "Select a goat --> ";
    cin >> choice;

    while (choice < 1 || choice > trip.size()) {
        cout << "Invalid choice. Try again ";
        cin >> choice;
    }

    return choice;
}

void delete_goat(list<Goat>& trip) {
    if(trip.empty()) {
        cout << "There are no goats to delete.\n";
        return;
    }

    int choice = select_goat(trip);

    auto it = trip.begin();

    for (int i = 1; i < choice; i++) {
        ++it;
    }

    trip.erase(it);
}