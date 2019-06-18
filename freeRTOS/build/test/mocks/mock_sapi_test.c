/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "mock_sapi_test.h"

static const char* CMockString_gpioRead = "gpioRead";
static const char* CMockString_gpioWrite = "gpioWrite";
static const char* CMockString_isHigh = "isHigh";
static const char* CMockString_pin = "pin";
static const char* CMockString_value = "value";

typedef struct _CMOCK_gpioWrite_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  bool_t ReturnVal;
  int CallOrder;
  gpioMap_t Expected_pin;
  bool_t Expected_value;

} CMOCK_gpioWrite_CALL_INSTANCE;

typedef struct _CMOCK_gpioRead_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  bool_t ReturnVal;
  int CallOrder;
  gpioMap_t Expected_pin;

} CMOCK_gpioRead_CALL_INSTANCE;

typedef struct _CMOCK_isHigh_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  bool_t ReturnVal;
  int CallOrder;
  gpioMap_t Expected_pin;

} CMOCK_isHigh_CALL_INSTANCE;

static struct mock_sapi_testInstance
{
  int gpioWrite_IgnoreBool;
  bool_t gpioWrite_FinalReturn;
  CMOCK_gpioWrite_CALLBACK gpioWrite_CallbackFunctionPointer;
  int gpioWrite_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE gpioWrite_CallInstance;
  int gpioRead_IgnoreBool;
  bool_t gpioRead_FinalReturn;
  CMOCK_gpioRead_CALLBACK gpioRead_CallbackFunctionPointer;
  int gpioRead_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE gpioRead_CallInstance;
  int isHigh_IgnoreBool;
  bool_t isHigh_FinalReturn;
  CMOCK_isHigh_CALLBACK isHigh_CallbackFunctionPointer;
  int isHigh_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE isHigh_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_sapi_test_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  if (Mock.gpioWrite_IgnoreBool)
    Mock.gpioWrite_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_gpioWrite);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.gpioWrite_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.gpioWrite_CallbackFunctionPointer != NULL)
    Mock.gpioWrite_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.gpioRead_IgnoreBool)
    Mock.gpioRead_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_gpioRead);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.gpioRead_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.gpioRead_CallbackFunctionPointer != NULL)
    Mock.gpioRead_CallInstance = CMOCK_GUTS_NONE;
  if (Mock.isHigh_IgnoreBool)
    Mock.isHigh_CallInstance = CMOCK_GUTS_NONE;
  UNITY_SET_DETAIL(CMockString_isHigh);
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.isHigh_CallInstance, cmock_line, CMockStringCalledLess);
  if (Mock.isHigh_CallbackFunctionPointer != NULL)
    Mock.isHigh_CallInstance = CMOCK_GUTS_NONE;
}

void mock_sapi_test_Init(void)
{
  mock_sapi_test_Destroy();
}

void mock_sapi_test_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  Mock.gpioWrite_CallbackFunctionPointer = NULL;
  Mock.gpioWrite_CallbackCalls = 0;
  Mock.gpioRead_CallbackFunctionPointer = NULL;
  Mock.gpioRead_CallbackCalls = 0;
  Mock.isHigh_CallbackFunctionPointer = NULL;
  Mock.isHigh_CallbackCalls = 0;
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

bool_t gpioWrite(gpioMap_t pin, bool_t value)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_gpioWrite_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_gpioWrite);
  cmock_call_instance = (CMOCK_gpioWrite_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.gpioWrite_CallInstance);
  Mock.gpioWrite_CallInstance = CMock_Guts_MemNext(Mock.gpioWrite_CallInstance);
  if (Mock.gpioWrite_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.gpioWrite_FinalReturn;
    Mock.gpioWrite_FinalReturn = cmock_call_instance->ReturnVal;
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.gpioWrite_CallbackFunctionPointer != NULL)
  {
    return Mock.gpioWrite_CallbackFunctionPointer(pin, value, Mock.gpioWrite_CallbackCalls++);
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  {
    UNITY_SET_DETAILS(CMockString_gpioWrite,CMockString_pin);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_pin), (void*)(&pin), sizeof(gpioMap_t), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_gpioWrite,CMockString_value);
    UNITY_TEST_ASSERT_EQUAL_UINT8(cmock_call_instance->Expected_value, value, cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_gpioWrite(CMOCK_gpioWrite_CALL_INSTANCE* cmock_call_instance, gpioMap_t pin, bool_t value)
{
  memcpy(&cmock_call_instance->Expected_pin, &pin, sizeof(gpioMap_t));
  cmock_call_instance->Expected_value = value;
}

void gpioWrite_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_gpioWrite_CALL_INSTANCE));
  CMOCK_gpioWrite_CALL_INSTANCE* cmock_call_instance = (CMOCK_gpioWrite_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.gpioWrite_CallInstance = CMock_Guts_MemChain(Mock.gpioWrite_CallInstance, cmock_guts_index);
  Mock.gpioWrite_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.gpioWrite_IgnoreBool = (int)1;
}

