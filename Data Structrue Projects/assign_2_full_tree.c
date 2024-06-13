#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct user
{
    int ID;
    int group;
    char name[50];
    int age;
    int daily_goal;
    int weekly_count[7];
    int height;

    struct user *left;
    struct user *right;


} user;

typedef struct clanmate
{
    user *clan;
    int height;

    struct clanmate *left;
    struct clanmate *right;
} clanmate;

typedef struct group
{
    int ID;
    char name[50];
    int weelky_goal;
    clanmate *teammates;
    int height;

    struct group *left;
    struct group *right;
} group;

typedef struct leader
{
    group *team;
    int height;
    struct leader *left;
    struct leader *right;
    struct leader *next; // duplicate case

} leader;

int parse(char s[])
{
    int num = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        num = num * 10 + (s[i] - 48);
    }
    return num;
}
// for converting string from file and store aas integer for the program
int Avg_steps(int steps[])
{
    int sum = 0;
    for (int i = 0; i < 7; i++)
    {
        sum += steps[i];
    }
    return sum /7;
}

int clan_avg_steps(clanmate *root)
{
    int sum = 0;
    if (root)
    {
        sum = sum + clan_avg_steps(root->left);
        sum = sum + Avg_steps(root->clan->weekly_count);
        sum = sum + clan_avg_steps(root->right);
    }
    return sum;
}
// used in generating leader board while comparing groups
void visit_user(user *users)
{
    if (users)
    {
        printf("ID \t %d\n", users->ID);
        printf("Group \t %d\n", users->group);
        printf("Name \t %s\n", users->name);
        printf("Age \t %d\n", users->age);
        printf("Daily Goal\t %d\n", users->daily_goal);
        printf("Weekly goal (Sundya->Saturday):\n");
        for (int i = 0; i < 7; i++)
            printf("   %d", users->weekly_count[i]);
        printf("\n the average step count of the week is %d \n", Avg_steps(users->weekly_count));
        printf("\n");
    }
}

int clan_num(clanmate *root)
{
    int num = 0;
    if (root)
    {
        num = num + clan_num(root->left);
        num = num + 1;
        num = num + clan_num(root->right);
    }
    return num;
}
// for overwriting into the text file for further reading
void user_InOrder(user *root)
{
    if (root != NULL)
    {
        user_InOrder(root->left);
        visit_user(root);
        user_InOrder(root->right);
    }
}

void clan_free_group(clanmate *root)
{
    if (root)
    {
        clan_free_group(root->left);
        root->clan->group = 0;
        clan_free_group(root->right);
    }
}
// when a group is deleted
void clan_inorder(clanmate *root)
{
    if (root)
    {
        clan_inorder(root->left);
        printf("%d  ", root->clan->ID);
        clan_inorder(root->right);
    }
}

void visit_group(group *temp)
{
    printf("entered visit");
    if (temp)
    {
        printf("Group ID \t %d\n", temp->ID);
        printf("Group Name \t %s\n", temp->name);
        printf("Weekly Group Goal\t %d\n", temp->weelky_goal);
        printf(" the clan members are : \n");
        clan_inorder(temp->teammates);
        printf("\n");
    }
}

void group_Inorder(group *root)
{
    if (root)
    {
        group_Inorder(root->left);
        visit_group(root);
        group_Inorder(root->right);
    }
}

user *create_user()
{
    user *newIndividual = (user *)malloc(sizeof(user));
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
        scanf("%s", newIndividual->name);
        printf("\n Enter the age of user : ");
        scanf("%d", &newIndividual->age);
        printf("]\\n Enter the daily step goal , that user wants to complete : ");
        scanf("%d", &newIndividual->daily_goal);
        printf("\n Enter the weekly step count (sunday to saturday) \n");
        for (int i = 0; i < 7; i++)
            scanf("%d", &newIndividual->weekly_count[i]);
            
        newIndividual->left = NULL;
        newIndividual->right = NULL;

        printf("user created succesfully \n");
    }

    return newIndividual;
}

group *group_search(group *root, int key)
{
    group *temp = root;
    if (root)
    {
        int flag = 0;
        while (temp && !flag)
        {
            if (temp->ID == key)
                flag = 1;
            else if (temp->ID > key)
                temp = temp->left;
            else if (temp->ID < key)
                temp = temp->right;
        }
    }
    return temp;
}

