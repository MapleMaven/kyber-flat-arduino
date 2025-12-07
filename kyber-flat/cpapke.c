#include <string.h>
#include "cpapke.h"
#include "randombytes.h"

size_t kyber_cpapke_encrypt_blocks(uint8_t *out_ct,
                                   const uint8_t *m,
                                   size_t m_len,
                                   const uint8_t *pk) {
    size_t offset_m = 0;
    size_t blocks = 0;
    while (offset_m < m_len) {
        uint8_t block[KYBER_INDCPA_MSGBYTES] = {0};
        size_t remaining = m_len - offset_m;
        size_t take = remaining > KYBER_INDCPA_MSGBYTES ? KYBER_INDCPA_MSGBYTES : remaining;
        memcpy(block, m + offset_m, take);
        uint8_t coins[KYBER_SYMBYTES];
        randombytes(coins, sizeof coins);
        indcpa_enc(out_ct + blocks * KYBER_INDCPA_BYTES, block, pk, coins);
        offset_m += take;
        blocks++;
    }
    return blocks;
}

size_t kyber_cpapke_decrypt_blocks(uint8_t *out_m,
                                   size_t m_len_requested,
                                   const uint8_t *in_ct,
                                   size_t ct_len,
                                   const uint8_t *sk) {
    size_t blocks = ct_len / KYBER_INDCPA_BYTES;
    size_t written = 0;
    for (size_t i = 0; i < blocks; i++) {
        uint8_t block[KYBER_INDCPA_MSGBYTES];
        indcpa_dec(block, in_ct + i * KYBER_INDCPA_BYTES, sk);
        size_t remain = m_len_requested - written;
        size_t take = remain > KYBER_INDCPA_MSGBYTES ? KYBER_INDCPA_MSGBYTES : remain;
        memcpy(out_m + written, block, take);
        written += take;
        if (written >= m_len_requested) break;
    }
    return written;
}
