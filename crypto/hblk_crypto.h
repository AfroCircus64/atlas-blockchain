#ifndef HBLK_CRYPTO_H
#define HBLK_CRYPTO_H
#include <openssl/sha.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>

#define EC_CURVE NID_secp256k1

uint8_t *sha256(int8_t const *s, size_t len,
	 uint8_t digest[SHA256_DIGEST_LENGTH]);
EC_KEY *ec_create(void);



#endif /* HBLK_CRYPTO_H */
