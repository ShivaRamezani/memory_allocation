#include <stdio.h>
#include <stdlib.h>
// declare structure to store block information (id, starting address, ending address, link to next block)
struct node {
   int id;
   int start;
   int end;
   struct node *link;
} *block_list = NULL;
typedef struct node block_type;

// declare global variables
int pm_size;
int hole_algo; //algorithm
int remaining;  //remaining space
/********************************************************************/
void option1() {
// declare local variables (if any)
// prompt for size of physical memory and choice of hole-fitting algorithm (0=first-fit, 1=best-fit), initialize remaining memory
   printf("Enter the size of physical memory: ");
   scanf("%d", &pm_size);
   
   
   printf("Enter the choice of hole fitting algorithm: ");
   scanf("%d", &hole_algo);
   
   remaining = pm_size;
   
//allocate memory 
   block_list = (block_type*)malloc(sizeof(block_type));
   
// initilize linked list with "dummy" block of size 0
   block_list->id = -1;
   block_list->start = 0;
   block_list->end = 0;
   block_list->link = NULL;
   
   return;
}
/********************************************************************/
void print() {
// declare local variables
   block_type* table = block_list;
   
   printf("id\tstart\tend\n");
   printf("------------------------------------------------\n");
// print table containing block id, starting address, ending address
   while (table != NULL) {
      printf("%d\t", table->id);
      printf("%d\t", table->start);
      printf("%d\n", table->end);
      table= table->link;
      }
   
return;
}
/********************************************************************/
void option2() {
// declare local variables
   int best_hole;
   int block_id;
   int block_size;
   block_type* new_block;
   block_type* next_block = block_list;
   int start_hole;
   int end_hole;
   int hole_size;
   int best_start;
   block_type* best_block;
   int one_hole = 0;
   
   //int at_least_one = 0;
// initialize best hole so far to size of physical memory
   best_hole = remaining;
// prompt for block id & block size
   printf("Enter the block id: ");
   scanf("%d", &block_id);
   
   printf("Enter the block size: ");
   scanf("%d", &block_size);


// check if size of block is larger than remaining unallocated space, if so, print message and return
   if (block_size > remaining) {
      printf("out of range!");
      return;
      }

// allocate space for new block and set id
   new_block = (block_type*)malloc(sizeof(block_type));
   new_block->id = block_id;
   
// if only "dummy" block exists, insert block at end of linked list, set fields, return
   if (block_list->link == NULL) {
      block_list->link = new_block;
      new_block->start = 0;
      new_block->end = block_size;
      new_block->link = NULL;
      
      remaining = remaining - block_size;
      print();
      return;
   }
   else {
   
// else traverse list until either appropriate hole is found or the end of the list is reached
   //curremt_block = block_list;
   while (next_block != NULL) {
   // if id already exists, reject request and return
      if (next_block->id == block_id) {
         printf("rejected"); 
         return;
      }
         
// set values for start and end of currently found hole
      start_hole = next_block->end;
      
      if (next_block->link == NULL)
         end_hole = pm_size;
      else
         end_hole = next_block->link->start;
         
      hole_size = end_hole - start_hole;
      
// if hole is large enough for block
      if (block_size <= hole_size)  {
         one_hole = 1;
      // if first-fit algorithm
         if (hole_algo == 0) {
            // set start & end fields of new block & add block into linked list
            new_block->start = start_hole;
            new_block->end = start_hole + block_size ;
            new_block->link = next_block->link;
            next_block->link = new_block;
            //current_block->link = new_block;
            
            // reduce remaining available memory and return
            remaining -= block_size;
            return;
         }
         // else--best-fit algorithm
         else {
            // if hole is smaller than best so far
            if (hole_size <= best_hole) {
            // set values of best start & best end & best hole size so far
               best_hole = hole_size;
               
               best_start = start_hole;
               best_block = next_block; 
            }
         } 
       } 
      // update best block & advance next block
      next_block = next_block->link;
      }
      
      
   if (one_hole == 0) {
      printf("hole not big enough");
      //free(new_block);
      return;
   }
   else {
// set start & end fields of new block & add block into linked list 
      new_block->start = best_start;
      new_block->end = best_start + block_size;
      
      new_block->link = best_block->link;
      best_block->link = new_block;
// reduce remaining available memory and return
      remaining = remaining - block_size;
      
     }
     }
      print();
      return;
}
/********************************************************************/
void option3() {
// declare local variables
int block_id;
block_type* endOfList = block_list;
block_type* followList;

// prompt for block id
printf("Enter block id: ");
scanf("%d", &block_id);


// until end of linked list is reached or block id is found
while ( (endOfList!= NULL) && (block_id != endOfList->id) ) {
   followList = endOfList;
   endOfList = endOfList->link;
   }
// traverse list
// if end of linked list reached, print block id not found
if (endOfList == NULL) {
   printf("Block id not found");
   return;
   }
else {
// else remove block and deallocate memory
followList->link = endOfList->link;
remaining = remaining + (endOfList->end - endOfList->start);
free(endOfList);
}
print();
return;
}
/********************************************************************/
void option4() {
// declare local variables 
int block_size;
int previous_end = 0;
block_type* endOfList = block_list;

// until end of list is reached
while (endOfList != NULL) {
   // calculate current hole size
   block_size = endOfList->end - endOfList->start;
   
   // adjust start & end fields of current block to eliminate hole
   endOfList->start = previous_end;
   endOfList->end = previous_end + block_size;
   previous_end = endOfList->end;
   endOfList = endOfList->link;
   } 
print();
return;
}
/********************************************************************/
void option5(block_type *node) {

// if node is NULL, return
if (node == NULL) {
return;
}
// else
else {
   option5(node->link);
//recursively call procedure on node->link
// deallocate memory from node
   free(node);
   printf("quiting the program...")
   }

return;
}
/***************************************************************/
int main() {


  int choice = 0;
  
  while (choice != 5) {
     printf("\nMemory allocation\n");
     printf("--------------------------------\n");
     printf("1) Enter parameters\n");
     printf("2) Allocate memory for block\n");
     printf("3) Deallocate memory\n");
     printf("4) Difragment memory\n");
     printf("5) Quit program\n");


     printf("\nEnter selection: ");
     scanf("%d", &choice);
    
     switch(choice) {
        case 1: option1();
        break;
        case 2: option2();
        break;
        case 3: option3(); 
        break;
        case 4: option4(); 
        break;
        case 5: option5(block_list); 
        break;
        default: 
        printf("Invalid option!\n"); 
        break;
     }    
   }    
  return 1;
}