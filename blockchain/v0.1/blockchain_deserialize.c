#include "blockchain.h"
#include "provided/endianness.h"

#define HBLK_MAGIC "HBLK"
#define HBLK_VERSION "0.1"

/**
 * blockchain_deserialize - Deserialize a blockchain from a file
 *
 * @path: The path to the file containing the serialized blockchain
 *
 * Return: A pointer to the deserialized blockchain, or NULL on failure
 */
blockchain_t *blockchain_deserialize(char const *path)
{
	FILE *fp;
	char magic[4], version[3];
	uint8_t endianness, sys_endian;
	uint32_t blocks, i;
	blockchain_t *blockchain = NULL;
	block_t *block = NULL;

	if (!path)
		return (NULL);

	fp = fopen(path, "rb");
	if (!fp)
		return (NULL);

	if (fread(magic, 1, 4, fp) != 4 || memcmp(magic, HBLK_MAGIC, 4) != 0)
		goto fail;
	if (fread(version, 1, 3, fp) != 3 || memcmp(version, HBLK_VERSION, 3) != 0)
		goto fail;
	if (fread(&endianness, 1, 1, fp) != 1)
		goto fail;

	sys_endian = _get_endianness();

	if (fread(&blocks, sizeof(blocks), 1, fp) != 1)
		goto fail;
	if (endianness != sys_endian)
		SWAPENDIAN(blocks);

	blockchain = malloc(sizeof(*blockchain));
	if (!blockchain)
		goto fail;

	blockchain->chain = llist_create(MT_SUPPORT_FALSE);
	if (!blockchain->chain)
		goto fail2;

	for (i = 0; i < blocks; i++)
	{
		block_info_t info;
		block_data_t data;
		uint32_t data_len;
		uint8_t hash[SHA256_DIGEST_LENGTH];

		if (fread(&info, sizeof(info), 1, fp) != 1)
			goto fail3;
		if (fread(&data_len, sizeof(data_len), 1, fp) != 1)
			goto fail3;
		if (endianness != sys_endian)
		{
			SWAPENDIAN(info.index);
			SWAPENDIAN(info.difficulty);
			SWAPENDIAN(info.timestamp);
			SWAPENDIAN(info.nonce);
			SWAPENDIAN(data_len);
		}
		memset(&data, 0, sizeof(data));
		data.len = data_len;
		if (data_len > BLOCKCHAIN_DATA_MAX)
			goto fail3;
		if (fread(data.buffer, 1, data_len, fp) != data_len)
			goto fail3;
		if (fread(hash, 1, SHA256_DIGEST_LENGTH, fp) != SHA256_DIGEST_LENGTH)
			goto fail3;

		block = calloc(1, sizeof(*block));
		if (!block)
			goto fail3;
		block->info = info;
		block->data = data;
		memcpy(block->hash, hash, SHA256_DIGEST_LENGTH);

		if (llist_add_node(blockchain->chain, block, ADD_NODE_REAR) == -1)
		{
			free(block);
			goto fail3;
		}
	}

	fclose(fp);
	return (blockchain);

fail3:
	llist_destroy(blockchain->chain, 1, (node_dtor_t)block_destroy);
fail2:
	free(blockchain);
fail:
	if (fp)
		fclose(fp);
	return (NULL);
}
