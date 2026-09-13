// image offset 0x8327D4 address 7ff7a39c27d4

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a39c27b0(undefined8 param_1,longlong param_2,undefined8 param_3,undefined8 param_4)

{
  undefined1 auStack_38 [32];
  longlong local_18;
  ulonglong local_10;
  
  local_10 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_38;
  local_18 = param_2;
  FUN_7ff7a32cc480(*(undefined8 *)(param_2 + 0x30),param_4);
  FUN_7ff7a3bbc6f0(param_2 + 0x38);
  FUN_7ff7a3c04d10(param_2 + 0x38);
  return;
}

