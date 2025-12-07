// ESP32 PUF/UID helpers. Requires upstream fips202 (shake256) present.
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "puf.h"
#include "fips202.h"

__attribute__((weak)) uint64_t ESP_getEfuseMac(void);

int puf_get_bytes(uint8_t *buf, size_t len) {
	if (!buf) return -1;
	uint64_t mac = 0;
	if (&ESP_getEfuseMac) { mac = ESP_getEfuseMac(); }
	uint8_t macb[8];
	for (int i = 0; i < 8; ++i) macb[i] = (uint8_t)((mac >> (8 * i)) & 0xFF);
	size_t off = 0;
	while (off < len) {
		size_t c = (len - off) < sizeof(macb) ? (len - off) : sizeof(macb);
		memcpy(buf + off, macb, c);
		off += c;
	}
	return 0;
}

int puf_derive_seed32(uint8_t out32[32], const uint8_t *salt, size_t salt_len) {
	if (!out32) return -1;
	uint8_t buf[96];
	uint8_t pufbuf[32];
	if (puf_get_bytes(pufbuf, sizeof pufbuf) != 0) return -1;
	size_t inlen = 0;
	memcpy(buf + inlen, pufbuf, sizeof pufbuf);
	inlen += sizeof pufbuf;
	if (salt && salt_len) { memcpy(buf + inlen, salt, salt_len); inlen += salt_len; }
	shake256(out32, 32, buf, inlen);
	return 0;
}
