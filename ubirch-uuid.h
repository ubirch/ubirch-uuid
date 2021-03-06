/*!
 * @file ubirch-uuid.h
 * @brief UUID Version 5 Generator header file
 *
 * @author Waldemar Gruenwald
 * @date   2020-11-15
 *
 * @copyright &copy; check `copyrt.h`
 *
 * @note:	Origin = https://tools.ietf.org/html/rfc4122
 */

#ifndef UUID_UUID_H
#define UUID_UUID_H

#include "copyrt.h"

typedef unsigned long   unsigned32;
typedef unsigned short  unsigned16;
typedef unsigned char   unsigned8;
typedef unsigned char   byte;

#undef uuid_t
typedef struct {
	unsigned32  time_low;
	unsigned16  time_mid;
	unsigned16  time_hi_and_version;
	unsigned8   clock_seq_hi_and_reserved;
	unsigned8   clock_seq_low;
	byte        node[6];
} uuid_t;

/* uuid_create_sha1_from_name -- create a version 5 (SHA-1) UUID
   using a "name" from a "name space" */
void uuid_create_sha1_from_name(

		uuid_t *uuid,         /* resulting UUID */
		uuid_t nsid,          /* UUID of the namespace */
		void *name,           /* the name from which to generate a UUID */
		int namelen           /* the length of the name */
);

/* uuid_compare --  Compare two UUID's "lexically" and return
        -1   u1 is lexically before u2
         0   u1 is equal to u2
         1   u1 is lexically after u2
   Note that lexical ordering is not temporal ordering!
*/
int uuid_compare(uuid_t *u1, uuid_t *u2);

#endif //UUID_UUID_H
