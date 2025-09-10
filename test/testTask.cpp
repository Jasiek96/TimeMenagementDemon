#include <gtest/gtest.h>
#include <Event_task.h>
#include <DateTime.h>
#include <sstream>

TEST(TaskTest, ConstructorAndGetters)
{
    DateTime dt(2023, 8, 15, 14, 30, 45);
    Task task("Zadanie1", "Opis zadania", dt, 4, true);
    EXPECT_EQ(task.getName(), "Zadanie1");
    EXPECT_EQ(task.getDescription(), "Opis zadania");
    EXPECT_EQ(task.getPriority(), 4);
    EXPECT_TRUE(task.hasNotification());
    EXPECT_EQ(task.getEventDateTime(), dt);
    EXPECT_FALSE(task.isCompleted());
}

TEST(TaskTest, MarkDoneAndSetCompleted)
{
    Task task("Zadanie2", "Opis", DateTime(2023, 1, 1), 2, false);
    EXPECT_FALSE(task.isCompleted());
    task.markDone();
    EXPECT_TRUE(task.isCompleted());
    task.setCompleted(false);
    EXPECT_FALSE(task.isCompleted());
}

TEST(TaskTest, Setters)
{
    Task task("A", "B", DateTime(2023, 1, 1));
    task.setName("Nowa nazwa");
    task.setDescription("Nowy opis");
    task.setPriority(5);
    task.setNotification(true);
    DateTime dt(2025, 12, 24, 10, 0, 0);
    task.setEventDateTime(dt);
    EXPECT_EQ(task.getName(), "Nowa nazwa");
    EXPECT_EQ(task.getDescription(), "Nowy opis");
    EXPECT_EQ(task.getPriority(), 5);
    EXPECT_TRUE(task.hasNotification());
    EXPECT_EQ(task.getEventDateTime(), dt);
}

TEST(TaskTest, Display)
{
    Task task("Zadanie3", "Opis3", DateTime(2024, 5, 10, 12, 0, 0), 3, true);
    std::ostringstream oss;
    std::streambuf *oldCout = std::cout.rdbuf(oss.rdbuf());
    task.display();
    std::cout.rdbuf(oldCout);
    std::string output = oss.str();
    EXPECT_NE(output.find("Zadanie3"), std::string::npos);
    EXPECT_NE(output.find("Opis3"), std::string::npos);
    EXPECT_NE(output.find("2024-05-10 12:00:00"), std::string::npos);
    EXPECT_NE(output.find("ukończone"), std::string::npos) << "Status powinien być nieukończone na początku";
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
