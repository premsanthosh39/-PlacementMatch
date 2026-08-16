# Architecture Notes

This is a deeper look at how PlacementMatch is put together and why I made the choices I did. The README covers what it does and how to run it — this is more about the reasoning behind the design.

## Overall shape

The code is split into three layers that only depend on each other in one direction.

`models/` (Student, Company, Application) just holds data. These classes don't know anything about CSV files, eligibility rules, or the menu — they have private fields and getters/setters, and that's it.

`services/` is where the actual logic sits — checking eligibility, registering people, searching, saving/loading CSVs, handling applications. This layer reads from the models but the models never know these services exist.

`utils/` and `strategies/` are supporting pieces — the Trie, the logger, the config reader, and the Strategy/Factory pattern for eligibility rules.

`main.cpp` sits on top and just wires everything together through the menu. It doesn't contain business logic itself, just calls into services.

## Why I picked the data structures I did

I didn't want to just use `vector` for everything and call it done, so here's the actual reasoning per structure:

**unordered_map for lookups** — Every time you check eligibility or apply to a company, the code needs to find a specific student by roll number or a specific company by name. Scanning a vector for this is O(n), and it happens constantly. A hash map gets that down to O(1) on average. I keep the vector around too, though, since I still need ordered iteration for things like "view all students" and saving back to CSV in a consistent order — the map is just an index into it, not a replacement.

**A Trie for name search** — I wanted to be able to search "show me all students whose name starts with 'ra'" without scanning every single name and checking `.find()` on each one. A hash map can't really do that well, because you'd have to precompute every possible prefix in advance. A Trie handles it naturally — you walk down the tree one character at a time, and once you hit the right node, everything below it is a match. It was genuinely the hardest thing to build in this whole project, mainly the recursive part that collects all the words under a node.

**priority_queue for ranking** — When showing a student their eligible companies ranked by package, I didn't want to sort the entire company list just to show a few results. A priority queue keeps the highest package on top without needing everything fully sorted.

**Binary search for filtering by package** — Once companies are sorted by package, finding "everyone above X LPA" doesn't need a linear scan — `std::lower_bound` finds the cutoff point in O(log n).

## The eligibility check itself

It runs four checks in order: CGPA, backlogs, branch, and graduation year. As soon as one fails, it stops and returns that specific reason. That's a simplification — if a student fails two things, they only find out about the first one. I kept it this way because handling multiple failure reasons would have meant changing the return type into something more complex, and for this version, one clear reason at a time felt like enough.

## Strategy pattern for eligibility rules

I have two ways of checking eligibility — a standard one, and a stricter one that also requires zero backlogs no matter what the company normally allows. Instead of putting an if/else for "strict mode" inside the original eligibility function, I made a base class with one method (`evaluate`), and two versions of it — Standard and Strict. Adding the strict version didn't require touching the original, already-tested code at all, which is the whole point of doing it this way.

There's also a small factory function that creates the right strategy based on a string ("standard" or "strict") so the calling code doesn't need to know the actual class names.

Honest gap: this is only wired into one part of the menu right now, not used everywhere eligibility gets checked. Something I'd finish given more time.

## CSV storage

CSV was the simplest choice given the scope — no external database dependency, human-readable, easy to debug by just opening the file.

Two things worth explaining about how it's parsed:

Fields like skills (`C++,DSA,SQL`) have commas inside them, which would normally break CSV parsing since commas are the delimiter. The parser handles this by tracking whether it's currently inside quotes, and only treating a comma as a real separator when it's not.

Every row is parsed inside a try/catch block. If one row has a typo or bad data (say, someone manually broke the CGPA field), that one row gets skipped with a warning instead of crashing the whole program on startup.

The real tradeoff here: every save rewrites the entire file from scratch. That's fine at this size but would get slow with a lot of records — a real system would append or use an actual database.

## Testing

There are two kinds of tests, both just using plain `assert()` rather than a testing framework, since the project didn't need anything heavier.

Unit tests check the eligibility function directly against known student/company pairs — one test per failure reason (bad CGPA, too many backlogs, wrong branch, wrong batch).

Integration tests check the full flow together — register, check eligibility, apply, update status, delete — including things like making sure you can't apply to the same company twice, and that an ineligible student actually gets blocked from applying.

## Build and CI

I moved from a long manual g++ command listing every file to a CMakeLists.txt, mostly because retyping that command wrong was a constant source of errors while building this. CMake also builds the test executables the same way.

GitHub Actions runs the build on a fresh Ubuntu machine on every push, which is deliberately different from the Windows setup I built this on — it actually caught a real bug the first time, since a Windows-specific time function I'd used didn't exist on Linux and broke the build until I swapped it for a portable one.

## What I'd change with more scale

- CSV → a real database, mainly for the rewrite-on-every-save issue
- Finish wiring the Strategy pattern into every eligibility check, not just one
- Collect all failing eligibility reasons instead of stopping at the first one
- Move from a single local console session to something multi-user, likely with a proper backend