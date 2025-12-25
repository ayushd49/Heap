#include <iostream>
#include <algorithm>
using namespace std;

// ============================================================
// MIN HEAP IMPLEMENTATION
// ============================================================

class MinHeap {
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
    
    // Moves element down the tree to maintain min heap property
    // Used after deletion
    void heapifyDown(int i) {
        int minIdx = i;
        int l = left(i);
        int r = right(i);
        
        // Find the smallest among node, left child, and right child
        if (l < heapSize && heap[l] < heap[minIdx])
            minIdx = l;
        if (r < heapSize && heap[r] < heap[minIdx])
            minIdx = r;
        
        // If smallest is not the current node, swap and continue heapifying
        if (minIdx != i) {
            swap(heap[i], heap[minIdx]);
            heapifyDown(minIdx);
        }
    }
    
public:
    // Constructor: creates heap with given capacity
    MinHeap(int cap = 100) {
        capacity = cap;
        heapSize = 0;
        heap = new int[capacity];
    }
    
    // Constructor: creates heap from an array (Heapify method)
    // Time Complexity: O(n)
    MinHeap(int arr[], int n, int cap = 100) {
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
    ~MinHeap() {
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
        
        // Move element up to maintain min heap property
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
        
        heapSize++;
        cout << "Inserted " << key << " into Min Heap\n";
    }
    
    // Deletes and returns the minimum element (root)
    // Time Complexity: O(log n)
    int deleteMin() {
        if (heapSize == 0) {
            cout << "Heap underflow!\n";
            return -1;
        }
        
        int minVal = heap[0];    // Store the minimum value
        heap[0] = heap[heapSize - 1];  // Move last element to root
        heapSize--;              // Reduce heap size
        
        // Move element down to maintain min heap property
        if (heapSize > 0) {
            int i = 0;
            while (true) {
                int minIdx = i;
                int l = left(i);
                int r = right(i);
                
                // Find the smallest among node, left child, and right child
                if (l < heapSize && heap[l] < heap[minIdx])
                    minIdx = l;
                if (r < heapSize && heap[r] < heap[minIdx])
                    minIdx = r;
                
                // If smallest is current node, heap property is satisfied
                if (minIdx == i)
                    break;
                
                // Swap and continue
                swap(heap[i], heap[minIdx]);
                i = minIdx;
            }
        }
        
        cout << "Deleted minimum element: " << minVal << " from Min Heap\n";
        return minVal;
    }
    
    // Returns the minimum element without removing it
    // Time Complexity: O(1)
    int getMin() {
        if (heapSize == 0) {
            cout << "Heap is empty!\n";
            return -1;
        }
        return heap[0];
    }
    
    // Displays all elements in the heap (level order)
    void display() {
        cout << "Min Heap: ";
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
// MAIN FUNCTION - MIN HEAP DEMONSTRATIONS
// ============================================================

int main() {
    // ============================================================
    // DEMONSTRATION 1: Building Heap from Random Array
    // ============================================================
    cout << "========== BUILDING MIN HEAP FROM ARRAY ==========\n";
    
    // Create a random unsorted array
    int randomArray[] = {20, 15, 30, 8, 10, 40, 25, 12, 18, 35};
    int n = sizeof(randomArray) / sizeof(randomArray[0]);
    
    cout << "Original Array: ";
    for (int i = 0; i < n; i++)
        cout << randomArray[i] << " ";
    cout << "\n\n";
    
    // Create Min Heap from array using constructor
    // This uses the efficient O(n) heapify algorithm
    cout << "Creating Min Heap from array...\n";
    MinHeap minHeapFromArray(randomArray, n);
    minHeapFromArray.display();
    cout << "Minimum element: " << minHeapFromArray.getMin() << "\n\n";
    
    // Demonstrate deletion from array-built heaps
    cout << "Deleting elements from Min Heap built from array:\n";
    minHeapFromArray.deleteMin();
    minHeapFromArray.display();
    minHeapFromArray.deleteMin();
    minHeapFromArray.display();
    cout << "\n";
    
    // ============================================================
    // DEMONSTRATION 2: Building Heap by Inserting Elements
    // ============================================================
    cout << "========== MIN HEAP - INSERT & DELETE ==========\n";
    MinHeap minHeap(50);  // Create heap with capacity 50
    
    // Insert elements one by one
    cout << "Inserting elements one by one:\n";
    minHeap.insert(3);
    minHeap.insert(2);
    minHeap.insert(15);
    minHeap.insert(5);
    minHeap.insert(4);
    minHeap.insert(45);
    minHeap.display();
    cout << "Minimum element: " << minHeap.getMin() << "\n\n";
    
    // Delete minimum elements
    cout << "Deleting minimum elements:\n";
    minHeap.deleteMin();
    minHeap.display();
    minHeap.deleteMin();
    minHeap.display();
    cout << "Minimum element: " << minHeap.getMin() << "\n\n";
    
    // ============================================================
    // DEMONSTRATION 3: Heap Sort using Min Heap (In-place)
    // ============================================================
    cout << "========== HEAP SORT DEMONSTRATION (IN-PLACE) ==========\n";
    int unsortedArray[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(unsortedArray) / sizeof(unsortedArray[0]);
    
    cout << "Original Array: ";
    for (int i = 0; i < size; i++)
        cout << unsortedArray[i] << " ";
    cout << "\n";
    
    // Build min heap from the array (in-place)
    cout << "Building Min Heap...\n";
    
    // Heapify the array - start from last non-leaf node
    for (int i = size / 2 - 1; i >= 0; i--) {
        int node = i;
        while (true) {
            int minIdx = node;
            int l = 2 * node + 1;
            int r = 2 * node + 2;
            
            if (l < size && unsortedArray[l] < unsortedArray[minIdx])
                minIdx = l;
            if (r < size && unsortedArray[r] < unsortedArray[minIdx])
                minIdx = r;
            
            if (minIdx == node)
                break;
            
            swap(unsortedArray[node], unsortedArray[minIdx]);
            node = minIdx;
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
        // Store minimum at correct position from start
        int minVal = unsortedArray[0];
        
        // Move last element to root
        unsortedArray[0] = unsortedArray[heapEnd - 1];
        heapEnd--;
        
        // Heapify down with reduced heap size
        int node = 0;
        while (true) {
            int minIdx = node;
            int l = 2 * node + 1;
            int r = 2 * node + 2;
            
            if (l < heapEnd && unsortedArray[l] < unsortedArray[minIdx])
                minIdx = l;
            if (r < heapEnd && unsortedArray[r] < unsortedArray[minIdx])
                minIdx = r;
            
            if (minIdx == node)
                break;
            
            swap(unsortedArray[node], unsortedArray[minIdx]);
            node = minIdx;
        }
        
        // Place extracted minimum at the end of heap
        unsortedArray[heapEnd] = minVal;
    }
    
    cout << "Sorted Array (ascending): ";
    for (int i = 0; i < size; i++)
        cout << unsortedArray[i] << " ";
    cout << "\n";
    
    return 0;
}