/*
 * This implementation replicates the implicit list implementation
 * provided in the textbook
 * "Computer Systems - A Programmer's Perspective"
 * Blocks are never coalesced or reused.
 * Realloc is implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    "woozy_koala",
    "yanisa khambanonda",
    "yanisa.khambanonda@mail.utoronto.ca",
    /* Second member's full name (do not modify this as this is an individual lab) */
    "",
    /* Second member's email address (do not modify this as this is an individual lab)*/
    ""
};

/*************************************************************************
 * Basic Constants and Macros
 * You are not required to use these macros but may find them helpful.
*************************************************************************/
#define WSIZE       sizeof(void *)            /* word size (bytes) */
#define DSIZE       (WSIZE + WSIZE)            /* doubleword size (bytes) */
#define TSIZE       (DSIZE + DSIZE)

#define MAX(x,y) ((x) > (y)?(x) :(y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p)          (*(uintptr_t *)(p))
#define PUT(p,val)      (*(uintptr_t *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)     (GET(p) & ~(DSIZE - 1))
#define GET_ALLOC(p)    (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)        ((char *)(bp) - WSIZE)
#define FTRP(bp)        ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)) )
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)) )

#define FREE_LIST_NUMBER 10 //8


void* heap_listp = NULL;
typedef struct free_block{
    struct free_block* next;
    struct free_block* prev;
}free_block;
free_block* free_lists[FREE_LIST_NUMBER];
int find_free_list(int size);
void add_to_freelist(free_block* temp);
void remove_from_freelist(free_block* block);
void unplace(void* bp, size_t asize);
void place(void* bp, size_t asize);
/**********************************************************
 *  HEADER = 8 BYTE (1 WORD) FOOTER = 8 BYTE (1 WORD)
 * 
 *  FOOTER 8
 * |       |
 * | DATA  |        DATA MUST BE MULTIPLE OF 16 
 * |       |
 *  HEADER 8
 *  
 * Free list sizes
 * bucket 0 : 16 bytes (1-2 word)
 * bucket 1 : 32 bytes (4 word)
 * bucket 2 : 64 bytes (5-8 word)
 * bucket 3 : 128 (9-16 word)
 * bucket 4 : 256 (17-32 word)
 * bucket 5 : 512 (33-64 word)
 * bucket 6 : 1024 
 * bucket 7 : 2048 
 *  
 *********************************************************/

/**********************************************************
 * mm_init
 * Initialize the heap, including "allocation" of the
 * prologue and epilogue
 **********************************************************/
 int mm_init(void)
 {
   if ((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1)
         return -1;
     PUT(heap_listp, 0);                         // alignment padding
     PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));   // prologue header
     PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));   // prologue footer
     PUT(heap_listp + (3 * WSIZE), PACK(0, 1));    // epilogue header
     heap_listp += DSIZE;
     for (int i = 0; i < FREE_LIST_NUMBER; i ++){
         free_lists[i] = NULL;
     }
     return 0;
 }

/**********************************************************
 * coalesce
 * Covers the 4 cases discussed in the text:
 * - both neighbours are allocated
 * - the next block is available for coalescing
 * - the previous block is available for coalescing
 * - both neighbours are available for coalescing
 **********************************************************/
void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp))- DSIZE;

    if (prev_alloc && next_alloc) {       /* Case 1 */
        return bp;
    }

    else if (prev_alloc && !next_alloc) { /* Case 2 */

        free_block * temp = (free_block *)NEXT_BLKP(bp);
        remove_from_freelist(temp);

        size += GET_SIZE(HDRP(temp));
        
        PUT(HDRP(bp),PACK(size+DSIZE,0));
        PUT(FTRP(bp),PACK(size+DSIZE,0));
        return (bp);
    }

    else if (!prev_alloc && next_alloc) { /* Case 3 */
        remove_from_freelist((free_block*) PREV_BLKP(bp));

        size += GET_SIZE(HDRP(PREV_BLKP(bp))) ;
        PUT(FTRP(bp),PACK(size+DSIZE,0));
        PUT(HDRP(PREV_BLKP(bp)),PACK(size+DSIZE,0));
        return (PREV_BLKP(bp));
    }

    else {            /* Case 4 */
        free_block* temp = (free_block *)NEXT_BLKP(bp);
        remove_from_freelist((free_block *)PREV_BLKP(bp));
        remove_from_freelist(temp);

        size += GET_SIZE(FTRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp))) ;
        PUT(HDRP(PREV_BLKP(bp)),PACK(size+DSIZE,0));
        PUT(FTRP(temp),PACK(size+DSIZE,0));
        return (PREV_BLKP(bp));
    }
}

