#include "blockchain.h"

/**
 * block_hash - Computes the hash of a block
 *
 * @block: Pointer to the block to hash
 * @hash_buf: Buffer to store the resulting hash
 *
 * Return: Pointer to the hash buffer or NULL on failure
 */
uint8_t *block_hash(block_t const *block,
	 uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	if (!block || !hash_buf)
		return (NULL);

	SHA256((unsigned char *)block,
	 sizeof(block->info) + sizeof(block->data), hash_buf);

	return (hash_buf);
}
