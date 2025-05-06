#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <sstream>

std::istringstream &operator>>(std::istringstream& f, int& num);

bool read_single_value_line(std::ifstream& f, int& value);

bool read_two_values_line(std::ifstream& f, Time& first, Time& second);

#endif