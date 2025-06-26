#include "blockchain.h"

/**
 * block_is_valid - Checks if a block is valid
 *
 * @block: Pointer to the block to check
 * @prev_block: Pointer to the previous block
 *
 * Return: 1 if the block is valid, 0 otherwise
 */
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	static const block_t genesis = {
		.info = {
			.index = 0,
			.difficulty = 0,
			.timestamp = 1537578000,
			.nonce = 0,
			.prev_hash = {0}
		},
		.data = {
			.buffer = "Holberton School",
			.len = 16
		},
		.hash = "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4"
				"\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51"
				"\x58\x03"
	};
	uint8_t hash_buf[SHA256_DIGEST_LENGTH];

	if (!block)
		return (1);

	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);

	if (block->info.index == 0)
	{
		if (prev_block != NULL)
			return (1);
		if (memcmp(block, &genesis, sizeof(block_t)) != 0)
			return (1);
		return (0);
	}

	if (!prev_block)
		return (1);

	if (block->info.index != prev_block->info.index + 1)
		return (1);

	block_hash(prev_block, hash_buf);
	if (memcmp(prev_block->hash, hash_buf, SHA256_DIGEST_LENGTH) != 0)
		return (1);

	if (memcmp(block->info.prev_hash, prev_block->hash, SHA256_DIGEST_LENGTH) != 0)
		return (1);

	block_hash(block, hash_buf);
	if (memcmp(block->hash, hash_buf, SHA256_DIGEST_LENGTH) != 0)
		return (1);

	return (0);
}
