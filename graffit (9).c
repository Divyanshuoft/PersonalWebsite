/**
 * CSC A48 - Intro to Computer Science II, Summer 2021
 * 
 * Assignment 3 - Graffit
 * 
 * Graphs &
 * Recursion
 * Assignment
 * For
 * Freshmen
 * In
 * Toronto
 *
 * (I am so proud of that initialism.)
 * 
 * This is the program file where you will implement your solution for
 * Assignment 3. Please make sure you read through this file carefully
 * and that you understand what is provided and what you need to complete.
 * 
 * You will also need to have read the handout carefully. 
 * 
 * Parts where you have to implement functionality are clearly labeled TODO.
 * 
 * Be sure to test your work thoroughly, our testing will be extensive
 * and will check that your solution is *correct*, not only that it
 * provides functionality.
 * 
 * (c) 2020 William Song, Mustafa Quraish
 * (c) 2021 Charles Xu
 **/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_LEN 1024

#ifndef MAT_SIZE
#define MAT_SIZE 3// A small graph
#endif

typedef struct user_struct
{
  char name[MAX_STR_LEN];
  struct friend_node_struct *friends;
  struct brand_node_struct *brands;
  bool visited;
} User;

typedef struct friend_node_struct
{
  User *user;
  struct friend_node_struct *next;
} FriendNode;

typedef struct brand_node_struct
{
  char brand_name[MAX_STR_LEN];
  struct brand_node_struct *next;
} BrandNode;

FriendNode *allUsers = NULL;

int brand_adjacency_matrix[MAT_SIZE][MAT_SIZE];
char brand_names[MAT_SIZE][MAX_STR_LEN];

/**
 * Given the head to a FriendNode linked list, returns true if a
 * given user's name exists in the list. Returns false otherwise.
 */
bool in_friend_list(FriendNode *head, User *node)
{
  for (FriendNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->user->name, node->name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a BrandNode linked list, returns true if a
 * given brand's name exists in the list. Returns false otherwise.
 */
bool in_brand_list(BrandNode *head, char *name)
{
  for (BrandNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->brand_name, name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a FriendNode linked list, inserts a given user
 * into the linked list and returns the head of the new linked list.
 * The insertion is done in alphabetical order. If the user already
 * exists, no modifications are made and the list is returned as is.
 */
FriendNode *insert_into_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (in_friend_list(head, node))
  {
    printf("User already in list\n");
    return head;
  }

  FriendNode *fn = calloc(1, sizeof(FriendNode));
  fn->user = node;
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->user->name, node->name) > 0)
  {
    fn->next = head;
    return fn;
  }

  FriendNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->user->name, node->name) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a BrandNode linked list, inserts a given brand into
 * the linked list and returns the head of the new linked list. The
 * insertion is done in alphabetical order. If the brand already exists,
 * no modifications are made and the list is returned as is.
 */
BrandNode *insert_into_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (in_brand_list(head, node))
  {
    printf("Brand already in list\n");
    return head;
  }

  BrandNode *fn = calloc(1, sizeof(BrandNode));
  strcpy(fn->brand_name, node);
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->brand_name, node) > 0)
  {
    fn->next = head;
    return fn;
  }

  BrandNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->brand_name, node) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a FriendNode linked list, removes a given user from
 * the linked list and returns the head of the new linked list. If the user
 * does not exist, no modifications are made and the list is returned as is.
 */
FriendNode *delete_from_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (!in_friend_list(head, node))
  {
    printf("User not in list\n");
    return head;
  }

  if (strcmp(head->user->name, node->name) == 0)
  {
    FriendNode *temp = head->next;
    free(head);
    return temp;
  }

  FriendNode *cur;
  for (cur = head; cur->next->user != node; cur = cur->next)
    ;

  FriendNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given the head to a BrandNode linked list, removes a given brand from
 * the linked list and returns the head of the new linked list. If the brand
 * does not exist, no modifications are made and the list is returned as is.
 */
