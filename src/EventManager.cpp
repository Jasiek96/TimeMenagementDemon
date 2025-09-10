#include <EventManager.h>

#include <algorithm>
#include <iostream>
#include <utility>

void EventManager::add(std::unique_ptr<Event> ev)
{
    events_.push_back(std::move(ev));
}

// Iterators
EventManager::iterator EventManager::begin() noexcept
{
    return events_.begin();
}

EventManager::iterator EventManager::end() noexcept
{
    return events_.end();
}

EventManager::const_iterator EventManager::begin() const noexcept
{
    return events_.begin();
}

EventManager::const_iterator EventManager::end() const noexcept
{
    return events_.end();
}

// Functions
void EventManager::list(std::ostream &os) const
{
    if (events_.empty())
    {
        os << "[Brak wydarzeń]\n";
        return;
    }
    for (const auto &ev : events_)
    {
        ev->display();
        os << '\n';
    }
}

Event *EventManager::findByName(const std::string &name)
{
    const auto it = std::find_if(events_.begin(), events_.end(),
                                 [&](const auto &ev)
                                 { return ev->getName() == name; });
    return (it != events_.end()) ? it->get() : nullptr;
}

std::size_t EventManager::removeIf(const std::function<bool(const Event &)> &pred)
{
    const auto oldSize = events_.size();
    events_.erase(std::remove_if(events_.begin(), events_.end(),
                                 [&](const auto &ev)
                                 { return pred(*ev); }),
                  events_.end());
    return oldSize - events_.size();
}

// Sorting
void EventManager::sortByDate()
{
    std::sort(events_.begin(), events_.end(),
              [](const auto &a, const auto &b)
              {
                  return a->getEventDateTime() < b->getEventDateTime();
              });
}

void EventManager::sortByName()
{
    std::sort(events_.begin(), events_.end(),
              [](const auto &a, const auto &b)
              {
                  return a->getName() < b->getName();
              });
}