user *user_search(user *root, int key)
{
    user *temp = root;
    if (root)
    {
        int flag = 0;
        while (temp && !flag)
        {
            if (temp->ID == key)
                flag = 1;
            else if (temp->ID > key)
                temp = temp->left;
            else if (temp->ID < key)
                temp = temp->right;
        }
    }
    return temp;
}

user *user_rotate_right(user *root)
{
    if (root)
    {
        if (root->left)
        {
            user *temp = root->left;
            root->left = temp->right;
            temp->right = root;
            root->height = root->height - 2;
            root = temp;
        }
    }
    return root;
}
// height updated
user *user_rotate_left(user *root)
{
    if (root)
    {
        if (root->right)
        {
            user *temp = root->right;
            root->right = temp->left;
            temp->left = root;
            root->height = root->height - 2;
            root = temp;
        }
    }
    return root;
}
// height updated
user *user_balance_root(user *root)
{
    if (root)
    {
        int left = 0;
        if (root->left)
            left = root->left->height;
        int right = 0;
        if (root->right)
            right = root->right->height;

        if (left - right > 1)
        {
            root = user_rotate_right(root);
        }
        if (right - left > 1)
        {
            root = user_rotate_left(root);
        }
    }
    return root;
}
// height updated
user *user_insert_avl(user *root, user *ins)
{
    if (root)
    {
        if (root->ID > ins->ID)
        {
            root->left = user_insert_avl(root->left, ins);
        }
        else if (root->ID < ins->ID)
        {
            root->right = user_insert_avl(root->right, ins);
        }

        else if (root->ID == ins->ID)
        {
            return root;
        }

        int left = 0;
        if (root->left)
            left = root->left->height;
        int right = 0;
        if (root->right)
            right = root->right->height;

        if (left > right)
            root->height = left + 1;
        else
            root->height = right + 1;

        root = user_balance_root(root);
    }
    else
    {
        root = ins;
        root->height = 1;
    }
    return root;
}
// height updated
user *create_user_tree(user *head)
{
    FILE *fp = fopen("individuals.txt", "r");
    char word[40];
    int c;
    while (fscanf(fp, "%s", word) == 1)
    {                                              // traversing the file
        user *temp = (user *)malloc(sizeof(user)); // creating space
        int c;
        // reading string from file
        temp->ID = parse(word); // changing it into int
        temp->group = 0;        // initially independent
        fscanf(fp, "%s", word);
        strcpy(temp->name, word); // setting word

        fscanf(fp, "%d", &c);
        temp->age = c; // setting age
        fscanf(fp, "%d", &c);
        temp->daily_goal = c; // Daily step goal
        for (int i = 0; i < 7; i++)
        {
            fscanf(fp, "%d", &c);
            temp->weekly_count[i] = c; // weekly count of steps
        }
        temp->left = NULL;
        temp->right = NULL; // individual node , later added at leaf

        head = user_insert_avl(head, temp); // inserts every entry , starting from NULL
    }

    fclose(fp);
    return head; // returning the starting node pointer
}
// creating from text file
user *user_top_3(user *root, user *top_3[])
{
    if (root)
    {
        // Traverse left subtree
        user_top_3(root->left, top_3);

        // Update top 3
        int avg_steps = Avg_steps(root->weekly_count);
        int max1 = 0;
        if (top_3[0])
            max1 = Avg_steps(top_3[0]->weekly_count);
        int max2 = 0;
        if (top_3[1])
            max2 = Avg_steps(top_3[1]->weekly_count);
        int max3 = 0;
        if (top_3[2])
            max3 = Avg_steps(top_3[2]->weekly_count);
        if (avg_steps >= root->daily_goal)
        {
            if (avg_steps > max1)
            {
                top_3[2] = top_3[1];
                top_3[1] = top_3[0];
                top_3[0] = root;
            }
            else if (avg_steps>max2 && root->ID!=top_3[0]->ID)
            {
                top_3[2] = top_3[1];
                top_3[1] = root;
            }
            else if (avg_steps > max3 && (root->ID!=top_3[1]->ID && root->ID!=top_3[0]->ID))
            {
                top_3[2] = root;
            }
        }

        // Traverse right subtree
        user_top_3(root->right, top_3);
    }
    return root;
}

