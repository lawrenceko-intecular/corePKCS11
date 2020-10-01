/*
 * corePKCS11 V2.0.0
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/* C runtime includes. */
#include <stdlib.h>
#include <stdbool.h>

/* Test includes. */
#include "unity.h"

/* Library includes. */
#include "iot_pki_utils.h"

/*******************************************************************************
 * Unity fixtures
 ******************************************************************************/
void setUp( void )
{
}

/* called before each testcase */
void tearDown( void )
{
}

/* called at the beginning of the whole suite */
void suiteSetUp()
{
}

/* called at the end of the whole suite */
int suiteTearDown( int numFailures )
{
    return numFailures;
}

/* ======================  TESTING PKI_mbedTLSSignatureToPkcs11Signature  ============================ */

/*!
 * @brief PKI_mbedTLSSignatureToPkcs11Signature happy path.
 *
 */
void test_PKI_mbedTLSSignatureToPkcs11Signature( void )
{
    int32_t xResult = 0;
    uint8_t pucKnownSignature[] =
    {
        0x30, 0x45, 0x2,  0x20, 0x5a, 0x88, 0x7f,
        0x8c, 0x15, 0xea, 0xe6, 0x41, 0x26, 0xe5,
        0x65, 0x28, 0xc5, 0xb7, 0x7c, 0x3a, 0x8d,
        0xf3, 0x2c, 0x2e, 0xb3, 0x5c, 0xbc, 0xfd,
        0xd5, 0xdb, 0x32, 0x20, 0x88, 0xb4, 0x5b,
        0x54, 0x2,  0x21, 0x0,  0xf9, 0xf7, 0xaf,
        0x21, 0x36, 0x1e, 0x5c, 0xa3, 0xa6, 0x88,
        0x43, 0x19, 0xa7, 0x3e, 0xbe, 0xfb, 0x4d,
        0x26, 0xb6, 0x91, 0xe0, 0xc,  0x50, 0xe8,
        0x1f, 0x97, 0xe1, 0xaf, 0x3c, 0xab, 0x85,
        0xfd, 0x0,  0x0,  0x0
    };


    uint8_t pucExpectedSignature[] =
    {
        0x5a, 0x88, 0x7f, 0x8c, 0x15, 0xea, 0xe6,
        0x41, 0x26, 0xe5, 0x65, 0x28, 0xc5, 0xb7,
        0x7c, 0x3a, 0x8d, 0xf3, 0x2c, 0x2e, 0xb3,
        0x5c, 0xbc, 0xfd, 0xd5, 0xdb, 0x32, 0x20,
        0x88, 0xb4, 0x5b, 0x54, 0xf9, 0xf7, 0xaf,
        0x21, 0x36, 0x1e, 0x5c, 0xa3, 0xa6, 0x88,
        0x43, 0x19, 0xa7, 0x3e, 0xbe, 0xfb, 0x4d,
        0x26, 0xb6, 0x91, 0xe0, 0xc,  0x50, 0xe8,
        0x1f, 0x97, 0xe1, 0xaf, 0x3c, 0xab, 0x85,
        0xfd
    };


    uint8_t pucConversionBuffer[ sizeof( pucExpectedSignature ) ] = { 0 };

    xResult = PKI_mbedTLSSignatureToPkcs11Signature( pucConversionBuffer, pucKnownSignature );
    TEST_ASSERT_EQUAL( 0, xResult );
    TEST_ASSERT_EQUAL_MEMORY( pucExpectedSignature, pucConversionBuffer,
                              sizeof( pucExpectedSignature ) );
}

/*!
 * @brief PKI_mbedTLSSignatureToPkcs11Signature test converting an R component
 * with 0 padding.
 *
 * R components are represented by mbedTLS as 33 bytes when the first bit is
 * zero to avoid any sign confusion.
 */
