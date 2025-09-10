#include <DateTime.h>
#include <Event.h>
#include <gtest/gtest.h>
#include <sstream>

// Test konstuktora domyślego i geterów
TEST(EventTest, DefaultConstructor)
{
    Event event;
    EXPECT_EQ(event.getName(), "NAME");
    EXPECT_EQ(event.getDescription(), "DESCRIPTION");
    EXPECT_EQ(event.getPriority(), 3);
    EXPECT_FALSE(event.hasNotification());

    DateTime dt = event.getEventDateTime();

    EXPECT_TRUE(dt.isValid());
    EXPECT_GT(dt.get_year(), 1970);

    EXPECT_GE(dt.get_month(), 1);
    EXPECT_LE(dt.get_month(), 12);

    EXPECT_GE(dt.get_day(), 1);
    EXPECT_LE(dt.get_day(), 31);

    EXPECT_GE(dt.get_hour(), 0);
    EXPECT_LE(dt.get_hour(), 23);

    EXPECT_GE(dt.get_minute(), 0);
    EXPECT_LE(dt.get_minute(), 59);

    EXPECT_GE(dt.get_second(), 0);
    EXPECT_LE(dt.get_second(), 59);
}
// Testy konstruktora parametrycznego
TEST(EventTest, ParametricConstructor)
{
    DateTime dt(2023, 8, 15, 14, 30, 45);
    Event event("name", "Description", dt, 5, true);

    EXPECT_EQ(event.getName(), "name");
    EXPECT_EQ(event.getDescription(), "Description");
    EXPECT_EQ(event.getPriority(), 5);
    EXPECT_TRUE(event.hasNotification());

    DateTime dt_read = event.getEventDateTime();

    EXPECT_EQ(dt_read.get_year(), 2023);
    EXPECT_EQ(dt_read.get_month(), 8);
    EXPECT_EQ(dt_read.get_day(), 15);
    EXPECT_EQ(dt_read.get_hour(), 14);
    EXPECT_EQ(dt_read.get_minute(), 30);
    EXPECT_EQ(dt_read.get_second(), 45);
}
// Testy konstruktora kopiujacego
TEST(EventTest, CopyConstructor)
{
    DateTime dt(2023, 8, 15, 14, 30, 45);
    Event event_1("Name_1", "Description_1", dt, 5, true);
    Event event_2(event_1);

    EXPECT_EQ(event_2.getName(), "Name_1");
    EXPECT_EQ(event_2.getDescription(), "Description_1");
    EXPECT_EQ(event_2.getPriority(), 5);
    EXPECT_TRUE(event_2.hasNotification());

    EXPECT_EQ(event_2.getEventDateTime(), dt);
}

// Testy operatora =
TEST(EventTest, EqualConstructor)
{
    DateTime dt(2023, 8, 15, 14, 30, 45);
    Event event_1("Name_1", "Description_1", dt, 5, true);
    Event event_2 = event_1;

    EXPECT_EQ(event_2.getName(), "Name_1");
    EXPECT_EQ(event_2.getDescription(), "Description_1");
    EXPECT_EQ(event_2.getPriority(), 5);
    EXPECT_TRUE(event_2.hasNotification());

    EXPECT_EQ(event_2.getEventDateTime(), dt);
}

// Test seterów
TEST(EventTest, Setters)
{
    Event event_3;
    event_3.setName("Nazwa_2");
    EXPECT_EQ(event_3.getName(), "Nazwa_2");
    event_3.setDescription("Description_2");
    EXPECT_EQ(event_3.getDescription(), "Description_2");
    event_3.setPriority(1);
    EXPECT_EQ(event_3.getPriority(), 1);
    event_3.setNotification(true);
    EXPECT_TRUE(event_3.hasNotification());

    DateTime dt(2036, 03, 15, 15, 15, 15);
    event_3.setEventDateTime(dt);
    EXPECT_EQ(event_3.getEventDateTime(), dt);
}

// Test display
TEST(EventTest, Display)
{
    Event event_3;
    event_3.setName("Nazwa_2");
    EXPECT_EQ(event_3.getName(), "Nazwa_2");
    event_3.setDescription("Description_2");
    EXPECT_EQ(event_3.getDescription(), "Description_2");
    event_3.setPriority(1);
    EXPECT_EQ(event_3.getPriority(), 1);
    event_3.setNotification(true);
    EXPECT_TRUE(event_3.hasNotification());

    DateTime dt(2036, 03, 15, 15, 15, 15);
    event_3.setEventDateTime(dt);
    EXPECT_EQ(event_3.getEventDateTime(), dt);
}

// Definicja funkcji main, która uruchamia wszystkie testy
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    DateTime dt(2023, 8, 15, 14, 30, 45);
    Event event("Spotkanie", "Omówienie projektu", dt, 5, true);
    event.display();
    return RUN_ALL_TESTS();
}