void Check_individual_rewards(user *root, user *top_3[])
{
    printf("Enter the ID of the user to be checked : ");
    int id;
    scanf("%d", &id);

    user *uptr = user_search(root, id);
	if(uptr){
   if(uptr==top_3[0]){
	printf("You got 100 points");
   }
   else if(uptr==top_3[1]){
	printf("You got 75 points");
}
else if(uptr==top_3[2]){
	printf("You got 50 points");
}
else{
	printf("you are not in top 3");
}
	}
	else{
		printf("You entered the wrong id");
	}
}
// updated
clanmate *clan_rotate_right(clanmate *root)
{
    if (root)
    {
        if (root->left)
        {
            clanmate *temp = root->left;
            root->left = temp->right;
            temp->right = root;
            root->height = root->height - 2;
            root = temp;
        }
    }
    return root;
}
// heught updated
clanmate *clan_rotate_left(clanmate *root)
{
    if (root)
    {
        if (root->right)
        {
            clanmate *temp = root->right;
            root->right = temp->left;
            temp->left = root;
            root->height = root->height - 2;
            root = temp;
        }
    }
    return root;
}
// height updated
clanmate *clan_balance_root(clanmate *root)
{
    if (root)
    {
        int left = 0;
        if (root->left)
            left = root->left->height;
        int right = 0;
        if (root->right)
            right = root->right->height;

        if (left - right > 1)
        {
            root = clan_rotate_right(root);
        }
        if (right - left > 1)
        {
            root = clan_rotate_left(root);
        }
    }
    return root;
}
// height updated
clanmate *clan_insert_avl(clanmate *root, clanmate *ins)
{
    if (root)
    {
        if (root->clan->ID > ins->clan->ID)
        {
            root->left = clan_insert_avl(root->left, ins);
        }
        else if (root->clan->ID < ins->clan->ID)
        {
            root->right = clan_insert_avl(root->right, ins);
        }

        else if (root->clan->ID == ins->clan->ID)
        {
            return root;
        }

        int left = 0;
        if (root->left)
            left = root->left->height;
        int right = 0;
        if (root->right)
            right = root->right->height;

        if (left > right)
            root->height = left + 1;
        else
            root->height = right + 1;

        root = clan_balance_root(root);
    }
    else
    {
        root = ins;
        root->height = 1;
    }
    return root;
}
// height updated
clanmate *clan_find_replace(clanmate *root)
{
    clanmate *ans = NULL;
    if (root)
    {
        if (root->right)
        {
            ans = clan_find_replace(root->right);

            if (root->right == ans)
                root->right = NULL;

            int left = 0;
            if (root->left)
                left = root->left->height;
            int right = 0;
            if (root->right)
                right = root->right->height;

            if (left > right)
                root->height = left + 1;
            else
                root->height = right + 1;

            root = clan_balance_root(root);
        }
        else
        {
            ans = root;
            root->height = 0;
        }
    }
    return ans;
}
// height updated
clanmate *clan_delete_node_2(clanmate *root, group *group_tree)
{
    if (root)
    {
        clanmate *rep = clan_find_replace(root->left);
        if (rep)
        {
            rep->right = root->right;
            if (rep == root->left)
                rep->left = NULL;
            else
                rep->left = root->left;

            free(root);
            root = rep;
        }
        else
        {
            clanmate *temp = root->right;
            free(root);
            root = temp;
        }

        if (root)
        {
            int left = 0;
            if (root->left)
                left = root->left->height;
            int right = 0;
            if (root->right)
                right = root->right->height;

            if (left > right)
                root->height = left + 1;
            else
                root->height = right + 1;
        }
    }
    return root;
}
// height updated
clanmate *clan_delete_avl(clanmate *root, group *group_tree, int key)
{
    if (root)
    {
        if (root->clan->ID == key)
        {
            root = clan_delete_node_2(root, group_tree);
        }
        else if (root->clan->ID > key)
        {
            root->left = clan_delete_avl(root->left, group_tree, key);
        }
        else if (root->clan->ID < key)
        {
            root->right = clan_delete_avl(root->right, group_tree, key);
        }

        if(root){
            int left = 0;
            if (root->left)
                left = root->left->height;
            int right = 0;
            if (root->right)
                right = root->right->height;

            if (left > right)
                root->height = left + 1;
            else
                root->height = right + 1;
        }

        root = clan_balance_root(root);
    }
    return root;
}
// height updated
clanmate *clan_copy(clanmate *root, clanmate *new)
{
    printf("enterd clan copy \n");
    if (root)
    {
        new = clan_copy(root->left, new);
        printf("inserting %d ", root->clan->ID);
        clanmate *temp = (clanmate *)malloc(sizeof(clanmate));
        printf("new node created ");
        temp->clan = root->clan;
        temp->left = NULL;
        temp->right = NULL;
        new = clan_insert_avl(new, temp);
        printf("insertred \n");
        new = clan_copy(root->right, new);
    }
    return new;
}
// incase of merging two groups , adding members from one group to other in sorted order
user *find_replace(user *root)
{
    user *ans = NULL;
    if (root)
    {
        if (root->right)
        {
            ans = find_replace(root->right);

            if (root->right == ans)
                root->right = NULL;

            int left = 0;
            if (root->left)
                left = root->left->height;
            int right = 0;
            if (root->right)
                right = root->right->height;

            if (left > right)
                root->height = left + 1;
            else
                root->height = right + 1;

            root = user_balance_root(root);
        }
        else
        {
            ans = root;
            root->height = 0;
        }
    }
    return ans;
}
// height updated 
// finding the best value to take the place of node getting deleted , returns the replaced node
// new node gets detached here itself to avoid infinite recursions 
user *user_delete_node_2(user *root, group *group_tree)
{
    if (root)
    {
        user *rep = find_replace(root->left);
        if (rep)
            printf("the found replace ment is %d \n", rep->ID);
        if (rep)
        {
            rep->right = root->right;
            if (rep == root->left)
                rep->left = NULL;
            else
                rep->left = root->left;

            int grp = root->group; // finding his group
            group *gtemp = group_search(group_tree, grp);

            if (gtemp)
            {
                gtemp->teammates = clan_delete_avl(gtemp->teammates, group_tree, root->ID);
            }

            free(root);
            root = rep;
        }
        else
        {
            user *temp = root->right;

            int grp = root->group; // finding his group
            group *gtemp = group_search(group_tree, grp);

            if (gtemp)
            {
                gtemp->teammates = clan_delete_avl(gtemp->teammates, group_tree, root->ID);
            }

            free(root);
            root = temp;
        }

        if (root)
        {
            int left = 0;
            if (root->left)
                left = root->left->height;
            int right = 0;
            if (root->right)
                right = root->right->height;

            if (left > right)
                root->height = left + 1;
            else
                root->height = right + 1;
        }
    }
    return root;
}
// height updated
user *user_delete_avl(user *root, group *group_tree, int key)
{
    if (root)
    {
        if (root->ID == key)
        {
            root = user_delete_node_2(root, group_tree);
        }
        else if (root->ID > key)
        {
            root->left = user_delete_avl(root->left, group_tree, key);
        }
        else if (root->ID < key)
        {
            root->right = user_delete_avl(root->right, group_tree, key);
        }

        if (root)
        {
            int left = 0;
            if (root->left)
                left = root->left->height;
            int right = 0;
            if (root->right)
                right = root->right->height;

            if (left > right)
                root->height = left + 1;
            else
                root->height = right + 1;
        }

        root = user_balance_root(root);
    }
    return root;
}
// height updated
group *create_group(user *root)
{
    group *new = (group *)malloc(sizeof(group));

    printf("Enter the name of the new group ; \n");
    scanf("%s", new->name);
    printf("Enter the unique ID of the group : \n");
    scanf("%d", &new->ID);
    printf("Enter the member ID of the group members : \n");
    printf("(give all the 5 entries ,empty ones with 0)");
    new->teammates = NULL;
    for (int i = 0; i < 5; i++)
    {
        printf("enter the %d useer id : ", i);
        int id;
        scanf("%d", &id);

        user *uptr = user_search(root, id);

        if (uptr)
        { // NULL represents invalid user
            if (uptr->group == 0)
            {
                printf("the users group is %d \n", uptr->group);
                clanmate *temp = (clanmate *)malloc(sizeof(clanmate));
                temp->clan = uptr;
                temp->left = NULL;
                temp->right = NULL;
                new->teammates = clan_insert_avl(new->teammates, temp);
            }
            else
                printf("the user %d is present alreday prresent in the group %d \n", uptr->ID, uptr->group);
        }
        else
            printf(" the given user id is invalid , please give a valid user id \n ");
    }
    printf("enter the weekly goal of group \n");
    scanf("%d", &new->weelky_goal);
    return new;
}

