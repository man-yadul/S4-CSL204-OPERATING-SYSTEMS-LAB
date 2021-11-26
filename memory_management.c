#include<stdio.h>
#include<stdlib.h>
 
struct block
{
    struct block *prev;
 
    int block_no;
    int block_size;
    int process_no;
    int free_space;
 
    struct block *next;                                              
};
 
struct process
{
    int status;
    int process_no;
    int process_size;
};
 
int i, no_of_blocks, no_of_processes;
struct block *start = NULL, *end = NULL, *ptr = NULL, *new_block = NULL;
struct process processes[10];
 
void display()
{
    printf("\nDetails of blocks:");
    printf("\nBlock no.\tBlock size\tFree space in block\tAllocated process no.");
 
    for(ptr = start; ptr != NULL; ptr = ptr -> next)
    {
        printf("\n%d\t\t", ptr -> block_no);
        printf("%d\t\t", ptr -> block_size);
        printf("%d\t\t\t", ptr -> free_space);
 
        if(ptr -> process_no == -1)
            printf("-");
        else 
            printf("%d", ptr -> process_no);
    }
 
    printf("\nDetails of processes:");
    printf("\nProcess no.\tProcess size\tAllocated to block no.");
 
    for(i = 0; i < no_of_processes; i++)
    {
        printf("\n%d\t\t", processes[i].process_no);
        printf("%d\t\t", processes[i].process_size);
        
        if(processes[i].status >= 1)
            printf("%d", processes[i].status);
        else 
            printf("Unallocated");
    }
}
 
void first_fit()
{
    for(i = 0; i < no_of_processes; i++)
    {
        for(ptr = start; ptr != NULL; ptr = ptr -> next)
        {
            if(ptr -> process_no == -1 && ptr -> block_size >= processes[i].process_size)
            {
                processes[i].status = ptr -> block_no;
                ptr -> process_no = processes[i].process_no;
                ptr -> free_space = ptr -> free_space - processes[i].process_size;
                
                break; 
            }
        }
    }
}
 
void best_fit()
{
    int smallest_size;
    struct block *smallest; 
 
    for(i = 0; i < no_of_processes; i++)
    {
        smallest = NULL;
        smallest_size = 1000;   //1000 is taken as a dummy size to find the smallest block in the list
 
        for(ptr = start; ptr != NULL; ptr = ptr -> next)
        {
            if(ptr -> process_no == -1 && ptr -> block_size >= processes[i].process_size && ptr -> block_size <= smallest_size)  
            {
                smallest = ptr;
                smallest_size = ptr -> block_size;
            }
        }
 
        if(smallest != NULL)
        {
            processes[i].status = smallest -> block_no;
            smallest -> process_no = processes[i].process_no;
            smallest -> free_space = smallest -> free_space - processes[i].process_size;
        }
    }
}
 
void worst_fit()
{
    int largest_size;
    struct block *largest; 
 
    for(i = 0; i < no_of_processes; i++)
    {
        largest = NULL;
        largest_size = 0;   //0 is taken as a dummy size to find the largest block in the list
 
        for(ptr = start; ptr != NULL; ptr = ptr -> next)
        {
            if(ptr -> process_no == -1 && ptr -> block_size >= processes[i].process_size && ptr -> block_size >= largest_size)  
            {
                largest = ptr;
                largest_size = ptr -> block_size;
            }
        }
        
        if(largest != NULL)
        {
            processes[i].status = largest -> block_no;
            largest -> process_no = processes[i].process_no;
            largest -> free_space = largest -> free_space - processes[i].process_size;
        }
    }
}
 
void main()
{
    printf("\nEnter no. of blocks: ");
    scanf("%d", &no_of_blocks);
 
    for(i = 0; i < no_of_blocks; i++)
    {
        struct block *new_block = (struct block *)malloc(sizeof(struct block));
        new_block -> prev = NULL;
        new_block -> next = NULL;
 
        new_block -> block_no = i + 1;
        new_block -> process_no = -1;
 
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &new_block -> block_size);
 
        new_block -> free_space = new_block -> block_size;
 
        if(start == NULL && end == NULL)
            start = end = new_block;
        else 
        {
            end -> next = new_block;
            new_block -> prev = end;
            end = new_block;
        }
    }
 
    printf("Enter no. of processes: ");
    scanf("%d", &no_of_processes);
 
    for(i = 0; i < no_of_processes; i++)
    {
        processes[i].process_no = i + 1;
 
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &processes[i].process_size);
    }
 
    printf("\nFirst fit allocation:");
    first_fit();
    display();
 
    for(ptr = start; ptr != NULL; ptr = ptr -> next)    //To clear allocation
    {
        ptr -> process_no = -1;
        ptr -> free_space = ptr -> block_size;
    }
 
    for(i = 0; i < no_of_processes; i++)
    {
        processes[i].status = -1;
    }
 
    printf("\n\nBest fit allocation:");
    best_fit();
    display();
 
    for(ptr = start; ptr != NULL; ptr = ptr -> next)    //To clear allocation
    {
        ptr -> process_no = -1;
        ptr -> free_space = ptr -> block_size;
    }
 
    for(i = 0; i < no_of_processes; i++)
    {
        processes[i].status = -1;
    }
 
    printf("\n\nWorst fit allocation:");
    worst_fit();
    display();
}
