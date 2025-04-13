#include <DateTime.h>
#include <iomanip>  // std::setw, std::setfill
#include <sstream>  // std::ostringstream

DateTime::DateTime() { // Konstruktor domyślny - aktualna data i czas
    time_t now = time(0);
    tm* localtm = localtime(&now);
    day = localtm->tm_mday;
    month = localtm->tm_mon + 1; // Miesiące są indeksowane od 0
    year = localtm->tm_year + 1900;
    hour = localtm->tm_hour;
    minute = localtm->tm_min;
    second = localtm->tm_sec;
}

DateTime::DateTime(int year_i, int month_i, int day_i, int hour_i, int minute_i, int second_i)
    : day{day_i}, month{month_i}, year{year_i}, hour{hour_i}, minute{minute_i}, second{second_i} {
    if (!isValid()) {
        throw InvalidDateTimeException();  // Rzucenie wyjątku
    }
}

DateTime::DateTime(const DateTime& dt)
    : day{dt.day}, month{dt.month}, year{dt.year}, hour{dt.hour}, minute{dt.minute}, second{dt.second} {}

DateTime::~DateTime() {}

DateTime& DateTime::operator=(const DateTime& dt) {
    if (this != &dt) {
        day = dt.day;
        month = dt.month;
        year = dt.year;
        hour = dt.hour;
        minute = dt.minute;
        second = dt.second;
    }
    return *this;
}

// Gettery
int DateTime::get_day() const { return day; }
int DateTime::get_month() const { return month; }
int DateTime::get_year() const { return year; }
int DateTime::get_hour() const { return hour; }
int DateTime::get_minute() const { return minute; }
int DateTime::get_second() const { return second; }

// Konwersje do stringów
std::string DateTime::toDateString() const {
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << year << "-"
        << std::setw(2) << std::setfill('0') << month << "-"
        << std::setw(2) << std::setfill('0') << day;
    return oss.str();
}

std::string DateTime::toTimeString() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour << ":"
        << std::setw(2) << std::setfill('0') << minute << ":"
        << std::setw(2) << std::setfill('0') << second;
    return oss.str();
}

std::string DateTime::toString() const {
    return toDateString() + " " + toTimeString();
}

// Metody wyświetlające dane
void DateTime::display_date() const {
    std::cout << toDateString() << std::endl;
}

void DateTime::display_time() const {
    std::cout << toTimeString() << std::endl;
}

void DateTime::display() const {
    std::cout << toString() << std::endl;
}


void DateTime::set_date(int year_i, int month_i, int day_i) {
    day = day_i;
    month = month_i;
    year = year_i;
    if (!isValid_Date()){
        std::cerr << "Data nie poprawna" << std::endl;
        day = 1;
        month = 1;
        year = 1970;
    } 
}

void DateTime::set_time(int hour_i, int minute_i, int second_i) {
    hour = hour_i;
    minute = minute_i;
    second = second_i;
    if (!isValid_Time()){
        std::cerr << "Czas nie jest poprawny" << std::endl;
        hour = 0;
        minute = 0;
        second = 0;
    }
}
void DateTime::set_date_time(int year_i, int month_i, int day_i, int hour_i, int minute_i, int second_i) {
    set_date(year_i, month_i, day_i);
    set_time(hour_i, minute_i, second_i);

}
bool DateTime::isValid() const {
    return (isValid_Date() && isValid_Time());
}

bool DateTime::isValid_Date() const {
    if (year < 1970 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) { // Rok przestępny
            return day <= 29;
        } else {
            return day <= 28;
        }
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return day <= 30;
    }
    return true;
}
bool DateTime::isValid_Time()const {
    if (hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59){
        return false;
    }
    return true;
}
bool DateTime::operator==(const DateTime& dt) const {
    return (day == dt.day && month == dt.month && year == dt.year &&
            hour == dt.hour && minute == dt.minute && second == dt.second);
}
bool DateTime::operator!=(const DateTime& dt) const {
    return !(*this == dt);
}
bool DateTime::operator<(const DateTime& dt) const {
    if (year != dt.year) return year < dt.year;
    if (month != dt.month) return month < dt.month;
    if (day != dt.day) return day < dt.day;
    if (hour != dt.hour) return hour < dt.hour;
    if (minute != dt.minute) return minute < dt.minute;
    return second < dt.second;
}
bool DateTime::operator>(const DateTime& dt) const {
    return dt < *this;
}
std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
    os << dt.toString();
    return os;
}
std::istream& operator>>(std::istream& is, DateTime& dt) {
    std::string dateTimeStr;
    std::getline(is,dateTimeStr);
    try {
        dt = DateTime::fromString(dateTimeStr);
        if (!dt.isValid()) {
            throw std::invalid_argument("Niepoprawny format lub warości.");
        }
    } catch (const std::exception& e) {
        //std::cerr << "Error parsing DateTime: " << e.what() << std::endl;
        is.setstate(std::ios::failbit);
    }
    return is;
}
// Implementacja metody fromString
DateTime DateTime::fromString(const std::string& dateTimeStr) {
    int year_i, month_i, day_i, hour_i, minute_i, second_i;
    char delimiter1, delimiter2, delimiter3, delimiter4;

    std::string trimmedStr = dateTimeStr;
    trimmedStr.erase(0, trimmedStr.find_first_not_of("\t\n\r")); // Trim leading spaces
    trimmedStr.erase(trimmedStr.find_last_not_of("\t\n\r") + 1); // Trim trailing spaces

    std::istringstream iss(trimmedStr);
    if (!(iss >> year_i >> delimiter1 >> month_i >> delimiter2 >> day_i >>  hour_i >> delimiter3 >> minute_i >> delimiter4 >> second_i) ||
        delimiter1 != '-' || delimiter2 != '-' || delimiter3 != ':' || delimiter4 != ':') {
        throw std::invalid_argument("Invalid date-time format");
    }

    return DateTime(year_i, month_i, day_i, hour_i, minute_i, second_i);
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    switch(month) {
        case 2: return isLeapYear(year) ? 29 : 28;
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
    }
}