group *group_rotate_right(group *root)
{
    if (root)
    {
        if (root->left)
        {
            group *temp = root->left;
            root->left = temp->right;
            temp->right = root;
            root->height = root->height - 2;
            root = temp;
        }
    }
    return root;
}
// height updated
group *group_rotate_left(group *root)
{
    if (root)
    {
        if (root->right)
        {
            group *temp = root->right;
            root->right = temp->left;
            temp->left = root;
            root->height = root->height - 2;
            root = temp;
        }
    }
    return root;
}

group *group_balance_root(group *root)
{
    if (root)
    {
        int left = 0;
        if (root->left)
            left = root->left->height;
        int right = 0;
        if (root->right)
            right = root->right->height;

        if (left - right > 1)
        {
            root = group_rotate_right(root);
        }
        if (right - left > 1)
        {
            root = group_rotate_left(root);
        }
    }
    return root;
}

group *group_inserst_avl(group *root, group *ins)
{
    if (root)
    {
        if (root->ID > ins->ID)
        {
            root->left = group_inserst_avl(root->left, ins);
        }
        else if (root->ID < ins->ID)
        {
            root->right = group_inserst_avl(root->right, ins);
        }

        else if (root->ID == ins->ID)
        {

            return root;
        }

        int left = 0;
        if (root->left)
            left = root->left->height;
        int right = 0;
        if (root->right)
            right = root->right->height;

        if (left > right)
            root->height = left + 1;
        else
            root->height = right + 1;

        root = group_balance_root(root);
    }
    else
    {
        root = ins;
        root->height = 1;
    }

    return root;
}

