// COMSC-210 || Lab 29 | Ibrahim Bello
// BelloCorp Workforce Simulation
// Data Structures Project - Pseudocode & Wireframe
#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <list>
#include <string>
using namespace std;
const int ARR_SIZE = 3;
void displayDepartment(string , array<list<string>, ARR_SIZE> );

void hiringEvent(map<string, array<list<string>, ARR_SIZE>>& , string );

void layoffEvent(map<string, array<list<string>, ARR_SIZE>>& , string );

int main()
{
    // --------------------------------------------------------
    // STEP 1: Declare the main data structure
    // A map where:
    //   Key   = department name (string)
    //   Value = array of 3 lists (Managers, Entry-Level, Interns)
    // --------------------------------------------------------
    map<string, array<list<string>, ARR_SIZE>> workforce;

    // --------------------------------------------------------
    // STEP 2: Open the external data file
    // --------------------------------------------------------
    // // Open the file (e.g., "employees.txt") using ifstream
    // // If the file does not open successfully, print an error and exit

    // --- WIREFRAME: simulate file reading with one dummy entry ---
    ifstream fin("employees.txt");
    if (!fin)
    {
        cout << "[WARNING] Could not open employees.txt. Running with dummy data." << endl;

        // Dummy data: one department entry to prove the data structure works
        workforce["Sales"][0].push_back("Alice_Manager");      // Manager
        workforce["Sales"][1].push_back("Bob_EntryLevel");     // Entry-Level
        workforce["Sales"][2].push_back("Carol_Intern");       // Intern
    }

    // --------------------------------------------------------
    // STEP 3: Read data from file and populate the map
    // --------------------------------------------------------
    // // While there are still lines to read from the file:
    // //   Read: department name, employee type (0/1/2), employee name
    // //   Insert the employee name into workforce[dept][type]
    // // Close the file after reading

    // --------------------------------------------------------
    // STEP 4: Display INITIAL STATE of BelloCorp
    // --------------------------------------------------------
    cout << "============================================" << endl;
    cout << "   BELLOCORP WORKFORCE - INITIAL STATE     " << endl;
    cout << "============================================" << endl;

    // // Iterate through each entry in the map
    // // For each department, call displayDepartment()

    // --- WIREFRAME ---
    for (auto it = workforce.begin(); it != workforce.end(); it++)
    {
        displayDepartment(it->first, it->second);
    }

    // --------------------------------------------------------
    // STEP 5: Run the discrete-event simulation (25 time periods)
    // --------------------------------------------------------
    // // For each time period from 1 to 25:
    // //   Print the current time period number
    // //   Randomly select a department from the map
    // //   Randomly decide which event occurs:
    // //     0 = No event (quiet period)
    // //     1 = Hiring Surge -> call hiringEvent()
    // //     2 = Layoff       -> call layoffEvent()

    cout << "\n============================================" << endl;
    cout << "       RUNNING SIMULATION (25 PERIODS)      " << endl;
    cout << "============================================" << endl;

    // --- WIREFRAME: run just 3 dummy periods to show simulation flow ---
    for (int period = 1; period <= 3; period++)
    {
        cout << "\n--- Time Period " << period << " ---" << endl;

        // // [In full implementation] pick random dept & random event
        // Dummy: alternate between hiring and layoff on "Sales"
        if (period % 2 == 1)
        {
            hiringEvent(workforce, "Sales");
        }
        else
        {
            layoffEvent(workforce, "Sales");
        }
    }

    // --------------------------------------------------------
    // STEP 6: Display FINAL STATE of BelloCorp after simulation
    // --------------------------------------------------------
    cout << "\n============================================" << endl;
    cout << "    BELLOCORP WORKFORCE - FINAL STATE       " << endl;
    cout << "============================================" << endl;

    // // Iterate through the map again and call displayDepartment() for each

    // --- WIREFRAME ---
    for (auto it = workforce.begin(); it != workforce.end(); it++)
    {
        displayDepartment(it->first, it->second);
    }

    return 0;
}

// FUNCTION: displayDepartment
// Purpose: Neatly print all employees in a given department,
//          organized by their type (Manager, Entry-Level, Intern)
// Parameters: department name (string), array of three lists (employees by type)

void displayDepartment(string deptName, array<list<string>, ARR_SIZE> employees) {
    // // Print the department name as a header

    // // Print each of the three employee type categories:
    // //   Index 0 = Managers, Index 1 = Entry-Level, Index 2 = Interns

    // // For each category, iterate through the list and print each employee name

    // --- WIREFRAME (dummy output to demonstrate function works) ---
    cout << "=== Department: " << deptName << " ===" << endl;
    cout << "  Managers:     [list of manager names]" << endl;
    cout << "  Entry-Level:  [list of entry-level names]" << endl;
    cout << "  Interns:      [list of intern names]" << endl;
}

// FUNCTION: hiringEvent
// Purpose: Simulate a hiring surge by adding employees to a department
// Parameters: reference to the map (so changes persist), department name (string)

void hiringEvent(map<string, array<list<string>, ARR_SIZE>>& workforce, string dept) {
    // // Randomly determine how many employees to hire (e.g., between 1 and 5)

    // // Randomly determine which employee type to hire (0=Manager, 1=Entry-Level, 2=Intern)

    // // Add that many new employee names to the correct list in the department's array

    // // Print a message announcing the hiring event, e.g.:
    // //   "HIRING SURGE in [dept]: Added [n] new [type] employee(s)."

    // --- WIREFRAME (dummy output to demonstrate function works) ---
    cout << "[EVENT] Hiring Surge in " << dept << ": Added 3 new Entry-Level employee(s)." << endl;
    workforce[dept][1].push_back("New_Hire_Dummy");  // dummy: add one name to entry-level list
}

// FUNCTION: layoffEvent
// Purpose: Simulate a layoff by removing employees from a department
// Parameters: reference to the map, department name (string)

void layoffEvent(map<string, array<list<string>, ARR_SIZE>>& workforce, string dept) {
    // Randomly determine which employee type category to lay off from

    // Make sure the chosen list is not empty before removing

    // Randomly determine how many employees to remove (cannot exceed list size)

    // Remove that many employees from the list

    // Print a message announcing the layoff, e.g.:
    // "LAYOFF in [dept]: Removed [n] [type] employee(s)."

    // --- WIREFRAME (dummy output to demonstrate function works) ---
    cout << "[EVENT] Layoff in " << dept << ": Removed 1 Intern(s)." << endl;
    if (!workforce[dept][2].empty())
    {
        workforce[dept][2].pop_front();  // dummy: remove first intern
    }
}