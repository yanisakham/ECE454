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
#define DSIZE       (2 * WSIZE)            /* doubleword size (bytes) */
#define CHUNKSIZE   (1<<7)      /* initial heap size (bytes) */

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
#define FTRP(bp)        ((char *)(bp) + GET_SIZE(HDRP(bp)))

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)) + DSIZE)
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)) - DSIZE)

#define FREE_LIST_NUMBER 8


void* heap_listp = NULL;
typedef struct free_block{
    struct free_block* next;
    struct free_block* prev;
}free_block;
free_block* free_lists[FREE_LIST_NUMBER];
int find_free_list(int size);
void add_to_freelist(free_block* temp);
void remove_from_freelist(free_block* block);
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
     printf("done mm_init \n");
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
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {       /* Case 1 */
        return bp;
    }

    else if (prev_alloc && !next_alloc) { /* Case 2 */
        free_block* temp = (free_block *)NEXT_BLKP(bp);
        remove_from_freelist(temp);

        size += GET_SIZE(HDRP(NEXT_BLKP(bp))) + DSIZE;
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        return (bp);
    }

    else if (!prev_alloc && next_alloc) { /* Case 3 */
        remove_from_freelist(bp);
    
        size += GET_SIZE(FTRP(PREV_BLKP(bp))) + DSIZE;
        PUT(FTRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        return (PREV_BLKP(bp));
    }

    else {            /* Case 4 */
        free_block* temp = (free_block *)NEXT_BLKP(bp);
        remove_from_freelist(temp);
        remove_from_freelist(bp);

        size += GET_SIZE(FTRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp))) + DSIZE*2 ;
        PUT(HDRP(PREV_BLKP(bp)), PACK(size,0));
        PUT(FTRP(PREV_BLKP(bp)), PACK(size,0));
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
    printf("Extending the heap and my knowledge...\n");
    char *bp;
    size_t size = words;

    /* Allocate an even number of words to maintain alignments */
    if ( (bp = mem_sbrk(size + DSIZE)) == (void *)-1 )
        return NULL;
    printf("annie's (heap) brain can be extended!\n");
    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));                // free block header
    PUT(FTRP(bp), PACK(size, 0));                // free block footer
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));        // new epilogue header

    /* Coalesce if the previous block was free */
    return bp;
    //coalesce(bp);
}


/**********************************************************
 * find_fit
 * Traverse the heap searching for a block to fit asize
 * Return NULL if no free blocks can handle that size
 * Assumed that asize is aligned
 **********************************************************/
