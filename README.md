# PlacementMatch

A C++ console application that matches students to companies based on placement eligibility criteria — CGPA, backlog count, and branch — and tracks applications end-to-end.

## Features (current)
- Student and Company data modeling with encapsulated classes (private fields, getters/setters)
- Eligibility engine that checks CGPA, backlog, and branch criteria, returning a specific reason on failure
- Student registration with input validation (CGPA range, duplicate roll number checks)
- Company registration with input validation (duplicate name checks)
- Application system — students can apply to companies they're eligible for, with status tracking
- Interactive menu-driven CLI

## Tech Stack
- C++ (STL: vector, string)
- Modular file structure (include/ + src/)

## Folder Structure
\```
PlacementMatch/
├── include/       # Header files (class declarations)
├── src/           # Implementation files (.cpp)
├── data/          # (planned) CSV data storage
└── README.md
\```

## How to Build & Run
\```bash
g++ -Iinclude src/*.cpp -o placement_checker.exe
./placement_checker.exe
\```

## Roadmap (in progress)
- [x] Student & Company classes
- [x] Eligibility engine
- [x] Registration system
- [x] Application tracking
- [ ] Search & filter
- [ ] Sorting (by package, CGPA)
- [ ] CSV file persistence (load/save)
- [ ] Hash map optimization for O(1) lookups
- [ ] Unit tests
- [ ] CI/CD via GitHub Actions

## Notes
This project is under active development as a learning exercise in C++ OOP, file I/O, and software design principles (SRP, encapsulation, separation of data vs. business logic).