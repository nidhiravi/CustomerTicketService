#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ticket {
    char id[5];
    char customerName[50];
    char issue[100];
    int issuenum;
    struct Ticket* next;
    int priority;
};

struct TicketQueue {
    struct Ticket* front;
};

struct TicketHistory {
    struct Ticket* processed;
};


struct Ticket* createTicket(char id[], char customerName[], char issue[], int issuenum, int prior) {
    struct Ticket* newTicket = (struct Ticket*)malloc(sizeof(struct Ticket));
    if (newTicket == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    strcpy(newTicket->id, id);
    strcpy(newTicket->customerName, customerName);
    strcpy(newTicket->issue, issue);
    newTicket->issuenum = issuenum;
    newTicket->next = NULL;
    newTicket->priority = prior;

    return newTicket;
}

struct TicketQueue* initTicketQueue() {
    struct TicketQueue* queue = (struct TicketQueue*)malloc(sizeof(struct TicketQueue));
    if (queue == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    queue->front = NULL;
    return queue;
}

struct TicketHistory* initTicketHistory() {
    struct TicketHistory* history = (struct TicketHistory*)malloc(sizeof(struct TicketHistory));
    if (history == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    history->processed = NULL;
    return history;
}

void enqueue(struct TicketQueue* queue, struct Ticket* newTicket) {
    if (queue->front == NULL) {
        queue->front = newTicket;
    } else {
        struct Ticket* current = queue->front;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newTicket;
    }
    newTicket->next = NULL; 
}

void updateTicket(struct TicketQueue* queue, const char* ticketID, int newIssuenum, const char* newIssue) {
    struct Ticket* current = queue->front;
    while (current != NULL) {
        if (strcmp(current->id, ticketID) == 0) {
            current->issuenum = newIssuenum;
            strcpy(current->issue, newIssue);
            printf("Ticket %s updated successfully\n", ticketID);
            return;
        }
        current = current->next;
    }
    printf("Ticket %s not found in the queue\n", ticketID);
}

void updateName(struct TicketQueue* queue, const char* ticketID, const char* newCustomerName,  int newIssuenum, const char* newIssue) {
    struct Ticket* current = queue->front;
    while (current != NULL) {
        if (strcmp(current->id, ticketID) == 0) {
            current->issuenum = newIssuenum;
            strcpy(current->issue, newIssue);
            strcpy(current->customerName, newCustomerName);
            printf("Customer name for Ticket %s updated successfully\n", ticketID);
            return;
        }
        current = current->next;
    }
    printf("Ticket %s not found in the queue\n", ticketID);
}

void displayQueue(struct TicketQueue* queue) {
    struct Ticket* current = queue->front;
    while (current != NULL) {
        printf("Ticket ID: %s, Priority: %d, Issue.No: %d, Issue: %s\n", current->id, current->priority, current->issuenum, current->issue);
        current = current->next;
    }
}

void displayTicketSolutions(const char* ticketnum,int issuenum) {
    printf("Solution for %s (Issue.No %d):\n", ticketnum,issuenum);
    switch (issuenum) {
        case 1:
            printf(" Sorry for the inconvenience. The website may be experiencing downtime or maintenance issues. Please try again after a while\n\n");
            break;
        case 2:
            printf(" Clear your browser's cache and cookies, disable browser extensions, and reset your password\n\n");
            break;
        case 3:
            printf(" Please email a request form for password recovery\n\n");
            break;
        case 4:
            printf(" Go to settings, account, and delete my account\n\n");
            break;
        case 5:
            printf(" Go to settings, my account, extend, and renew your account\n\n");
            break;
        default:
            break;
    }
}

void displayHistory(struct TicketHistory* history) {
    printf("\n\nProcessed Ticket History:\n\n");
    struct Ticket* current = history->processed;
    if(current != NULL){
    while (current != NULL) {
        printf("Ticket ID: %s, Issue.No: %d, Issue: %s\n\n", current->id, current->issuenum, current->issue);
        current = current->next;
    }}
    else{
    printf("No history\n");}
}

struct Ticket* ProcessTicket(struct TicketQueue* queue, const char* ticketID, struct TicketHistory* history) {
    struct Ticket* current = queue->front;
    if (strcmp(current->id, ticketID) == 0) {
            queue->front = current->next;
            current->next = history->processed;
            history->processed = current;
            return current;
        }
    else{
    return NULL;} 
}

struct Ticket* removeTicket(struct TicketQueue* queue, const char* ticketID) {
    struct Ticket* current = queue->front;
    struct Ticket* prev = NULL;

