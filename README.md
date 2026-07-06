# Placement Eligibility Checker

A console-based C++ application that manages student and 
company records and automatically checks placement eligibility.

## Features
- Add, view, search, delete students
- Add, view, delete companies
- Automatic eligibility check based on CGPA, 12th %, 
  10th %, and backlog criteria
- Persistent file storage using file handling

## Algorithm
- O(n x m) eligibility check where n = students, 
  m = companies
- Checks CGPA, academic percentages, and backlogs 
  against each company's criteria

## Tech Stack
- Language: C++
- Concepts: OOP, Classes, Vectors, File Handling, STL

## How to Run
g++ main.cpp student.cpp company.cpp -o project
./project