void test_PKI_mbedTLSSignatureToPkcs11SignatureRConversion( void )
{
    int32_t xResult = 0;
    uint8_t pucKnownSignature[] =
    {
        0x30, 0x45, 0x2,  0x21, 0x5a, 0x88, 0x7f,
        0x8c, 0x15, 0xea, 0xe6, 0x41, 0x26, 0xe5,
        0x65, 0x28, 0xc5, 0xb7, 0x7c, 0x3a, 0x8d,
        0xf3, 0x2c, 0x2e, 0xb3, 0x5c, 0xbc, 0xfd,
        0xd5, 0xdb, 0x32, 0x20, 0x88, 0xb4, 0x5b,
        0x54, 0x2,  0x21, 0x0,  0xf9, 0xf7, 0xaf,
        0x21, 0x36, 0x1e, 0x5c, 0xa3, 0xa6, 0x88,
        0x43, 0x19, 0xa7, 0x3e, 0xbe, 0xfb, 0x4d,
        0x26, 0xb6, 0x91, 0xe0, 0xc,  0x50, 0xe8,
        0x1f, 0x97, 0xe1, 0xaf, 0x3c, 0xab, 0x85,
        0xfd, 0x0,  0x0,  0x0
    };


    uint8_t pucExpectedSignature[] =
    {
        0x88, 0x7f, 0x8c, 0x15, 0xea, 0xe6, 0x41,
        0x26, 0xe5, 0x65, 0x28, 0xc5, 0xb7, 0x7c,
        0x3a, 0x8d, 0xf3, 0x2c, 0x2e, 0xb3, 0x5c,
        0xbc, 0xfd, 0xd5, 0xdb, 0x32, 0x20, 0x88,
        0xb4, 0x5b, 0x54, 0x2,  0x0,  0x0,  0x0, 0x0,
        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0, 0x0,
        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0, 0x0,
        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0, 0x0,
        0x0,  0x0,  0x0,  0x0
    };


    uint8_t pucConversionBuffer[ sizeof( pucExpectedSignature ) ] = { 0 };

    xResult = PKI_mbedTLSSignatureToPkcs11Signature( pucConversionBuffer, pucKnownSignature );
    TEST_ASSERT_EQUAL( 0, xResult );
    TEST_ASSERT_EQUAL_MEMORY( pucExpectedSignature, pucConversionBuffer,
                              sizeof( pucExpectedSignature ) );
}

/*!
 * @brief PKI_mbedTLSSignatureToPkcs11Signature test converting an S component
 * that is less than 33 bytes.
 *
 * If the S component is less than 32 bytes we pad with 0's.
 *
 */
void test_PKI_mbedTLSSignatureToPkcs11SignatureSConversion( void )
{
    int32_t xResult = 0;
    uint8_t pucKnownSignature[] =
    {
        0x30, 0x45, 0x2,  0x21, 0x5a, 0x88, 0x7f,
        0x8c, 0x15, 0xea, 0xe6, 0x41, 0x26, 0xe5,
        0x65, 0x28, 0xc5, 0xb7, 0x7c, 0x3a, 0x8d,
        0xf3, 0x2c, 0x2e, 0xb3, 0x5c, 0xbc, 0xfd,
        0xd5, 0xdb, 0x32, 0x1F, 0x88, 0xb4, 0x5b,
        0x54, 0x2,  0x21, 0x0,  0xf9, 0xf7, 0xaf,
        0x21, 0x36, 0x1e, 0x5c, 0xa3, 0xa6, 0x88,
        0x43, 0x19, 0xa7, 0x3e, 0xbe, 0xfb, 0x4d,
        0x26, 0xb6, 0x91, 0xe0, 0xc,  0x50, 0xe8,
        0x1f, 0x97, 0xe1, 0xaf, 0x3c, 0xab, 0x85,
        0xfd, 0x0,  0x0,  0x0
    };


    uint8_t pucExpectedSignature[] =
    {
        0x88, 0x7f, 0x8c, 0x15, 0xea, 0xe6, 0x41,
        0x26, 0xe5, 0x65, 0x28, 0xc5, 0xb7, 0x7c,
        0x3a, 0x8d, 0xf3, 0x2c, 0x2e, 0xb3, 0x5c,
        0xbc, 0xfd, 0xd5, 0xdb, 0x32, 0x1f, 0x88,
        0xb4, 0x5b, 0x54, 0x2,  0x0,  0x0,  0x0, 0x0,
        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0, 0x0,
        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0, 0x0,
        0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0, 0x0,
        0x0,  0x0,  0x0,  0x0
    };


    uint8_t pucConversionBuffer[ sizeof( pucExpectedSignature ) ] = { 0 };

    xResult = PKI_mbedTLSSignatureToPkcs11Signature( pucConversionBuffer, pucKnownSignature );
    TEST_ASSERT_EQUAL( 0, xResult );
    TEST_ASSERT_EQUAL_MEMORY( pucExpectedSignature, pucConversionBuffer,
                              sizeof( pucExpectedSignature ) );
}

/*!
 * @brief PKI_mbedTLSSignatureToPkcs11Signature NULL params.
 *
 */
void test_PKI_mbedTLSSignatureToPkcs11SignatureNull( void )
{
    int32_t xResult = 0;
    uint8_t pucKnownSignature[] = { 0xAA };

    xResult = PKI_mbedTLSSignatureToPkcs11Signature( NULL, pucKnownSignature );
    TEST_ASSERT_EQUAL( -1, xResult );

    xResult = PKI_mbedTLSSignatureToPkcs11Signature( pucKnownSignature, NULL );
    TEST_ASSERT_EQUAL( -1, xResult );

    xResult = PKI_mbedTLSSignatureToPkcs11Signature( NULL, NULL );
    TEST_ASSERT_EQUAL( -1, xResult );
}