/**********************************************************
 * extend_heap
 * Extend the heap by "words" words, maintaining alignment
 * requirements of course. Free the former epilogue block
 * and reallocate its new header
 **********************************************************/
void *extend_heap(size_t words)
{   
    char *bp;
    size_t size = words;
    /* Allocate an even number of words to maintain alignments */
    if ( (bp = mem_sbrk(size + DSIZE)) == (void *)-1 )
        return NULL;
    unplace(bp, size);
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));        // new epilogue header
    place(bp, size);
    return bp;
}


/**********************************************************
 * find_fit
 * Traverse the heap searching for a block to fit asize
 * Return NULL if no free blocks can handle that size
 * Assumed that asize is aligned
 **********************************************************/
void * find_fit(size_t asize){   
    // void *bp;
    // printf("fitting into jeans... \n");
    int free_list = find_free_list(asize);
    size_t size = asize;
    for (int i = free_list; i < FREE_LIST_NUMBER; i++){
        
        if (free_lists[i] != NULL){
            free_block* temp = free_lists[i];
            while (temp !=NULL){
                int tsize = GET_SIZE(HDRP(temp)) - DSIZE;
                // printf("%d %d \n",size, tsize);
                if (tsize >= size && tsize < (size + TSIZE)){
                    remove_from_freelist(temp);
                    place(temp, tsize);
                    return (void*)temp;
                }
                else if (tsize >= (size + TSIZE)){
                    remove_from_freelist(temp);
                    size_t extra_size = tsize - size - DSIZE;
                    // printf("%d %d %d \n", extra_size%16, tsize%16, size%16);
                    void* use_ptr = (void*)temp + extra_size + DSIZE;
                    unplace(use_ptr, size);
                    unplace(temp, extra_size);
                    add_to_freelist(temp);
                    place(use_ptr,size);
                    return use_ptr;
                }
                temp = temp->next;      
            }
        }
    }
    return NULL;
}

/*********************************************************
 * find_free_list
 * Lookup Index of FreeList
 *********************************************************/
int find_free_list(int size){
    int cnt = -4;
    size --;
    while (size != 0){
        size = size >> 1;
        cnt ++;
    }
    cnt = MAX(0,cnt);
    return cnt >= FREE_LIST_NUMBER ? FREE_LIST_NUMBER -1 : cnt;
}

/**********************************************************
 * add_to_freelist
 * 
 *********************************************************/
void add_to_freelist(free_block* temp){
    if (temp == NULL){
        return;
    }
    size_t size = GET_SIZE(HDRP(temp))-DSIZE;
    int free_list = find_free_list(size);
    if (free_lists[free_list] == NULL){
        free_lists[free_list] = temp;
        free_lists[free_list]->next = NULL;
        free_lists[free_list]->prev = NULL;
    }
    else{
        temp -> next = free_lists[free_list];
        temp -> prev = NULL;
        free_lists[free_list]->prev = temp;
        free_lists[free_list] = temp;
    }
    return;
}

/**********************************************************
 * remove_from_freelist
 * 
 *********************************************************/
void remove_from_freelist(free_block* block){
    if (block == NULL){
        return;
    }
    size_t size = GET_SIZE(HDRP(block)) - DSIZE;
    int freelist = find_free_list(size);
    if (block-> prev == NULL && block->next == NULL){ // empty list
        free_lists[freelist] = NULL;
        return;
    }
    else if (block->prev==NULL){        // if b is first elem of list
        free_lists[freelist] = block->next;
        (block->next)->prev = NULL; 
        return;
    }
    else if (block->next == NULL){      // if b is last elem of list
        (block->prev)->next = NULL;
        return;
    }
    else{                               // b is in the middle
        ((block)->prev)->next = (block)->next;
        ((block)->next)->prev = (block)->prev;
        return;
    }
}
/**********************************************************
 * place
 * Mark the block as allocated
 **********************************************************/