group *create_group_list(user *user_list, group *head)
{
    FILE *fp = fopen("group.txt", "r");
    char word[40];
    while (fscanf(fp, "%s", word) != EOF)
    {
        int d;
        group *temp = (group *)malloc(sizeof(group));
        int c;
        if (!temp)
            printf("no space \n");
        temp->ID = parse(word);
        fscanf(fp, "%s", word);
        strcpy(temp->name, word);

        temp->teammates = NULL;

        fscanf(fp, "%d", &c);
        int flag = 0;
        for (int i = 0; i < c; i++)
        {
            fscanf(fp, "%s", word);
            user *uptr = user_search(user_list, parse(word)); // getting the user pointer

            if (uptr)
            { // NULL represents invalid user
                if (uptr->group == 0)
                {
                    clanmate *new = (clanmate *)malloc(sizeof(clanmate));
                    new->clan = uptr;
                    new->left = NULL;
                    new->right = NULL;
                    temp->teammates = clan_insert_avl(temp->teammates, new);
                    uptr->group = temp->ID;
                }
                else
                    printf(" WARNING : the user %d is present alreday prresent in the group %d \n", uptr->ID, uptr->group);
            }
            else
                printf("INVALID : the given user id is invalid , please give a valid user id \n ");
        }

        fscanf(fp, "%d", &c);
        temp->weelky_goal = c;

        temp->left = NULL;
        temp->right = NULL;

        head = group_inserst_avl(head, temp);
    }

    fclose(fp);
    return head;
}
// updated
void Check_group_acheivement(group *temp)
{
    if (temp)
    {
        int sum = clan_avg_steps(temp->teammates);
        sum = sum / clan_num(temp->teammates);
        if (sum >= temp->weelky_goal)
            printf(" the group %s has succesfully achieved their weekly goal \n", temp->name);
        else
            printf("the group %s has nat achieved their weekly goal \n", temp->name);
    }
    else
        printf("the group with given id doesn.t exist ");
}

