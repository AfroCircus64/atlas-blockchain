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
	.hash = "\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4"
			"\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51"
			"\x58\x03"
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
