#include <iostream>
#include <algorithm>
using namespace std;

// ============================================================
// MAX HEAP IMPLEMENTATION
// ============================================================

class MaxHeap {
private:
    int* heap;           // Dynamic array to store heap elements
    int capacity;        // Maximum capacity of heap
    int heapSize;        // Current number of elements in heap
    
    // Returns the index of parent node
    int parent(int i) { return (i - 1) / 2; }
    
    // Returns the index of left child
    int left(int i) { return 2 * i + 1; }
    
    // Returns the index of right child
    int right(int i) { return 2 * i + 2; }
    
    // Moves element up the tree to maintain max heap property
    // Used after insertion
    void heapifyUp(int i) {
        // Keep swapping with parent if current element is larger
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }
    
    // Moves element down the tree to maintain max heap property
    // Used after deletion
    void heapifyDown(int i) {
        int maxIdx = i;
        int l = left(i);
        int r = right(i);
        
        // Find the largest among node, left child, and right child
        if (l < heapSize && heap[l] > heap[maxIdx])
            maxIdx = l;
        if (r < heapSize && heap[r] > heap[maxIdx])
            maxIdx = r;
        
        // If largest is not the current node, swap and continue heapifying
        if (maxIdx != i) {
            swap(heap[i], heap[maxIdx]);
            heapifyDown(maxIdx);
        }
    }
    
public:
    // Constructor: creates heap with given capacity
    MaxHeap(int cap = 100) {
        capacity = cap;
        heapSize = 0;
        heap = new int[capacity];
    }
    
