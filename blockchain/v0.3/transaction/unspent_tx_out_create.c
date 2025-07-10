#include "transaction.h"

/**
 * unspent_tx_out_create - Creates an unspent transaction output
 *
 * @block_hash: Hash of the Block containing the transaction
 * @tx_id: ID of the transaction containing the output
 * @out: Pointer to the transaction output
 *
 * Return: Pointer to unspent transaction output, or NULL on failure
 */
unspent_tx_out_t *unspent_tx_out_create(
	uint8_t block_hash[SHA256_DIGEST_LENGTH],
	uint8_t tx_id[SHA256_DIGEST_LENGTH],
	tx_out_t const *out)
{
	unspent_tx_out_t *unspent = malloc(sizeof(unspent_tx_out_t));

	if (!unspent)
	{
		return (NULL);
	}

	memcpy(unspent->block_hash, block_hash, SHA256_DIGEST_LENGTH);
	memcpy(unspent->tx_id, tx_id, SHA256_DIGEST_LENGTH);

	if (out)
	{
		unspent->out = *out;
	}

	return (unspent);
}
