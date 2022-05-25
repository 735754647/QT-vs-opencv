/*****************************************************************************
 * HAlloc.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Memory allocation
 *
 * (c) 1996-2014 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *
 */

#ifndef HALLOC_H
#define HALLOC_H


#if defined(__cplusplus)
extern "C" {
#endif


/*===========================================================================*/
/*                          Defines                                          */
/*===========================================================================*/
#define H_LOCAL_ALLOC  -111                    /* AllocLevel for local. mem. */
#define H_GLOBAL_ALLOC -112                    /* use global AllocLevel      */
#define H_TMP_ALLOC    -113                    /* use tmp alloc              */

/*===========================================================================*/
/*                          Prototypes of Functions                          */
/*===========================================================================*/
/*---------------------------------------------------------------------------*/
/*                          Test Memory Allocation                           */
/*---------------------------------------------------------------------------*/
enum {HMEMtemp=0, HMEMlocal, HMEMglobal};

/* HXTestPtrRange - tests memory (address) allocated with HAlloc/HAllocLocal */
extern HLibExport Herror HXTestPtrRange(void *ptr, const char *file,
                                        INT4_8 line,HBOOL do_print);

/* HXTestPtr - tests memory (address+size) allocated with HAlloc/HAllocLocal */
extern HLibExport Herror HXTestPtr(void *ptr, const char *file, INT4_8 line);

/* HTestMem - tests all the memory currently allocated by HAlloc/HAllocLocal */
extern HLibExport Herror HTestMem (void);



/*---------------------------------------------------------------------------*/
/*                 Auxiliary Functions for Memory Management                 */
/*---------------------------------------------------------------------------*/
extern HLibExport HBOOL  HTraceMemory; /* switch if memory statistics
                             * should be collected (do not set this directly)*/

/* set HMemoryTrace Flag to TRUE (efficient) / FALSE (debug information
 * available)
 * NOTE: this function is not thread save and has to be used exclusively     */
extern HLibExport Herror HSetTraceMemory(Hproc_handle proc_handle,
                                         HBOOL trace_memory);
extern HLibExport HBOOL HGetTraceMemory(void);

/* HTmpStackSize - return stack size for temporary memory blocks             */
extern HLibExport Herror HTmpStackSize(Hproc_handle proc_handle, INT4_8 *size);

/* HSetAllocLevel - set 'level' of memory allocation                         */
extern HLibExport Herror HSetAllocLevel(INT4_8 level);

/* HGetAllocLevel - read 'level' of memory allocation                        */
extern HLibExport Herror HGetAllocLevel(INT4_8 *level);

/* HGetImageCacheSize - current size in bytes of all cached images           */
extern HLibExport Herror HGetImageCacheSize(Hproc_handle proc_handle,
                                            INT4_8 *size);

/* HGetImageCacheCapacity - maximum size in bytes of all cached images       */
extern HLibExport Herror HGetImageCacheCapacity(Hproc_handle proc_handle,
                                                INT4_8 *size);

/* HGetImageCacheCapacity - set maximum size in bytes of all cached images
 *                      0 switches off image caching                         */
extern HLibExport Herror HSetImageCacheCapacity(Hproc_handle proc_handle,
                                                INT4_8 size);

/* HClearImageCache - free all cached memory blocks                          */
extern HLibExport Herror HClearImageCache(Hproc_handle proc_handle);

/* HMallocInfo - return the number of calls of clib malloc                   */
extern HLibExport Herror HMallocInfo(INT4_8 *mcalls);

/* HMemInfo - retrieve informationen zaboutc current memory allocation       */
extern HLibExport Herror HMemInfo(Hproc_handle proc_handle,
                                  INT4_8 *alloc_mem, INT4_8 *free_mem,
                                  INT4_8 *used_mem, INT4_8 *alloc_call,
                                  INT4_8 *free_call, double *hit_rate,
                                  double *small_rate, size_t *cache,
                                  size_t *stack);

/* HNumMemElements - get number of currently allocated memory blocks         */
extern HLibExport Herror HNumMemElements(INT4_8  *num);

/* HAllocInfo - get line of call/size of all blocks with level >= AllocLevel */
extern HLibExport Herror HAllocInfo(INT max, char *file[], INT4 line[],
                                    INT4_8 size[], INT4 level[], INT4_8 *num);
extern HLibExport int HfprintfAllocInfo( FILE *stream);

/* HPrepMem - prepares memory (allocates+frees memory) => more efficiency    */
extern HLibExport Herror HPrepMem (Hproc_handle proc_handle, size_t size,
                                   size_t *si_ze);

/* HFreeUnusedTmpMem - free any unused temporary memory                      */
extern HLibExport Herror HFreeUnusedTmpMem(Hproc_handle proc_handle);

/*---------------------------------------------------------------------------*/
/*                   Management of Free Usable Memory                        */
/*---------------------------------------------------------------------------*/
/* HXAlloc - allocate free usable memory                                     */
extern HLibExport Herror HXAlloc (Hproc_handle proc_handle, size_t size,
                                  VOIDP void_p);

/* HXAllocAlign - allocate free usable memory with given ptr alignment */
extern HLibExport Herror HXAllocAlign (Hproc_handle proc_handle, size_t size,
                                       size_t alignement, VOIDP void_p);


/* HXAllocMemCheck - allocate free usable memory and collect test info       */
extern HLibExport Herror HXAllocMemCheck (Hproc_handle proc_handle,
                                          size_t size, const char *file,
                                          INT4_8 line, INT4 level,
                                          VOIDP void_p);

/* HXAllocAlignMemCheck - allocate free usable memory with given ptr alignment
                          and collect test info       */
extern HLibExport Herror HXAllocAlignMemCheck (Hproc_handle proc_handle,
                                               size_t size, size_t alignment,
                                               const char *file, INT4_8 line,
                                               INT4 level, VOIDP void_p);

/* HXFree - give free (free usable) memory (insert it into cache) */
extern HLibExport Herror HXFree(Hproc_handle proc_handle, VOIDP mem);

/* HXFree - give free (free usable) memory (insert it into cache) and test it*/
extern HLibExport Herror HXFreeMemCheck(Hproc_handle proc_handle, VOIDP mem,
                                        const char *file, INT4_8 line);

/* HXRealloc - reallocate memory and test it (memory still available?)       */
extern HLibExport Herror HXRealloc(Hproc_handle proc_handle, VOIDP ptr,
                                   size_t size, VOIDP void_p,
                                   const char *file, INT4_8 line);
/* HXReallocToGlobal - reallocate global/local memory and convert to global
 *  memory   */
extern HLibExport Herror HXReallocToGlobal(Hproc_handle proc_handle, VOIDP ptr,
                                           size_t size, VOIDP void_p,
                                           const char *file, INT4_8 line);

/* HXAllocRLNum - allocate permanent memory for specific region
 * (pass Hrlregion** to region parameter)                                    */
extern HLibExport Herror HXAllocRLNum(Hproc_handle proc_handle,
                                      VOIDP region, size_t num,
                                      const char *file, INT4_8 line);

/* HXReallocRLNum - reallocate global memory for specific region
 * (pass Hrlregion** to reg_new parameter but Hrlregion * to reg_old)        */
extern HLibExport Herror HXReallocRLNum(Hproc_handle proc_handle,
                                        VOIDP reg_old,size_t num_new,
                                        VOIDP reg_new,
                                        const char *file, INT4_8 line);

/* HXReallocRLNumToGlobal - reallocate local or global memory for specific
 * region and convert it to global memory (pass Hrlregion** to reg_new
 * parameter but Hrlregion * to reg_old) */
extern HLibExport Herror HXReallocRLNumToGlobal(Hproc_handle proc_handle,
                                                VOIDP reg_old,size_t num_new,
                                                VOIDP reg_new,
                                                const char *file, INT4_8 line);

/* HXAllocRL - allocate permanent memory for new regions
 * (pass Hrlregion** to region parameter)                                    */
extern HLibExport Herror HXAllocRL(Hproc_handle proc_handle,
                                   VOIDP region,
                                   const char *file, INT4_8 line);

/* HXFreeRL - give free (permanent) memory of a specific region              */
extern HLibExport Herror HXFreeRL(Hproc_handle proc_handle,VOIDP region,
                                  const char *file, INT4_8 line);


/* HXAllocGeneral - allocate memory according to allocation bit     */
extern HLibExport Herror HXAllocGeneral(Hproc_handle ph, MACHINE_WORD allocbit,
                                        size_t size, void *mem,
                                        const char *file, INT4_8 line);
#define HAllocGeneral(ph,allocbit,size,mem)               \
  HXAllocGeneral(ph,allocbit,size,(void*)mem,__FILE__,__LINE__)



/* HXFreeGeneral - give free (free usable) memory (insert it into cache)     */
extern HLibExport Herror HXFreeGeneral(Hproc_handle proc_handle, VOIDP mem);
extern HLibExport Herror HXFreeGeneralMemCheck(Hproc_handle proc_handle,
                                               VOIDP mem, char const*file,
                                               INT4_8 line);

/* HXReallocGeneral - reallocate global/local memory and test it             */
extern HLibExport Herror HXReallocGeneral(Hproc_handle proc_handle, VOIDP ptr,
                                          size_t size, VOIDP void_p,
                                          const char *file, INT4_8 line);

/* HXReallocRLNumGeneral - reallocate global/local memory for specific region
 * (pass Hrlregion** to reg_new parameter but Hrlregion * to reg_old)        */
extern HLibExport Herror HXReallocRLNumGeneral(Hproc_handle proc_handle,
                                        VOIDP reg_old,size_t num_new,
                                        VOIDP reg_new,
                                        const char *file, INT4_8 line);

/* HXFreeRLGeneral - give free global/local/temp  memory of a  region        */
extern HLibExport Herror HXFreeRLGeneral(Hproc_handle proc_handle,
                                         VOIDP region,
                                         const char *file, INT4_8 line);


/* HAllocImageCached - fetch image memory from cache                         */
extern HLibExport void* HAllocImageCached(size_t size);

/* HFreeImageCached - cache image memory                                     */
extern HLibExport void HFreeImageCached(VOIDP image);



/*---------------------------------------------------------------------------*/
/*                   Management of Local Free Memory                         */
/*---------------------------------------------------------------------------*/
/* HXAllocLocal - allocate local memory (AllocLevel=H_LOCAL_ALLOC)           */
extern HLibExport Herror HXAllocLocal (Hproc_handle proc_handle, size_t size,
                                       const char *file,
                                       INT4_8 line, VOIDP void_p);

/* HXAllocLocalAlign - allocate local memory with given ptr alignment
                       (AllocLevel=H_LOCAL_ALLOC)           */
extern HLibExport Herror HXAllocLocalAlign (Hproc_handle proc_handle,
                                            size_t size, size_t alignment,
                                            const char *file,
                                            INT4_8 line, VOIDP void_p);

/* HXFreeLocal - give free local memory (insert it in cache) and test it     */
extern HLibExport Herror HXFreeLocal(Hproc_handle proc_handle,
                                     VOIDP mem, const char *file,
                                     INT4_8 line);

/* HXReallocLocal - reallocate local memory (AllocLevel=H_LOCAL_ALLOC)       */
extern HLibExport Herror HXReallocLocal(Hproc_handle proc_handle, VOIDP ptr,
                                        size_t size, VOIDP void_p,
                                        const char *file, INT4_8 line);

/* HConvertLocalToGlobal - converts a local memory block to a global one     */
extern HLibExport Herror HConvertLocalToGlobal(Hproc_handle proc_handle,
                                               VOIDP ptr);


/* HXAllocRLNumLocal - allocate local memory for specific region
 * (pass Hrlregion** to region parameter)                                    */
extern HLibExport Herror HXAllocRLNumLocal(Hproc_handle proc_handle,
                                           VOIDP region, size_t num,
                                           const char *file, INT4_8 line);

/* HXReallocRLNumLocal - reallocate local memory for specific region
 * (pass Hrlregion** to reg_new parameter but Hrlregion * to reg_old)        */
extern HLibExport Herror HXReallocRLNumLocal(Hproc_handle proc_handle,
                                             VOIDP reg_old,size_t num_new,
                                             VOIDP reg_new,
                                             const char *file, INT4_8 line);

/* HXAllocRLLocal -  allocate local memory for new regions
 * (pass Hrlregion** to region parameter)                                    */
extern HLibExport Herror HXAllocRLLocal(Hproc_handle proc_handle,
                                        VOIDP region,
                                        const char *file, INT4_8 line);

/* HXFreeRLLocal - give free (local) memory of a specific region             */
extern HLibExport Herror HXFreeRLLocal(Hproc_handle proc_handle,
                                       VOIDP region,
                                       const char *file, INT4_8 line);

/* HMemClrLocal - give free the whole local memory (alloc. by HXAllocLocal)  */
extern HLibExport Herror HMemClrLocal(Hproc_handle proc_handle);

/* HMemMoveLocal - transfers all local memory from a proc_handle to an other */
extern HLibExport void HMemMoveLocal(Hproc_handle dest, Hproc_handle src);


/* HFreeMemTTable - give free all temporary stack memory (of an instance)    */
extern HLibExport Herror HFreeMemTTable(Hproc_handle proc_handle);

/* HXFreeAllTmp - give free all the allocated temporary memory               */
extern HLibExport Herror HXFreeAllTmp(Hproc_handle proc_handle,
                                      const char *file, INT4_8 line);

/* HMemClrTTable - free (logically) all the allocated stack memory(MemTTable)*/
extern HLibExport Herror HMemClrTTable(Hproc_handle proc_handle);

/* HXAllocTmp - allocate temporary memory within a stack                     */
extern HLibExport Herror HXAllocTmp(Hproc_handle proc_handle, VOIDP ptr,
                                    size_t size, const char *file,
                                    INT4_8 line);

/* HXAllocDomainImageTmp - allocate memory for temporary images regarding
 * input image width and domain height */
extern HLibExport Herror HXAllocDomainImageTmp(Hproc_handle proc_handle,
                                               VOIDP mem_ptr, VOIDP img_ptr,
                                               Hrlregion *region,
                                               HIMGDIM width, HIMGDIM height,
                                               INT byte_per_pixel,
                                               HIMGDIM border_rows,
                                               HIMGCNT border_bytes,
                                               const char *file, INT4_8 line);

/* HXAllocRLNumTmp - allocate temporary memory for specific region
 * (pass Hrlregion** to region parameter)                                    */
extern HLibExport Herror HXAllocRLNumTmp(Hproc_handle proc_handle,
                                         VOIDP region, size_t num,
                                         const char *file, INT4_8 line);

/* HXAllocRLTmp - allocate temporary memory for new regions
 * (pass Hrlregion** to region parameter)                                    */
extern HLibExport Herror HXAllocRLTmp(Hproc_handle proc_handle,
                                      VOIDP region,
                                      const char *file, INT4_8 line);

/* HXTestAllTmp - test all stacks for temporary memory of consistency        */
extern HLibExport Herror HXTestAllTmp(Hproc_handle proc_handle,
                                      const char *file, INT4_8 line);

/* HXTestTmp - test the specified temporary memory block of consistency      */
extern HLibExport Herror HXTestTmp( VOIDP ptr, const char *file, INT4_8 line,
                                    HBOOL do_printf);

/* HXFreeTmp - gives free the lastly allocated (!) stack memory              */
extern HLibExport Herror HXFreeTmp(Hproc_handle proc_handle, VOIDP ptr,
                                   const char *file, INT4_8 line);

/* HXFreeRLTmp - gives free temporary memory of a specific region            */
extern HLibExport Herror HXFreeRLTmp(Hproc_handle proc_handle,
                                     VOIDP region,
                                     const char *file, INT4_8 line);

/* HXFreeNTmp - gives free the 'num' lastly allocated stack memory blocks    */
extern HLibExport Herror HXFreeNTmp(Hproc_handle proc_handle, INT num,
                                    const char *file, INT4_8 line);

/* HXFreeUpToTmp - give free stack memory up to a specified memory block,
 *                 including the specified memory block.                     */
extern HLibExport Herror HXFreeUpToTmp(Hproc_handle proc_handle, void *ptr,
                                       const char *file, INT4_8 line);

/* HXFreeUpToTmpExcl - give free stack memory up to a specified memory block,
 *                     excluding the specified memory block.                 */
extern HLibExport Herror HXFreeUpToTmpExcl(Hproc_handle proc_handle,
                                           void *ptr,
                                           const char *file, INT4_8 line);

/* HXGetLastTmp - get the last allocated memory block on the stack memory    */
extern HLibExport Herror HGetLastTmp(Hproc_handle proc_handle, void **last);

/* HFreeUnusedStacks - gives free (physically) all currently unused stacks   */
extern HLibExport Herror HFreeUnusedStacks(Hproc_handle proc_handle);

/* HShrinkRL - gives free the unused memory of a specific region
 * (pass Hrlregion** to region parameter)                                    */
extern HLibExport Herror HShrinkRL(Hproc_handle proc_handle,
                                   VOIDP region);



/* HlibAlloc
 * HlibFree
 *  workarround for windows: under windows every DLL has its own memory heap
 *  -> the free method must be called in the same DLL as the malloc
 *---------------------------------------------------------------------------*/
#ifdef _WIN32
extern HLibExport void* Hlib_malloc(size_t size);
extern HLibExport void  Hlib_free(void* mem);
#else
#define Hlib_malloc malloc
#define Hlib_free   free
#endif

#if defined(__cplusplus)
}
#endif


#endif
