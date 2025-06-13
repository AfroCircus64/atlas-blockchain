#include "blockchain.h"

/**
 * block_create - Creates a new block
 *
 * @prev: Pointer to the previous block
 * @data: Pointer to the data stored in the block
 * @data_len: Length of the data
 *
 * Return: Pointer to the new block, or NULL on failure
 */
block_t *block_create(block_t const *prev,
	 int8_t const *data, uint32_t data_len)
{
	block_t *block;
	uint32_t copy_len;

	block = calloc(1, sizeof(*block));
	if (!block)
		return (NULL);

	if (prev)
	{
		block->info.index = prev->info.index + 1;
		memcpy(block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
	}
	else
	{
		block->info.index = 0;
		memset(block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
	}
	block->info.difficulty = 0;
	block->info.nonce = 0;
	block->info.timestamp = (uint64_t)time(NULL);

	copy_len = data_len > BLOCKCHAIN_DATA_MAX ? BLOCKCHAIN_DATA_MAX : data_len;
	if (data && copy_len)
		memcpy(block->data.buffer, data, copy_len);
	block->data.len = copy_len;

	memset(block->hash, 0, SHA256_DIGEST_LENGTH);

	return (block);
}
