#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <string>

class InvalidDateTimeException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Niepoprawna data lub czas.";
        }
    };

class DateTime {
private:
    int day, month, year;
    int hour, minute, second;

public:
    //  Konstruktory
    DateTime();  // Aktualna data i czas
    DateTime(int day, int month, int year, int hour = 0, int minute = 0, int second = 0);
    DateTime(const DateTime& dt); // Konstruktor kopiujący
    ~DateTime();  // Destruktor

    //  Gettery (z `const`)
    int get_day() const;
    int get_month() const;
    int get_year() const;
    int get_hour() const;
    int get_minute() const;
    int get_second() const;

    //  Konwersja na stringi
    std::string toDateString() const;
    std::string toTimeString() const;
    std::string toString() const;  // Pełna data + czas

    //wyświetlanie 
    void display_date() const;
    void display_time() const;
    void display() const;

    //  Konwersja z stringa
    static DateTime fromString(const std::string& dateTimeStr);

    //  Settery
    void set_date(int day, int month, int year);
    void set_time(int hour, int minute, int second = 0);
    void set_date_time(int day, int month, int year, int hour = 0, int minute = 0, int second = 0);

    //  Walidacja daty
    bool isValid() const;
    bool isValid_Date() const;
    bool isValid_Time() const;

    //  Operatory porównania
    bool operator==(const DateTime& dt) const;
    bool operator!=(const DateTime& dt) const;
    bool operator<(const DateTime& dt) const;
    bool operator>(const DateTime& dt) const;

    //  Operatory strumieniowe
    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);
    friend std::istream& operator>>(std::istream& is, DateTime& dt);

    //  Operator przypisania
    DateTime& operator=(const DateTime& dt);

};

#endif // DATETIME_H