BrandNode *delete_from_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (!in_brand_list(head, node))
  {
    printf("Brand not in list\n");
    return head;
  }

  if (strcmp(head->brand_name, node) == 0)
  {
    BrandNode *temp = head->next;
    free(head);
    return temp;
  }

  BrandNode *cur;
  for (cur = head; strcmp(cur->next->brand_name, node) != 0; cur = cur->next)
    ;

  BrandNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given a user, prints their name, friends, and liked brands.
 */
void print_user_data(User *user)
{
  printf("User name: %s\n", user->name);

  printf("Friends:\n");
  for (FriendNode *f = user->friends; f != NULL; f = f->next)
  {
    printf("   %s\n", f->user->name);
  }

  printf("Brands:\n");
  for (BrandNode *b = user->brands; b != NULL; b = b->next)
  {
    printf("   %s\n", b->brand_name);
  }
}

/**
 * Given a brand, returns the index of the brand inside the brand_names array.
 * If it doesn't exist in the array, return -1
 */
int get_brand_index(char *name)
{
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (strcmp(brand_names[i], name) == 0)
    {
      return i;
    }
  }

  printf("Brand '%s' not found\n", name);
  return -1; // Not found
}

/**
 * Given a brand, prints their name, index (inside the brand_names
 * array), and the names of other similar brands.
 */
void print_brand_data(char *brand_name)
{
  int idx = get_brand_index(brand_name);
  if (idx < 0)
  {
    printf("Brand '%s' not in the list.\n", brand_name);
    return;
  }

  printf("Brand name: %s\n", brand_name);
  printf("Brand idx: %d\n", idx);

  printf("Similar brands:\n");
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (brand_adjacency_matrix[idx][i] == 1 && strcmp(brand_names[i], "") != 0)
    {
      printf("   %s\n", brand_names[i]);
    }
  }
}

/**
 * Read from a given file and populate a the brand list and brand matrix.
 **/
void populate_brand_matrix(char *file_name)
{
  // Read the file
  char buff[MAX_STR_LEN];
  FILE *f = fopen(file_name, "r");
  fscanf(f, "%s", buff);
  char *line = buff;
  // Load up the brand_names matrix
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (i == MAT_SIZE - 1)
    {
      strcpy(brand_names[i], line);
      break;
    }
    int index = strchr(line, ',') - line;
    strncpy(brand_names[i], line, index);
    line = strchr(line, ',') + sizeof(char);
  }
  // Load up the brand_adjacency_matrix
  for (int x = 0; x < MAT_SIZE; x++)
  {
    fscanf(f, "%s", buff);
    for (int y = 0; y < MAT_SIZE; y++)
    {
      int value = (int)buff[y * 2];
      if (value == 48)
      {
        value = 0;
      }
      else
      {
        value = 1;
      }
      brand_adjacency_matrix[x][y] = value;
    }
  }
}

int search(FriendNode *list, char *name){
  FriendNode *traverse = NULL;
  traverse = list;
  int checker = 0;
  while (traverse != NULL){
    if(strcmp(traverse->user->name, name) == 0) checker++;
    traverse = traverse->next;}
  if(checker == 0) return 0;
  return 1;}

int search_brands(BrandNode *list, char *name){
  BrandNode *traverse = NULL;
  traverse = list;
  int checker = 0;
  while (traverse != NULL){
    if(strcmp(traverse->brand_name, name) == 0) checker++;
    traverse = traverse->next;}
  if(checker == 0) return 0;
  return 1;}

/**
 * TODO: Complete this function
 * Creates and returns a user.
 */
User *create_user(char *name)
{ 
  if(search(allUsers, name) == 1 || name == NULL) return NULL; 
  User *new_node = (User *)calloc(1, sizeof(User));
  strcpy(new_node->name, name);
  new_node->brands = NULL;
  new_node->friends = NULL;
  new_node->visited = false;
  allUsers = insert_into_friend_list(allUsers, new_node);
  return new_node;}

/**
 * TODO: Complete this function
 * Deletes a given user.
 */

