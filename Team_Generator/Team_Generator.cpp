/*
    How to use:
    1. Make a file called team.txt in the same folder as this program
    2. Enter all person's name in team.txt, one person one line. DON'T FORGET TO SAVE!
    3. Compile and run this program
*/

#include <bits/stdc++.h>
using namespace std;


vector<string> input() {
    ifstream file("team.txt");

    string personName;
    vector<string> names;
    while (getline(file, personName)) {
        names.push_back(personName);
    }

    return names;
}

int getTeamNumber(string choice, const vector<string> &names) {
    int n;
    if (choice == "a") {
        cout << "Number of teams: "; cin >> n;
    } else if (choice == "b") {
        int personPerTeam;
        cout << "Number of members per team: "; cin >> personPerTeam;
        n = names.size() / personPerTeam;
        if (names.size() % n > (n + 1) / 2) n += 1;
    }
        
    return n;
}

void outputRandom(vector<string> names, int n) {
    int personPerTeam = names.size() / n;
    int remainder = names.size() % n;

    int team = 0;
    while (team < n) {
        team++;
        if (team == n - remainder + 1) personPerTeam += 1;

        cout << "Team #" << team << ": ";
        for (int i = 1; i <= personPerTeam; i++) {
            int random = rand() % names.size();
            cout << names[random];
            names.erase(names.begin() + random);

            if (i < personPerTeam) cout << ", ";
        }
        cout << "\n";
    }
}

int main() {
    srand(time(NULL));

    bool repeat = true;
    vector<string> names = input();
    while (repeat) {
        cout    << "Choose input mode:\n"
                << "a. Number of teams\n"
                << "b. Number of members per team\n>>> ";
        string choice; cin >> choice;
        int n = getTeamNumber(choice, names);
        
        outputRandom(names, n);

        string ans;
        cout << "\nRegenerate team? (y/n)\n"; cin >> ans;
        if (ans != "y") repeat = false;
    }
    
    return 0;
}