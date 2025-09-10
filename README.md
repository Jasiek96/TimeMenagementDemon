# TimeMenagementDemon

A small C++ project focused on date/time utilities and event structures.  
**Note:** At this stage the repository builds **GoogleTest-based tests** and initial model of the application.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Build & Run ](# Build & Run)
- [License](#license)

---

## Overview

The code provides basic building blocks for working with date–time values and event objects (e.g., title, description, time, priority, notification flag). The current entry point is a **GoogleTest** target used to verify and demonstrate functionality.

## Features

- Lightweight `DateTime` and `Event`-style abstractions
- Basic validation and formatted input/output
- GoogleTest-based manual/unit tests

## Project Structure

```text
TimeMenagementDemon/
├── include/          # Public headers (DateTime, Event, helpers)
├── src/              # Library / implementation sources
├── test/             # GoogleTest sources (manual/unit tests)
└── CMakeLists.txt    # CMake build
```

## Requirements

- C++17-compatible compiler (GCC)
- CMake ≥ 3.16
- Make (on Linux/macOS) or a build tool supported by your platform
- GoogleTest available to CMake

> If GoogleTest is not fetched automatically by CMake in your setup, install it.

## Build & Run

From the **repository root**, do:

```bash
cmake .
make
```

then you can access the tests and app by following commands

```bash
./DateTimeTestManual
./DateTimeTestAuto
./DateTimeTestManual
./EventTestAuto
./MeetingTestAuto
./TaskTestAuto
./EventManagerTestAuto
./EventApp
```

## License

Open access / open-source. This repository is released under the **MIT License**.