/* ======================  TESTING PKI_pkcs11SignatureTombedTLSSignature  ============================ */

/*!
 * @brief PKI_pkcs11SignatureTombedTLSSignature happy path.
 *
 */
void test_PKI_pkcs11SignatureTombedTLSSignature( void )
{
    int32_t xResult = 0;
    uint8_t pucBeforeSignature[] =
    {
        0xb6, 0xd0, 0x4,  0x23, 0x1c, 0xef, 0x7f,
        0xfe, 0xf4, 0x10, 0x10, 0xbe, 0x43, 0x26,
        0x16, 0x7,  0xe3, 0xbe, 0xc6, 0x1e, 0x48,
        0xf8, 0xfd, 0x7a, 0xf3, 0x12, 0x4f, 0x1a,
        0x1d, 0x4f, 0x44, 0xa0, 0xd1, 0xef, 0xb3,
        0xb0, 0xda, 0x4e, 0xfd, 0x5,  0xa1, 0xb6,
        0x64, 0xfb, 0xa5, 0x36, 0x59, 0xe0, 0xc8,
        0x3a, 0xfe, 0x21, 0x88, 0x32, 0xc7, 0xa0,
        0x3e, 0xf3, 0x43, 0x6d, 0xfa, 0x34, 0x9e,
        0xd6, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
        0x0,  0x0
    };

    uint8_t pucAfterSignature[] =
    {
        0x30, 0x46, 0x2,  0x21, 0x0,  0xb6, 0xd0,
        0x4,  0x23, 0x1c, 0xef, 0x7f, 0xfe, 0xf4,
        0x10, 0x10, 0xbe, 0x43, 0x26, 0x16, 0x7,
        0xe3, 0xbe, 0xc6, 0x1e, 0x48, 0xf8, 0xfd,
        0x7a, 0xf3, 0x12, 0x4f, 0x1a, 0x1d, 0x4f,
        0x44, 0xa0, 0x2,  0x21, 0x0,  0xd1, 0xef,
        0xb3, 0xb0, 0xda, 0x4e, 0xfd, 0x5,  0xa1,
        0xb6, 0x64, 0xfb, 0xa5, 0x36, 0x59, 0xe0,
        0xc8, 0x3a, 0xfe, 0x21, 0x88, 0x32, 0xc7,
        0xa0, 0x3e, 0xf3, 0x43, 0x6d, 0xfa, 0x34,
        0x9e, 0xd6
    };
    size_t ulSignLen = 0;

    xResult = PKI_pkcs11SignatureTombedTLSSignature( pucBeforeSignature, &ulSignLen );
    TEST_ASSERT_EQUAL( 0, xResult );
    TEST_ASSERT_EQUAL_MEMORY( pucBeforeSignature, pucAfterSignature,
                              ulSignLen );
}

/*!
 * @brief PKI_pkcs11SignatureTombedTLSSignature convert an R component that has
 * a leading 0 in the size byte.
 *
 */
void test_PKI_pkcs11SignatureTombedTLSSignatureRComponent0( void )
{
    int32_t xResult = 0;
    uint8_t pucBeforeSignature[] =
    {
        0x36, 0xd0, 0x4,  0x23, 0x1c, 0xef, 0x7f,
        0xfe, 0xf4, 0x10, 0x10, 0xbe, 0x43, 0x26,
        0x16, 0x7,  0xe3, 0xbe, 0xc6, 0x1e, 0x48,
        0xf8, 0xfd, 0x7a, 0xf3, 0x12, 0x4f, 0x1a,
        0x1d, 0x4f, 0x44, 0xa0, 0xd1, 0xef, 0xb3,
        0xb0, 0xda, 0x4e, 0xfd, 0x5,  0xa1, 0xb6,
        0x64, 0xfb, 0xa5, 0x36, 0x59, 0xe0, 0xc8,
        0x3a, 0xfe, 0x21, 0x88, 0x32, 0xc7, 0xa0,
        0x3e, 0xf3, 0x43, 0x6d, 0xfa, 0x34, 0x9e,
        0xd6, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
        0x0,  0x0
    };

    uint8_t pucAfterSignature[] =
    {
        0x30, 0x45, 0x2,  0x20, 0x36, 0xd0, 0x4,
        0x23, 0x1c, 0xef, 0x7f, 0xfe, 0xf4, 0x10,
        0x10, 0xbe, 0x43, 0x26, 0x16, 0x7,  0xe3,
        0xbe, 0xc6, 0x1e, 0x48, 0xf8, 0xfd, 0x7a,
        0xf3, 0x12, 0x4f, 0x1a, 0x1d, 0x4f, 0x44,
        0xa0, 0x2,  0x21, 0x0,  0xd1, 0xef, 0xb3,
        0xb0, 0xda, 0x4e, 0xfd, 0x5,  0xa1, 0xb6,
        0x64, 0xfb, 0xa5, 0x36, 0x59, 0xe0, 0xc8,
        0x3a, 0xfe, 0x21, 0x88, 0x32, 0xc7, 0xa0,
        0x3e, 0xf3, 0x43, 0x6d, 0xfa, 0x34, 0x9e,
        0xd6, 0x0
    };
    size_t ulSignLen = 0;

    xResult = PKI_pkcs11SignatureTombedTLSSignature( pucBeforeSignature, &ulSignLen );
    TEST_ASSERT_EQUAL( 0, xResult );
    TEST_ASSERT_EQUAL_MEMORY( pucBeforeSignature, pucAfterSignature,
                              ulSignLen );
}

