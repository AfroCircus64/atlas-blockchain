#include "hblk_crypto.h"

/**
 * ec_load - Loads an EC key pair from disk in PEM format
 *
 * @folder: path to the folder to load the keys from
 *
 * Return: pointer to created EC_KEY structure, or NULL on failure
 */
EC_KEY *ec_load(char const *folder)
{
	char priv_path[1024];
	FILE *priv_file = NULL;
	EC_KEY *key = NULL;

	if (!folder)
		return (NULL);

	snprintf(priv_path, sizeof(priv_path), "%s/key.pem", folder);

	priv_file = fopen(priv_path, "r");
	if (!priv_file)
		return (NULL);

	key = PEM_read_ECPrivateKey(priv_file, NULL, NULL, NULL);

	fclose(priv_file);

	return (key);
}
