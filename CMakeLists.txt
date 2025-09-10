cmake_minimum_required(VERSION 3.10)
project(EventApp)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Common sources
set(COMMON_SOURCES
    src/DateTime.cpp
    src/Event.cpp
    src/Event_meeting.cpp
    src/Event_task.cpp
    src/EventManager.cpp
)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Executable for DateTimeTestManual
add_executable(DateTimeTestManual ${COMMON_SOURCES} test/testDateTimeManual.cpp)
target_link_libraries(DateTimeTestManual ${GTEST_LIBRARIES} pthread)

# Executable for DateTimeTestAuto
add_executable(DateTimeTestAuto ${COMMON_SOURCES} test/testDateTimeAuto.cpp)
target_link_libraries(DateTimeTestAuto ${GTEST_LIBRARIES} pthread)

# Executable for EventTestAuto
add_executable(EventTestAuto ${COMMON_SOURCES} test/testEventAuto.cpp)
target_link_libraries(EventTestAuto ${GTEST_LIBRARIES} pthread) 

# Executable for MeetingTestAuto
add_executable(MeetingTestAuto ${COMMON_SOURCES} test/testMeeting.cpp)
target_link_libraries(MeetingTestAuto ${GTEST_LIBRARIES} pthread)

# Executable for TaskTestAuto
add_executable(TaskTestAuto ${COMMON_SOURCES} test/testTask.cpp)
target_link_libraries(TaskTestAuto ${GTEST_LIBRARIES} pthread)

# Executable for EventManagerTestAuto
add_executable(EventManagerTestAuto ${COMMON_SOURCES} test/testEventManager.cpp)
target_link_libraries(EventManagerTestAuto ${GTEST_LIBRARIES} pthread)

# Executable for EventApp
add_executable(EventApp ${COMMON_SOURCES} src/app.cpp)