group *group_find_replace(group *root)
{
    group *ans = NULL;
    if (root)
    {
        if (root->right)
        {
            ans = group_find_replace(root->right);

            if (root->right == ans)
                root->right = NULL;

            int left = 0;
            if (root->left)
                left = root->left->height;
            int right = 0;
            if (root->right)
                right = root->right->height;

            if (left > right)
                root->height = left + 1;
            else
                root->height = right + 1;

            root = group_balance_root(root);
        }
        else
        {
            ans = root;
            root->height = 0;
        }
    }
    return ans;
}
// height updated
group *group_delete_node_2(group *root)
{
    if (root)
    {
        group *rep = group_find_replace(root->left);
        if (rep)
            printf("the found replace ment is %d \n", rep->ID);
        if (rep)
        {
            rep->right = root->right; // handles when right tree is NULL
            if (rep == root->left)
                rep->left = NULL;
            else
                rep->left = root->left;
            clan_free_group(root->teammates); // frees all the members of group
            free(root);
            root = rep;
        } // case of single and multiple left nodes
        else
        {
            group *temp = root->right; // handles when right tree is NULL
            clan_free_group(root->teammates);
            free(root);
            root = temp;
        } // case when there is no left tree for the to be deleted node

        if (root)
        {
            int left = 0;
            if (root->left)
                left = root->left->height;
            int right = 0;
            if (root->right)
                right = root->right->height;

            if (left > right)
                root->height = left + 1;
            else
                root->height = right + 1;
        }
    }
    return root;
}
// height updated

group *group_delete_avl(group *root, int key)
{
    if (root)
    {
        if (root->ID == key)
        {
            root = group_delete_node_2(root);
        }
        else if (root->ID > key)
        {
            root->left = group_delete_avl(root->left, key);
        }
        else if (root->ID < key)
        {
            root->right = group_delete_avl(root->right, key);
        }
        if (root)
        {
            int left = 0;
            if (root->left)
                left = root->left->height;
            int right = 0;
            if (root->right)
                right = root->right->height;

            if (left > right)
                root->height = left + 1;
            else
                root->height = right + 1;
        }

        root = group_balance_root(root);
    }
    return root;
}
// height updated
group *merge_groups(group *root)
{
    if (root)
    {
        printf("Enter the IDs of the groups to be merged \n");
        int grp1_id;
        int grp2_id;
        scanf("%d%d", &grp1_id, &grp2_id);

        group *grp1 = group_search(root, grp1_id);

        group *grp2 = group_search(root, grp2_id);

        if (grp1 && grp2)
        {

            int cnt1 = clan_num(grp1->teammates);
            int cnt2 = clan_num(grp2->teammates);

            if (cnt1 + cnt2 > 5)
            {
                printf("the groups given can't be merged");
            }
            else if (grp1 == grp2)
            {
                group *new = (group *)malloc(sizeof(group));
                new->ID = grp1_id;
                printf(" Enter the group name for the newly created group : ");
                scanf("%s", new->name);
                printf(" set the weekly group goal for the newly created group :");
                scanf("%d", &new->weelky_goal);

                new->teammates = clan_copy(grp1->teammates, new->teammates);

                new->left = NULL;
                new->right = NULL;

                root = group_delete_avl(root, grp1->ID);
                root = group_inserst_avl(root, new);
            }
            else
            {
                group *new = (group *)malloc(sizeof(group));
                new->ID = grp1_id;
                printf(" Enter the group name for the newly created group : ");
                scanf("%s", new->name);
                printf(" set the weekly group goal for the newly created group :");
                scanf("%d", &new->weelky_goal);

                new->teammates = NULL;
                new->teammates = clan_copy(grp1->teammates, new->teammates);
                new->teammates = clan_copy(grp2->teammates, new->teammates);

                root = group_delete_avl(root, grp1->ID);
                root = group_delete_avl(root, grp2->ID);

                root = group_inserst_avl(root, new);
            }
        }
        else
            printf("ERROR : unable to find the groups , try again \n");
    }
    else
        printf("ERROR : no groups formed yet \n");

    return root;
}

