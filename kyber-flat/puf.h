#pragma once
#include <stdint.h>
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
int puf_get_bytes(uint8_t *buf, size_t len);
int puf_derive_seed32(uint8_t out32[32], const uint8_t *salt, size_t salt_len);
#ifdef __cplusplus
}
#endif
