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

#ifndef UUID_UTEST_H
#define UUID_UTEST_H

/*!
 * Generate UUID based on one namespace
 */
void uuid_test(void);

/*!
 * Generate UUID based on namespace and derived namespace
 */
void uuid_test_derived(void);

#endif // UUID_UTEST_H
