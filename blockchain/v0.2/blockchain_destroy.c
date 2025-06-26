#include "blockchain.h"

/**
 * blockchain_destroy - Destroys a blockchain
 *
 * @blockchain: Pointer to the blockchain to destroy
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	if (!blockchain)
		return;

	llist_destroy(blockchain->chain, 1, (node_dtor_t)block_destroy);
	free(blockchain);
}
