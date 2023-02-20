/*!
 * @file test.c for uuid testing
 * all tests can be done online via https://www.uuidtools.com/v5
 */

#include "unity.h"
#include <string.h>
#include <esp_log.h>

#include "ubirch_uuid.h"

// test uuid
unsigned char test_UUID[16] = {0};
/* NILL UUID */
uuid_t nil_uuid = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
/* expected namespace UUID */
uuid_t exp_namespace_uuid = {
    0x73, 0x79, 0x9f, 0xba, 0x4f, 0x42, 0x57, 0x15, 0x86, 0x73, 0xe4, 0x28, 0xc4, 0x45, 0x48, 0xd1
};
char *exp_namespace_uuid_string = "73799fba-4f42-5715-8673-e428c44548d1";

/* expected device UUID */
uuid_t exp_device_uuid = {
    0xe9, 0x7e, 0xf8, 0x29, 0x65, 0xa8, 0x5a, 0x3c, 0xa6, 0x2a, 0x1a, 0x44, 0x06, 0x81, 0x31, 0x69
};
char *exp_device_uuid_string = "e97ef829-65a8-5a3c-a62a-1a4406813169";

/* expected derive namespace UUID */
uuid_t exp_der_namespace_uuid = {
    0xbc, 0x5b, 0x4e, 0x99, 0x1d, 0x5a, 0x52, 0x94, 0x97, 0xa9, 0x4e, 0xa0, 0xff, 0xb1, 0xde, 0x3b
};
char *exp_der_namespace_uuid_string = "bc5b4e99-1d5a-5294-97a9-4ea0ffb1de3b";

/* expected derived device UUID */
uuid_t exp_der_device_uuid = {
    0x10, 0x1b, 0xdb, 0x0b, 0x89, 0xdc, 0x52, 0xdb, 0x83, 0x5f, 0xa8, 0x66, 0xdd, 0x23, 0x21, 0x4a
};
char *exp_der_device_uuid_str = "101bdb0b-89dc-52db-835f-a866dd23214a";

// nil_uuid: 00000000-0000-0000-0000-000000000000
// Namespace based on ["Namespace Test"] = 73799fba-4f42-5715-8673-e428c44548d1
TEST_CASE("create namespace UUID and string", "[uuid handling]") {
    char charbuf[37]= { 0 };
    char *p_charbuf = charbuf;
    uuid_t namespace_uuid;
    char *namespace_name = "Namespace Test";

    uuid_create_sha1_from_name((uuid_t *)&namespace_uuid, nil_uuid, namespace_name, strlen(namespace_name));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(namespace_uuid, exp_namespace_uuid, UUID_SIZ);

    ubirch_uuid2str(namespace_uuid, &p_charbuf);
    printf("Namespace based on [\"%s\"] =  %s\n",namespace_name, charbuf);
    TEST_ASSERT_EQUAL_STRING(charbuf, exp_namespace_uuid_string);
}

// nil_uuid: 00000000-0000-0000-0000-000000000000
// Namespace based on ["Namespace Test"]: 73799fba-4f42-5715-8673-e428c44548d1
// device uuid, based on ["12345678"]: e97ef829-65a8-5a3c-a62a-1a4406813169
TEST_CASE("create UUID v5 based on namespace UUID", "[uuid handling]") {
    char charbuf[37]= { 0 };
    char *p_charbuf = charbuf;
    uuid_t namespace_uuid;
    char *namespace_name = "Namespace Test";

    uuid_t device_uuid;
    char *device_name = "12345678";
    
    uuid_create_sha1_from_name((uuid_t *)&namespace_uuid, nil_uuid, namespace_name, strlen(namespace_name));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(namespace_uuid, exp_namespace_uuid, UUID_SIZ);

    ubirch_uuid2str(namespace_uuid, &p_charbuf);
    printf("Namespace based on [\"%s\"] = %s\n",namespace_name, charbuf);
    TEST_ASSERT_EQUAL_STRING(charbuf, exp_namespace_uuid_string);
    
    uuid_create_sha1_from_name(&device_uuid,namespace_uuid,device_name,strlen(device_name));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(device_uuid, exp_device_uuid, UUID_SIZ);
    ubirch_uuid2str(device_uuid, &p_charbuf);
    printf("device uuid, based on [\"%s\"] = %s\n",device_name, charbuf);
    TEST_ASSERT_EQUAL_STRING(charbuf, exp_device_uuid_string);

}

// NIL uuid: 00000000-0000-0000-0000-000000000000
// Namespace based on ["Namespace Test"]: 73799fba-4f42-5715-8673-e428c44548d1
// Namespace based on ["Namespace Derived"]: bc5b4e99-1d5a-5294-97a9-4ea0ffb1de3b
// device uuid, based on ["12345678"]: 101bdb0b-89dc-52db-835f-a866dd23214a
TEST_CASE("create derived UUID v5 based on derived namespace UUID", "[uuid handling]") {
    char charbuf[37]= { 0 };
    char *p_charbuf = charbuf;
    uuid_t namespace_uuid;
    char *namespace_name = "Namespace Test";

    uuid_t der_namespace_uuid;
    char * der_namespace_name = "Namespace Derived";

    uuid_t der_device_uuid;
    char *device_name = "12345678";

    
    uuid_create_sha1_from_name((uuid_t *)&namespace_uuid, nil_uuid, namespace_name, strlen(namespace_name));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(namespace_uuid, exp_namespace_uuid, UUID_SIZ);

    ubirch_uuid2str(namespace_uuid, &p_charbuf);
    printf("Namespace based on [\"%s\"] = %s\n",namespace_name, charbuf);
    TEST_ASSERT_EQUAL_STRING(charbuf, exp_namespace_uuid_string);
    
    uuid_create_sha1_from_name(&der_namespace_uuid, namespace_uuid, der_namespace_name, strlen(der_namespace_name));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(der_namespace_uuid, exp_der_namespace_uuid, UUID_SIZ);
    ubirch_uuid2str(der_namespace_uuid, &p_charbuf);
    printf("Namespace based on [\"%s\"] = %s\n", der_namespace_name, charbuf);
    
    uuid_create_sha1_from_name(&der_device_uuid, der_namespace_uuid, device_name, strlen(device_name));
    TEST_ASSERT_EQUAL_UINT8_ARRAY(der_device_uuid, exp_der_device_uuid, UUID_SIZ);
    ubirch_uuid2str(der_device_uuid, &p_charbuf);
    printf("device uuid, based on [\"%s\"] = %s",device_name, charbuf);
    TEST_ASSERT_EQUAL_STRING(charbuf, exp_der_device_uuid_str);
}


