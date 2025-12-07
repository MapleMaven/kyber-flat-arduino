// ESP32-friendly randombytes() compatible with Kyber reference API (void signature)
#include <stdint.h>
#include <stddef.h>

__attribute__((weak)) uint32_t esp_random(void);

static uint32_t s_xorshift_state = 0x12345678u;
static inline uint32_t xorshift32(void) {
	uint32_t x = s_xorshift_state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	s_xorshift_state = x;
	return x;
}

void randombytes(uint8_t *buf, size_t len) {
	while (len) {
		uint32_t r = (&esp_random) ? esp_random() : xorshift32();
		size_t c = len < 4 ? len : 4;
		for (size_t i = 0; i < c; ++i) { *buf++ = (uint8_t)(r & 0xFF); r >>= 8; }
		len -= c;
	}
}
