#include "hblk_crypto.h"

/**
 * ec_sign - Signs a given set of bytes using a given EC_KEY private key
 * @key: pointer to EC_KEY structure containing the private key
 * @msg: pointer to the bytes to be signed
 * @msglen: number of bytes to sign
 * @sig: address at which to store the signature
 * Return: pointer to the signature buffer upon success, NULL on failure
 */
uint8_t *ec_sign(EC_KEY const *key,
	 uint8_t const *msg, size_t msglen, sig_t *sig)
{
	unsigned int sig_len = sizeof(sig->sig);

	if (!key || !msg || !sig)
		return (NULL);

	if (!ECDSA_sign(0, msg, msglen, sig->sig, &sig_len, (EC_KEY *)key))
		return (NULL);

	sig->len = (uint8_t)sig_len;
	return (sig->sig);
}
