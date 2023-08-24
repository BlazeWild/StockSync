#ifndef UTIL_H
#define UTIL_H

#pragma once
#include <iostream>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <regex>
#include <sstream>
#include <vector>
#include <filesystem>

std::chrono::system_clock::time_point get_date();
std::string get_printable_date(std::chrono::system_clock::time_point date);

#endif