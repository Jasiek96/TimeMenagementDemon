#include <Event_meeting.h>
#include <iostream>
#include <algorithm>

Meeting::Meeting(const std::string &name, const std::string &description, const DateTime &dateTime,
                 const std::string &location, const std::vector<std::string> &participants,
                 int priority, bool notification)
    : Event(name, description, dateTime, priority, notification), location(location), participants(participants) {}

void Meeting::display() const
{
    std::cout << "Spotkanie: " << getName() << " (" << getDescription() << ")\n";
    std::cout << "Data i czas: " << getEventDateTime().toString() << "\n";
    std::cout << "Miejsce: " << location << "\n";
    std::cout << "Uczestnicy: ";
    for (const auto &p : participants)
    {
        std::cout << p << ", ";
    }
    std::cout << "\n";
    std::cout << "Priorytet: " << getPriority() << "\n";
    std::cout << "Powiadomienie: " << (hasNotification() ? "Tak" : "Nie") << "\n";
}

const std::string &Meeting::getLocation() const
{
    return location;
}

void Meeting::setLocation(const std::string &loc)
{
    location = loc;
}

const std::vector<std::string> &Meeting::getParticipants() const
{
    return participants;
}

void Meeting::setParticipants(const std::vector<std::string> &parts)
{
    participants = parts;
}

void Meeting::addParticipant(const std::string &participant)
{
    participants.push_back(participant);
}

void Meeting::removeParticipant(const std::string &participant)
{
    auto it = std::remove(participants.begin(), participants.end(), participant);
    if (it != participants.end())
    {
        participants.erase(it, participants.end());
    }
}
