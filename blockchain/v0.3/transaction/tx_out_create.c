#include "transaction.h"

/**
 * tx_out_create - Creates a transaction output
 *
 * @amount: Amount to be received
 * @pub:    Receiver's public address
 *
 * Return: Pointer to the created transaction output, or NULL on failure
 */
tx_out_t *tx_out_create(uint32_t amount, uint8_t const pub[EC_PUB_LEN])
{
	tx_out_t *out = malloc(sizeof(tx_out_t));
	uint8_t buf[sizeof(uint32_t) + EC_PUB_LEN];

	if (!out)
	{
		return (NULL);
	}

	out->amount = amount;

	memcpy(out->pub, pub, EC_PUB_LEN);
	memcpy(buf, &out->amount, sizeof(uint32_t));
	memcpy(buf + sizeof(uint32_t), out->pub, EC_PUB_LEN);
	sha256((const int8_t *)buf, sizeof(buf), out->hash);

	return (out);
}
