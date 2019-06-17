/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_UART_H
#define _MOCK_UART_H

#include "uart.h"

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

void mock_uart_Init(void);
void mock_uart_Destroy(void);
void mock_uart_Verify(void);




#define sendUart_IgnoreAndReturn(cmock_retval) sendUart_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void sendUart_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, int cmock_to_return);
#define sendUart_ExpectAndReturn(cmock_arg1, cmock_arg2, cmock_retval) sendUart_CMockExpectAndReturn(__LINE__, cmock_arg1, cmock_arg2, cmock_retval)
void sendUart_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, char* cmock_arg1, char* cmock_arg2, int cmock_to_return);
typedef int (* CMOCK_sendUart_CALLBACK)(char* cmock_arg1, char* cmock_arg2, int cmock_num_calls);
void sendUart_StubWithCallback(CMOCK_sendUart_CALLBACK Callback);

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif