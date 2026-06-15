#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========== NODE STRUCTURE ==========
struct Node
{
    int prn;
    char name[50];
    struct Node *next;
};

struct Node *head = NULL;

// ========== a) ADD AND DELETE MEMBERS ==========

// Add President (at beginning)
void addPresident(int prn, char name[])
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->prn = prn;
    strcpy(newNode->name, name);
    newNode->next = head;
    head = newNode;

    printf("✓ President added: %s (PRN: %d)\n", name, prn);
}

// Add Secretary (at end)
void addSecretary(int prn, char name[])
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->prn = prn;
    strcpy(newNode->name, name);
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        printf("✓ Secretary added (also President): %s (PRN: %d)\n", name, prn);
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;

    printf("✓ Secretary added: %s (PRN: %d)\n", name, prn);
}

// Add Member (at end, before secretary position)
void addMember(int prn, char name[])
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->prn = prn;
    strcpy(newNode->name, name);
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        printf("✓ Member added (also President): %s (PRN: %d)\n", name, prn);
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;

    printf("✓ Member added: %s (PRN: %d)\n", name, prn);
}

// Delete President (from beginning)
void deletePresident()
{
    if (head == NULL)
    {
        printf("✗ Club is empty! No president to delete.\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;

    printf("✓ President deleted: %s (PRN: %d)\n", temp->name, temp->prn);
    free(temp);
}

// Delete Secretary (from end)
void deleteSecretary()
{
    if (head == NULL)
    {
        printf("✗ Club is empty! No secretary to delete.\n");
        return;
    }

    if (head->next == NULL)
    {
        printf("✓ Secretary deleted: %s (PRN: %d)\n", head->name, head->prn);
        free(head);
        head = NULL;
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;

    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }

    printf("✓ Secretary deleted: %s (PRN: %d)\n", temp->name, temp->prn);
    prev->next = NULL;
    free(temp);
}

// Delete Member by PRN
void deleteMember(int prn)
{
    if (head == NULL)
    {
        printf("✗ Club is empty!\n");
        return;
    }

    // If member to delete is president
    if (head->prn == prn)
    {
        deletePresident();
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;

    while (temp != NULL && temp->prn != prn)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("✗ Member with PRN %d not found!\n", prn);
        return;
    }

    prev->next = temp->next;
    printf("✓ Member deleted: %s (PRN: %d)\n", temp->name, temp->prn);
    free(temp);
}

// ========== b) COMPUTE TOTAL MEMBERS ==========
int countMembers()
{
    int count = 0;
    struct Node *temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

// ========== c) DISPLAY MEMBERS ==========
void displayMembers()
{
    if (head == NULL)
    {
        printf("✗ Club is empty!\n");
        return;
    }

    struct Node *temp = head;
    int position = 1;

    printf("\n========== PINNACLE CLUB MEMBERS ==========\n");
    printf("%-10s %-10s %-20s %-15s\n", "Position", "PRN", "Name", "Role");
    printf("----------------------------------------------------\n");

    while (temp != NULL)
    {
        char role[20];

        if (position == 1)
        {
            strcpy(role, "President");
        }
        else if (temp->next == NULL)
        {
            strcpy(role, "Secretary");
        }
        else
        {
            strcpy(role, "Member");
        }

        printf("%-10d %-10d %-20s %-15s\n", position, temp->prn, temp->name, role);
        temp = temp->next;
        position++;
    }
    printf("===========================================\n");
    printf("Total Members: %d\n", countMembers());
}

// ========== d) SORTING LINKED LIST ==========
void sortList()
{
    if (head == NULL || head->next == NULL)
    {
        printf("✗ List is empty or has only one member!\n");
        return;
    }

    printf("\n--- Before Sorting ---\n");
    displayMembers();

    struct Node *i, *j;
    int tempPrn;
    char tempName[50];

    for (i = head; i != NULL; i = i->next)
    {
        for (j = head; j->next != NULL; j = j->next)
        {
            if (j->prn > j->next->prn)
            {
                // Swap PRN
                tempPrn = j->prn;
                j->prn = j->next->prn;
                j->next->prn = tempPrn;

                // Swap Name
                strcpy(tempName, j->name);
                strcpy(j->name, j->next->name);
                strcpy(j->next->name, tempName);
            }
        }
    }

    printf("\n✓ List sorted by PRN!\n");
    printf("\n--- After Sorting ---\n");
    displayMembers();
}

// ========== e) MERGE TWO LINKED LISTS ==========
struct Node *head2 = NULL;

void addToSecondList(int prn, char name[])
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->prn = prn;
    strcpy(newNode->name, name);
    newNode->next = NULL;

    if (head2 == NULL)
    {
        head2 = newNode;
    }
    else
    {
        struct Node *temp = head2;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    printf("✓ Added to List 2: %s (PRN: %d)\n", name, prn);
}

void displaySecondList()
{
    if (head2 == NULL)
    {
        printf("✗ Second list is empty!\n");
        return;
    }

    struct Node *temp = head2;
    printf("\n========== SECOND LIST ==========\n");
    printf("%-10s %-20s\n", "PRN", "Name");
    printf("--------------------------------\n");

    while (temp != NULL)
    {
        printf("%-10d %-20s\n", temp->prn, temp->name);
        temp = temp->next;
    }
    printf("================================\n");
}

void mergeLists()
{
    if (head == NULL)
    {
        printf("✗ First list is empty!\n");
        return;
    }

    if (head2 == NULL)
    {
        printf("✗ Second list is empty!\n");
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = head2;
    head2 = NULL;

    printf("✓ Lists merged successfully!\n");
}

// ========== f) REVERSE USING THREE POINTERS ==========
void reverseList()
{
    if (head == NULL)
    {
        printf("✗ List is empty!\n");
        return;
    }

    printf("\n--- Before Reversing ---\n");
    displayMembers();

    struct Node *prev = NULL;
    struct Node *current = head;
    struct Node *next = NULL;

    printf("\n--- Reversing Process ---\n");
    int step = 1;

    while (current != NULL)
    {
        printf("Step %d:\n", step);

        // Store next
        next = current->next;
        printf("  1. Save next node\n");

        // Reverse link
        current->next = prev;
        printf("  2. Reverse current node's link\n");

        // Move pointers ahead
        prev = current;
        current = next;
        printf("  3. Move pointers forward\n\n");

        step++;
    }

    head = prev;

    printf("✓ List reversed successfully!\n");
    printf("\n--- After Reversing ---\n");
    displayMembers();
}

// ========== MAIN FUNCTION ==========
int main()
{
    int choice, prn;
    char name[50];

    printf("\n");
    printf("╔════════════════════════════════════════════╗\n");
    printf("║         PINNACLE CLUB MANAGEMENT          ║\n");
    printf("║    Computer Engineering Department        ║\n");
    printf("╚════════════════════════════════════════════╝\n");

    while (1)
    {
        printf("\n┌─────────────────────────────────────────┐\n");
        printf("│           MENU OPTIONS                  │\n");
        printf("├─────────────────────────────────────────┤\n");
        printf("│ 1.  Add President                       │\n");
        printf("│ 2.  Add Secretary                       │\n");
        printf("│ 3.  Add Member                          │\n");
        printf("│ 4.  Delete President                    │\n");
        printf("│ 5.  Delete Secretary                    │\n");
        printf("│ 6.  Delete Member (by PRN)              │\n");
        printf("│ 7.  Display Members                     │\n");
        printf("│ 8.  Count Total Members                 │\n");
        printf("│ 9.  Sort List by PRN                    │\n");
        printf("│ 10. Add to Second List                  │\n");
        printf("│ 11. Display Second List                 │\n");
        printf("│ 12. Merge Two Lists                     │\n");
        printf("│ 13. Reverse List (3 pointers)          │\n");
        printf("│ 14. Exit                                │\n");
        printf("└─────────────────────────────────────────┘\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch (choice)
        {
        case 1:
            printf("\n--- ADD PRESIDENT ---\n");
            printf("Enter PRN: ");
            scanf("%d", &prn);
            getchar();
            printf("Enter Name: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;
            addPresident(prn, name);
            break;

        case 2:
            printf("\n--- ADD SECRETARY ---\n");
            printf("Enter PRN: ");
            scanf("%d", &prn);
            getchar();
            printf("Enter Name: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;
            addSecretary(prn, name);
            break;

        case 3:
            printf("\n--- ADD MEMBER ---\n");
            printf("Enter PRN: ");
            scanf("%d", &prn);
            getchar();
            printf("Enter Name: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;
            addMember(prn, name);
            break;

        case 4:
            printf("\n--- DELETE PRESIDENT ---\n");
            deletePresident();
            break;

        case 5:
            printf("\n--- DELETE SECRETARY ---\n");
            deleteSecretary();
            break;

        case 6:
            printf("\n--- DELETE MEMBER ---\n");
            printf("Enter PRN of member to delete: ");
            scanf("%d", &prn);
            deleteMember(prn);
            break;

        case 7:
            displayMembers();
            break;

        case 8:
            printf("\nTotal Members: %d\n", countMembers());
            break;

        case 9:
            sortList();
            break;

        case 10:
            printf("\n--- ADD TO SECOND LIST ---\n");
            printf("Enter PRN: ");
            scanf("%d", &prn);
            getchar();
            printf("Enter Name: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;
            addToSecondList(prn, name);
            break;

        case 11:
            displaySecondList();
            break;

        case 12:
            printf("\n--- MERGE LISTS ---\n");
            mergeLists();
            break;

        case 13:
            reverseList();
            break;

        case 14:
            printf("\n✓ Thank you for using Pinnacle Club Management!\n");
            printf("✓ Exiting...\n\n");
            exit(0);

        default:
            printf("\n✗ Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

/*
═══════════════════════════════════════════════════════════
                    PINNACLE CLUB - EXPLAINED
═══════════════════════════════════════════════════════════

WHAT IS ASKED:
✓ a) Add and delete members/president/secretary
✓ b) Compute total number of members
✓ c) Display members
✓ d) Sorting of linked list
✓ e) Merging of two linked lists
✓ f) Reversing using three pointers

STRUCTURE:
- First node = President
- Middle nodes = Members
- Last node = Secretary

═══════════════════════════════════════════════════════════
                        HOW IT WORKS
═══════════════════════════════════════════════════════════

a) ADD & DELETE:
   • Add President → Insert at beginning
   • Add Secretary → Insert at end
   • Add Member → Insert at end
   • Delete President → Delete from beginning
   • Delete Secretary → Delete from end
   • Delete Member → Delete by PRN (search and remove)

b) COUNT MEMBERS:
   • Traverse list and count nodes

c) DISPLAY:
   • Shows Position, PRN, Name, Role
   • First = President, Last = Secretary, Others = Members

d) SORTING:
   • Bubble sort by PRN
   • Swaps both PRN and Name data

e) MERGING:
   • Connect end of List 1 to beginning of List 2
   • List 2 becomes part of List 1

f) REVERSING (3 Pointers):
   • prev = NULL
   • current = head
   • next = NULL
   • Loop: save next → reverse link → move forward

═══════════════════════════════════════════════════════════
                        EXAMPLE
═══════════════════════════════════════════════════════════

Add Members:
1. Add President: John (PRN: 101)
2. Add Member: Alice (PRN: 102)
3. Add Member: Bob (PRN: 103)
4. Add Secretary: Carol (PRN: 104)

Structure:
President → Member → Member → Secretary
  John   →  Alice →   Bob  →  Carol
 (101)      (102)    (103)    (104)

After Reverse:
Secretary → Member → Member → President
  Carol  →   Bob  →  Alice →   John
 (104)      (103)    (102)    (101)

After Sort (by PRN):
President → Member → Member → Secretary
  John   →  Alice →   Bob  →  Carol
 (101)      (102)    (103)    (104)

═══════════════════════════════════════════════════════════
                    EXAM TIPS
═══════════════════════════════════════════════════════════

1. SETUP:
   - Always add President first
   - Then add Members
   - Finally add Secretary

2. DELETE:
   - Delete President → New president is next member
   - Delete Secretary → Previous member becomes secretary
   - Delete Member → Any middle member

3. REVERSE:
   - President becomes Secretary
   - Secretary becomes President
   - Order completely reversed

4. MERGE:
   - Create two separate lists first
   - Merge connects List 2 to end of List 1

5. SORT:
   - Sorts by PRN (ascending order)
   - Uses bubble sort (simple to understand)

COMMON OPERATIONS SEQUENCE:
1. Add President
2. Add 2-3 Members
3. Add Secretary
4. Display (see structure)
5. Count (verify total)
6. Sort (rearrange by PRN)
7. Reverse (flip order)

═══════════════════════════════════════════════════════════
*/