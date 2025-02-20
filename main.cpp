#include <iostream>
#include <chrono>  // for measuring time
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include "BST.h"
#include "AVL.h"
#include "BTree.h"

using namespace std;
class PerformanceTester
{
private:
    // Method to calculate and display timing results
    void displayResults(const string &operation, double totalTime, int datasetSize, int iterations = 0)
    {
        cout << "- " << operation << " Results:\n";
        cout << "Total Time Taken: " << totalTime << " ms\n";
        if (iterations > 0)
        {
            cout << "Average Time: " << (totalTime / iterations) << " ms per operation" << endl;
        }
        else
        {
            cout << "Average Time: " << (totalTime / datasetSize) << " ms per operation" << endl;
        }
        cout << endl;
    }

    // Method to generate random keys to search
    void generateRandomKeys(int *keys, int numKeys, int maxKey)
    {
        for (int i = 0; i < numKeys; i++)
        {
            keys[i] = rand() % maxKey; // will generate the random key between 0 to maxKey i.e. 0 to datasetSize
        }
    }

public:
    void testTrees(int datasetSize)
    {
        srand(time(0)); // Seed random number generator

        // Dummy Keys for testing
        int randomKeys[20];
        generateRandomKeys(randomKeys, 20, datasetSize);

        // ------------------------ BST ------------------------
        BinarySearchTree BST;
        cout << "------------------- Testing BSTs -------------------" << endl
             << endl;

        // Measuring Insertion Time
        auto start = chrono::high_resolution_clock::now(); // storing start time
        for (int i = 0; i < datasetSize; i++)
        {
            BST.insert(i, "Name: alpha_" + to_string(i + 1), i % 100); // inserting the data
        }
        auto end = chrono::high_resolution_clock::now();                             // storing ending time
        double BSTInsertTime = chrono::duration<double, milli>(end - start).count(); // calculate the total time taken
        displayResults("Insert", BSTInsertTime, datasetSize);                        // displaying the results i.e. total time taken and average time taken per operation

        // Measuring Search Time
        start = chrono::high_resolution_clock::now(); // storing start time
        for (int i = 0; i < 20; i++)
        {
            BST.search(randomKeys[i]); // searching the random keys
        }
        end = chrono::high_resolution_clock::now();                                  // storing ending time
        double BSTSearchTime = chrono::duration<double, milli>(end - start).count(); // calculate the total time taken
        displayResults("Search", BSTSearchTime, 20, 20);                             // displaying the results i.e. total time taken and average time taken per operation

        // Measuring Deletion Time
        start = chrono::high_resolution_clock::now(); // storing start time
        for (int i = 0; i < datasetSize; i++)
        {
            BST.remove(i); // removing the data
        }
        end = chrono::high_resolution_clock::now();                                  // storing ending time
        double BSTDeleteTime = chrono::duration<double, milli>(end - start).count(); // calculate the total time taken
        displayResults("Delete", BSTDeleteTime, datasetSize);                        // displaying the results i.e. total time taken and average time taken per operation
        // cout << "-----------------------------------------------" << endl
        //      << endl;

        // ------------------------ AVL ------------------------
        AVL avl;

        cout << "------------------- Testing AVL-Trees -------------------" << endl
             << endl;

        // Measuring Insertion Time
        start = chrono::high_resolution_clock::now(); // storing start time
        for (int i = 0; i < datasetSize; i++)
        {
            avl.insert(i, "Name: Comrade_" + to_string(i + 1), i % 100); // inserting the data
        }
        end = chrono::high_resolution_clock::now();                                  // storing ending time
        double avlInsertTime = chrono::duration<double, milli>(end - start).count(); // calculate the total time taken
        displayResults("Insert", avlInsertTime, datasetSize);                        // displaying the results i.e. total time taken and average time taken per operation

        // Measuring Search Time
        start = chrono::high_resolution_clock::now(); // storing start time
        for (int i = 0; i < 20; i++)
        {
            avl.search(randomKeys[i]); // searching the random keys
        }
        end = chrono::high_resolution_clock::now();                                  // storing ending time
        double avlSearchTime = chrono::duration<double, milli>(end - start).count(); // calculate the total time taken
        displayResults("Search", avlSearchTime, 20, 20);                             // displaying the results i.e. total time taken and average time taken per operation

        // Measuring Deletion Time
        start = chrono::high_resolution_clock::now(); // storing start time
        for (int i = 0; i < datasetSize; i++)
        {
            avl.remove(i); // removing the data
        }
        end = chrono::high_resolution_clock::now();                                  // storing ending time
        double avlDeleteTime = chrono::duration<double, milli>(end - start).count(); // calculate the total time taken
        displayResults("Delete", avlDeleteTime, datasetSize);                        // displaying the results i.e. total time taken and average time taken per operation
        // cout << "-----------------------------------------------" << endl
        //      << endl;

        // ------------------------ B-Tree ------------------------
        BTree btree(3);
        cout << "------------------- Testing B-Trees -------------------" << endl
             << endl;

        // Measuring Insertion Time
        start = chrono::high_resolution_clock::now(); // storing start time
        for (int i = 0; i < datasetSize; i++)
        {
            btree.insert(i); // inserting the data
        }
        end = chrono::high_resolution_clock::now();                                    // storing ending time
        double btreeInsertTime = chrono::duration<double, milli>(end - start).count(); // calculate the total time taken
        displayResults("Insert", btreeInsertTime, datasetSize);                        // displaying the results i.e. total time taken and average time taken per operation

        // Measuring Search Time
        start = chrono::high_resolution_clock::now(); // storing start time
        for (int i = 0; i < 20; i++)
        {
            btree.search(randomKeys[i]); // searching the random keys
        }
        end = chrono::high_resolution_clock::now();                                    // storing ending time
        double btreeSearchTime = chrono::duration<double, milli>(end - start).count(); // calculate the total time taken
        displayResults("Search", btreeSearchTime, 20, 20);                             // displaying the results i.e. total time taken and average time taken per operation

        // Measuring Deletion Time
        start = chrono::high_resolution_clock::now(); // storing start time
        for (int i = 0; i < datasetSize; i++)
        {
            btree.remove(i); // removing the data
        }
        end = chrono::high_resolution_clock::now();                                    // storing ending time
        double btreeDeleteTime = chrono::duration<double, milli>(end - start).count(); // calculate the total time taken
        displayResults("Delete", btreeDeleteTime, datasetSize);                        // displaying the results i.e. total time taken and average time taken per operation
        // cout << "-----------------------------------------------" << endl
        //      << endl;
    }
};

int main()
{
    PerformanceTester tester;

    int datasetSize;
    cout << "Enter the number of records to test: ";
    cin >> datasetSize;
    cout << endl;

    tester.testTrees(datasetSize);

    return 0;
}