void * find_fit(size_t asize){   
    // void *bp;
    printf("fitting into jeans... \n");
    int free_list = find_free_list(asize);
    int size = asize;
    for (int i = free_list; i < FREE_LIST_NUMBER; i++){
        printf("checking jean size %d",i);
        if (free_lists[i] != NULL){
            free_block* temp = free_lists[i];

            while (temp !=NULL){
                int tsize = GET_SIZE(HDRP(temp));
                if (tsize >= size && tsize < (size + DSIZE)){
                    remove_from_freelist(temp);
                    
                    return (void*)temp;
                }
                else if (tsize >= (size + DSIZE)){
                    printf("cropping jeans: can split block!\n");
                    remove_from_freelist(temp);
                    int extra_size = tsize - size;
                    void* use_ptr = (void*)temp + extra_size;

                    // Adjust size of the pointed being used
                    PUT(HDRP(use_ptr), PACK(size,1));
                    PUT(FTRP(use_ptr), PACK(size,1));
                    // Adjust size of new split free block
                    PUT(HDRP(temp), PACK(extra_size,0));
                    PUT(HDRP(temp), PACK(extra_size,0));

                    add_to_freelist(temp);
                    return use_ptr;
                }
                temp = temp->next;      
            }
        }
    }
    printf("annie's jeans don't fit\n");
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
    size_t size = GET_SIZE(HDRP(temp));
    int free_list = find_free_list(size);
    printf("adding to free list...\n");
    if (free_lists[free_list] == NULL){
        temp->prev = NULL;
        temp->next = NULL;
        free_lists[free_list] = temp;
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
    printf("remove from freelist...\n");
    if (block == NULL){
        return;
    }
    size_t size = GET_SIZE(HDRP(block));
    int freelist = find_free_list(size);
    printf("ok starting shitting prints\n");
    if (block-> prev == NULL && block->next == NULL){ // empty list
        free_lists[freelist] = NULL;
        printf("empty list\n");
        return;
    }
    else if (block->prev==NULL){        // if b is first elem of list
        free_lists[freelist] = block->next;
        free_lists[freelist]->prev = NULL; 
        printf("curr is first element\n");
        return;
    }
    else if (block->next == NULL){      // if b is last elem of list
        block->prev->next = NULL;
        printf("curr is last element\n");
        return;
    }
    else{                               // b is in the middle
        block->prev->next = block->next;
        block->next->prev = block->prev;
        printf("curr is in the middle\n");
        return;
    }
}
/**********************************************************
 * place
 * Mark the block as allocated
 **********************************************************/
void place(void* bp, size_t asize)
{
  /* Get the current block size */
  size_t bsize = GET_SIZE(HDRP(bp));
  
  PUT(HDRP(bp), PACK(bsize, 1));
  PUT(FTRP(bp), PACK(bsize, 1));
}

/**********************************************************
 * mm_free
 * Free the block and coalesce with neighbouring blocks
 **********************************************************/
void mm_free(void *bp)
{
    printf("I am free!\n");
    printf("I am a joke\n");
    if(bp == NULL){
        printf("i am null\n");
        return NULL;
    }


    if(GET_ALLOC(HDRP(bp))==0){
        printf("get alloc = 0\n");
        return NULL;
    }

    printf("getting size\n");
    size_t size = GET_SIZE(HDRP(bp));
    printf("size gotten\n");

    printf("PUT function %d \n", size);
    PUT(HDRP(bp), PACK(size,0));
    PUT(FTRP(bp), PACK(size,0));
    printf("i am no longer free ): \n");

    add_to_freelist(bp);
    //add_to_freelist((free_block*)coalesce(bp));
    // coalesce(bp);
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
     printf("enter mm_malloc with size %d \n", size);
    // size_t asize; /* adjusted block size */
    char * bp;
    /* Ignore spurious requests */
    if (size == 0)
        return NULL;

    if (size < DSIZE ){
        size = DSIZE;
    }

    else if (size <= 2048){
        size --;
        size |= size >> 1;
        size |= size >> 2;
        size |= size >> 4;
        size |= size >> 8;
        size |= size >> 16;
        size++;
    }
    printf("try to fit size %d \n", size);
    if ((bp = find_fit(size)) != NULL){
        place(bp, size);
        return bp;
    }
    printf("i dont fit in :(\n");
    int extendsize = ((size-1)/ DSIZE)*DSIZE + DSIZE;  // round to nearest 16 byte
    // EXTEND HEAP AND ALLOCATE BLOCK 
    if ((bp = extend_heap(extendsize))== NULL){
        return NULL;
    }
    printf("placed here\n");
    place(bp, extendsize);
    //printf("%d\n",bp);
    return bp;
}


/**********************************************************
 * mm_realloc
 * Implemented simply in terms of mm_malloc and mm_free
 *********************************************************/
void *mm_realloc(void *ptr, size_t size)
{
    printf("doing realloc... \n");
    /* If size == 0 then this is just free, and we return NULL. */
    if(size == 0){
      mm_free(ptr);
      return NULL;
    }

    /* If oldptr is NULL, then this is just malloc. */
    if (ptr == NULL)
      return (mm_malloc(size));


    void *oldptr = ptr;
    void *newptr;
    size_t old_size = GET_SIZE(HDRP(oldptr));
    if (size<DSIZE){
        size = DSIZE;
    }
    else if (size<2048){
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
        printf("wants less of annie\n");
        size_t extra = old_size-size;
        if (extra >= DSIZE){
            newptr = (void *) (oldptr + size + DSIZE);
            PUT(HDRP(newptr), PACK(extra,0));
            PUT(FTRP(newptr), PACK(extra,0));
            add_to_freelist((free_block*)newptr);

            PUT(HDRP(oldptr), PACK(size,1));
            PUT(FTRP(oldptr), PACK(size,1));
        }
        return oldptr;
    }
    
    else{       // wants more space
        printf("wants more of annie\n");
        PUT(HDRP(ptr),PACK(old_size, 0));
        PUT(FTRP(ptr),PACK(old_size, 0));
        // ptr = coalesce(ptr);
        size_t coalesced_size = GET_SIZE(HDRP(ptr));
        if(coalesced_size >= size){
            
            memmove(ptr, oldptr, old_size);
            PUT(HDRP(ptr),PACK(coalesced_size, 1));
            PUT(FTRP(ptr),PACK(coalesced_size, 1));
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
