// image offset 0x8390A0 address 7ff7a39c90a0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a39c90a0(undefined8 param_1)

{
  __time64_t _Var1;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  longlong local_20;
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_48;
  _Var1 = _time64((__time64_t *)0x0);
  local_28 = FUN_7ff7a3941220();
  local_20 = _Var1 * 1000;
  FUN_7ff7a3c051f0(&local_28,0x10,param_1);
  return;
}

