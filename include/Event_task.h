#ifndef EVENT_TASK_H
#define EVENT_TASK_H

#include <DateTime.h>
#include <Event.h>
#include <string>

class Task : public Event
{
private:
    bool completed;

public:
    Task(const std::string &name, const std::string &description, const DateTime &dateTime,
         int priority = 3, bool notification = false);

    void markDone();
    bool isCompleted() const;
    void setCompleted(bool value);

    void display() const override;
};

#endif // EVENT_TASK_H