int delete_user(User *user)
{ 
  if(search(allUsers, user->name) == 0 || user == NULL) return -1;
  allUsers = delete_from_friend_list(allUsers, user);
  FriendNode *traverse = NULL;
  traverse = allUsers;
  while (traverse != NULL){ 
    if(search(traverse->user->friends, user->name) == 1){
    traverse->user->friends = delete_from_friend_list(traverse->user->friends, user);}
    traverse = traverse->next;}
  return 0;}

/**
 * TODO: Complete this function
 * Create a friendship between user and friend.
 */

int add_friend(User *user, User *friend)
{ 
  if(user == NULL || friend == NULL) return -1;
  if(search(user->friends, friend->name) != 1 && search(friend->friends, user->name) != 1){
  if(strcmp(user->name, friend->name) != 0){
  user->friends = insert_into_friend_list(user->friends, friend);
  friend->friends = insert_into_friend_list(friend->friends, user);}
  return 0;}
  return -1;}

/**
 * TODO: Complete this function
 * Removes a friendship between user and friend.
 */

int remove_friend(User *user, User *friend)
{
  if(user == NULL || friend == NULL) return -1;
  if(search(user->friends, friend->name) != 0 && search(friend->friends, user->name) != 0){
  user->friends = delete_from_friend_list(user->friends, friend);
  friend->friends = delete_from_friend_list(friend->friends, user);
  return 0;}
  return -1;}

/**
 * TODO: Complete this function
 * Creates a follow relationship, the user follows the brand.
 */

int follow_brand(User *user, char *brand_name)
{ 
  if(user == NULL) return -1;
  if(search_brands(user->brands, brand_name) == 1) return -1;
  user->brands = insert_into_brand_list(user->brands, brand_name);
  return 0;}

/**
 * TODO: Complete this function
 * Removes a follow relationship, the user unfollows the brand.
 */
int unfollow_brand(User *user, char *brand_name)
{
  if(search_brands(user->brands, brand_name) == 0) return -1;
  user->brands = delete_from_brand_list(user->brands, brand_name);
  return 0;}

/**
 * TODO: Complete this function
 * Return the number of mutual friends between two users.
 */
int get_mutual_friends(User *a, User *b)
{ 
  if(a != NULL && b != NULL){
  int i = 0;
  FriendNode *t = NULL;
  t = a->friends;
  while (t != NULL){
    if(search(b->friends, t->user->name) == 1) i++;
    t = t->next;}
  return i;}
  return 0;}

/**
 * TODO: Complete this function
 * A degree of connection is the number of steps it takes to get from
 * one user to another. Returns a non-negative integer representing
 * the degrees of connection between two users.
 */

void answer(User *a, User *b, int depth, int *p, int *z){
  FriendNode *traverse = NULL;
  traverse = a->friends;
  while (traverse != NULL){
    if(strcmp(traverse->user->name, b->name) == 0){
      *p = depth + 1;
      if(*z == -1 || *z > *p) *z = *p;}
    else{
      if(traverse->user->visited == false){
      traverse->user->visited = true;
      answer(traverse->user, b, depth + 1, p, z);
      traverse->user->visited = false;}}
    traverse = traverse->next;}}

int get_degrees_of_connection(User *a, User *b)
{ 
  if(strcmp(a->name, b->name) == 0) return 0;
  int result = 0;
  int *p = &result;
  *p = 0;
  FriendNode *j = allUsers;
  while (j != NULL){
    j->user->visited = false;
    j = j->next;} 
  int ans = -1;
  int *z = NULL;
  z = &ans;
  answer(a, b, 0, p, z);
  FriendNode *t = NULL;
  t = allUsers;
  while (t != NULL){
    t->user->visited = false;
    t = t->next;} 
  return *z;}

int brandname_validity(char a[MAT_SIZE][MAX_STR_LEN], char *name){
  int i = 0;
  int ctr = 0;
  while (i < MAT_SIZE){
    if(strcmp(a[i], name) == 0) ctr++;
    i++;}
  if(ctr == 0) return 0;
  return 1;}

/**
 * TODO: Complete this function
 * Marks two brands as similar.
 */
