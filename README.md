# Kyber (Flattened) — Arduino-friendly 

This is a flattened copy of the Kyber public-key / KEM reference implementation adapted for use with the Arduino IDE (and other environments that require all source files to live in a single directory). The original Kyber project was written in multiple subfolders; this distribution places all `.c`, `.h`, and helper files together so the Arduino IDE can compile them inside a sketch folder.

**Original Kyber Resources**

- **Official Website**: [https://pq-crystals.org/kyber/index.shtml](https://pq-crystals.org/kyber/index.shtml)
- **GitHub Repository**: [https://github.com/pq-crystals/kyber](https://github.com/pq-crystals/kyber)

Important: this repo is a literal flattened source set — it preserves the original library's C sources. Arduino sketches are C++ (`.ino`) files; when including these C headers from a sketch, wrap includes with `extern "C" { ... }` as shown in the example below.

**Included files**

The folder contains these source and header files:

- `cbd.c`, `cbd.h`
- `cpapke.c`, `cpapke.h`
- `fips202.c`, `fips202.h`
- `indcpa.c`, `indcpa.h`
- `kem.c`, `kem.h`
- `kyber.h`
- `ntt.c`, `ntt.h`
- `params.h`
- `poly.c`, `poly.h`
- `polyvec.c`, `polyvec.h`
- `puf_esp32.c`, `puf_get_bytes.cpp`, `puf.h`
- `randombytes_esp32.c`, `randombytes.h`
- `reduce.c`, `reduce.h`
- `symmetric-shake.c`, `symmetric.h`
- `verify.c`, `verify.h`

Note: Files with `esp32` in the name are specific to ESP32 platforms (hardware PUF / RNG helpers). If you target AVR-based Arduino boards (Uno, Nano, Mega), you may need to replace or stub out ESP32-specific code (or use platform-appropriate `randombytes` implementation).

**Quick Usage (Arduino IDE)**

1. Create a new sketch folder (Arduino IDE creates a folder named after the sketch).
2. Copy all files from this directory into that sketch folder.
3. Create your sketch `.ino` file next to these files.
4. In the `.ino` file include the library headers inside an `extern "C"` block to prevent C++ name mangling, for example:

```cpp
extern "C" {
#include "kyber.h"
}

void setup() {
  Serial.begin(115200);
  // Use Kyber API functions here
}

void loop() {
}
```

**Example notes**

- The high-level API is provided by `kem.h` / `kem.c` and `kyber.h` (look for functions such as the standard `crypto_kem_*` names in the implementation).
- Because this is a full KEM implementation, some operations may be memory- and compute-intensive. Smaller Arduino boards with limited RAM may not be suitable for full parameter sets. Consider using a board with more RAM (e.g., ESP32, Teensy, Arduino Portenta) or cross-compiling/performing heavy work off-device.
- For ESP32 targets, you can use the `puf_esp32.c` and `randombytes_esp32.c` helpers included here. For AVR or other MCUs, provide an appropriate `randombytes` implementation (or adapt the reference `randombytes` available from other Kyber ports).

**Build / Compilation tips**

- Keep all files in the sketch folder so the Arduino IDE compiles them together.
- If the IDE complains about conflicting C/C++ linkage or missing prototypes, ensure your `.ino` includes the C headers using the `extern "C"` block.
- If you prefer to build via `arduino-cli` or a Makefile, include these sources in the compilation unit and link as usual.

**Testing**

- Start with simple compile-only tests (empty `setup()`/`loop()` with the `extern "C"` include) to verify the IDE compiles the flat source set for your board.
- Once it compiles, add small calls to Kyber functions and test step-by-step (keypair generation first, then encapsulation/decapsulation).

**Caveats & Recommendations**

- This flattening is for convenience with the Arduino IDE; it does not change the underlying algorithm or security properties — use the same caution and review as for any crypto library.
- Ensure you understand memory requirements for the parameter set you choose. Smaller boards may run out of RAM.
- If you distribute or publish projects that include this code, check and comply with the original Kyber project's license and attribution requirements.

**License & Credits**

This folder is a flattened redistribution of the Kyber reference implementation. Credit and license belong to the original Kyber project authors. Refer to the upstream repository for the authoritative license text and authorship details.

