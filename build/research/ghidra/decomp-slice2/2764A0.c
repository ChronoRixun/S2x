// image offset 0x2764A0 address 7ff7a34064a0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a34064a0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,
                     undefined4 param_5)

{
  int iVar1;
  undefined8 uVar2;
  undefined1 auStack_68 [32];
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  ulonglong local_30;

  local_30 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_68;
  iVar1 = FUN_7ff7a37e2250(param_2);
  if (iVar1 == 0) {
    uVar2 = FUN_7ff7a38fa3d0("Pawnable_Uniform_%X",param_2);
    FUN_7ff7a3408180(param_1,uVar2,param_4,param_3);
  }
  else {
    local_3c = param_5;
    local_40 = 2;
    local_38 = 0;
    local_48 = param_2;
    local_44 = param_3;
    FUN_7ff7a340bfe0(param_1,&local_48,1,param_4);
  }
  return;
}