    // Constructor: creates heap from an array (Heapify method)
    // Time Complexity: O(n)
    MaxHeap(int arr[], int n, int cap = 100) {
        capacity = max(cap, n);
        heapSize = n;
        heap = new int[capacity];
        
        // Copy array elements to heap
        for (int i = 0; i < n; i++) {
            heap[i] = arr[i];
        }
        
        // Start from last non-leaf node and heapify down
        // Last non-leaf node is at index (n/2 - 1)
        for (int i = heapSize / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }
    
    // Destructor: free allocated memory
    ~MaxHeap() {
        delete[] heap;
    }
    
    // Inserts a new key into the heap
    // Time Complexity: O(log n)
    void insert(int key) {
        if (heapSize == capacity) {
            cout << "Heap overflow! Cannot insert " << key << "\n";
            return;
        }
        
        heap[heapSize] = key;  // Add element at the end
        int i = heapSize;
        
        // Move element up to maintain max heap property
        while (i > 0 && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
        
        heapSize++;
        cout << "Inserted " << key << " into Max Heap\n";
    }
    
    // Deletes and returns the maximum element (root)
    // Time Complexity: O(log n)
    int deleteMax() {
        if (heapSize == 0) {
            cout << "Heap underflow!\n";
            return -1;
        }
        
        int maxVal = heap[0];    // Store the maximum value
        heap[0] = heap[heapSize - 1];  // Move last element to root
        heapSize--;              // Reduce heap size
        
        // Move element down to maintain max heap property
        if (heapSize > 0) {
            int i = 0;
            while (true) {
                int maxIdx = i;
                int l = left(i);
                int r = right(i);
                
                // Find the largest among node, left child, and right child
                if (l < heapSize && heap[l] > heap[maxIdx])
                    maxIdx = l;
                if (r < heapSize && heap[r] > heap[maxIdx])
                    maxIdx = r;
                
                // If largest is current node, heap property is satisfied
                if (maxIdx == i)
                    break;
                
                // Swap and continue
                swap(heap[i], heap[maxIdx]);
                i = maxIdx;
            }
        }
        
        cout << "Deleted maximum element: " << maxVal << " from Max Heap\n";
        return maxVal;
    }
    
    // Returns the maximum element without removing it
    // Time Complexity: O(1)
    int getMax() {
        if (heapSize == 0) {
            cout << "Heap is empty!\n";
            return -1;
        }
        return heap[0];
    }
    
    // Displays all elements in the heap (level order)
    void display() {
        cout << "Max Heap: ";
        for (int i = 0; i < heapSize; i++)
            cout << heap[i] << " ";
        cout << "\n";
    }
    
    // Checks if heap is empty
    bool isEmpty() { return heapSize == 0; }
    
    // Returns the size of heap
    int size() { return heapSize; }
};

// ============================================================
// MAIN FUNCTION - MAX HEAP DEMONSTRATIONS
// ============================================================

int main() {
    // ============================================================
    // DEMONSTRATION 1: Building Heap from Random Array
    // ============================================================
    cout << "========== BUILDING MAX HEAP FROM ARRAY ==========\n";
    
    // Create a random unsorted array
    int randomArray[] = {20, 15, 30, 8, 10, 40, 25, 12, 18, 35};
    int n = sizeof(randomArray) / sizeof(randomArray[0]);
    
    cout << "Original Array: ";
    for (int i = 0; i < n; i++)
        cout << randomArray[i] << " ";
    cout << "\n\n";
    
    // Create Max Heap from array using constructor
    // This uses the efficient O(n) heapify algorithm
    cout << "Creating Max Heap from array...\n";
    MaxHeap maxHeapFromArray(randomArray, n);
    maxHeapFromArray.display();
    cout << "Maximum element: " << maxHeapFromArray.getMax() << "\n\n";
    
    // Demonstrate deletion from array-built heaps
    cout << "Deleting elements from Max Heap built from array:\n";
    maxHeapFromArray.deleteMax();
    maxHeapFromArray.display();
    maxHeapFromArray.deleteMax();
    maxHeapFromArray.display();
    cout << "\n";
    
    // ============================================================
    // DEMONSTRATION 2: Building Heap by Inserting Elements
    // ============================================================
    cout << "========== MAX HEAP - INSERT & DELETE ==========\n";
    MaxHeap maxHeap(50);  // Create heap with capacity 50
    
    // Insert elements one by one
    cout << "Inserting elements one by one:\n";
    maxHeap.insert(3);
    maxHeap.insert(2);
    maxHeap.insert(15);
    maxHeap.insert(5);
    maxHeap.insert(4);
    maxHeap.insert(45);
    maxHeap.display();
    cout << "Maximum element: " << maxHeap.getMax() << "\n\n";
    
    // Delete maximum elements
    cout << "Deleting maximum elements:\n";
    maxHeap.deleteMax();
    maxHeap.display();
    maxHeap.deleteMax();
    maxHeap.display();
    cout << "Maximum element: " << maxHeap.getMax() << "\n\n";
    
    // ============================================================
    // DEMONSTRATION 3: Heap Sort using Max Heap (In-place)
    // ============================================================
    cout << "========== HEAP SORT DEMONSTRATION (IN-PLACE) ==========\n";
    int unsortedArray[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(unsortedArray) / sizeof(unsortedArray[0]);
    
    cout << "Original Array: ";
    for (int i = 0; i < size; i++)
        cout << unsortedArray[i] << " ";
    cout << "\n";
    
    // Build max heap from the array (in-place)
    cout << "Building Max Heap...\n";
    
    // Heapify the array - start from last non-leaf node
    for (int i = size / 2 - 1; i >= 0; i--) {
        int node = i;
        while (true) {
            int maxIdx = node;
            int l = 2 * node + 1;
            int r = 2 * node + 2;
            
            if (l < size && unsortedArray[l] > unsortedArray[maxIdx])
                maxIdx = l;
            if (r < size && unsortedArray[r] > unsortedArray[maxIdx])
                maxIdx = r;
            
            if (maxIdx == node)
                break;
            
            swap(unsortedArray[node], unsortedArray[maxIdx]);
            node = maxIdx;
        }
    }
    
    cout << "After Heapify: ";
    for (int i = 0; i < size; i++)
        cout << unsortedArray[i] << " ";
    cout << "\n";
    
    // Extract elements one by one and place at end (in-place sorting)
    cout << "Performing Heap Sort...\n";
    int heapEnd = size;
    
    for (int i = 0; i < size; i++) {
        // Store maximum at correct position from end
        int maxVal = unsortedArray[0];
        
        // Move last element to root
        unsortedArray[0] = unsortedArray[heapEnd - 1];
        heapEnd--;
        
        // Heapify down with reduced heap size
        int node = 0;
        while (true) {
            int maxIdx = node;
            int l = 2 * node + 1;
            int r = 2 * node + 2;
            
            if (l < heapEnd && unsortedArray[l] > unsortedArray[maxIdx])
                maxIdx = l;
            if (r < heapEnd && unsortedArray[r] > unsortedArray[maxIdx])
                maxIdx = r;
            
            if (maxIdx == node)
                break;
            
            swap(unsortedArray[node], unsortedArray[maxIdx]);
            node = maxIdx;
        }
        
        // Place extracted maximum at the end of heap
        unsortedArray[heapEnd] = maxVal;
    }
    
    cout << "Sorted Array (descending): ";
    for (int i = 0; i < size; i++)
        cout << unsortedArray[i] << " ";
    cout << "\n";
    
    return 0;
}