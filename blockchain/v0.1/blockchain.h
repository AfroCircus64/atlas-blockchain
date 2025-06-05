#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdint.h>
#include <openssl/sha.h>

/* DATA STRUCTURES */

/**
 * struct blockchain_s - Represents a blockchain
 */
typedef struct blockchain_s
{
	/* Struct */
} blockchain_t;

/**
 * struct block_s - Represents a block in the blockchain
 */
typedef struct block_s
{
	/* Struct */
} block_t;

/* FUNCTION PROTOTYPES */

blockchain_t *blockchain_create(void);
block_t *block_create(block_t const *prev,
	 int8_t const *data, uint32_t data_len);
void block_destroy(block_t *block);
void blockchain_destroy(blockchain_t *blockchain);
uint8_t *block_hash(block_t const *block,
	 uint8_t hash_buf[SHA256_DIGEST_LENGTH]);
int blockchain_serialize(blockchain_t const *blockchain, char const *path);
blockchain_t *blockchain_deserialize(char const *path);
int block_is_valid(block_t const *block, block_t const *prev_block);


#endif /* BLOCKCHAIN_H */
