/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Jungle",
    /* First member's email address */
    "544859995@qq.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};


/* Basic constants and macros */
#define WSIZE       4
#define DSIZE       8
#define CHUNKSIZE   (1<<12)

#define MAX(x, y) ((x) > (y)? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc)  ((size) | (alloc))

/* Read and write a word at address p */
#define GET(p)       (*(unsigned int *)(p))
#define PUT(p, val)  (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

/* Given block ptr bp, compute address of its header and footer */
#define HDRP(bp)       ((char *)(bp) - WSIZE)
#define FTRP(bp)       ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

/* Given block ptr bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)  ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)  ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

#define PRED(bp) ((char*)(bp) + WSIZE)
#define SUCC(bp) ((char*)bp)

#define PRED_BLKP(bp) (GET(PRED(bp)))
#define SUCC_BLKP(bp) (GET(SUCC(bp)))

static char *heap_listp;
static char *listp;

static int Index(size_t size){
    int ind = 0;
    if(size >= 4096)
        return 8;

    size = size>>5;
    while(size){
        size = size>>1;
        ind++;
    }
    return ind;
}

static void *LIFO(void *bp, void *root){
    if(SUCC_BLKP(root)!=NULL){
        PUT(PRED(SUCC_BLKP(root)), bp);	//SUCC->BP
        PUT(SUCC(bp), SUCC_BLKP(root));	//BP->SUCC
    }else{
        PUT(SUCC(bp), NULL);
    }
    PUT(SUCC(root), bp);    //ROOT->BP
    PUT(PRED(bp), root);    //BP->ROOT
    return bp;
}

static void delete_block(void *bp){
    PUT(SUCC(PRED_BLKP(bp)), SUCC_BLKP(bp));
    if(SUCC_BLKP(bp)!=NULL)
        PUT(PRED(SUCC_BLKP(bp)), PRED_BLKP(bp));
}

static void *add_block(void *bp){
    size_t size = GET_SIZE(HDRP(bp));
    int index = Index(size);
    void *root = listp+index*WSIZE;
	
    //LIFO
    return LIFO(bp, root);
    //AddressOrder
    //return AddressOrder(bp, root);
}

static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {
        return bp;
    }
    
    else if (prev_alloc && !next_alloc) {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        delete_block(NEXT_BLKP(bp));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }

    else if (!prev_alloc && next_alloc) {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        delete_block(PREV_BLKP(bp));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    else {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
            GET_SIZE(FTRP(NEXT_BLKP(bp)));
        delete_block(NEXT_BLKP(bp));
        delete_block(PREV_BLKP(bp));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    return bp;
}

static void *extend_heap(size_t words)
{
    char *bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words+1) * WSIZE : words * WSIZE;
    if ((long)(bp = mem_sbrk(size)) == -1)
        return NULL;

    /* Initialize free block header/footer and the epilogue header */
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

    PUT(PRED(bp), NULL);
    PUT(SUCC(bp), NULL);

    /* Coalesce if the previous block was free */
    bp = coalesce(bp);
    bp = add_block(bp);
    return bp;
}

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    /* Create the initial empty heap */
    if ((heap_listp = mem_sbrk(12*WSIZE)) == (void *)-1)
        return -1;
    PUT(heap_listp +  0*WSIZE, NULL);	//{16~31}
    PUT(heap_listp +  1*WSIZE, NULL);	//{32~63}
    PUT(heap_listp +  2*WSIZE, NULL);	//{64~127}
    PUT(heap_listp +  3*WSIZE, NULL);	//{128~255}
    PUT(heap_listp +  4*WSIZE, NULL);	//{256~511}
    PUT(heap_listp +  5*WSIZE, NULL);	//{512~1023}
    PUT(heap_listp +  6*WSIZE, NULL);	//{1024~2047}
    PUT(heap_listp +  7*WSIZE, NULL);	//{2048~4095}
    PUT(heap_listp +  8*WSIZE, NULL);	//{4096~inf}
    PUT(heap_listp +  9*WSIZE, PACK(DSIZE, 1));
    PUT(heap_listp + 10*WSIZE, PACK(DSIZE, 1));
    PUT(heap_listp + 11*WSIZE, PACK(0, 1));
    listp = heap_listp;
    heap_listp += (10*WSIZE);

    /* Extend the empty heap with a free block of CHUNSIZE bytes */
    if (extend_heap(CHUNKSIZE/WSIZE) == NULL)
        return -1;
    return 0;
}

static void *find_fit(size_t asize)
{
    /* First-fit search */
    /*int ind = Index(asize);
    void *succ;
    while(ind <= 8){
        succ = listp+ind*WSIZE;
        while((succ = SUCC_BLKP(succ)) != NULL){
            if(GET_SIZE(HDRP(succ)) >= asize && !GET_ALLOC(HDRP(succ))){
                return succ;
            }
        }
        ind+=1;
    }
    return NULL;*/
    /* Best-fit search */
    int ind = Index(asize);
    void *best = NULL;
    int min_size = 0, size;
    void *succ;
    while(ind <= 8){
        succ = listp+ind*WSIZE;
        while((succ = SUCC_BLKP(succ)) != NULL){
            size = GET_SIZE(HDRP(succ));
            if(size >= asize && !GET_ALLOC(HDRP(succ)) && (size<min_size||min_size==0)){
                best = succ;
                min_size = size;
            }
        }
        if(best != NULL)
            return best;
        ind+=1;
    }
    return NULL;
}

static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));
    delete_block(bp);
    if ((csize - asize) >= (2*DSIZE)) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0));
        PUT(FTRP(bp), PACK(csize-asize, 0));
        add_block(bp);
    }
    else {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    size_t asize;
    size_t extendsize;
    char *bp;

    if (size == 0)
        return NULL;

    if (size <= DSIZE)
        asize = 2*DSIZE;
    else
        asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);

    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
        return NULL;
    place(bp, asize);
    return bp;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    size_t size = GET_SIZE(HDRP(ptr));

    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    ptr = coalesce(ptr);
    add_block(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    size_t asize, ptr_size, old_size;
    void *new_ptr, *a_ptr;

    if (ptr == NULL)
        return mm_malloc(size);
    if (size == 0) {
        mm_free(ptr);
        return NULL;
    }

    old_size = GET_SIZE(HDRP(ptr));
    asize = size<=DSIZE ? 2*DSIZE : DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);
    new_ptr = coalesce(ptr);
    ptr_size = GET_SIZE(HDRP(new_ptr));

    if(ptr_size < asize){
        a_ptr = mm_malloc(size);
        if(a_ptr == NULL)
            return NULL;
        memcpy(a_ptr, ptr, old_size - DSIZE);
        mm_free(new_ptr);
        return a_ptr;
    }

    PUT(HDRP(new_ptr), PACK(ptr_size, 1));
    PUT(FTRP(new_ptr), PACK(ptr_size, 1));
    if(new_ptr != ptr)
        memmove(new_ptr, ptr, GET_SIZE(HDRP(ptr)) - DSIZE);	
    if(ptr_size == asize)
        return new_ptr;
    if(ptr_size > asize) {
        if(ptr_size - asize >= DSIZE*2){
            PUT(HDRP(new_ptr), PACK(asize, 1));
            PUT(FTRP(new_ptr), PACK(asize, 1));
            PUT(HDRP(NEXT_BLKP(new_ptr)), PACK(ptr_size - asize, 0));
            PUT(FTRP(NEXT_BLKP(new_ptr)), PACK(ptr_size - asize, 0));
            add_block(NEXT_BLKP(new_ptr));
        }
        return new_ptr;
    }
}