/*!
 * @brief PKI_pkcs11SignatureTombedTLSSignature convert an S component that has
 * a leading 0 in the size byte.
 *
 */
void test_PKI_pkcs11SignatureTombedTLSSignatureSComponent0( void )
{
    int32_t xResult = 0;
    uint8_t pucBeforeSignature[] =
    {
        0xb6, 0xd0, 0x4,  0x23, 0x1c, 0xef, 0x7f,
        0xfe, 0xf4, 0x10, 0x10, 0xbe, 0x43, 0x26,
        0x16, 0x7,  0xe3, 0xbe, 0xc6, 0x1e, 0x48,
        0xf8, 0xfd, 0x7a, 0xf3, 0x12, 0x4f, 0x1a,
        0x1d, 0x4f, 0x44, 0xa0, 0x51, 0x3f, 0xb3,
        0xb0, 0xda, 0x4e, 0xfd, 0x5,  0xa1, 0xb6,
        0x64, 0xfb, 0xa5, 0x36, 0x59, 0xe0, 0xc8,
        0x3a, 0xfe, 0x21, 0x88, 0x32, 0xc7, 0xa0,
        0x3e, 0xf3, 0x43, 0x6d, 0xfa, 0x34, 0x9e,
        0xd6, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,
        0x0,  0x0
    };

    uint8_t pucAfterSignature[] =
    {
        0x30, 0x45, 0x2,  0x21, 0x0,  0xb6, 0xd0, 0x4,
        0x23, 0x1c, 0xef, 0x7f, 0xfe, 0xf4, 0x10,
        0x10, 0xbe, 0x43, 0x26, 0x16, 0x7,  0xe3,
        0xbe, 0xc6, 0x1e, 0x48, 0xf8, 0xfd, 0x7a,
        0xf3, 0x12, 0x4f, 0x1a, 0x1d, 0x4f, 0x44,
        0xa0, 0x2,  0x20, 0x51, 0x3f, 0xb3, 0xb0,
        0xda, 0x4e, 0xfd, 0x5,  0xa1, 0xb6, 0x64,
        0xfb, 0xa5, 0x36, 0x59, 0xe0, 0xc8, 0x3a,
        0xfe, 0x21, 0x88, 0x32, 0xc7, 0xa0, 0x3e,
        0xf3, 0x43, 0x6d, 0xfa, 0x34, 0x9e, 0xd6
    };
    size_t ulSignLen = 0;

    xResult = PKI_pkcs11SignatureTombedTLSSignature( pucBeforeSignature, &ulSignLen );
    TEST_ASSERT_EQUAL( 0, xResult );
    TEST_ASSERT_EQUAL_MEMORY( pucBeforeSignature, pucAfterSignature,
                              ulSignLen );
}

/*!
 * @brief PKI_pkcs11SignatureTombedTLSSignature NULL params.
 *
 */
void test_PKI_pkcs11SignatureTombedTLSSignatureNull( void )
{
    int32_t xResult = 0;
    size_t xLen = 0;
    uint8_t pucKnownSignature[] = { 0xAA };

    xResult = PKI_pkcs11SignatureTombedTLSSignature( NULL, &xLen );
    TEST_ASSERT_EQUAL( -1, xResult );

    xResult = PKI_pkcs11SignatureTombedTLSSignature( pucKnownSignature, NULL );
    TEST_ASSERT_EQUAL( -1, xResult );

    xResult = PKI_pkcs11SignatureTombedTLSSignature( NULL, NULL );
    TEST_ASSERT_EQUAL( -1, xResult );
}
