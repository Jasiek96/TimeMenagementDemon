#include <DateTime.h>
#include <Event.h>
#include <string>


//Konstruktory i destruktor
Event::Event() : name("NAME"), description("DESCRIPTION"), eventDateTime(DateTime()), priority(3), notification(false) {}

Event::Event(const std::string& name, const std::string& description, const DateTime& eventDateTime, int priority, bool notification)
    : name(name), description(description), eventDateTime(eventDateTime), priority(priority), notification(notification) {}
Event::Event(const Event& other)
    : name(other.name), description(other.description), eventDateTime(other.eventDateTime), priority(other.priority), notification(other.notification) {}
Event& Event::operator=(const Event& other) {
    if (this != &other){
        name = other.name;
        description = other.description;
        eventDateTime = other.eventDateTime;
        priority = other.priority;
        notification = other.notification;
    }
    return *this;
}
Event::~Event() {
    //std::cout << "Wydarzenie usunięte" << std::endl;
}

//Getery 
std::string Event::getName() const{
    return name;
}

std::string Event::getDescription() const {
    return description;
}

DateTime Event::getEventDateTime() const {
    return eventDateTime;
}
int Event::getPriority() const {
    return priority;
}
bool Event::hasNotification() const {
    return notification;
}
//Settery
void Event::setName(const std::string& name_i){
    name = name_i;
}
void Event::setDescription(const std::string& description_i) {
    description = description_i;
}
void Event::setEventDateTime(const DateTime& eventDateTime_i) {
    eventDateTime = eventDateTime_i;
}
void Event::setPriority(int priority_i) {
    if (priority_i <=5 && priority_i >= 1){
        priority = priority_i;
    }
    else{
        std::cerr << "Priorytet poza zakresem 1-5" << std::endl;
    }
}
void Event::setNotification(bool notification_i) {
    notification = notification_i;
}
// Metody pomocnicze
void Event::display() const {
    std::cout << "Nazwa: " << name << std::endl;
    std::cout << "Opis: " << description << std::endl;
    std::cout << "Data i czas wydarzenia: " << eventDateTime.toString() << std::endl;
    std::cout << "Priorytet: " << priority << std::endl;
    std::cout << "Powiadomienie: " << (notification ? "Tak" : "Nie") << std::endl;
}


