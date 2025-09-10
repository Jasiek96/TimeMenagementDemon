#include <Event_task.h>
#include <iostream>

Task::Task(const std::string &name, const std::string &description, const DateTime &dateTime,
           int priority, bool notification)
    : Event(name, description, dateTime, priority, notification), completed(false) {}

void Task::markDone()
{
    completed = true;
}

bool Task::isCompleted() const
{
    return completed;
}

void Task::setCompleted(bool value)
{
    completed = value;
}

void Task::display() const
{
    std::cout << "Zadanie: " << getName() << " (" << getDescription() << ")\n";
    std::cout << "Data i czas: " << getEventDateTime().toString() << "\n";
    std::cout << "Priorytet: " << getPriority() << "\n";
    std::cout << "Powiadomienie: " << (hasNotification() ? "Tak" : "Nie") << "\n";
    std::cout << "Status: " << (completed ? "ukończone" : "nieukończone") << "\n";
}