void gpioWrite_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, gpioMap_t pin, bool_t value, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_gpioWrite_CALL_INSTANCE));
  CMOCK_gpioWrite_CALL_INSTANCE* cmock_call_instance = (CMOCK_gpioWrite_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.gpioWrite_CallInstance = CMock_Guts_MemChain(Mock.gpioWrite_CallInstance, cmock_guts_index);
  Mock.gpioWrite_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  CMockExpectParameters_gpioWrite(cmock_call_instance, pin, value);
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

void gpioWrite_StubWithCallback(CMOCK_gpioWrite_CALLBACK Callback)
{
  Mock.gpioWrite_IgnoreBool = (int)0;
  Mock.gpioWrite_CallbackFunctionPointer = Callback;
}

bool_t gpioRead(gpioMap_t pin)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_gpioRead_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_gpioRead);
  cmock_call_instance = (CMOCK_gpioRead_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.gpioRead_CallInstance);
  Mock.gpioRead_CallInstance = CMock_Guts_MemNext(Mock.gpioRead_CallInstance);
  if (Mock.gpioRead_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.gpioRead_FinalReturn;
    Mock.gpioRead_FinalReturn = cmock_call_instance->ReturnVal;
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.gpioRead_CallbackFunctionPointer != NULL)
  {
    return Mock.gpioRead_CallbackFunctionPointer(pin, Mock.gpioRead_CallbackCalls++);
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  {
    UNITY_SET_DETAILS(CMockString_gpioRead,CMockString_pin);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_pin), (void*)(&pin), sizeof(gpioMap_t), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_gpioRead(CMOCK_gpioRead_CALL_INSTANCE* cmock_call_instance, gpioMap_t pin)
{
  memcpy(&cmock_call_instance->Expected_pin, &pin, sizeof(gpioMap_t));
}

void gpioRead_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_gpioRead_CALL_INSTANCE));
  CMOCK_gpioRead_CALL_INSTANCE* cmock_call_instance = (CMOCK_gpioRead_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.gpioRead_CallInstance = CMock_Guts_MemChain(Mock.gpioRead_CallInstance, cmock_guts_index);
  Mock.gpioRead_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.gpioRead_IgnoreBool = (int)1;
}

void gpioRead_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, gpioMap_t pin, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_gpioRead_CALL_INSTANCE));
  CMOCK_gpioRead_CALL_INSTANCE* cmock_call_instance = (CMOCK_gpioRead_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.gpioRead_CallInstance = CMock_Guts_MemChain(Mock.gpioRead_CallInstance, cmock_guts_index);
  Mock.gpioRead_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  CMockExpectParameters_gpioRead(cmock_call_instance, pin);
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

void gpioRead_StubWithCallback(CMOCK_gpioRead_CALLBACK Callback)
{
  Mock.gpioRead_IgnoreBool = (int)0;
  Mock.gpioRead_CallbackFunctionPointer = Callback;
}

bool_t isHigh(gpioMap_t pin)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_isHigh_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_isHigh);
  cmock_call_instance = (CMOCK_isHigh_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.isHigh_CallInstance);
  Mock.isHigh_CallInstance = CMock_Guts_MemNext(Mock.isHigh_CallInstance);
  if (Mock.isHigh_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.isHigh_FinalReturn;
    Mock.isHigh_FinalReturn = cmock_call_instance->ReturnVal;
    return cmock_call_instance->ReturnVal;
  }
  if (Mock.isHigh_CallbackFunctionPointer != NULL)
  {
    return Mock.isHigh_CallbackFunctionPointer(pin, Mock.isHigh_CallbackCalls++);
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  {
    UNITY_SET_DETAILS(CMockString_isHigh,CMockString_pin);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_pin), (void*)(&pin), sizeof(gpioMap_t), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_isHigh(CMOCK_isHigh_CALL_INSTANCE* cmock_call_instance, gpioMap_t pin)
{
  memcpy(&cmock_call_instance->Expected_pin, &pin, sizeof(gpioMap_t));
}

void isHigh_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_isHigh_CALL_INSTANCE));
  CMOCK_isHigh_CALL_INSTANCE* cmock_call_instance = (CMOCK_isHigh_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.isHigh_CallInstance = CMock_Guts_MemChain(Mock.isHigh_CallInstance, cmock_guts_index);
  Mock.isHigh_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.isHigh_IgnoreBool = (int)1;
}

void isHigh_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, gpioMap_t pin, bool_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_isHigh_CALL_INSTANCE));
  CMOCK_isHigh_CALL_INSTANCE* cmock_call_instance = (CMOCK_isHigh_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.isHigh_CallInstance = CMock_Guts_MemChain(Mock.isHigh_CallInstance, cmock_guts_index);
  Mock.isHigh_IgnoreBool = (int)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  CMockExpectParameters_isHigh(cmock_call_instance, pin);
  cmock_call_instance->ReturnVal = cmock_to_return;
  UNITY_CLR_DETAILS();
}

void isHigh_StubWithCallback(CMOCK_isHigh_CALLBACK Callback)
{
  Mock.isHigh_IgnoreBool = (int)0;
  Mock.isHigh_CallbackFunctionPointer = Callback;
}

