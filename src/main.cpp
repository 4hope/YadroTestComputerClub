#include "computer_club.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        throw runtime_error("Incorrect number of arguments");
    }

    string path{ argv[1] };
    ifstream f(path, ios::in);

    ComputerClub club;
    f >> club;
    if (f.fail()) return 0;

    if (club.simulate(f))
        cout << club;

    f.close();
    return 0;
}
