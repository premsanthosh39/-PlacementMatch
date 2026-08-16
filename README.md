# 🎓 PlacementMatch

**A C++ console application that matches students to companies based on real placement eligibility rules — CGPA, backlogs, branch, and graduation year — with full application tracking.**

Built as a hands-on project to apply core Data Structures & Algorithms, Object-Oriented Design, and Software Engineering practices to a realistic, end-to-end problem: campus placements.

---

## 📌 Why This Project Exists

Every placement season, students manually cross-check dozens of company criteria against their own profile — CGPA cutoffs, backlog limits, eligible branches, batch year — often through scattered spreadsheets or WhatsApp messages. **PlacementMatch automates that entire process**: register once, and instantly see which companies you qualify for, why you don't qualify for others, and track every application you submit.

---

## ✨ Features

| Category | What it does |
|---|---|
| **Eligibility Engine** | Checks CGPA, backlog count, branch, and graduation year — and tells you *exactly* which rule failed, not just a yes/no |
| **Student & Company Management** | Full CRUD — register, view, search, update, delete |
| **Application Tracking** | Apply to eligible companies, track status (Applied → Shortlisted → Selected/Rejected), withdraw anytime |
| **Fast Search** | Instant roll number / company lookup via hash maps, and prefix-based name search via a custom-built Trie |
| **Smart Ranking** | See your eligible companies ranked by package (highest first) using a priority queue |
| **Persistent Storage** | All data saved to CSV files automatically — nothing is lost between sessions |
| **Configurable** | File paths and settings controlled through an external config file, not hardcoded |
| **Resilient** | Exception handling and input validation throughout — a corrupted CSV row or bad input never crashes the app |
| **Logged** | Every major action (registration, application, update) is timestamped and logged to a file |
| **Flexible Rules** | Switch between Standard and Strict eligibility rule sets on the fly (Strategy Pattern) |
| **Tested** | Unit and integration tests covering the core eligibility and application logic |
| **CI/CD** | Every push is automatically built and tested via GitHub Actions |

---

## 🖥️ Demo

```
===== Placement Eligibility Checker =====
1.  Register Student
2.  Register Company
3.  Check Eligibility
4.  View All Students
5.  View All Companies
6.  Search Student
7.  Search Company
8.  View Companies Sorted by Package
9.  Apply to Company
10. View My Applications
11. Search Student by Name Prefix
12. Update Student        13. Delete Student
14. Update Company        15. Delete Company
16. Update Application    17. Delete Application
18. Ranked Eligible Companies for a Student
19. Companies with Minimum Package
20. Exit
Enter choice: 3

Enter Roll Number: 21CS001
Enter Company Name: TI
Use (1) Standard or (2) Strict eligibility rules? 1

Rahul Sharma is ELIGIBLE for TI!
```

---

## 🏗️ Architecture

The project follows a clean, layered structure — data models are kept completely separate from business logic, which is separate from persistence and presentation.

```
                         main.cpp (menu / CLI)
                                │
        ┌───────────────────────┼───────────────────────┐
        ▼                       ▼                       ▼
   models/                 services/               strategies/
  Student                 EligibilityChecker       EligibilityStrategy
  Company                 Registration              (Standard / Strict)
  Application             Search & Sort             Factory
                           CSV Storage
                           Application System
                                │
                                ▼
                             utils/
                        Trie · Logger · Config
```

**Design principles applied:**
- **Single Responsibility** — each class/module has exactly one reason to change
- **Open/Closed** — new eligibility rules are added as new Strategy classes, without touching existing logic
- **Encapsulation** — all class fields are private, accessed only through validated getters/setters

---

## 🧠 Data Structures & Algorithms Used

| Problem | Data Structure / Algorithm | Time Complexity | Why |
|---|---|---|---|
| Find a student/company by ID | `unordered_map` | O(1) average | Instant lookup instead of scanning every record |
| Search names by prefix | Custom **Trie** | O(k), k = prefix length | Scales independently of how many students are stored |
| Rank eligible companies by package | `priority_queue` (max-heap) | O(log n) per operation | Always know the highest package without a full sort |
| Filter companies by minimum package | `std::lower_bound` (binary search) | O(log n) | Fast range queries on sorted data |
| General sorting | `std::sort` with custom comparators | O(n log n) | Standard, reliable, well-tested |

---

## 🛠️ Tech Stack

- **Language:** C++17
- **Standard Library:** `vector`, `unordered_map`, `priority_queue`, `algorithm`, `fstream`
- **Build System:** CMake
- **CI/CD:** GitHub Actions
- **Storage:** CSV (custom quote-aware parser, no external library dependencies)

---

## 🚀 Getting Started

### Prerequisites
- A C++17-compatible compiler (g++, MinGW, or MSVC)
- CMake 3.10+

### Build & Run

```bash
git clone https://github.com/premsanthosh39/PlacementMatch.git
cd PlacementMatch
mkdir build && cd build
cmake ..
cmake --build .
./placement_checker
```

### Run the Test Suite

```bash
./run_tests
./run_integration_tests
```

---

## 📂 Project Structure

```
PlacementMatch/
├── include/
│   ├── models/          # Student.h, Company.h, Application.h
│   ├── services/         # EligibilityChecker, Registration, Search, CSVStorage...
│   ├── strategies/        # EligibilityStrategy, Factory
│   └── utils/             # Trie, Logger, Config
├── src/                   # Mirrors include/ — implementation files
├── tests/                 # Unit & integration tests
├── data/                  # CSV data files (students, companies, applications)
├── config/                # config.txt — configurable file paths
├── logs/                  # app.log — runtime event log
├── .github/workflows/     # CI pipeline
├── CMakeLists.txt
└── main.cpp
```

---

## 🔍 Known Limitations & Honest Notes

Being upfront about the current state, rather than overselling it:

- **CSV storage rewrites the full file on every save** — fine at this scale, but a production system would use append-only writes or a real database (SQLite/MySQL) for larger datasets.
- **The Strategy Pattern is implemented but only partially wired into the menu** — a deliberate next refactor, not an oversight.
- **Single-user, local console app** — no authentication, no concurrent access. A natural next step would be a REST API + web frontend, built as a separate project.
- **`unordered_map` indexes are rebuilt on every write** rather than incrementally updated — simple and correct, with a known performance tradeoff at very large scale.

---

## 🗺️ Possible Future Improvements

- [ ] Migrate storage from CSV to SQLite for real query support
- [ ] Build a REST API layer (Node.js/Express or a C++ HTTP framework)
- [ ] Build a web frontend for a real multi-user experience
- [ ] Add role-based access (Student vs. Admin views)
- [ ] Replace linear application lookups with an indexed structure

---

## 🤝 What I Learned Building This

- Designing clean class hierarchies with proper encapsulation
- Choosing the right data structure for the right access pattern (hash map vs. Trie vs. heap vs. sorted array)
- Writing exception-safe, defensive code that doesn't crash on bad input
- Setting up a real build pipeline (CMake) and CI (GitHub Actions) from scratch
- The practical difference between "code that works on my machine" and "code that's actually portable" (debugging Windows vs. Linux build differences)

---

## 📄 License

MIT License — free to use, modify, and learn from.

---

<p align="center">Built with C++ and a lot of debugging. 🛠️</p>