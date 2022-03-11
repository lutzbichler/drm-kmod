/* Public domain */

#include <sys/param.h>

#include <linux/dma-fence-array.h>
#include <linux/dma-fence-chain.h>
#include <linux/dma-fence-unwrap.h>

static inline struct dma_fence *
__dma_fence_unwrap(struct dma_fence_unwrap *unwrap)
{
    unwrap->array = dma_fence_chain_contained(unwrap->chain);
    unwrap->index = 0;
    return (dma_fence_array_first(unwrap->array));
}

struct dma_fence *
dma_fence_unwrap_first(struct dma_fence *fence,
    struct dma_fence_unwrap *unwrap)
{
    unwrap->chain = dma_fence_get(fence);
    return (dma_fence_array_first(unwrap->array));
}

struct dma_fence *
dma_fence_unwrap_next(struct dma_fence_unwrap *unwrap)
{
    struct dma_fence *tmp_fence;

    unwrap->index++;
    tmp_fence = dma_fence_array_next(unwrap->array, unwrap->index);
    if (!tmp_fence) {
        unwrap->chain = dma_fence_chain_walk(unwrap->chain);
        tmp_fence = __dma_fence_unwrap(unwrap);
    }

    return (tmp_fence);
}
