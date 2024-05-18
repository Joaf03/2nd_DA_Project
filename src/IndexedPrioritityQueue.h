#ifndef INC_2ND_PROJECT_INDEXEDPRIORITITYQUEUE_H
#define INC_2ND_PROJECT_INDEXEDPRIORITITYQUEUE_H

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <iostream>

/**
 * @brief A class for an indexed priority queue.
 */
class IndexedPriorityQueue {
private:
    std::vector<std::pair<int, double>> heap; // Vector of pairs: (nodeId, distance)
    std::vector<int> position; // Maps node index to heap position

public:
    /**
     * @brief Constructs an indexed priority queue of a given size.
     * @param size The size of the priority queue.
     */
    explicit IndexedPriorityQueue(int size) : position(size, -1) {}

    /**
     * @brief Pushes a node with a given priority into the priority queue.
     * @param node The node to be inserted.
     * @param priority The priority of the node.
     * @complexity O(log n), where n is the number of elements in the priority queue.
     */
    void push(int node, double priority) {
        if (position[node] != -1) {
            decreaseKey(node, priority);
        } else {
            heap.emplace_back(node, priority);
            int heapIndex = static_cast<int>(heap.size()) - 1;
            position[node] = heapIndex;
            heapifyUp(heapIndex);
        }
    }

    /**
     * @brief Pops the node with the minimum priority from the priority queue.
     * @return The node with the minimum priority.
     * @complexity O(log n), where n is the number of elements in the priority queue.
     */
    int popMin() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }

        int minNode = heap[0].first;
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            position[heap[0].first] = 0;
            heapifyDown(0);
        }

        position[minNode] = -1;
        return minNode;
    }

    /**
     * @brief Decreases the priority of a given node.
     * @param node The node whose priority is to be decreased.
     * @param newPriority The new priority of the node.
     * @complexity O(log n), where n is the number of elements in the priority queue.
     */
    void decreaseKey(int node, double newPriority) {
        int heapIndex = position[node];
        heap[heapIndex].second = newPriority;
        heapifyUp(heapIndex);
    }

    /**
     * @brief Checks if the priority queue is empty.
     * @return True if the priority queue is empty, false otherwise.
     * @complexity O(1)
     */
    [[nodiscard]] bool empty() const {
        return heap.empty();
    }

    /**
     * @brief Gets the minimum distance (priority) from the priority queue.
     * @return The minimum distance.
     * @complexity O(1)
     */
    [[nodiscard]] double getMinDistance() const {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0].second;
    }

    /**
     * @brief Clears the priority queue.
     * @complexity O(n), where n is the size of the priority queue.
     */
    void clear() {
        heap.clear();
        heap.shrink_to_fit();
        std::fill(position.begin(), position.end(), -1);
    }

private:
    /**
     * @brief Restores the heap property by moving the element at index i up the heap.
     * @param i The index of the element to move up.
     * @complexity O(log n), where n is the number of elements in the heap.
     */
    void heapifyUp(int i) {
        while (i > 0 && heap[i].second < heap[parent(i)].second) {
            std::swap(heap[i], heap[parent(i)]);
            position[heap[i].first] = i;
            position[heap[parent(i)].first] = parent(i);
            i = parent(i);
        }
    }

    /**
     * @brief Restores the heap property by moving the element at index i down the heap.
     * @param i The index of the element to move down.
     * @complexity O(log n), where n is the number of elements in the heap.
     */
    void heapifyDown(int i) {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < heap.size() && heap[left].second < heap[smallest].second) {
            smallest = left;
        }
        if (right < heap.size() && heap[right].second < heap[smallest].second) {
            smallest = right;
        }
        if (smallest != i) {
            std::swap(heap[i], heap[smallest]);
            position[heap[i].first] = i;
            position[heap[smallest].first] = smallest;
            heapifyDown(smallest);
        }
    }

    /**
     * @brief Gets the parent index of a given index.
     * @param i The index of the element.
     * @return The parent index.
     * @complexity O(1)
     */
    static int parent(int i) {
        return (i - 1) / 2;
    }

    /**
     * @brief Gets the left child index of a given index.
     * @param i The index of the element.
     * @return The left child index.
     * @complexity O(1)
     */
    static int leftChild(int i) {
        return 2 * i + 1;
    }

    /**
     * @brief Gets the right child index of a given index.
     * @param i The index of the element.
     * @return The right child index.
     * @complexity O(1)
     */
    static int rightChild(int i) {
        return 2 * i + 2;
    }
};

#endif //INC_2ND_PROJECT_INDEXEDPRIORITITYQUEUE_H