leader *leader_rotate_right(leader *root)
{
    if (root)
    {
        if (root->left)
        {
            leader *temp = root->left;
            root->left = temp->right;
            temp->right = root;
            root->height = root->height - 2;
            root = temp;
        }
    }
    return root;
}
// height updated
leader *leader_rotate_left(leader *root)
{
    if (root)
    {
        if (root->right)
        {
            leader *temp = root->right;
            root->right = temp->left;
            temp->left = root;
            root->height = root->height - 2;
            root = temp;
        }
    }
    return root;
}
// height updated
leader *leader_balance_root(leader *root)
{
    if (root)
    {
        int left = 0;
        if (root->left)
            left = root->left->height;
        int right = 0;
        if (root->right)
            right = root->right->height;

        if (left - right > 1)
        {
            root = leader_rotate_right(root);
        }
        if (right - left > 1)
        {
            root = leader_rotate_left(root);
        }
    }
    return root;
}
// height updated
leader *leader_inserst_avl(leader *root, leader *ins)
{
    if (root)
    {
        int avg_grp = clan_avg_steps(root->team->teammates);
        avg_grp = avg_grp / clan_num(root->team->teammates);
        int avg_new = clan_avg_steps(ins->team->teammates);
        avg_new = avg_new / clan_num(ins->team->teammates);

        if (avg_grp > avg_new)
        {
            root->left = leader_inserst_avl(root->left, ins);
        }
        else if (avg_grp < avg_new)
        {
            root->right = leader_inserst_avl(root->right, ins);
        }

        else if (avg_grp == avg_new)
        {
            if(!root->next)
                root->next = ins ; // incase of no LL before
            else{
                leader* temp = root->next ;
                while(temp->next) temp = temp->next ; // incase of more than one nodes in LL
                temp->next = ins;
            }
            return root;
        }

        int left = 0;
        if (root->left)
            left = root->left->height;
        int right = 0;
        if (root->right)
            right = root->right->height;

        if (left > right)
            root->height = left + 1;
        else
            root->height = right + 1;

        root = leader_balance_root(root);
    }
    else
    {
        root = ins;
        root->height = 1;
    }

    return root;
}
// height updated
leader *create_leader_tree(leader *root, group *group_tree)
{
    if (group_tree)
    {
        root = create_leader_tree(root, group_tree->left);

        leader *new = (leader *)malloc(sizeof(leader));
        new->team = group_tree;
        new->left = NULL;
        new->right = NULL;
        new->next = NULL ;
        root = leader_inserst_avl(root, new);

        root = create_leader_tree(root, group_tree->right);
    }
}

void visit_leader(leader *root)
{
    if (root)
    {
        printf(" Group ID : %d\n", root->team->ID);
        printf(" Group name : %s \n ", root->team->name);
        int sum = clan_avg_steps(root->team->teammates);
        sum = sum / clan_num(root->team->teammates);
        printf(" Group average : %d \n", sum);
        printf(" Group goal : %d \n", root->team->weelky_goal);
        printf(" the height of the node is %d \n", root->height);
        printf("\n");
        if(root->next) visit_leader(root->next); // handles the LL case recursively 
    }
}

void leader_inorder(leader *root)
{
    if (root)
    {
        leader_inorder(root->right);
        visit_leader(root);
        leader_inorder(root->left);
    }
}

void Suggest_goal_update(user *user_list, user *top_3[])
{
    printf("Enter the ID of the user to be deleted \n");
    int user_id;
    scanf("%d", &user_id);

    user *temp = user_search(user_list, user_id);

    if (temp)
    {
        if (temp == top_3[0])
            printf("Currently you need no suggestions as you are the first\n");
        else if (top_3[0])
            printf("Your goal for the week is %d \n", Avg_steps(top_3[0]->weekly_count));
        else
            printf("Your goal for the week is %d \n", temp->daily_goal);
    }
    else
        printf("ERROR : provide a valid user ID \n");
}
// updated

void user_preorder(user* root){
    if(root){
        printf("%d  ",root->ID);
        user_preorder(root->left);
        user_preorder(root->right);
    }
}
void user_postorder(user* root){
    if(root){
        user_postorder(root->left);
        user_postorder(root->right);
        printf("%d  ",root->ID);
    }
}
// for understanding the structure of the tree thats created 
void group_preorder(group* root){
    if(root){
        printf("%d  ",root->ID);
        group_preorder(root->left);
        group_preorder(root->right);
    }
}
void group_postorder(group* root){
    if(root){
        group_postorder(root->left);
        group_postorder(root->right);
        printf("%d  ",root->ID);
    }
}

void leader_preorder(leader* root){
    if(root){
        printf("%d  ",root->team->ID);
        leader_preorder(root->left);
        leader_preorder(root->right);
    }
}
void leader_postorder(leader* root){
    if(root){
        leader_postorder(root->left);
        leader_postorder(root->right);
        printf("%d  ",root->team->ID);
    }
}

