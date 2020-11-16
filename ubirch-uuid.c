/*!
 * @file ubirch-uuid.c
 * @brief UUID Version 5 Generator
 *
 * @author Waldemar Gruenwald
 * @date   2020-11-15
 *
 * @copyright &copy; check `copyrt.h`
 *
 * @note:	Origin = https://tools.ietf.org/html/rfc4122
 */

#include "copyrt.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <lwip/def.h>
#include "ubirch-uuid.h"
#include "mbedtls/sha1.h"

/* format_uuid_v3or5 -- make a UUID from a (pseudo)random 128-bit
   number */
void format_uuid_v3or5(uuid_t *uuid, unsigned char hash[16], int v)
{
	/* convert UUID to local byte order */
	memcpy(uuid, hash, sizeof *uuid);
	uuid->time_low = ntohl(uuid->time_low);
	uuid->time_mid = ntohs(uuid->time_mid);
	uuid->time_hi_and_version = ntohs(uuid->time_hi_and_version);

	/* put in the variant and version bits */
	uuid->time_hi_and_version &= 0x0FFF;
	uuid->time_hi_and_version |= (v << 12);
	uuid->clock_seq_hi_and_reserved &= 0x3F;
	uuid->clock_seq_hi_and_reserved |= 0x80;
}

void uuid_create_sha1_from_name(uuid_t *uuid, uuid_t nsid, void *name, int namelen)
{
	mbedtls_sha1_context c;
	unsigned char hash[20];
	uuid_t net_nsid;

	/* put name space ID in network byte order so it hashes the same
	   no matter what endian machine we're on */
	net_nsid = nsid;
	net_nsid.time_low = htonl(net_nsid.time_low);
	net_nsid.time_mid = htons(net_nsid.time_mid);
	net_nsid.time_hi_and_version = htons(net_nsid.time_hi_and_version);

	mbedtls_sha1_init(&c);
	mbedtls_sha1_starts_ret(&c);
	mbedtls_sha1_update_ret(&c, &net_nsid, sizeof net_nsid);
	mbedtls_sha1_update_ret(&c, name, namelen);
	mbedtls_sha1_finish_ret(&c, hash);

	/* the hash is in network byte order at this point */
	format_uuid_v3or5(uuid, hash, 5);
}

/* uuid_compare --  Compare two UUID's "lexically" and return */
#define CHECK(f1, f2) if (f1 != f2) return f1 < f2 ? -1 : 1;
int uuid_compare(uuid_t *u1, uuid_t *u2)
{
	int i;

	CHECK(u1->time_low, u2->time_low);
	CHECK(u1->time_mid, u2->time_mid);
	CHECK(u1->time_hi_and_version, u2->time_hi_and_version);
	CHECK(u1->clock_seq_hi_and_reserved, u2->clock_seq_hi_and_reserved);
	CHECK(u1->clock_seq_low, u2->clock_seq_low)
	for (i = 0; i < 6; i++) {
		if (u1->node[i] < u2->node[i])
			return -1;
		if (u1->node[i] > u2->node[i])
			return 1;
	}
	return 0;
}
#undef CHECK
