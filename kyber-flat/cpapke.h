#pragma once
#include <stdint.h>
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif

#include "params.h"
#include "indcpa.h"

// Encrypt an arbitrary-length message m into blocks of KYBER_INDCPA_MSGBYTES (32 bytes).
// out_ct must have space for ceil(m_len/32)*KYBER_INDCPA_BYTES bytes.
// Returns number of ciphertext blocks written.
size_t kyber_cpapke_encrypt_blocks(uint8_t *out_ct,
                                   const uint8_t *m,
                                   size_t m_len,
                                   const uint8_t *pk);

// Decrypt blocks back into m (truncates to m_len_requested).
// Returns bytes written to out_m.
size_t kyber_cpapke_decrypt_blocks(uint8_t *out_m,
                                   size_t m_len_requested,
                                   const uint8_t *in_ct,
                                   size_t ct_len,
                                   const uint8_t *sk);

// Helper to compute ciphertext length for a given message length.
static inline size_t kyber_cpapke_ciphertext_len(size_t m_len) {
    size_t blocks = (m_len + KYBER_INDCPA_MSGBYTES - 1) / KYBER_INDCPA_MSGBYTES;
    return blocks * KYBER_INDCPA_BYTES;
}

#ifdef __cplusplus
}
#endif
