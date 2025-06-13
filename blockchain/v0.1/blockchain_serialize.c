#include "blockchain.h"
#include "provided/endianness.h"

#define HBLK_MAGIC "HBLK"
#define HBLK_VERSION "0.1"

#include <unistd.h>

/**
 * blockchain_serialize - Serializes a blockchain to a file
 *
 * @blockchain: Pointer to the blockchain to serialize
 * @path: Path to the file where the blockchain will be serialized
 *
 * Return: 0 on success, -1 on failure
 */
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *fp;
	uint32_t blocks, i;
	uint8_t endianness;
	block_t *block;

	if (!blockchain || !path)
		return (-1);

	fp = fopen(path, "wb");
	if (!fp)
		return (-1);

	blocks = llist_size(blockchain->chain);
	endianness = _get_endianness();

	/* Write header */
	fwrite(HBLK_MAGIC, 1, 4, fp);
	fwrite(HBLK_VERSION, 1, 3, fp);
	fwrite(&endianness, 1, 1, fp);

	if (endianness == 1)
		fwrite(&blocks, sizeof(blocks), 1, fp);
	else
	{
		uint32_t tmp = blocks;
		SWAPENDIAN(tmp);
		fwrite(&tmp, sizeof(tmp), 1, fp);
	}

	/* Write blocks */
	for (i = 0; i < blocks; i++)
	{
		block = llist_get_node_at(blockchain->chain, i);
		if (!block)
			break;

		block_info_t info = block->info;
		block_data_t data = block->data;
		uint32_t data_len = data.len;

		if (endianness != 1)
		{
			SWAPENDIAN(info.index);
			SWAPENDIAN(info.difficulty);
			SWAPENDIAN(info.timestamp);
			SWAPENDIAN(info.nonce);
			SWAPENDIAN(data_len);
		}

		fwrite(&info, sizeof(info), 1, fp);
		fwrite(&data_len, sizeof(data_len), 1, fp);
		fwrite(data.buffer, 1, data.len, fp);
		fwrite(block->hash, 1, SHA256_DIGEST_LENGTH, fp);
	}

	fclose(fp);
	return (0);
}
