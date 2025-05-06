#include <sstream>

using namespace std;

istringstream &operator>>(istringstream& f, int& num) {
    string number;
    f >> number;

    try {
        num = stoi(number);
    }
    catch (...) {
        f.setstate(ios::failbit);
    }

    return f;
}