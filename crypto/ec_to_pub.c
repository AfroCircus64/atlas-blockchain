#include "hblk_crypto.h"

/**
 * ec_to_pub - Extracts the public key from an EC_KEY structure
 *
 * @key: pointer to EC_KEY structure
 * @pub: buffer to store the public key (uncompressed, EC_PUB_LEN bytes)
 *
 * Return: pointer to pub or NULL on failure
 */
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_POINT *pub_key;
	const EC_GROUP *group;

	if (!key || !pub)
		return (NULL);

	group = EC_KEY_get0_group(key);
	pub_key = EC_KEY_get0_public_key(key);

	if (!group || !pub_key)
		return (NULL);

	if (EC_POINT_point2oct(group, pub_key, POINT_CONVERSION_UNCOMPRESSED,
		pub, EC_PUB_LEN, NULL) != EC_PUB_LEN)
		return (NULL);

	return (pub);
}
