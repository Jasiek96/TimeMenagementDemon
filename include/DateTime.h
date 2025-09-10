#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <string>

class InvalidDateTimeException : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Niepoprawna data lub czas.";
    }
};

class DateTime
{
private:
    int day, month, year;
    int hour, minute, second;

public:
    // Constructors
    DateTime();
    DateTime(int day, int month, int year, int hour = 0, int minute = 0, int second = 0);
    DateTime(const DateTime &dt);
    ~DateTime();

    // Getters
    int get_day() const;
    int get_month() const;
    int get_year() const;
    int get_hour() const;
    int get_minute() const;
    int get_second() const;

    // Convert to string
    std::string toDateString() const;
    std::string toTimeString() const;
    std::string toString() const;

    // Display
    void display_date() const;
    void display_time() const;
    void display() const;

    // Convert From String
    static DateTime fromString(const std::string &dateTimeStr);

    // Setters
    void set_date(int day, int month, int year);
    void set_time(int hour, int minute, int second = 0);
    void set_date_time(int day, int month, int year, int hour = 0, int minute = 0, int second = 0);

    // Validation
    bool isValid() const;
    bool isValid_Date() const;
    bool isValid_Time() const;

    // Comparision
    bool operator==(const DateTime &dt) const;
    bool operator!=(const DateTime &dt) const;
    bool operator<(const DateTime &dt) const;
    bool operator>(const DateTime &dt) const;
    DateTime &operator=(const DateTime &dt);
    // Stream
    friend std::ostream &operator<<(std::ostream &os, const DateTime &dt);
    friend std::istream &operator>>(std::istream &is, DateTime &dt);
};

#endif
