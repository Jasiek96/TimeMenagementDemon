#include <DateTime.h>
#include <string>

#ifndef EVENT_H
#define EVENT_H

class Event {
private:
    std::string name;
    std::string description;
    DateTime eventDateTime; // data i czas wydarzenia poczatek
    int priority = 3; // 1-5, 1 - najniższy, 5 - najwyższy
    bool notification = false; // true - powiadomienie, false - brak powiadomienia
public:
    Event();
    Event(const std::string& name, const std::string& description, const DateTime& eventDateTime, int priority = 3, bool notification = false);
    Event(const Event& other); // konstruktor kopiujący
    Event& operator=(const Event& other); // operator przypisania
    ~Event(); // destruktor

    // Gettery
    std::string getName() const;
    std::string getDescription() const;
    DateTime getEventDateTime() const;
    int getPriority() const;
    bool hasNotification() const;

    // Settery
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setEventDateTime(const DateTime& eventDateTime);
    void setPriority(int priority);
    void setNotification(bool notification);

    // Metody pomocnicze
     virtual void display() const;  // wyświetlanie szczegółów wydarzenia

};
#endif // EVENT_H