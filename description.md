

## Summary Table

| Operation | Time Complexity | Space Complexity | Notes |
|-----------|----------------|------------------|-------|
| **Insert** | O(log n) | O(1) | Iterative heapifyUp |
| **Delete Min/Max** | O(log n) | O(log n) | Recursive heapify |
| **Get Min/Max** | O(1) | O(1) | Direct array access |
| **Build Heap** | O(n) | O(1) | Top-down heapify |
| **Heapify** | O(log n) | O(log n) | Recursive |
| **Display** | O(n) | O(1) | Array traversal |
| **isEmpty/size** | O(1) | O(1) | Direct access |
| **Heap Storage** | - | O(n) | Array of n elements |

---

## Practical Implications

### When to Use Heaps

1. **Priority Queues**: O(log n) insert and delete make heaps ideal
2. **Finding K largest/smallest elements**: O(n + k log n)
3. **Heap Sort**: O(n log n) time, O(1) space
4. **Median Finding**: Using two heaps (min and max)

---

## Comparison with Other Data Structures

| Operation | Heap | BST | Array (unsorted) | Array (sorted) |
|-----------|------|-----|-----------------|----------------|
| Insert | O(log n) | O(log n) avg | O(1) | O(n) |
| Delete Min/Max | O(log n) | O(log n) avg | O(n) | O(1) or O(n) |
| Find Min/Max | O(1) | O(log n) avg | O(n) | O(1) |
| Search arbitrary | O(n) | O(log n) avg | O(n) | O(log n) |
| Build from array | O(n) | O(n log n) | O(1) | O(n log n) |

---