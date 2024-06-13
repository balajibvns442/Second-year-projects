#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXUSERS 5
#define WEEKDAYS 7
#define NAMELENGTH 50

typedef struct Individual
{
    int group; // group id of the group the individual is in
    int ID;    // given from 0
    char Name[NAMELENGTH];
    int Age;
    int DailyStepGoal;
    int WeeklyStepCount[WEEKDAYS];
    struct Individual *next;
    struct Individual *team; // new feature for optimisation
} users;

typedef struct Group
{
    int group_id;
    char group_name[NAMELENGTH];
    users *members;
    int weekly_goal;
    struct Group *next;
} group;

int parse(char s[])
{
    int num = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        num = num * 10 + (s[i] - 48);
    }
    return num;
}

int group_count(group *group)
{
    int sum = 0;
    int cnt = 0;
    users *temp = group->members;
    while (temp)
    {
        cnt++;
        for (int i = 0; i < 7; i++)
            sum = sum + temp->WeeklyStepCount[i];
        temp = temp->team;
    }
    sum = sum / cnt;
    return sum;
}
// updated
int Avg_steps(int steps[])
{
    int sum = 0;
    for (int i = 0; i < 7; i++)
        sum += steps[i];
    return sum / 7;
} // calculates the average steps per day

void visit_user(users *user)
{
    if (user)
    {
        printf("ID \t %d\n", user->ID);
        printf("Group \t %d\n", user->group);
        printf("Name \t %s\n", user->Name);
        printf("Age \t %d\n", user->Age);
        printf("Daily Goal\t %d\n", user->DailyStepGoal);
        printf("Weekly goal (Sundya->Saturday):\n");
        for (int i = 0; i < 7; i++)
            printf("   %d", user->WeeklyStepCount[i]);
        printf("\n the average step count of the week is %d \n", Avg_steps(user->WeeklyStepCount));
        printf("\n");
    }
}
// updated
users *find_user_id(users *head, int id)
{
    users *temp;
    int flag = 0;
    if (head)
    {
        temp = head;
        while (temp != NULL && flag == 0)
        {
            if (temp->ID == id)
                flag = 1;
            else
                temp = temp->next;
        }
        if (flag == 0)
            temp = NULL;
    }
    else
        temp = head;
    return temp;
} // finds the user details for a given id and returns the pointer for his details
// updated
group *create_group_list(users *user_list, group *head)
{
    FILE *fp = fopen("group.txt", "r");
    char word[40];
    group *tail = (group *)malloc(sizeof(group));
    head = tail;
    while (fscanf(fp, "%s", word) != EOF)
    {
        int d;
        group *temp = (group *)malloc(sizeof(group));
        tail->next = temp;
        int c;

        temp->group_id = parse(word);

        fscanf(fp, "%s", word);
        strcpy(temp->group_name, word);

        fscanf(fp, "%d", &c);
        int flag = 0 ;
        users* utail = NULL;

        for (int i = 0; i < c ; i++)
        {
            fscanf( fp , "%s" , word) ;
             users *uptr = find_user_id(user_list, parse(word)); // getting the user pointer

            if (uptr)
            { // NULL represents invalid user
                if (uptr->group == 0)
                { // an independent user
                    if (flag == 0)
                    {
                        temp->members = uptr;
                        flag = 1;
                    } // for first member of the group
                    else
                        utail->team = uptr; // for later members

                    uptr->group = temp->group_id; // assigning group to the individual
                    utail = uptr;                 // updating tail
                }
                else
                    printf(" WARNING : the user %d is present alreday prresent in the group %d \n", uptr->ID, uptr->group);
            }
            else
                printf("INVALID : the given user id is invalid , please give a valid user id \n ");
        }
        
        fscanf(fp, "%d", &c);
        temp->weekly_goal = c;

        temp->next = NULL;
        tail = tail->next;
    }
    tail = head;
    head = head->next;
    free(tail);

    fclose(fp);
    return head;
}
// updated
users *create_user_list(users *head)
{

    FILE *fp = fopen("individuals.txt", "r");
    char word[40];
    int c;
    users *tail = (users *)malloc(sizeof(users));
    head = tail;
    while (fscanf(fp, "%s", word) == 1)
    {                                                 // traversing the file
        users *temp = (users *)malloc(sizeof(users)); // creating space
        tail->next = temp;
        int c;
        // reading string from file
        temp->ID = parse(word); // changing it into int
        temp->group = 0;
        fscanf(fp, "%s", word);
        strcpy(temp->Name, word); // setting word

        fscanf(fp, "%d", &c);
        temp->Age = c; // setting age
        fscanf(fp, "%d", &c);
        temp->DailyStepGoal = c; // Daily step goal
        for (int i = 0; i < 7; i++)
        {
            fscanf(fp, "%d", &c);
            temp->WeeklyStepCount[i] = c; // weekly count of steps
        }
        temp->next = NULL;
        temp->team = NULL; // initially independent // new feature
        tail = tail->next; // setting it(new) to tail
    }

    tail = head;
    head = head->next;
    free(tail);

    fclose(fp);
    return head; // returning the starting node pointer
}
// updated
users *user_merge(users *lptr1, users *lptr2)
{
    users *ptr1, *ptr2, *result, *head, *tail;

    if (lptr1 == NULL)
        result = lptr2;
    else if (lptr2 == NULL)
        result = lptr1;
    else
    {
        ptr1 = lptr1;
        ptr2 = lptr2;

        if (lptr1->ID < lptr2->ID)
        {
            result = lptr1;
            ptr1 = ptr1->next;
        }
        else
        {
            result = lptr2;
            ptr2 = ptr2->next;
        }
        tail = result;

        while ((ptr1 != NULL) && (ptr2 != NULL))
        {
            if (ptr1->ID < ptr2->ID)
            {
                tail->next = ptr1;
                tail = tail->next;
                ptr1 = ptr1->next;
            }
            else
            {
                tail->next = ptr2;
                tail = tail->next;
                ptr2 = ptr2->next;
            }
        }

        if (ptr1 != NULL)
            tail->next = ptr1;
        else
            tail->next = ptr2;
    }

    return result;
}
// updated
users *user_divide(users *lptr)
{
    users *fast, *slow;

    slow = lptr;
    if (lptr)
        fast = lptr->next;
    if (fast)
        fast = fast->next;

    while (fast != NULL)
    {
        slow = slow->next;
        fast = fast->next;
        if (fast)
            fast = fast->next;
    }

    users *ptr = slow->next;
    slow->next = NULL;

    return ptr;
}
// updated
users *user_merge_sort(users *lptr)
{
    users *ptr;
    users *head = lptr;

    if ((lptr != NULL) && (lptr->next != NULL))
    {
        ptr = user_divide(lptr);
        lptr = user_merge_sort(lptr);
        ptr = user_merge_sort(ptr);
        head = user_merge(lptr, ptr);
    }

    return head;
}
// updated
group *group_merge(group *lptr1, group *lptr2)
{
    group *ptr1, *ptr2, *result, *head, *tail;

    if (lptr1 == NULL)
        result = lptr2;
    else if (lptr2 == NULL)
        result = lptr1;
    else
    {
        ptr1 = lptr1;
        ptr2 = lptr2;
        if (group_count(lptr1) > group_count(lptr2))
        {
            result = lptr1;
            ptr1 = ptr1->next;
        }
        else
        {
            result = lptr2;
            ptr2 = ptr2->next;
        }
        tail = result;

        while ((ptr1 != NULL) && (ptr2 != NULL))
        {
            if (group_count(ptr1) > group_count(ptr2))
            {
                tail->next = ptr1;
                tail = tail->next;
                ptr1 = ptr1->next;
            }
            else
            {
                tail->next = ptr2;
                tail = tail->next;
                ptr2 = ptr2->next;
            }
        }

        if (ptr1 != NULL)
            tail->next = ptr1;
        else
            tail->next = ptr2;
    }
    return result;
}
// updated
group *group_divide(group *lptr)
{
    group *fast, *slow;
    slow = lptr;
    if (lptr)
        fast = lptr->next;
    if (fast)
        fast = fast->next;

    while (fast)
    {
        slow = slow->next;
        fast = fast->next;
        if (fast)
            fast = fast->next;
    }

    group *temp = slow->next;
    slow->next = NULL;
    return temp;
}
// updated
group *group_mwrge_sort(group *lptr)
{
    group *temp;
    group *head = lptr;

    if ((lptr != NULL) && (lptr->next != NULL))
    {
        temp = group_divide(lptr);
        lptr = group_mwrge_sort(lptr);
        temp = group_mwrge_sort(temp);
        head = group_merge(lptr, temp);
    }

    return head;
}
// updated
void display_all_users(users *head)
{
    if (head == NULL)
    {
        printf("there are no users yet\n");
    }
    else
    {
        users *temp = head;
        while (temp)
        {
            visit_user(temp);
            temp = temp->next;
        }
    }
}
// updated
users *create_user()
{
    users *newIndividual = (users *)malloc(sizeof(users));
    if (!newIndividual)
    {
        printf("Memory allocation failed.\n");
        newIndividual = NULL; // type mismatch ?
    }
    else
    {
        newIndividual->group = 0; // o is set for no group , natural number says the group
        printf("\n enter the desired ID of the user (should be unique) :");
        scanf("%d", &newIndividual->ID);
        printf("\n Enter the name of user :");
        scanf("%s", newIndividual->Name);
        printf("\n Enter the age of user : ");
        scanf("%d", &newIndividual->Age);
        printf("]\\n Enter the daily step goal , that user wants to complete : ");
        scanf("%d", &newIndividual->DailyStepGoal);
        printf("\n Enter the weekly step count (sunday to saturday) \n");
        for (int i = 0; i < 7; i++)
            scanf("%d", &newIndividual->WeeklyStepCount[i]);
        newIndividual->next = NULL;

        printf("user created succesfully \n");
    }

    return newIndividual;
}

