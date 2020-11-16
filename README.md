# UUID Version 5 Generator
This code allows you to generate UUIDs according to the [RFC4122](https://tools.ietf.org/html/rfc4122) on embedded devices.

## Single Namespace UUID
Based on a specific Namespace UUID, further device UUIDs can be generated, therefore:

- run the `uuid_test()` function from `utest.c`

The output should be:
```bash
NIL uuid: 00000000-0000-0000-0000-000000000000
Namespace based on ["Namespace Test"]: 73799fba-4f42-5715-8673-e428c44548d1
Comparison between stored and generated Test Namespace = 0 (should be 0)
device uuid, based on ["12345678"]: e97ef829-65a8-5a3c-a62a-1a4406813169
```

## Derived Namespace UUID
Based on a specific Namespace UUID, a derived Namespace UUID can be generated, from where further device UUIDs can be generated, therefore:

- run the `uuid_test_derived()` function from `utest.c`

The output should be:
```bash
NIL uuid: 00000000-0000-0000-0000-000000000000
Namespace based on ["Namespace Test"]: 73799fba-4f42-5715-8673-e428c44548d1
Comparison between stored and generated Test Namespace = 0 (should be 0)
Namespace based on ["Namespace Derived"]: bc5b4e99-1d5a-5294-97a9-4ea0ffb1de3b
Comparison between stored and generated Derived Namespace = 0 (should be 0)
device uuid, based on ["12345678"]: 101bdb0b-89dc-52db-835f-a866dd23214a
```

## Run on esp32

- Create a `CMakeLists.txt` with:
```cmake
set(COMPONENT_SRCS
        ubirch-uuid.c
        utest.c
        )
set(COMPONENT_ADD_INCLUDEDIRS ".")

set(COMPONENT_PRIV_REQUIRES mbedtls)

register_component()
```


