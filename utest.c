/*!
 * @file utest.c
 * @brief UUID Version 5 Generator test functions
 *
 * @author Waldemar Gruenwald
 * @date   2020-11-15
 *
 * @copyright &copy; check `copyrt.h`
 *
 * @note:	Origin = https://tools.ietf.org/html/rfc4122
 */

#include "copyrt.h"
#include <stdio.h>
#include <string.h>
#include "ubirch-uuid.h"
#include "utest.h"


// This is the the NIL uuid, which consists only of zeros.
uuid_t NIL_uuid = {
		0x00000000,
		0x0000,
		0x0000,
		0x00, 0x00,
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

// this is the recommended eon Namespace, based on the String "e.on Powerzone"
uuid_t NameSpace_TEST = {
		0x73799fba,
		0x4f42,
		0x5715,
		0x86, 0x73,
		{0xe4, 0x28, 0xc4, 0x45, 0x48, 0xd1}
}; /* 73799fba-4f42-5715-8673-e428c44548d1 */

uuid_t Namespace_DERIVED = {
		0xbc5b4e99,
		0x1d5a,
		0x5294,
		0x97, 0xa9,
		{0x4e, 0xa0, 0xff, 0xb1, 0xde, 0x3b}
} /* bc5b4e99-1d5a-5294-97a9-4ea0ffb1de3b */;


/* puid -- print a UUID */
void puid(uuid_t u)
{
	int i;

	printf("%8.8lx-%4.4x-%4.4x-%2.2x%2.2x-", u.time_low, u.time_mid,
	       u.time_hi_and_version, u.clock_seq_hi_and_reserved,
	       u.clock_seq_low);
	for (i = 0; i < 6; i++)
		printf("%2.2x", u.node[i]);
	printf("\n");
}

void uuid_test(void){
	printf("NIL uuid: ");
	puid(NIL_uuid);

	// generate the namespace uuid
	uuid_t namespace_uuid;
	char * namespace_name = "Namespace Test";
	uuid_create_sha1_from_name(&namespace_uuid, NIL_uuid, namespace_name, strlen(namespace_name));
	printf("Namespace based on [\"%s\"]: ", namespace_name);
	puid(namespace_uuid);

	// compare this generated uuid, with the precalculated namespace id
	int f = uuid_compare(&namespace_uuid, &NameSpace_TEST);
	printf("Comparison between stored and generated Test Namespace = %d (should be 0)\r\n", f);

	// generate the device uuid, based on namespace uuid
	uuid_t device_uuid;
	char * device_name = "12345678";
	uuid_create_sha1_from_name(&device_uuid,namespace_uuid,device_name,strlen(device_name));
	printf("device uuid, based on [\"%s\"]: ",device_name);
	puid(device_uuid);
	return;
}

/* output:

NIL uuid: 00000000-0000-0000-0000-000000000000
Namespace based on ["Namespace Test"]: 73799fba-4f42-5715-8673-e428c44548d1
Comparison between stored and generated Test Namespace = 0 (should be 0)
device uuid, based on ["12345678"]: e97ef829-65a8-5a3c-a62a-1a4406813169

 */

void uuid_test_derived(void){
	printf("NIL uuid: ");
	puid(NIL_uuid);

	// generate the namespace uuid
	uuid_t namespace_uuid;
	char * namespace_name = "Namespace Test";
	uuid_create_sha1_from_name(&namespace_uuid, NIL_uuid, namespace_name, strlen(namespace_name));
	printf("Namespace based on [\"%s\"]: ", namespace_name);
	puid(namespace_uuid);

	// compare this generated uuid, with the precalculated namespace id
	int f = uuid_compare(&namespace_uuid, &NameSpace_TEST);
	printf("Comparison between stored and generated Test Namespace = %d (should be 0)\r\n", f);

	// generate the derived namespace uuid
	uuid_t der_namespace_uuid;
	char * der_namespace_name = "Namespace Derived";
	uuid_create_sha1_from_name(&der_namespace_uuid, namespace_uuid, der_namespace_name, strlen(der_namespace_name));
	printf("Namespace based on [\"%s\"]: ", der_namespace_name);
	puid(der_namespace_uuid);

	// compare this generated uuid, with the precalculated namespace id
	f = uuid_compare(&der_namespace_uuid, &Namespace_DERIVED);
	printf("Comparison between stored and generated Derived Namespace = %d (should be 0)\r\n", f);

	// generate the device uuid, based on namespace uuid
	uuid_t device_uuid;
	char * device_name = "12345678";
	uuid_create_sha1_from_name(&device_uuid,der_namespace_uuid, device_name, strlen(device_name));
	printf("device uuid, based on [\"%s\"]: ",device_name);
	puid(device_uuid);
	return;
}



/* output:

NIL uuid: 00000000-0000-0000-0000-000000000000
Namespace based on ["Namespace Test"]: 73799fba-4f42-5715-8673-e428c44548d1
Comparison between stored and generated Test Namespace = 0 (should be 0)
Namespace based on ["Namespace Derived"]: bc5b4e99-1d5a-5294-97a9-4ea0ffb1de3b
Comparison between stored and generated Derived Namespace = 0 (should be 0)
device uuid, based on ["12345678"]: 101bdb0b-89dc-52db-835f-a866dd23214a

*/