void place(void* bp, size_t asize)
{
  asize += DSIZE;
  /* Get the current block size */
  PUT(HDRP(bp), PACK(asize, 1));
  PUT(FTRP(bp), PACK(asize, 1));
}

void unplace(void* bp, size_t asize){
    asize += DSIZE;
    PUT(HDRP(bp), PACK(asize, 0));
    PUT(FTRP(bp), PACK(asize, 0));

}

/**********************************************************
 * mm_free
 * Free the block and coalesce with neighbouring blocks
 **********************************************************/
void mm_free(void *bp)
{
    if(bp == NULL){
        return;
    }

    if(GET_ALLOC(HDRP(bp))==0){
        return;
    }

    size_t size = GET_SIZE(HDRP(bp))-DSIZE;
    unplace(bp, size);
    bp = coalesce(bp);
    add_to_freelist((free_block*)bp);
}


/**********************************************************
 * mm_malloc
 * Allocate a block of size bytes.
 * The type of search is determined by find_fit
 * The decision of splitting the block, or not is determined
 *   in place(..)
 * If no block satisfies the request, the heap is extended
 **********************************************************/
void *mm_malloc(size_t size)
{   
    char * bp;
    /* Ignore spurious requests */
    if (size == 0)
        return NULL;

    if (size < DSIZE ){
        size = DSIZE;
    }

    else if (size <= 8192){
        size --;
        size |= size >> 1;
        size |= size >> 2;
        size |= size >> 4;
        size |= size >> 8;
        size |= size >> 16;
        size++;
    }
    else{
        size = ((size-1)/ DSIZE)*DSIZE + DSIZE;
    }
    
    if ((bp = find_fit(size)) != NULL){
        return bp;
    }
    if ((bp = extend_heap(size))== NULL){
        return NULL;
    }
    return bp;
}


/**********************************************************
 * mm_realloc
 * Implemented simply in terms of mm_malloc and mm_free
 *********************************************************/
void *mm_realloc(void *ptr, size_t size)
{
    if(size == 0){
      mm_free(ptr);
      return NULL;
    }

    /* If oldptr is NULL, then this is just malloc. */
    if (ptr == NULL)
      return (mm_malloc(size));

    void *oldptr = ptr;
    void *newptr;
    size_t old_size = GET_SIZE(HDRP(oldptr))-DSIZE;

    if (size<DSIZE){
        size = DSIZE;
    }
    else if (size<=8192){ //4096 ){//2048){
        size --;
        size |= size >> 1;
        size |= size >> 2;
        size |= size >> 4;
        size |= size >> 8;
        size |= size >> 16;
        size++;
    }
    else{
        size = ((size-1)/ DSIZE)*DSIZE + DSIZE;
    }

    if (size<=old_size){   // wants less space
        size_t extra = old_size-size;
        if (extra >= DSIZE+DSIZE){
            newptr = (void *) (oldptr + size + DSIZE);
            unplace(newptr,extra-DSIZE);
            add_to_freelist((free_block*)newptr);

            place(oldptr, size);
        }
        return oldptr;
    }
    
    else{       // wants more space
        unplace(ptr, old_size);
        ptr = coalesce(ptr);
        size_t coalesced_size = GET_SIZE(HDRP(ptr)) - DSIZE;
        if(coalesced_size >= size){
            
            memmove(ptr, oldptr, old_size);
            place(ptr, coalesced_size);
            return ptr;
        }

        newptr = mm_malloc(size);
        if (newptr == NULL){
            return NULL;
        }
        memcpy(newptr, oldptr, old_size);
        add_to_freelist((free_block * )ptr);
        return newptr;
    }

}


/**********************************************************
 * mm_check
 * Check the consistency of the memory heap
 * Return nonzero if the heap is consistant.
 *********************************************************/
int mm_check(void){
  return 1;
}
