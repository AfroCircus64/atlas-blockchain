#include "hblk_crypto.h"

/**
 * ec_verify - Verifies the signature of a given set of
 * bytes using an EC_KEY public key
 *
 * @key: pointer to EC_KEY structure containing the public key
 * @msg: pointer to the bytes to verify
 * @msglen: number of bytes to verify
 * @sig: pointer to the signature to be checked
 *
 * Return: 1 if the signature is valid, 0 otherwise
 */
int ec_verify(EC_KEY const *key,
	 uint8_t const *msg, size_t msglen, sig_t const *sig)
{
	if (!key || !msg || !sig)
		return (0);

	if (ECDSA_verify(0, msg, msglen, sig->sig, sig->len, (EC_KEY *)key) == 1)
		return (1);

	return (0);
}
