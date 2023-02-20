/*!
 * @file ubirch_uuid.c
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
#include <mbedtls/sha1.h>

#include "ubirch_uuid.h"

/*!
 * UUID= 00112233-4455-6677-8899-AABBCCDDEEFF
 *                      ^    ^
 *                      |    variant
 *                      version
 */

/*!
 * @brief format_uuid_v3or5 -- make a UUID from a (pseudo)random 128-bit
   number */
static void format_uuid_v3or5(uuid_t *p_uuid, unsigned char hash[16], int v)
{
	/* convert UUID to local byte order */
	memcpy(*p_uuid, hash, sizeof(*p_uuid));
	
	/* put in the variant and version bits */
	(*p_uuid)[6] &= 0x0F; 		/*< first clear the version field */
	(*p_uuid)[6] |= (v << 4); 	/*< set the verion field*/
	(*p_uuid)[8] &= 0x3F;	 	/*< clear the variant bits*/
	(*p_uuid)[8] |= 0x80;		/*< set the variant bit*/
}


void uuid_create_sha1_from_name(uuid_t *p_uuid, uuid_t nsid, void *name, int namelen)
{
	mbedtls_sha1_context c;
	unsigned char hash[20];

	mbedtls_sha1_init(&c);
	mbedtls_sha1_starts_ret(&c);
	mbedtls_sha1_update_ret(&c, (unsigned char *)nsid, sizeof(uuid_t));
	mbedtls_sha1_update_ret(&c, name, namelen);
	mbedtls_sha1_finish_ret(&c, hash);

	// /* the hash is in network byte order at this point */
	format_uuid_v3or5(p_uuid, hash, 5);
}

void ubirch_uuid2str (const uuid_t uuid, char **strbuf) {
    char *hexchr = "0123456789abcdef";

    /*
     * a UUID string looks like this
     * 00000000-0000-0000-0000-000000000000
     *
     * this is hard coded to avoid the need of multiple loops or a full hexdump of the uuid
     */
    (*strbuf)[0]  = hexchr[uuid[0] >> 4];
    (*strbuf)[1]  = hexchr[uuid[0] & 0xf];
    (*strbuf)[2]  = hexchr[uuid[1] >> 4];
    (*strbuf)[3]  = hexchr[uuid[1] & 0xf];
    (*strbuf)[4]  = hexchr[uuid[2] >> 4];
    (*strbuf)[5]  = hexchr[uuid[2] & 0xf];
    (*strbuf)[6]  = hexchr[uuid[3] >> 4];
    (*strbuf)[7]  = hexchr[uuid[3] & 0xf];
    (*strbuf)[8]  = '-';
    (*strbuf)[9]  = hexchr[uuid[4] >> 4];
    (*strbuf)[10] = hexchr[uuid[4] & 0xf];
    (*strbuf)[11] = hexchr[uuid[5] >> 4];
    (*strbuf)[12] = hexchr[uuid[5] & 0xf];
    (*strbuf)[13] = '-';
    (*strbuf)[14] = hexchr[uuid[6] >> 4];
    (*strbuf)[15] = hexchr[uuid[6] & 0xf];
    (*strbuf)[16] = hexchr[uuid[7] >> 4];
    (*strbuf)[17] = hexchr[uuid[7] & 0xf];
    (*strbuf)[18] = '-';
    (*strbuf)[19] = hexchr[uuid[8] >> 4];
    (*strbuf)[20] = hexchr[uuid[8] & 0xf];
    (*strbuf)[21] = hexchr[uuid[9] >> 4];
    (*strbuf)[22] = hexchr[uuid[9] & 0xf];
    (*strbuf)[23] = '-';
    (*strbuf)[24] = hexchr[uuid[10] >> 4];
    (*strbuf)[25] = hexchr[uuid[10] & 0xf];
    (*strbuf)[26] = hexchr[uuid[11] >> 4];
    (*strbuf)[27] = hexchr[uuid[11] & 0xf];
    (*strbuf)[28] = hexchr[uuid[12] >> 4];
    (*strbuf)[29] = hexchr[uuid[12] & 0xf];
    (*strbuf)[30] = hexchr[uuid[13] >> 4];
    (*strbuf)[31] = hexchr[uuid[13] & 0xf];
    (*strbuf)[32] = hexchr[uuid[14] >> 4];
    (*strbuf)[33] = hexchr[uuid[14] & 0xf];
    (*strbuf)[34] = hexchr[uuid[15] >> 4];
    (*strbuf)[35] = hexchr[uuid[15] & 0xf];
}