users *Add_Person(users *head, users *new) // inserts the new node correctly at position acc to id
{
    printf("Entere dthe add person function \n");
    if (head == NULL)
    {
        printf("entered if part \n");
        head = new;
        new->next = NULL;
    }

    else
    {
        printf("entered else part \n");
        users *temp = head;
        users *prev = NULL;

        while (temp->ID < new->ID && temp->next != NULL) // inorder to acces the ID of the user
        {
            prev = temp;
            temp = temp->next;
            printf("in the loop \n");
        } // id skipping

        if (temp->next == NULL)
        {
            if (temp->ID < new->ID)
            {
                temp->next = new;
                new->next = NULL;
            }
            else
            {
                prev->next = new;
                new->next = temp;
            }
        } // for dealing with the last node case
          // as we can not acces ID in the comparision
        else
        {
            if (temp != head)
                prev->next = new;
            else
                head = new;
            new->next = temp;
        }
    }
    printf("user inserted successfully \n");

    return head;
}
// variables 'temp' , 'flag'
// o(n) worst case
group *Create_group(group *group_list, users *user_list)
{
    group *new = (group *)malloc(sizeof(group)); // new memory allocation

    if (!new)
        printf("sorry there is no memory available in heap \n");

    else
    {
        printf("Enter the name of the new group ; \n");
        scanf("%s", new->group_name);
        printf("Enter the unique ID of the group : \n");
        scanf("%d", &new->group_id);
        printf("Enter the member ID of the group members : \n");
        printf("(give all the 5 entries ,empty ones with 0)");
        int mem_id[5];
        for (int i = 0; i < 5; i++)
            scanf("%d", &mem_id[i]);

        users *utail = NULL;
        int cnt = 0;
        int flag = 0;

        for (int i = 0; i < 5; i++)
        {
            users *uptr = find_user_id(user_list, mem_id[i]); // finding the id
            if (uptr)
            { // NULL represents invalid user
                if (uptr->group == 0)
                { // an independent user
                    if (flag == 0)
                    {
                        new->members = uptr;
                        flag = 1;
                    } // for first member of the group
                    else
                        utail->team = uptr; // for later members

                    uptr->group = new->group_id; // assigning group to the individual
                    utail = uptr;                // updating tail
                }
                else
                    printf("the user %d is present alreday prresent in the group %d \n", uptr->ID, uptr->group);
            }
            else
                printf(" the given user id is invalid , please give a valid user id \n ");
        }

        printf("Enter the new weekly group goal \n");
        scanf("%d", &new->weekly_goal);

        new->next = group_list;
        group_list = new;
    }

    return group_list;
} // the returned new mwmory pointer shall be linked to the group list in the main function
// working
// changed
void Get_top_3(users *user_list, users *top_3[3])
{
    users *first = NULL;
    users *second = NULL;
    users *third = NULL; // initialising every pointer to NULL as there may not be any user who crossed daily goals
    int max1 = -1;
    int max2 = -1;
    int max3 = -1;




    users *temp = user_list;

    while (temp)
    {
        if ((Avg_steps(temp->WeeklyStepCount) >= temp->DailyStepGoal))
        { // eliminating the one who haven't crossed the goal
            if (Avg_steps(temp->WeeklyStepCount) > max1)
            {
                max3 = max2;
                third = second; // changing second position to third
                max2 = max1;
                second = first; // changing first position to second
                max1 = Avg_steps(temp->WeeklyStepCount);
                first = temp; // changing the highest to first
            }
            else if (Avg_steps(temp->WeeklyStepCount) > max2)
            {
                max3 = max2;
                third = second; // changing second position to third
                max2 = Avg_steps(temp->WeeklyStepCount);
                second = temp; // chaning the second highest to second
            }
            else if (Avg_steps(temp->WeeklyStepCount) > max3)
            {
                max3 = Avg_steps(temp->WeeklyStepCount);
                third = temp; // changing the third highest to third
            }
        }
        temp = temp->next;
    }
    // global array for tracking top 3 individuals
    top_3[0] = first;
    top_3[1] = second;
    top_3[2] = third; // storing the pointers in the top 3 array
}
// working
void Check_group_acheivement(group *group_list)
{
    printf("Enter the ID of the group you want to check : \n");
    int group_id;
    scanf("%d", &group_id);

    group *temp = group_list;
    int flag = 0;

    while (temp && !flag)
    {
        if (temp->group_id == group_id)
            flag = 1; // stops if found the required the group
        else
            temp = temp->next;
    }

    if (temp->group_id == group_id)
    {
        printf("the goal of group %d is %d , they achieved %d\n", temp->group_id, temp->weekly_goal, group_count(temp));
        if (temp->weekly_goal <= group_count(temp))
            printf("the group with the ID %d has completed their goal of the week \n", group_id);
        else
            printf("the group with the ID %d has not completed their goal of the week \n", group_id);
    }
    else
        printf("there is no group with the given ID , Please provide a valid one \n");
}
// working
void Generate_leader_board(group *group_list)
{
    group_list = group_mwrge_sort(group_list); // sorting based on group count steps
    group *temp = group_list;
    while (temp)
    {
        printf("\n Name : %s \t Step count : %d \n", temp->group_name, group_count(temp));
        temp = temp->next;
    }
}
// working
void Check_individual_rewards(users *user_list, users *top_3[3])
{
    printf("Enter the id of the user you need to check \n");
    int user_id;
    scanf("%d", &user_id);

    Get_top_3(user_list, top_3);

    users *temp = find_user_id(user_list , user_id); // can be eliminated , but there for more knowledge of id existence 
    if (!temp)
        printf("INVALID ID , please provide a valid one \n");
    else
    { // eliminating empty list case
        int flag = 0;
        printf("NOTE the rewards refreshes for every week \n");

        int first = -1;
        if (top_3[0])
            first = top_3[0]->ID; // sometimes anyone may not able to cross their goals where top_3 coould be NULL
        int second = -1;
        if (top_3[1])
            second = top_3[1]->ID;
        int third = -1;
        if (top_3[2])
            third = top_3[2]->ID;

        
                if (user_id == first)
                {
                    printf("the user is first in step count , he is rewarded with 100 points \n");
                    flag = 1; // to cut the loop as id is unique
                }
                else if (user_id == second)
                {
                    printf("the user is second in step count , he is rewarded with 75 points \n");
                    flag = 1;
                }
                else if (user_id == third)
                {
                    printf("the user is third in step count , he is rewarded with 50 points \n");
                    flag = 1;
                }
                else if (user_id == temp->ID)
                {
                    printf("the user is did not earn any rewards this week \n BETTER LUCK NEXT TIME \n");
                    flag = 1;
                }
            if (flag == 0)
                printf("Please enter a valid user id \n");
        
    }
}
// working
users *Delete_indidvidual(group *group_list, users *user_list)
{
    printf("Enter the ID of the user to be deleted \n");
    int user_id;
    scanf("%d", &user_id);

    users *temp = user_list, *prev = NULL;
    int grp_id;
    int flag = 0;

    if (!user_list)
        printf("there is no data yet \n");
    else
    {
        temp = user_list;
        while (temp && !flag)
        {
            if (temp->ID == user_id)
            {
                grp_id = temp->group; // getting the group of user
                flag = 1;             // stop if found
            }
            else
            {
                prev = temp; // tracking previous pointer of required user
                temp = temp->next;
            }
        } // getting the pointer to the node to b deleted

        if (flag == 0)
            printf("the user is not present in the list \n");
        else
        { // the user is present in the database
            if (grp_id == 0)
                printf("the user is an independent individual \n ");

            else
            { // user is in a group
                group *grp_temp = group_list;
                if (!group_list)
                    printf("there are no groups yet\n");
                else
                {
                    grp_temp = group_list;
                    flag = 0;

                    while (grp_temp && !flag)
                    {
                        if (grp_temp->group_id == grp_id)
                            flag = 1; // finding the group
                        else
                            grp_temp = grp_temp->next;
                    }

                    users *utemp = grp_temp->members;
                    users *uprev = NULL;
                    int uflag = 0;
                    while (utemp && !uflag)
                    {
                        if (utemp->ID == user_id)
                            uflag = 1;
                        else
                        {
                            uprev = utemp;
                            utemp = utemp->team;
                        }
                    }
                    if (utemp == grp_temp->members)
                        grp_temp->members = utemp->team; // for the first individua case
                    else
                        uprev->team = utemp->team; // general case , relinking to next individual
                }
            }

            if (temp != user_list)
                prev->next = temp->next;
            else
                user_list = temp->next;
            free(temp); // deleting user from memory ;
        }
    }
    return user_list;
}
//  updated , working
group *Delete_group(group *group_list)
{
    printf("nter the ID of the group to be deleted : \n");
    int grp_id;
    scanf("%d", &grp_id);

    group *temp;
    group *prev = NULL;
    printf("entered the delete group \n");

    if (!group_list)
        printf("there are no groups yetb \n");
    else
    {
        temp = group_list;
        int flag = 0;

        while (temp && !flag)
        {
            if (temp->group_id == grp_id)
            {
                printf(" the group is %s \n", temp->group_name);
                flag = 1;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }

        if (flag == 0)
            printf(" there is no group with the given id , please provide a valid one \n ");
        else
        {
            users *utemp = temp->members;
            users *uprev = NULL;
            while (utemp)
            {
                uprev = utemp;
                utemp = utemp->team;
                uprev->group = 0;   // freeing individual
                uprev->team = NULL; // removing links
            }
        }

        if (temp != group_list)
            prev->next = temp->next;
        else
            group_list = temp->next;
        free(temp); // deleting group ;
    }
    return group_list;
}
// updated , working
group *Merge_group(group *group_list)
{
    printf("Enter the ID s of the groups to be merged \n");
    int grp1_id, grp2_id;
    scanf("%d", &grp1_id);
    scanf("%d", &grp2_id);

    group *grp1 = NULL; // pointers to requires groups
    group *grp2 = NULL;
    group *prev1 = NULL;
    group *prev2 = NULL;
    group *temp = group_list;
    group *prev = NULL;

    group *new = (group *)malloc(sizeof(group));

    if (new)
    {
        while (temp)
        {
            if (temp->group_id == grp1_id)
            {
                prev1 = prev;
                grp1 = temp;
                if (grp1->group_id == grp2_id)
                    grp2 = grp1;
            } // finding the required one
            else if (temp->group_id == grp2_id)
            {
                grp2 = temp;
                prev2 = prev;
            }
            prev = temp;
            temp = temp->next;
        }

        int cnt1 = 0;
        users* utemp = NULL ;
        if(grp1) {
           utemp = grp1->members;
        }
        
        while (utemp)
        {
            cnt1++;
            utemp = utemp->team;
        }
        int cnt2 = 0;
        if(grp2)utemp = grp2->members;
        else utemp = NULL ;
        while (utemp)
        {
            cnt2++;
            utemp = utemp->team;
        }

        if (cnt1 + cnt2 > 5)
        {
            printf("the groups given can't be merged");
            new = NULL;
        }
        else if (!grp1) printf("INVALID GROUP ID 1 \n");
        else if (!grp2) printf("INVALID GROUP ID 2 \n");
        else if (grp1 == grp2)
        {
            printf(" Enter the ID for the newly ctreated group : ");
            scanf("%d", &new->group_id);
            printf(" Enter the group name for the newly created group : ");
            scanf("%s", new->group_name);
            printf(" set the weekly group goal for the newly created group :");
            scanf("%d", &new->weekly_goal);

            new->members = grp1->members;
            users *utemp = new->members;
            while (utemp)
            {
                utemp->group = new->group_id;
                utemp = utemp->team;
            } // setting previous group's users's group to new one

            if (grp1 != group_list)
                prev1->next = grp1->next;
            else
                group_list = grp1->next; // linking the previous one to the next one
            free(grp1);                  // deleting the group from memory

            new->next = group_list;
            group_list = new; // adding new group to the list
        }
        else
        {
            printf(" Enter the ID for the newly ctreated group : ");
            scanf("%d", &new->group_id);
            printf(" Enter the group name for the newly created group : ");
            scanf("%s", new->group_name);
            printf(" set the weekly group goal for the newly created group :");
            scanf("%d", &new->weekly_goal);

            new->members = grp1->members;
            users *uprev = NULL;
            utemp = grp1->members;
            while (utemp)
            {
                uprev = utemp;
                utemp->group = new->group_id; // assigning new group id
                utemp = utemp->team;
            }
            if (!prev)
                new->members = grp2->members; // no user in grouup case
            else
            {
                uprev->team = grp2->members; // linking members of group1 to group2
                utemp = grp2->members;
                while (utemp)
                {
                    uprev = utemp;
                    utemp->group = new->group_id; // assigning new group id
                    utemp = utemp->team;
                }
            }

            new->members = user_merge_sort(new->members) ; // sorting the merged link

            if (grp1 != group_list)
                prev1->next = grp1->next;
            else
                group_list = grp1->next;
            free(grp1);
            if (grp2 != group_list && prev2)
                prev2->next = grp2->next;
            else if (grp2 == group_list)
                group_list = grp2->next;
            else
                prev1->next = grp2->next; // for side by side cases

            free(grp2);

            new->next = group_list;
            group_list = new;
        }
    }

    return group_list;
}
// updated
void Display_group_info(group *group_list)
{
    group *temp = group_list;

    if (temp == NULL)
        printf("there are no groups yet ");

    while (temp)
    {
        printf(" Group ID : ");
        printf("%d \n ", temp->group_id);
        printf(" Group name : ");
        printf("%s \n ", temp->group_name);

        printf(" the ID s of the members are : \n");

        users *utemp = temp->members;
        while (utemp)
        {
            printf(" %d  ", utemp->ID);
            utemp = utemp->team;
        }

        printf(" \nWeekly Group Goal  of the week : ");
        printf(" %d \n", temp->weekly_goal);

        temp = temp->next;
    }
}
// updated
void Suggest_goal_update(users *user_list, users *top_3[3])
{
    printf("Enter the ID of the user to be deleted \n");
    int user_id;
    scanf("%d", &user_id);

    users *temp = user_list;
    int flag = 0;

    while (temp && !flag)
    {
        if (temp->ID == user_id)
        {
            printf("your daily goal to be in top 3 would be \n");
            if (top_3[0])
            {
                printf("%d \n ", Avg_steps(top_3[0]->WeeklyStepCount)); // aiming high
            }
            else
                printf("%d \n", temp->DailyStepGoal); // what if there is no first place
            flag = 1;                                 // found the user
        }
        temp = temp->next;
    }
}
// updated

void output_user_list(users* users_list)
{
    
    FILE *fp = fopen("individuals.txt", "w");
    while(users_list)
    {


        fprintf(fp,"%d\t\t",users_list->ID);
        fprintf(fp,"%s\t\t",users_list->Name);
        fprintf(fp,"%d\t\t",users_list->Age);
        fprintf(fp,"%d\t\t",users_list->DailyStepGoal);
        for(int i=0;i<6;i++)
        {
            fprintf(fp,"%d\t",users_list->WeeklyStepCount[i]);
        }
         fprintf(fp,"%d\n",users_list->WeeklyStepCount[6]);
        users_list=users_list->next;
    }
    fclose(fp) ;
}

void output_group_list(group* group_list ){
    FILE *fp = fopen("group.txt" , "w");
    while(group_list){
        fprintf( fp , "%d\t\t" , group_list->group_id);
        printf("printfing group id %d \n" , group_list->group_id);
        
        fprintf( fp , "%s\t\t" , group_list->group_name);
        int cnt = 0 ;
        users* temp = group_list->members ;
        while(temp){
            cnt++;
            temp = temp->team ;
        }
        fprintf(fp , "%d\t\t" , cnt );
        printf("printing group count %d \n" , cnt );
        temp = group_list->members ;
        while(temp){
            fprintf(fp , "%d\t\t" , temp->ID );
            printf("printfing user id %d \n" , temp->ID );
            temp = temp->team ;
        }
        fprintf( fp , "%d\t\n" , group_list->weekly_goal );
        
        group_list = group_list->next ;
    }
    fclose(fp);
}

void main()
{
    users *user_list = create_user_list(NULL);
    user_list = user_merge_sort(user_list);
    group *group_list = create_group_list(user_list, NULL);
    users *top_3[3];

    printf("Welcome to the fitness appliction \n ");

    printf("----------------------------------\n");
    printf("1 \t Add a personn publicly \n");
    printf("2 \t Create a Group \n");
    printf("3 \t Check global top 3 \n");
    printf("4 \t Group Achievement\n");
    printf("5 \t Group Leader Board \n");
    printf("6 \t Check My Rewards \n");
    printf("7 \t Delete a User \n");
    printf("8 \t Delete a Group of Useres \n");
    printf("9 \t Merge two given Groups \n");
    printf("10 \t Display Group Information \n");
    printf("11 \t Suggest Goal Updates \n");
    printf("12 \t diaplay information of individuals \n");
    printf("----------------------------------");

    char choice;
    int oprn;
    char null;

    do
    {
        printf("Choose your operatinon : \n");
        scanf("%d", &oprn);

        switch (oprn)
        {
        case 1:
        {
            users *new;
            new = create_user();
            user_list = Add_Person(user_list, new);
            printf("function completed \n");
            break;
        }

        case 2:
            group_list = Create_group(group_list, user_list);
            break;

        case 3:
            Get_top_3(user_list, top_3);
            printf("the top 3 individuals of the day are : \n");
            printf("\n");
            visit_user(top_3[0]);
            printf("\n");
            visit_user(top_3[1]);
            printf("\n");
            visit_user(top_3[2]);
            break;

        case 4:
            Check_group_acheivement(group_list);
            break;

        case 5:
            Generate_leader_board(group_list);
            break;

        case 6:
            Check_individual_rewards(user_list, top_3);
            break;

        case 7:
            user_list = Delete_indidvidual(group_list, user_list);
            printf("===========================================\n");
            display_all_users(user_list);
            break;

        case 8:
            group_list = Delete_group(group_list);
             printf("===========================================\n");
            Display_group_info(group_list);
            break;

        case 9:
            group_list = Merge_group(group_list);
            break;

        case 10:
            printf("the information of the groups present are : \n");
            printf("===========================================\n");
            Display_group_info(group_list);
            printf("===========================================\n");
            break;

        case 11:
            Suggest_goal_update(user_list, top_3);
            break;

        case 12:
            printf("  INDIVIDUAL INFORMATION \n");
            printf("===========================================\n");
            display_all_users(user_list);
            printf("===========================================\n");
            break;
        }

        printf("Do you want to continue , if yes type y ");
        scanf("%c", &null);
        scanf("%c", &choice);
    } while (choice == 'y');
    
    output_user_list(user_list) ;
    output_group_list(group_list );
}











