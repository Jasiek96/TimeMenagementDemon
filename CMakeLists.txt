cmake_minimum_required(VERSION 3.10)
project(DateTimeTest)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Common sources
set(COMMON_SOURCES
    src/DateTime.cpp
    src/Event.cpp  # Added Event.cpp to the sources
)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Executable for testDateTimeManual
add_executable(DateTimeTestManual ${COMMON_SOURCES} test/testDateTimeManual.cpp)
target_link_libraries(DateTimeTestManual ${GTEST_LIBRARIES} pthread)

# Executable for testDateTimeAuto
add_executable(DateTimeTestAuto ${COMMON_SOURCES} test/testDateTimeAuto.cpp)
target_link_libraries(DateTimeTestAuto ${GTEST_LIBRARIES} pthread)

# Executable for testEventAuto
add_executable(EventAuto ${COMMON_SOURCES} test/testEventAuto.cpp)
target_link_libraries(EventAuto ${GTEST_LIBRARIES} pthread)  # Fixed target linking