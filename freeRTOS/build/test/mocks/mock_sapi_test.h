/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_SAPI_TEST_H
#define _MOCK_SAPI_TEST_H

#include "sapi_test.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void mock_sapi_test_Init(void);
void mock_sapi_test_Destroy(void);
void mock_sapi_test_Verify(void);




#define gpioWrite_IgnoreAndReturn(cmock_retval) gpioWrite_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void gpioWrite_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return);
#define gpioWrite_ExpectAndReturn(pin, value, cmock_retval) gpioWrite_CMockExpectAndReturn(__LINE__, pin, value, cmock_retval)
void gpioWrite_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, gpioMap_t pin, bool_t value, bool_t cmock_to_return);
typedef bool_t (* CMOCK_gpioWrite_CALLBACK)(gpioMap_t pin, bool_t value, int cmock_num_calls);
void gpioWrite_StubWithCallback(CMOCK_gpioWrite_CALLBACK Callback);
#define gpioRead_IgnoreAndReturn(cmock_retval) gpioRead_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void gpioRead_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return);
#define gpioRead_ExpectAndReturn(pin, cmock_retval) gpioRead_CMockExpectAndReturn(__LINE__, pin, cmock_retval)
void gpioRead_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, gpioMap_t pin, bool_t cmock_to_return);
typedef bool_t (* CMOCK_gpioRead_CALLBACK)(gpioMap_t pin, int cmock_num_calls);
void gpioRead_StubWithCallback(CMOCK_gpioRead_CALLBACK Callback);
#define isHigh_IgnoreAndReturn(cmock_retval) isHigh_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void isHigh_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return);
#define isHigh_ExpectAndReturn(pin, cmock_retval) isHigh_CMockExpectAndReturn(__LINE__, pin, cmock_retval)
void isHigh_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, gpioMap_t pin, bool_t cmock_to_return);
typedef bool_t (* CMOCK_isHigh_CALLBACK)(gpioMap_t pin, int cmock_num_calls);
void isHigh_StubWithCallback(CMOCK_isHigh_CALLBACK Callback);

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
