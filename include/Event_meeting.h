#ifndef EVENT_MEETING_H
#define EVENT_MEETING_H

#include <DateTime.h>
#include <Event.h>
#include <string>
#include <vector>

class Meeting : public Event
{
private:
    std::string location;
    std::vector<std::string> participants;

public:
    Meeting(const std::string &name, const std::string &description, const DateTime &dateTime,
            const std::string &location, const std::vector<std::string> &participants,
            int priority = 3, bool notification = false);

    void display() const override;

    const std::string &getLocation() const;
    void setLocation(const std::string &loc);

    const std::vector<std::string> &getParticipants() const;
    void setParticipants(const std::vector<std::string> &parts);
    void addParticipant(const std::string &participant);
    void removeParticipant(const std::string &participant);
};

#endif