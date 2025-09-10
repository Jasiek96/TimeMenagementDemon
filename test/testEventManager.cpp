#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

#include <EventManager.h>
#include <Event_task.h>
#include <Event_meeting.h>
#include <DateTime.h>

static DateTime makeDT(int y, int m, int d, int H, int M, int S = 0)
{
    return DateTime(y, m, d, H, M, S);
}

static std::unique_ptr<Event> makeTask(
    const std::string &name, const std::string &desc,
    const DateTime &dt, int priority = 3, bool notify = false)
{
    return std::make_unique<Task>(name, desc, dt, priority, notify);
}

static std::unique_ptr<Event> makeMeeting(
    const std::string &name, const std::string &desc,
    const DateTime &dt, const std::string &location,
    std::vector<std::string> attendees = {},
    int priority = 3, bool notify = false)
{
    return std::make_unique<Meeting>(name, desc, dt, location, attendees, priority, notify);
}

TEST(EventManager, AddAndFindByName)
{
    EventManager mgr;
    mgr.add(makeTask("Oddać projekt", "Zaliczenie OOP", makeDT(2025, 9, 12, 9, 0, 0)));
    mgr.add(makeMeeting("Standup", "Codzienny status", makeDT(2025, 9, 11, 10, 0, 0),
                        "Room 101", {"Ala", "Ola"}));

    Event *t = mgr.findByName("Oddać projekt");
    ASSERT_NE(nullptr, t);

    Event *m = mgr.findByName("Standup");
    ASSERT_NE(nullptr, m);

    Event *none = mgr.findByName("Nie ma takiego");
    ASSERT_EQ(nullptr, none);
}

TEST(EventManager, SortByDate)
{
    EventManager mgr;
    mgr.add(makeTask("T3", "najnowsze", makeDT(2025, 9, 13, 9, 0, 0)));
    mgr.add(makeTask("T1", "najstarsze", makeDT(2025, 9, 11, 9, 0, 0)));
    mgr.add(makeTask("T2", "środek", makeDT(2025, 9, 12, 9, 0, 0)));

    mgr.sortByDate();

    std::vector<std::string> names;
    for (auto &uptr : mgr)
        names.push_back(uptr->getName());

    ASSERT_EQ((std::vector<std::string>{"T1", "T2", "T3"}), names);
}

TEST(EventManager, SortByName)
{
    EventManager mgr;
    mgr.add(makeTask("Zebra", "z", makeDT(2025, 9, 12, 9, 0, 0)));
    mgr.add(makeTask("Ala", "a", makeDT(2025, 9, 11, 9, 0, 0)));
    mgr.add(makeTask("Marek", "m", makeDT(2025, 9, 10, 9, 0, 0)));

    mgr.sortByName();

    std::vector<std::string> names;
    for (auto &uptr : mgr)
        names.push_back(uptr->getName());

    ASSERT_EQ((std::vector<std::string>{"Ala", "Marek", "Zebra"}), names);
}

TEST(EventManager, RemoveIf_ByNamePrefix)
{
    EventManager mgr;
    mgr.add(makeTask("low_1", "", makeDT(2025, 9, 12, 9, 0, 0)));
    mgr.add(makeTask("high_1", "", makeDT(2025, 9, 13, 9, 0, 0)));
    mgr.add(makeTask("low_2", "", makeDT(2025, 9, 14, 9, 0, 0)));

    const auto removed = mgr.removeIf([](const Event &e)
                                      {
                                          const auto &n = e.getName();
                                          return n.rfind("low_", 0) == 0; // prefix
                                      });

    ASSERT_EQ(2u, removed);
    ASSERT_NE(nullptr, mgr.findByName("high_1"));
    ASSERT_EQ(nullptr, mgr.findByName("low_1"));
    ASSERT_EQ(nullptr, mgr.findByName("low_2"));
}

TEST(EventManager, IterationRangeFor_Count)
{
    EventManager mgr;
    mgr.add(makeTask("A", "", makeDT(2025, 9, 12, 9, 0, 0)));
    mgr.add(makeTask("B", "", makeDT(2025, 9, 11, 9, 0, 0)));
    mgr.add(makeTask("C", "", makeDT(2025, 9, 10, 9, 0, 0)));

    size_t count = 0;
    for (auto &e : mgr)
        (void)e, ++count;

    ASSERT_EQ(3u, count);
}

TEST(EventManager, List_PrintsEmptyMessage)
{
    EventManager mgr;
    std::ostringstream oss;
    mgr.list(oss);
    EXPECT_EQ("[Brak wydarzeń]\n", oss.str());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}