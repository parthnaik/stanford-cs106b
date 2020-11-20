/*
 * File: QuicksortRevisited.cpp
 * --------------
 * This is an empty C++ source file.
 */

#include <iostream>
#include "console.h"

using namespace std;

struct Cell {
    int value;
    Cell* next;
};

void concatenateLists(Cell*& first, Cell* second);
void prependCell(Cell* toPrepend, Cell*& list);
void partitionList(Cell* list, Cell*& smaller, Cell*& pivot, Cell*& bigger);
void quicksort(Cell*& list);

int main() {
    
    return 0;
}


/* Concatenates the two given lists together, updating first to
 * point to the new first cell of the concatenated list.
 */
void concatenateLists(Cell*& first, Cell* second) {
    /* Base case: If the first list is empty, we concatenate the
     * lists by just setting the second list to point to the first
     * list.
     */
    if (first == NULL) {
        first = second;
    }
    /* Recursive step: Otherwise, we concatenate the second list to
     * the list appearing after the first cell.
     */
    else {
        concatenateLists(first->next, second);
    }
}

/* Prepends the given single cell to the given list, updating the
 * pointer to the first element of that linked list.
 */
void prependCell(Cell* toPrepend, Cell*& list) {
    toPrepend->next = list;
    list = toPrepend;
}

void partitionList(Cell* list, Cell*& smaller, Cell*& pivot, Cell*& bigger) {
    /* Distribute cells in the list into the three groups. */
    while (list != NULL) {
        /* Remember the next pointer, because we're going to remove this
         * element from the list it is currently in.
         */
        Cell* next = list->next;
        /* Determine which list this element belongs to. */
        if (list->value == pivot->value) {
            prependCell(list, pivot);
        } else if (list->value < pivot->value) {
            prependCell(list, smaller);
        } else {
            prependCell(list, bigger);
        }
        list = next;
    }
}

void quicksort(Cell*& list) {
    /* Determine the length of the list. If it's length 0 or 1, we're done. */
    if (list == NULL || list->next == NULL) return;
    /* Remove the first element as the pivot element. */
    Cell* pivot = list;
    Cell* rest = pivot->next;
    /* Remove the pivot element from the list. */
    pivot->next = NULL;
    /* Create two other lists: one of elements less than the pivot and one of
     * elements greater than the pivot.
     */
    Cell* smaller = NULL;
    Cell* bigger = NULL;
    /* Distribute the elements into the three lists based on
     * whether they are smaller than, equal to, or greater
     * than the pivot.
     */
    partitionList(rest, smaller, pivot, bigger);
    /* Recursively sort the two smaller regions. */
    quicksort(smaller);
    quicksort(bigger);
    /* Concatenate everything together. */
    concatenateLists(smaller, pivot);
    concatenateLists(smaller, bigger);
    /* The sorted list now begins with the element pointed at by the
     * smaller pointer.
     */
    list = smaller;
}

