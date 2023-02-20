/*!
 * @file ubirch_uuid.h
 * @brief UUID Version 5 Generator header file
 *
 * @author Waldemar Gruenwald
 * @date   2020-11-15
 *
 * 
 * @note: This code is based on https://tools.ietf.org/html/rfc4122
 * @copyright &copy; check `copyrt.h`
 */

#ifndef UUID_UUID_H
#define UUID_UUID_H

#include "copyrt.h"

#define UUID_SIZ 16
#define UUID_STR_SIZ 37

typedef unsigned char uuid_t[UUID_SIZ];

/*!
 * @brief create a version 5 UUID based on SHA-1, `namespace` and `name`
 * 
 * @param [out] p_uuid pointer to uuid, where the resulting UUID will be stored into
 * @param [in] nsid namespace id, is the UUID of the namespace
 * @param [in] name pointer to the name from which to generate a UUID
 * @param [in] namelen length of the name 
 */
void uuid_create_sha1_from_name (uuid_t *p_uuid, uuid_t nsid, void *name, int namelen);

/*!
 * @brief Converts a UUID into a string in the usual XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX format
 *
 * Both pointer must **not** be `NULL`.
 *
 * @param [in] uuid The UUID to print into `strbuf`. Must have a size of 16 bytes.
 * @param [out] strbuf The buffer to print the string into. At least 37 bytes in size.
 */
void ubirch_uuid2str (const uuid_t uuid, char **strbuf);


#endif //UUID_UUID_H