    while (current != NULL && strcmp(current->id, ticketID) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Ticket not found in the queue\n");
        return NULL;
    }

    if (prev == NULL) {
        queue->front = current->next;
    } else {
        prev->next = current->next;
    }

    return current;
}

void findTicket(struct TicketQueue* queue, const char* ticketID) {
    struct Ticket* current = queue->front;
    while (current != NULL) {
        if (strcmp(current->id, ticketID) == 0) {
           printf("Ticket ID : %s\n", ticketID);
           printf("Name      : %s\n", current->customerName);
           printf("Issue.No  : %d\v", current->issuenum);
           printf("Issue     : %s\n", current->issue);

           return;
        }
        current = current->next;
    }
    printf("Ticket not present");
}



void freeQueue(struct TicketQueue* queue) {
    struct Ticket* current = queue->front;
    while (current != NULL) {
        struct Ticket* temp = current;
        current = current->next;
        free(temp);
    }
    free(queue);
}

void freeHistory(struct TicketHistory* history) {
    struct Ticket* current = history->processed;
    while (current != NULL) {
        struct Ticket* temp = current;
        current = current->next;
        free(temp);
    }
    free(history);
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct TicketQueue* supportQueue = initTicketQueue();
    struct TicketHistory* ticketHistory = initTicketHistory();
    char customerName[50];
    char issue[100];
    int issuenum;
    char continueOption;
    int ans = 1;
    int count= 1;

    printf("\nResolving Issue :\n");
    do {
        printf("\nEnter your name: ");
        scanf("%s", customerName);
        clearInputBuffer();

        printf("\nWhat may be your issue?\n");
        printf("1. Network Error\n");
        printf("2. Login Issues\n");
        printf("3. Forgot Password\n");
        printf("4. Delete Account\n");
        printf("5. Renew Account\n");

        printf("Enter the corresponding number of your issue: ");
        scanf("%d", &issuenum);
        clearInputBuffer();

        switch (issuenum) {
            case 1:
                strcpy(issue, "Network Error");
                break;
            case 2:
                strcpy(issue, "Login Issues");
                break;
            case 3:
                strcpy(issue, "Forgot Password");
                break;
            case 4:
                strcpy(issue, "Delete Account");
                break;
            case 5:
                strcpy(issue, "Renew Account");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                continue;
        }

        static int ticketCount = 1;
        char ticketID[5];
        sprintf(ticketID, "T%03d", ticketCount++);
        
        enqueue(supportQueue, createTicket(ticketID, customerName, issue, issuenum, count));

        printf("\nTicket Assigned:\n");
        printf("Ticket ID : %s\n", ticketID);
        printf("Name      : %s\n", customerName);
        printf("Issue.No  : %d\n", issuenum);
        printf("Issue     : %s\n", issue);
        printf("\nDo you want to continue (y/n)? ");
        scanf(" %c", &continueOption);
        clearInputBuffer();
        count+=1;

    } while (continueOption == 'y' || continueOption == 'Y');
    printf("\nService in process...\n");
    do {
        int in;
        if(supportQueue->front==NULL){
            ans =0;
            break;
        }
        else{
        printf("\n\nHow may we help you today? : \n");
        printf("1.Search Ticket\n");
        printf("2.Display all Tickets\n");
        printf("3.Update Ticket\n");
        printf("4.Remove Ticket\n");
        printf("5.Get solution\n");
        printf("0.End\n");
        printf("Enter choice : ");
        scanf("%d",&in);
        switch(in){ 
           case 1:{
                char ticketID[5];
                printf("\nEnter the Ticket number for searching (or 'stop' to end): ");
                scanf("%s", ticketID);

                if (strcmp(ticketID, "stop") == 0) {
                   ans=0;
                    break;
                }
                findTicket(supportQueue,ticketID);
                break;
            }
            case 2:{
                printf("\nCurrent Ticket Queue:\n\n");
                displayQueue(supportQueue);
                break; 
            }
            case 3:{
                char ans[1];
                char newCustomerName[50];
                char ticketToUpdate[5];
                char newissue[100];
                int newissuenum;


                printf("Do u want to update the name on ticket too (y/n) :");
                scanf("%s",ans);
                
                printf("\nEnter the Ticket number to update: ");
                scanf("%s", ticketToUpdate);

                printf("1. Network Error\n");
                printf("2. Login Issues\n");
                printf("3. Forgot Password\n");
                printf("4. Delete Account\n");
                printf("5. Renew Account\n");
                printf("Enter the corresponding number of your issue: ");
                scanf("%d", &newissuenum);
                clearInputBuffer();

                switch (issuenum) {
                    case 1:
                        strcpy(newissue, "Network Error");
                        break;
                    case 2:
                        strcpy(newissue, "Login Issues");
                        break;
                    case 3:
                        strcpy(newissue, "Forgot Password");
                        break;
                    case 4:
                        strcpy(newissue, "Delete Account");
                        break;
                    case 5:
                        strcpy(newissue, "Renew Account");
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                        continue;
                }

                if(strcmp(ans,"n")==0){
                // Update the ticket in the supportQueue
                updateTicket(supportQueue, ticketToUpdate, newissuenum, newissue);
                }
                else{
                    printf("Enter the new customer name: ");
                    scanf("%s", newCustomerName);
                    updateName(supportQueue, ticketToUpdate, newCustomerName, newissuenum, newissue);
                }
                break;
            }
            case 4:{
                char ticketID[5];
                printf("\nEnter the Ticket number for removal (or 'stop' to end): ");
                scanf("%s", ticketID);

                if (strcmp(ticketID, "stop") == 0) {
                    ans = 0;
                    break;
                }

                struct Ticket* removedTicket = removeTicket(supportQueue, ticketID);

                if (removedTicket != NULL) {
                    printf("Removed Ticket ID: %s\n", removedTicket->id);
                } else {
                    printf("Ticket not found in the queue\n");
                }                
                break;
            }
            case 5:{
               printf("\nCurrent Ticket Queue:\n\n");
               displayQueue(supportQueue);

               char ticketID[5];
               printf("\nEnter the Ticket number for processing (or 'stop' to end): ");
              scanf("%s", ticketID);

              if (strcmp(ticketID, "stop") == 0) {
                 ans =0;
                 break;  
               }   
               struct Ticket* processedTicket = ProcessTicket(supportQueue, ticketID, ticketHistory);

              if (processedTicket != NULL) {
                     // Display ticket details
                    printf("\nTicket ID   : %s\n", processedTicket->id);
                    printf("Name        : %s\n", processedTicket->customerName);
                    printf("Issue.No    : %d\n", processedTicket->issuenum);
                    printf("Issue       : %s\n", processedTicket->issue);
        
                    // Display ticket solution
                    printf("\nTicket Solutions:\n");
                    displayTicketSolutions(processedTicket->id,processedTicket->issuenum);
                } else {
                    printf("Please Wait ..\n");
                }
                break;
                }
            case 0:
                ans = 0;
                break;
            default:
                printf("Invalid Input\n\n");
                break;
            }
        }

    } while (ans==1);
    displayHistory(ticketHistory);
    
    freeQueue(supportQueue);
    freeHistory(ticketHistory);
   

    return 0;
}