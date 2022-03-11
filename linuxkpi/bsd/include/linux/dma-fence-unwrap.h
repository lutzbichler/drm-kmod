/* Public domain */
#ifndef LINUXKPI_DMA_FENCE_UNWRAP_H_
#define LINUXKPI_DMA_FENCE_UNWRAP_H_

#define dma_fence_unwrap_for_each(fence, iter, head)			\
	for (fence = dma_fence_unwrap_first(head, iter); fence;	\
	     fence = dma_fence_unwrap_next(iter))

struct dma_fence;

struct dma_fence_unwrap {
    struct dma_fence *chain;
    struct dma_fence *array;
    unsigned int index;
};

struct dma_fence *dma_fence_unwrap_first(struct dma_fence *fence,
    struct dma_fence_unwrap *unwrap);
struct dma_fence *dma_fence_unwrap_next(struct dma_fence_unwrap *unwrap);

#endif /* LINUXKPI_DMA_FENCE_UNWRAP_H_ */

