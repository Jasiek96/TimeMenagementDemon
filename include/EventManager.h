#pragma once
#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <algorithm>
#include <iostream>

#include <Event.h>
#include <DateTime.h>

class EventManager
{

    std::vector<std::unique_ptr<Event>> events_;

public:
    using iterator = std::vector<std::unique_ptr<Event>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<Event>>::const_iterator;

    EventManager() = default;
    EventManager(const EventManager &) = delete;
    EventManager &operator=(const EventManager &) = delete;

    void add(std::unique_ptr<Event> ev);

    template <typename E, typename... Args>
    E &emplaceEvent(Args &&...args); // <- definicja TYLKO w .h

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    void list(std::ostream &os = std::cout) const;
    Event *findByName(const std::string &name);
    std::size_t removeIf(const std::function<bool(const Event &)> &pred);

    void sortByDate();
    void sortByName();
};
