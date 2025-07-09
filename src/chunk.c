#include "common.h"

#define DAR_BE(type) \
	type dar_##type##be(type n) { \
		u16 s = 1; \
		if((*(u8*)&s) == 1) { \
			/* little endian */ \
			type r = 0; \
			int  i; \
			for(i = 0; i < sizeof(n); i++) { \
				r = r << 8; \
				r = r | (n & 0xff); \
				n = n >> 8; \
			} \
			return r; \
		} \
		return n; \
	}

DAR_BE(u32)
DAR_BE(u16)

void dar_write(const char* path) {
	dar_header_t hdr;
	memset(&hdr, 0, sizeof(hdr));
}
