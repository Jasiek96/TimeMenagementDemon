#include <DateTime.h>
#include <string>

#ifndef EVENT_H
#define EVENT_H

class Event
{
    friend class EventManager;

private:
    std::string name;
    std::string description;
    DateTime eventDateTime;
    int priority = 3;
    bool notification = false;

public:
    Event();
    Event(const std::string &name, const std::string &description, const DateTime &eventDateTime, int priority = 3, bool notification = false);
    Event(const Event &other);
    Event &operator=(const Event &other);
    ~Event();

    // Getters
    std::string getName() const;
    std::string getDescription() const;
    DateTime getEventDateTime() const;
    int getPriority() const;
    bool hasNotification() const;

    // Getters
    void setName(const std::string &name);
    void setDescription(const std::string &description);
    void setEventDateTime(const DateTime &eventDateTime);
    void setPriority(int priority);
    void setNotification(bool notification);

    // Function
    virtual void display() const;
};
#endif