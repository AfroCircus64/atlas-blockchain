#include "blockchain.h"

/* Definition of the genesis block */
static const block_t _genesis = {
	.info = {
		.index = 0,
		.difficulty = 0,
		.timestamp = 1537578000,
		.nonce = 0,
		.prev_hash = {0}
	},
	.data = {
		.buffer = "Holberton School",
		.len = 16
	},
	.hash = {
		0xc5, 0x2c, 0x26, 0xc8, 0xb5, 0x46, 0x16, 0x39,
		0x63, 0x5d, 0x8e, 0xdf, 0x2a, 0x97, 0xd4, 0x8d,
		0x0c, 0x8e, 0x00, 0x09, 0xc8, 0x17, 0xf2, 0xb1,
		0x77, 0xe2, 0x5f, 0xe2, 0x7d, 0x49, 0x34, 0x4d
	}
};

/**
 * blockchain_create - Creates a new blockchain
 *
 * Return: Pointer to the new blockchain, or NULL on failure
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain = NULL;
	block_t *genesis = NULL;

	/* Allocate blockchain */
	blockchain = malloc(sizeof(*blockchain));
	if (!blockchain)
		return (NULL);

	blockchain->chain = llist_create(MT_SUPPORT_FALSE);
	if (!blockchain->chain)
	{
		free(blockchain);
		return (NULL);
	}

	/* Allocate and copy the genesis block */
	genesis = malloc(sizeof(*genesis));
	if (!genesis)
	{
		llist_destroy(blockchain->chain, 1, NULL);
		free(blockchain);
		return (NULL);
	}
	memcpy(genesis, &_genesis, sizeof(_genesis));

	if (llist_add_node(blockchain->chain, genesis, ADD_NODE_REAR) == -1)
	{
		free(genesis);
		llist_destroy(blockchain->chain, 1, NULL);
		free(blockchain);
		return (NULL);
	}

	return (blockchain);
}
