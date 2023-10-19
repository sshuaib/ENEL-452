/**
   Project: Implementation of a Queue in C++.
   Programmer: Karim Naqvi
   Course: enel452

   Edited by: Salman Shuaib | 200374212
*/

#include "queue.h" 
#include <iostream>
#include <cstdlib>              // for exit

using namespace std;

Queue::Queue()
{
    head = 0;
    tail = 0;
    nelements = 0;
    verbose = false;
}

Queue::~Queue()
{
    for (QElement* qe = head; qe != 0;)
    {
	QElement* temp = qe;
	qe = qe->next;
	delete(temp);
    }
}

void Queue::remove(Data* d)
{
    if (size() > 0)
    {
        QElement* qe = head;
        head = head->next;
        nelements--;
        *d = qe->data;
	delete qe;
    }
    else
    {
        cerr << "Error: Queue is empty.\n";
        exit(1);
    }
}

void Queue::insert(Data d)
{
    if (verbose) std::cout << "insert(d)\n";
    QElement* el = new QElement(d);
    if (size() > 0)
    {
        tail->next = el;
    }
    else
    {
        head = el;
    }
    tail = el;
    nelements++;
}

void Queue::insert(Data d, unsigned position)
{
    if (position > size()) {
        // Check if the requested position is out of range
        std::cout << "insert: range error.\n";
        exit(3);  // Exit the program with an error code
    }

    QElement* el = new QElement(d);  // Create a new QElement with data 'd'

    if (position == 0) {
        // If inserting at the front (position 0)
        el->next = head;  // Set the new element's next to the current head
        head = el;  // Set the new element as the new head
        if (size() == 0) {
            // If the queue is empty, set the new element as the tail
            tail = el;
        }
    } else if (position == size()) {
        // If appending at the end (position equals size)
        tail->next = el;  // Set the current tail's next to the new element
        tail = el;  // Set the new element as the new tail
    } else {
        // Inserting at a specific position
        QElement* prev = head;  // Start with the head element
        for (unsigned i = 1; i < position; i++) {
            prev = prev->next;  // Traverse the queue to find the previous element to the insertion point
        }
        el->next = prev->next;  // Set the new element's next to the next of the previous element
        prev->next = el;  // Set the previous element's next to the new element
    }

    nelements++;  // Increment the number of elements in the queue
}

bool Queue::search(Data otherData) const
{
    QElement* insideEl = head;
    for (int i = 0; i < nelements; i++)
    {
        if (insideEl->data.equals(otherData))
            return true;
        insideEl = insideEl->next;
    }
    return false;
}

void Queue::print() const
{
    QElement* qe = head;
    if (size() > 0)
    {
        for (unsigned i = 0; i < size(); i++)
        {
            cout << i << ":(" << qe->data.x << "," << qe->data.y << ") ";
            qe = qe->next;
        }
    }
    cout << "\n";
}

unsigned Queue::size() const
{
    return nelements;
}
