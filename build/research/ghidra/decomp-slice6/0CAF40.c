// image offset 0xCAF40 address 7ff7a325af40

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a325af40(undefined8 param_1,undefined4 param_2)

{
  longlong lVar1;
  longlong lVar2;
  undefined1 auStack_48 [32];
  char local_28 [16];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_48;
  snprintf(local_28,0xb,&DAT_7ff7a3cc62d4,param_2);
  lVar2 = -1;
  do {
    lVar1 = lVar2 + 1;
    lVar2 = lVar2 + 1;
  } while (local_28[lVar1] != '\0');
  FUN_7ff7a3294620(param_1,local_28);
  return;
}

