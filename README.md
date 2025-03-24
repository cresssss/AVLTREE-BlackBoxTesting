# SEE600 Assignment: Custom AVL Tree vs std::map Performance Testing


**Date:** March 2025  
**Environment:**  
- OS: Windows 11  
- Compiler: MSYS2 g++ (C++17)  
- Memory: 16 GB RAM  
- Terminal: MSYS2 UCRT64 / VS Code

---

## Project Objective

This project explores the feasibility of replacing `std::map` with a custom AVL Tree implementation for a memory-constrained, event-driven, real-time software system.

The goal is to evaluate performance, scalability, and memory usage of each structure under various test scenarios.

---

## Test Suite Summary

| Test # | Description                         | Performed On         |
|--------|-------------------------------------|-----------------------|
| 1      | AVL Tree Insertion Correctness      | Yes (AVL)             |
| 2      | AVL Tree Deletion Correctness       | Yes (AVL)             |
| 3      | AVL Tree Max Size Test              | Yes (AVL)             |
| 4      | Load Test (100,000 insertions)      | Yes (AVL & std::map)  |
| 5      | Memory Leak Detection               | Pending               |
| 6      | Worst-Case Search Speed             | Yes (AVL & std::map)  |

---

## Test Results

### Test 1: AVL Insertion Correctness
- Inserted SINs: 100000005, 100000010, 100000015
- Output showed in-order traversal confirming correct AVL structure.
- Result: Passed

---

### Test 2: AVL Deletion Correctness
- Deleted SIN: 100000005
- Remaining in-order traversal: 100000010, 100000015
- Result: Passed

---

### Test 3: Max Size Test
- AVL Tree inserted over 39.4 million nodes
- Peak RAM usage: 14.2 / 14.8 GB (among other things)
- No crash occurred; system remained stable during the test
- Result: Passed (manually interrupted)

**Memory Recommendation:** Reserve approximately 12–13 GB for full-scale AVL Tree operations in constrained systems. (considering having other tabs open)

---

### Test 4: Load Test (100,000 insertions)

| Structure   | Elapsed Time |
|-------------|--------------|
| std::map    | 0.182 sec    |
| AVL Tree    | 0.09 sec     |

**Analysis:** The AVL Tree performed approximately 2x faster than `std::map` in bulk insertion.

---

### Test 6: Worst-Case Search Speed

| Structure   | SIN Searched   | Time     |
|-------------|----------------|----------|
| std::map    | 100099999      | 0 sec    |
| AVL Tree    | 100099999      | 0 sec    |

**Analysis:** Both data structures performed equally well under worst-case search.

---

## Summary: AVL Tree vs std::map

| Metric             | std::map   | AVL Tree         |
|--------------------|------------|------------------|
| Insertion Speed    | Moderate   | Faster           |
| Search Speed       | Fast       | Fast             |
| Memory Usage       | Unknown    | Efficient        |
| Max Size Handling  | Unverified | 39.4M+ nodes     |
| Reusability        | High       | High (modular)   |
| Customizability    | Low        | Full control     |
| Overhead           | Low        | Higher code size |

---

## Test 5: Memory Leak Detection

**Pending.** This test will be conducted using one of the following tools:
- `valgrind` (on Linux)
- `Dr. Memory` (on Windows)
- Visual Studio Diagnostics Tools

The objective is to ensure that memory is correctly deallocated after operations and no leaks are present after insert/delete/load cycles.

---

## Conclusion

For embedded or real-time systems requiring fast insertions, predictable structure, and fine-grained memory control, the custom AVL Tree implementation demonstrates superior performance compared to `std::map`. It is especially suitable when memory consumption must be closely monitored and deterministic operation is essential.
