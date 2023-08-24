#include "util.h"

std::chrono::system_clock::time_point get_date() {
    std::regex date_regex(R"((\d{4})-(\d{2})-(\d{2}))");
    while (true) {
        std::cout << "Enter date (YYYY-MM-DD): ";
        std::string date;
        std::cin >> date;
        if (std::regex_match(date, date_regex)) {
            int year = std::stoi(date.substr(0, 4));
            if (year <2023 || year > 2030) {
                std::cout << "Invalid year. Please enter a year between 2023 and 2030." << std::endl;
                continue;
            }
            int month = std::stoi(date.substr(5, 2));
            if (month < 1 || month > 12) {
                std::cout << "Invalid month. Please enter a month between 1 and 12." << std::endl;
                continue;
            }
            int day = std::stoi(date.substr(8, 2));
            if (day < 1 || day > 31) {
                std::cout << "Invalid day. Please enter a day between 1 and 31." << std::endl;
                continue;
            }

            std::tm time_info{};
            time_info.tm_year = year - 1900;
            time_info.tm_mon = month - 1;
            time_info.tm_mday = day;

            std::time_t time_stamp = std::mktime(&time_info);
            return std::chrono::system_clock::from_time_t(time_stamp);
        }
        else {
            std::cout << "Invalid date format. Please enter in YYYY-MM-DD format." << std::endl;
        }
    }
}

//std::string get_printable_date(std::chrono::system_clock::time_point date) {
//    std::time_t timestamp = std::chrono::system_clock::to_time_t(date);
//    std::tm* time_info = std::localtime(&timestamp);
//
//    std::ostringstream oss;
//    oss << std::put_time(time_info, "%Y-%m-%d");
//    return oss.str();
//}
std::string get_printable_date(std::chrono::system_clock::time_point date) {
    std::time_t timestamp = std::chrono::system_clock::to_time_t(date);
    std::tm time_info{};

#ifdef _WIN32
    localtime_s(&time_info, &timestamp);
#else
    localtime_r(&timestamp, &time_info);
#endif

    std::ostringstream oss;
    oss << std::put_time(&time_info, "%Y-%m-%d");
    return oss.str();
}