void connect_similar_brands(char *brandNameA, char *brandNameB)
{
  if(brandname_validity(brand_names, brandNameA) == 1 && brandname_validity(brand_names, brandNameA) == 1){
    int index1 = get_brand_index(brandNameA);
    int index2 = get_brand_index(brandNameB);
    brand_adjacency_matrix[index1][index2] = 1;
    brand_adjacency_matrix[index2][index1] = 1;}
  return;}

/**
 * TODO: Complete this function
 * Marks two brands as not similar.
 */
void remove_similar_brands(char *brandNameA, char *brandNameB)
{
  if(brandname_validity(brand_names, brandNameA) == 1 && brandname_validity(brand_names, brandNameA) == 1){
    int index1 = get_brand_index(brandNameA);
    int index2 = get_brand_index(brandNameB);
    brand_adjacency_matrix[index1][index2] = 0;
    brand_adjacency_matrix[index2][index1] = 0;}
  return;}

/**
 * TODO: Complete this function
 * Returns a suggested friend for the given user.
 */

int search_similiar_brand(User *a, User *b){
  BrandNode *traverse1 = a->brands;
  int counter = 0;
  while(traverse1 != NULL){
      BrandNode *traverse2 = b->brands;
    while (traverse2 != NULL){
      if(strcmp(traverse1->brand_name, traverse2->brand_name) == 0) counter++;
      traverse2 = traverse2->next;}
    traverse1 = traverse1->next;}
  return counter;}

 
User *get_suggested_friend(User *user)
{ 
  if(user != NULL){
  int max = 0;
  FriendNode *t = NULL;
  t = allUsers;
  User *result = NULL;
  while (t != NULL){ 
  if(in_friend_list(t->user->friends, user) == false && strcmp(t->user->name, user->name)!=0)
		{
      int k = search_similiar_brand(t->user, user);
      if(k >= max){
        max = k;
        result = t->user;
      }
    }
    t = t->next;
    }
  if(result != NULL){
  return result;}}
  return NULL;
  }

/**
 * TODO: Complete this function
 * Adds n suggested friends for the given user.
 * Returns how many friends were successfully followed.
 */
int add_suggested_friends(User *user, int n)
{
  int ctr = 0;
  User *hepta = user;
  while(n != 0){
  User *t = get_suggested_friend(hepta);
  if(t != NULL){
    add_friend(user, t);
    n--;
    if(search(user->friends, t->name) == 1) ctr++;
  }
  else{
    break;
  }
  }
  return ctr;}

int connections(char brand[MAX_STR_LEN], BrandNode *user_brands){
  int index_brand = get_brand_index(brand);
  int ctr = 0;
  for (int i = 0; i < MAT_SIZE; i++){
    if(search_brands(user_brands, brand_names[i]) == 1){
    if((brand_adjacency_matrix[i][index_brand]) == 1) ctr++;}}
  return ctr;}

/**
 * TODO: Complete this function
 * Follows n suggested brands for the given user.
 * Returns how many brands were successfully followed.
 */
int follow_suggested_brands(User *user, int n)
{
  int t = 0;
  BrandNode *heifa = NULL;
  BrandNode *oo = user->brands;
  while(oo != NULL)
  {
    heifa = insert_into_brand_list(heifa, oo->brand_name);
    oo = oo->next;
  }
  int max = 0;
  while (n != 0){
  max = 0;
  char result[MAX_STR_LEN];
  strcpy(result, "");
  for(int i = 0; i < MAT_SIZE; i++){
    if(search_brands(user->brands, brand_names[i]) == 0){
      if(connections(brand_names[i], heifa) >= max){
      if(connections(brand_names[i], heifa) == max){
      if(strcmp(result, brand_names[i]) < 0){
        max = connections(brand_names[i], heifa);
        strcpy(result, brand_names[i]);
        }}
      else{
        max = connections(brand_names[i], heifa);
        strcpy(result, brand_names[i]);
      }}
        }}
  user->brands = insert_into_brand_list(user->brands, result);
  n--;
  if(search_brands(user->brands, result) == 1) t++;
      strcpy(result, "");}
  return t;
}


















































































































































