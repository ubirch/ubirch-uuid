set(COMPONENT_SRCS
        ubirch_uuid.c
        )
set(COMPONENT_ADD_INCLUDEDIRS ".")

set(COMPONENT_PRIV_REQUIRES mbedtls)

register_component()
