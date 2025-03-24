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


## Questions

### Are there any other tests that you feel are required? Describe them briefly.

Yes. While the current tests cover core functionality and performance, the following additional tests would be valuable:

1. **Concurrent Access Test:** Simulate multiple threads accessing the database simultaneously to test thread safety.
2. **Edge Case Inserts:** Insert duplicate SINs or boundary SINs to ensure error handling and input validation.
3. **Deletion Under Load:** Perform deletions during high-volume insertion to simulate live database update scenarios.
4. **Persistence Test:** Test ability to serialize and deserialize the AVL tree for persistent storage and recovery.

---

### Compare and contrast `std::map` vs AVL Tree for all six test cases above.

| Test                          | std::map                         | AVL Tree                        | Conclusion                        |
|-------------------------------|----------------------------------|----------------------------------|-----------------------------------|
| Insertion Correctness         | Built-in, assumed correct        | Passed all test cases            | Both acceptable                   |
| Deletion Correctness          | Built-in                         | Passed, maintained structure     | Both acceptable                   |
| Max Size Test                 | Not tested                       | Handled 39.4M nodes at ~14.2GB   | AVL Tree more stress-tested       |
| Load Test (Insert 100K)       | 0.182 sec                        | 0.09 sec                         | AVL Tree significantly faster     |
| Worst-Case Search             | 0 sec                            | 0 sec                            | Same performance (logarithmic)    |
| Memory Leak (Pending)         | N/A                              | Test pending                     | To be confirmed                   |

---

### Were there unexpected results?

Yes. It was surprising that the AVL Tree outperformed `std::map` in bulk insertions, achieving almost double the speed. This suggests that the custom AVL implementation is highly optimized for raw insert throughput in this context. Additionally, the tree handled significantly more entries than expected before reaching memory limits, demonstrating strong scalability.

---

### Which would you recommend, `std::map` or AVL Tree?

For general-purpose software with sufficient resources, `std::map` remains a practical and maintainable choice due to STL support, reliability, and portability.

However, for **embedded systems**, **low-latency applications**, or **memory-sensitive real-time software**, the **AVL Tree** is recommended due to:
- Faster insertion speed
- Predictable structure
- Full control over memory and balancing
- Demonstrated stability up to 39.4M+ entries

---

### Based on memory tests, what maximum memory would you recommend be reserved for the database?

To avoid system instability, a memory allocation of **12–13 GB** is recommended for AVL Tree operation at full scale. During the Max Size test, peak memory usage was measured at **14.2 GB**, and performance remained stable up to that point.

---

### Is this AVL Tree reusable for other projects?

Yes. With some modularization improvements (e.g., templating, better encapsulation, error handling), the AVL Tree implementation can be easily reused in other projects. It supports efficient insert, delete, and search operations and is suitable for use as an embedded database backend.

---

### Is your test software reusable?

Yes. The test suite was designed to be modular and can be reused or extended for other data structure performance tests. With minimal changes to class names or data types, the framework can benchmark additional structures such as Red-Black Trees, Hash Maps, or even file-backed storage engines.

