#include <gtest/gtest.h>
#include <Event_meeting.h>
#include <DateTime.h>
#include <sstream>
#include <vector>

TEST(MeetingTest, ConstructorAndGetters)
{
    DateTime dt(2023, 8, 15, 14, 30, 45);
    std::vector<std::string> participants = {"Anna", "Jan"};
    Meeting meeting("Spotkanie1", "Opis spotkania", dt, "Sala 101", participants, 4, true);
    EXPECT_EQ(meeting.getName(), "Spotkanie1");
    EXPECT_EQ(meeting.getDescription(), "Opis spotkania");
    EXPECT_EQ(meeting.getPriority(), 4);
    EXPECT_TRUE(meeting.hasNotification());
    EXPECT_EQ(meeting.getEventDateTime(), dt);
    EXPECT_EQ(meeting.getLocation(), "Sala 101");
    EXPECT_EQ(meeting.getParticipants().size(), 2);
    EXPECT_EQ(meeting.getParticipants()[0], "Anna");
}

TEST(MeetingTest, Setters)
{
    Meeting meeting("A", "B", DateTime(2023, 1, 1), "Miejsce", {}, 2, false);
    meeting.setName("Nowa nazwa");
    meeting.setDescription("Nowy opis");
    meeting.setPriority(5);
    meeting.setNotification(true);
    DateTime dt(2025, 12, 24, 10, 0, 0);
    meeting.setEventDateTime(dt);
    meeting.setLocation("Nowa sala");
    std::vector<std::string> parts = {"X", "Y"};
    meeting.setParticipants(parts);
    EXPECT_EQ(meeting.getName(), "Nowa nazwa");
    EXPECT_EQ(meeting.getDescription(), "Nowy opis");
    EXPECT_EQ(meeting.getPriority(), 5);
    EXPECT_TRUE(meeting.hasNotification());
    EXPECT_EQ(meeting.getEventDateTime(), dt);
    EXPECT_EQ(meeting.getLocation(), "Nowa sala");
    EXPECT_EQ(meeting.getParticipants().size(), 2);
}

TEST(MeetingTest, AddAndRemoveParticipants)
{
    Meeting meeting("A", "B", DateTime(2023, 1, 1), "Miejsce", {}, 2, false);
    meeting.addParticipant("Jan");
    meeting.addParticipant("Anna");
    EXPECT_EQ(meeting.getParticipants().size(), 2);
    meeting.removeParticipant("Jan");
    EXPECT_EQ(meeting.getParticipants().size(), 1);
    EXPECT_EQ(meeting.getParticipants()[0], "Anna");
}

TEST(MeetingTest, Display)
{
    std::vector<std::string> parts = {"Jan", "Anna"};
    Meeting meeting("Spotkanie2", "Opis2", DateTime(2024, 5, 10, 12, 0, 0), "Sala 202", parts, 3, true);
    std::ostringstream oss;
    std::streambuf *oldCout = std::cout.rdbuf(oss.rdbuf());
    meeting.display();
    std::cout.rdbuf(oldCout);
    std::string output = oss.str();
    EXPECT_NE(output.find("Spotkanie2"), std::string::npos);
    EXPECT_NE(output.find("Opis2"), std::string::npos);
    EXPECT_NE(output.find("Sala 202"), std::string::npos);
    EXPECT_NE(output.find("Jan"), std::string::npos);
    EXPECT_NE(output.find("Anna"), std::string::npos);
    EXPECT_NE(output.find("2024-05-10 12:00:00"), std::string::npos);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
