#include <DateTime.h>
#include <gtest/gtest.h>
#include <sstream>

TEST(DateTimeTest, DefaultConstructor)
{
    DateTime dt;

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

TEST(DateTimeTest, ParametricConstructor)
{
    DateTime dt(2023, 8, 15, 14, 30, 45);
    EXPECT_EQ(dt.get_year(), 2023);
    EXPECT_EQ(dt.get_month(), 8);
    EXPECT_EQ(dt.get_day(), 15);
    EXPECT_EQ(dt.get_hour(), 14);
    EXPECT_EQ(dt.get_minute(), 30);
    EXPECT_EQ(dt.get_second(), 45);
}

TEST(DateTimeTest, ValidDate)
{
    DateTime dt(2024, 2, 29, 14, 30, 45); // Rok przestępny
    EXPECT_TRUE(dt.isValid());
}

TEST(DateTimeTest, InvalidDate)
{
    try
    {
        DateTime dt(2025, 2, 30, 14, 30, 45);                                         // Nieistniejąca data
        FAIL() << "Oczekiwano wyjątku InvalidDateTimeException, ale go nie rzucono."; // Jeśli wyjątek nie zostanie rzucony, test się nie powiedzie
    }
    catch (const InvalidDateTimeException &e)
    {
        EXPECT_STREQ(e.what(), "Niepoprawna data lub czas.");
    }
    catch (...)
    {
        FAIL() << "Oczekiwano wyjątku InvalidDateTimeException, ale rzucono inny wyjątek.";
    }
    try
    {
        DateTime dt(2025, 2, 29, 14, 30, 45);                                         // Nieistniejąca data
        FAIL() << "Oczekiwano wyjątku InvalidDateTimeException, ale go nie rzucono."; // Jeśli wyjątek nie zostanie rzucony, test się nie powiedzie
    }
    catch (const InvalidDateTimeException &e)
    {
        EXPECT_STREQ(e.what(), "Niepoprawna data lub czas.");
    }
    catch (...)
    {
        FAIL() << "Oczekiwano wyjątku InvalidDateTimeException, ale rzucono inny wyjątek.";
    }
    try
    {
        DateTime dt(2025, 2, 30, 14, 30, 65);                                         // Nieistniejąca data
        FAIL() << "Oczekiwano wyjątku InvalidDateTimeException, ale go nie rzucono."; // Jeśli wyjątek nie zostanie rzucony, test się nie powiedzie
    }
    catch (const InvalidDateTimeException &e)
    {
        EXPECT_STREQ(e.what(), "Niepoprawna data lub czas.");
    }
    catch (...)
    {
        FAIL() << "Oczekiwano wyjątku InvalidDateTimeException, ale rzucono inny wyjątek.";
    }
}

TEST(DateTimeTest, ComparisonOperators)
{
    DateTime dt1(2023, 8, 15, 14, 30, 45);
    DateTime dt2(2023, 8, 15, 14, 30, 45);
    DateTime dt3(2024, 8, 15, 14, 30, 45);

    EXPECT_TRUE(dt1 == dt2);
    EXPECT_FALSE(dt1 != dt2);
    EXPECT_TRUE(dt1 < dt3);
    EXPECT_FALSE(dt3 < dt1);
}

TEST(DateTimeTest, StreamOperators)
{
    DateTime dt(2023, 8, 15, 14, 30, 45);
    std::ostringstream oss;
    oss << dt;
    EXPECT_EQ(oss.str(), "2023-08-15 14:30:45");

    std::istringstream iss("2023-08-15 14:30:45");
    DateTime dt2;
    iss >> dt2;
    EXPECT_EQ(dt2.get_year(), 2023);
    EXPECT_EQ(dt2.get_month(), 8);
    EXPECT_EQ(dt2.get_day(), 15);
    EXPECT_EQ(dt2.get_hour(), 14);
    EXPECT_EQ(dt2.get_minute(), 30);
    EXPECT_EQ(dt2.get_second(), 45);
}
TEST(DateTimeTest, Setters)
{
    DateTime dt;
    dt.set_date(2025, 3, 30);
    EXPECT_EQ(dt.get_year(), 2025);
    EXPECT_EQ(dt.get_month(), 3);
    EXPECT_EQ(dt.get_day(), 30);

    dt.set_time(14, 30, 45);
    EXPECT_EQ(dt.get_hour(), 14);
    EXPECT_EQ(dt.get_minute(), 30);
    EXPECT_EQ(dt.get_second(), 45);

    dt.set_date_time(2036, 03, 15, 15, 15, 15);
    EXPECT_EQ(dt.get_year(), 2036);
    EXPECT_EQ(dt.get_month(), 3);
    EXPECT_EQ(dt.get_day(), 15);
}
TEST(DateTimeTest, FromString)
{
    DateTime dt = DateTime::fromString("2023-08-15 04:30:45");
    EXPECT_EQ(dt.get_year(), 2023);
    EXPECT_EQ(dt.get_month(), 8);
    EXPECT_EQ(dt.get_day(), 15);
    EXPECT_EQ(dt.get_hour(), 4);
    EXPECT_EQ(dt.get_minute(), 30);
    EXPECT_EQ(dt.get_second(), 45);
}

TEST(DateTimeTest, FromString_double)
{
    DateTime dt = DateTime::fromString("2023-12-15 14:30:45");
    EXPECT_EQ(dt.get_year(), 2023);
    EXPECT_EQ(dt.get_month(), 12);
    EXPECT_EQ(dt.get_day(), 15);
    EXPECT_EQ(dt.get_hour(), 14);
    EXPECT_EQ(dt.get_minute(), 30);
    EXPECT_EQ(dt.get_second(), 45);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    DateTime dt(2025, 3, 30, 14, 30, 45);
    dt.display();
    return RUN_ALL_TESTS();
}
