#ifndef __IOTS_MODULES_XX_MBEDTLS_CONFIG_H__
#define __IOTS_MODULES_XX_MBEDTLS_CONFIG_H__


#ifdef __cplusplus
extern "C" {
#endif

/* mbed base system support */
#define MBEDTLS_HAVE_ASM
#define MBEDTLS_NO_PLATFORM_ENTROPY
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_CTR_DRBG_C

/* mbed SHA support */
#define MBEDTLS_SHA256_C

/* mbed RSA support */
#define MBEDTLS_AES_C
#define MBEDTLS_PK_C
#define MBEDTLS_GENPRIME
#define MBEDTLS_OID_C
#define MBEDTLS_RSA_C
#define MBEDTLS_PKCS1_V15
#define MBEDTLS_PKCS1_V21

#define MBEDTLS_ECDSA_C
#define MBEDTLS_PK_CAN_ECDSA_SIGN
#define MBEDTLS_PK_CAN_ECDSA_VERIFY

/* ECP options */
#define MBEDTLS_ECP_C
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED

/* For test certificates */
#define MBEDTLS_BASE64_C
#define MBEDTLS_PK_WRITE_C
#define MBEDTLS_PEM_WRITE_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_PEM_PARSE_C

/* Error string support for debugging */
#define MBEDTLS_ERROR_C
#define MBEDTLS_NO_PLATFORM_ENTROPY
#define MBEDTLS_NO_DEFAULT_ENTROPY_SOURCES

/* 2048-bit RSA Key: The encrypted data will always be 256 bytes long */
#define MBEDTLS_MPI_MAX_SIZE 256

#ifdef __cplusplus
}
#endif

#endif /* __IOTS_MODULES_XX_MBEDTLS_CONFIG_H__ */

