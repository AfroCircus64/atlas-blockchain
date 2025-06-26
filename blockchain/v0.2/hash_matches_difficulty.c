#include "blockchain.h"

/**
 * hash_matches_difficulty - Checks if the hash matches the given difficulty.
 *
 * @hash: The hash to check.
 * @difficulty: The minimum difficulty the hash should match.
 *
 * Return: 1 if the difficulty is respected, or 0 otherwise.
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
	 uint32_t difficulty)
{
	uint32_t i, byte, bit;

	if (!hash)
	{
		return (0);
	}

	for (i = 0; i < difficulty / 8; i++)
	{
		if (hash[i] != 0)
			return (0);
	}

	byte = difficulty / 8;
	bit = difficulty % 8;

	if (bit)
	{
		uint8_t mask = 0xFF << (8 - bit);

		if ((hash[byte] & mask) != 0)
		{
			return (0);
		}
	}

	return (1);
}
