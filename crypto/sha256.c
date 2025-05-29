#include "hblk_crypto.h"

/**
 * sha256 - Computes the SHA256 hash of a string
 *
 * @s: The string to hash
 * @len: The length of the string
 * @digest: The buffer to store the resulting hash
 *
 * Return: Pointer to digest, or NULL on failure
 */
uint8_t *sha256(int8_t const *s, size_t len,
	 uint8_t digest[SHA256_DIGEST_LENGTH])
{
	if (!digest)
		return (NULL);

	if (!s || len == 0)
	{
		SHA256((const unsigned char *)s, len, digest);
		return (digest);
	}

	SHA256((const unsigned char *)s, len, digest);
	return (digest);
}