void clan_preorder(clanmate* root){
    if(root){
        printf("%d  ",root->clan->ID);
        clan_preorder(root->left);
        clan_preorder(root->right);
    }
}
void clan_postorder(clanmate* root){
    if(root){
        clan_postorder(root->left);
        clan_postorder(root->right);
        printf("%d  ",root->clan->ID);
    }
}

void display_range_info(group* root , int low , int high){
    if(root){
        if( root->ID>=low && root->ID<=high ){
            display_range_info(root->left,low,high);
            visit_group(root);
            display_range_info(root->right,low,high);
        } // root is in required range
        else if( root->ID < low )
            display_range_info(root->right,low,high); // skipping unwanted part of tree
        else if (root->ID > high)
            display_range_info(root->left,low,high); // skipping unwanted part of tree
    }
}

void main()
{
    user *user_tree = create_user_tree(NULL);

    group *group_tree = create_group_list(user_tree, NULL);
    user *top_3[3] = {NULL, NULL, NULL};
    user_tree = user_top_3(user_tree, top_3);

    group *new = NULL;
    leader *leader_board = NULL;

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
            user *new;
            new = create_user();
            user_tree = user_insert_avl(user_tree, new);
            printf("==========================================\n");
            break;
        }

        case 2:
            new = create_group(user_tree);
            group_tree = group_inserst_avl(group_tree, new);
            printf("==========================================\n");
            break;

        case 3:
            user_tree = user_top_3(user_tree, top_3);
            printf("the top 3 individuals of the day are : \n");
            printf("\n");
            visit_user(top_3[0]);
            printf("\n");
            visit_user(top_3[1]);
            printf("\n");
            visit_user(top_3[2]);
            printf("==========================================\n");
            break;

        case 4:
            printf("Ente the ID of the group  : ");
            int id;
            scanf("%d", &id);
            group *temp = group_search(group_tree, id);
            Check_group_acheivement(temp);
            printf("==========================================\n");
            break;

        case 5:
            leader_board = create_leader_tree(NULL, group_tree);
            printf("==========================================\n");
            leader_inorder(leader_board);
            // printf("Leader preorder : \n");
            // leader_preorder(leader_board);
            // printf("Leader postorder : \n");
            // leader_postorder(leader_board);
            break;

        case 6:
            Check_individual_rewards(user_tree, top_3);
            printf("===========================================\n");
            break;

        case 7:
            printf("ENter th ID of the individual to be deleted \n");
            int key;
            scanf("%d", &key);
            user_tree = user_delete_avl(user_tree, group_tree, key);
            printf("===========================================\n");
            break;

        case 8:
            printf("Enter the ID of the group to be deleted : ");
            int gkey;
            scanf("%d", &gkey);
            group_tree = group_delete_avl(group_tree, gkey);
            printf("===========================================\n");
            break;

        case 9:
            group_tree = merge_groups(group_tree);
            printf("===========================================\n");
            break;

        case 10 :
            printf("Enter the range of groups you need \n");
            int low , high ;
            scanf("%d%d",&low,&high);
            if(low>high){
                int temp = low ;
                low = high ;
                high = temp ;
            }
            printf("------------------------------\n");
            display_range_info(group_tree,low,high);
            printf("------------------------------\n");
            break;

        case 11:
            Suggest_goal_update(user_tree, top_3);
            break;

        case 12:
            printf("  INDIVIDUAL INFORMATION \n");
            printf("===========================================\n");
            user_InOrder(user_tree);            
            // printf("the height of the tree is %d \n",user_tree->height);
            // printf("===========================================\n");
            // printf(" User Preorder  \n");
            // user_preorder(user_tree);
            // printf(" User Postorder \n");
            // user_postorder(user_tree);
            // break;

        case 13:
            printf("the information of the groups present are : \n");
            printf("===========================================\n");
            group_Inorder(group_tree);
            // printf("the height of the tree is %d \n",group_tree->height);
            // printf("===========================================\n");
            // group_preorder(group_tree);
            // printf("===========================================\n");
            // group_postorder(group_tree);
            // printf("===========================================\n");
            break;

        }

        

        printf("Do you want to continue , if yes type y ");
        scanf("%c", &null);
        scanf("%c", &choice);
    } while (choice == 'y');

    // output_user_list(user_list) ;
    // output_group_list(group_list );
}