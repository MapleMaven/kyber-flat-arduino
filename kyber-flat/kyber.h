// Flat Kyber768 API shim for Arduino/ESP32.
// Pulls in upstream Kyber reference headers and exposes convenient aliases.
#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Upstream reference defaults to KYBER_K == 3 (Kyber768).
// Include params/kem to get canonical sizes and function prototypes.
#include "params.h"
#include "kem.h"

// Maintain explicit Kyber768 size macros for consumers that expect them.
#define KYBER768_SECRETKEYBYTES  KYBER_SECRETKEYBYTES
#define KYBER768_PUBLICKEYBYTES  KYBER_PUBLICKEYBYTES
#define KYBER768_CIPHERTEXTBYTES KYBER_CIPHERTEXTBYTES
#define KYBER768_SSBYTES         KYBER_SSBYTES

// Convenience wrappers (names unaffected by namespacing macros)
static inline int kyber768_keypair(uint8_t *pk, uint8_t *sk) { return crypto_kem_keypair(pk, sk); }
static inline int kyber768_enc(uint8_t *ct, uint8_t *ss, const uint8_t *pk) { return crypto_kem_enc(ct, ss, pk); }
static inline int kyber768_dec(uint8_t *ss, const uint8_t *ct, const uint8_t *sk) { return crypto_kem_dec(ss, ct, sk); }

#ifdef __cplusplus
}
#endif
