# Performance Analysis of BST, AVL, and B-Tree

This project implements and analyzes the performance of three different tree data structures:

- **Binary Search Tree (BST)**
- **AVL Tree**
- **B-Tree**

The goal is to compare their efficiency in terms of insertion, searching, and deletion operations. The program generates a dataset of records and measures the time taken for each operation across different tree types.

## Features

- Implements **BST, AVL Tree, and B-Tree** for comparison.
- Supports **Insertion, Searching, and Deletion** operations.
- Measures execution time for different operations.
- Allows user to specify dataset size for testing.

## Usage

1. **Clone the repository:**
   ```sh
   git clone https://github.com/codewithalphadotcom/Time-Complexities-Analyzer.git
   ```
2. **Navigate to the project directory:**
   ```sh
   cd Time-Complexities-Analyzer
   ```
3. **Compile the program:**
   ```sh
   g++ -o output main.cpp
   ```
4. **Run the executable:**
   ```sh
   ./output
   ```

## Example Output

```
Enter the number of records to test: 1000

------------------- Testing BSTs -------------------

- Insert Results:
Total Time Taken: 22.7353 ms
Average Time: 0.0227353 ms per operation

- Search Results:
Total Time Taken: 0.248334 ms
Average Time: 0.0124167 ms per operation

- Delete Results:
Total Time Taken: 0.088666 ms
Average Time: 8.8666e-05 ms per operation

------------------- Testing AVL-Trees -------------------

- Insert Results:
Total Time Taken: 0.68225 ms
Average Time: 0.00068225 ms per operation

- Search Results:
Total Time Taken: 0.004291 ms
Average Time: 0.00021455 ms per operation

- Delete Results:
Total Time Taken: 0.443375 ms
Average Time: 0.000443375 ms per operation

------------------- Testing B-Trees -------------------

- Insert Results:
Total Time Taken: 0.17275 ms
Average Time: 0.00017275 ms per operation

- Search Results:
Total Time Taken: 0.005292 ms
Average Time: 0.0002646 ms per operation

- Delete Results:
Total Time Taken: 0.2605 ms
Average Time: 0.0002605 ms per operation
```

<!-- ## Performance Analysis

- **BST:** Fast insertion but may become unbalanced, leading to slower search times.
- **AVL Tree:** Self-balancing, ensuring efficient operations.
- **B-Tree:** Optimized for large datasets and disk storage. -->