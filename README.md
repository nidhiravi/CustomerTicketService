# Customer Service Ticket Management System
This C program implements a simple ticket management system for handling customer issues. The system allows users to create, update, search, and process support tickets

Features
Create Ticket: Add a new ticket to the queue with a unique ID, customer name, issue type, and priority.
Display Tickets: View all tickets currently in the queue.
Update Ticket: Modify the issue details or customer name associated with a ticket.
Remove Ticket: Delete a ticket from the queue.
Process Ticket: Mark a ticket as processed and move it to the ticket history.
Display History: View all processed tickets along with their details.
Find Ticket: Search for a ticket by its ID and display its details.
Display Ticket Solutions: Provide solutions based on the issue number.

The Ticket Management System uses the following Data Structures and Algorithms (DSA):
Linked List: The system uses a linked list to manage the queue of tickets (TicketQueue) and the history of processed tickets (TicketHistory). Each ticket is a node in the linked list, allowing for efficient insertion, deletion, and traversal operations.
Queue: The TicketQueue is implemented using a linked list to represent a First-In-First-Out (FIFO) structure for managing incoming support tickets.
Basic Searching: The system performs linear search operations to find and update tickets by their ID in the queue.
