#include "hblk_crypto.h"

/**
 * ec_save - Saves an EC key pair to disk in PEM format
 *
 * @key: pointer to EC_KEY structure
 * @folder: path to the folder to save the keys
 *
 * Return: 1 on success, 0 on failure
 */
int ec_save(EC_KEY *key, char const *folder)
{
	char priv_path[1024], pub_path[1024];
	FILE *priv_file = NULL, *pub_file = NULL;
	int ret = 0;

	if (!key || !folder)
		return (0);

	if (mkdir(folder, 0700) == -1 && errno != EEXIST)
		return (0);

	snprintf(priv_path, sizeof(priv_path), "%s/key.pem", folder);
	snprintf(pub_path, sizeof(pub_path), "%s/key_pub.pem", folder);

	priv_file = fopen(priv_path, "w");
	if (!priv_file)
		return (0);
	if (!PEM_write_ECPrivateKey(priv_file, key, NULL, NULL, 0, NULL, NULL))
		goto cleanup;

	pub_file = fopen(pub_path, "w");
	if (!pub_file)
		goto cleanup;
	if (!PEM_write_EC_PUBKEY(pub_file, key))
		goto cleanup;

	ret = 1; /* Success */

cleanup:
	if (priv_file)
		fclose(priv_file);
	if (pub_file)
		fclose(pub_file);

	return (ret);
}
