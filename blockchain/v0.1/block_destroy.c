#include "blockchain.h"

/**
 * block_destroy - Destroys a block and frees its memory
 *
 * @block: Pointer to the block to be destroyed
 */
void block_destroy(block_t *block)
{
	if (block)
	{
		free(block);
	}
}
