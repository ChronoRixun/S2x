// image offset 0x11F560 address 7ff7a32af560

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32af560(longlong param_1)

{
  int iVar1;
  ulonglong uVar2;
  int iVar3;
  ulonglong uVar4;
  float fVar5;
  undefined1 auStack_1c8 [32];
  undefined4 local_1a8 [100];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_1c8;
  if ((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) != 1
       ) || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) ||
     (iVar1 = FUN_7ff7a3468d90(param_1), iVar1 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar4 = 0;
  uVar2 = uVar4;
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar5 = (float)FUN_7ff7a3469aa0(param_1);
    uVar2 = (ulonglong)(uint)(int)fVar5;
  }
  iVar1 = FUN_7ff7a3404ec0(uVar2,local_1a8,0x32);
  FUN_7ff7a324d6e0(1,iVar1,0,param_1);
  if (0 < iVar1) {
    iVar3 = 1;
    do {
      FUN_7ff7a324d6e0(iVar3,0,2,DAT_7ff7a4d63d08);
      FUN_7ff7a325c510("itemID",local_1a8[uVar4 * 2],DAT_7ff7a4d63d08);
      FUN_7ff7a325c620("quantity",local_1a8[uVar4 * 2 + 1],DAT_7ff7a4d63d08);
      FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
      iVar3 = iVar3 + 1;
      uVar4 = uVar4 + 1;
    } while ((longlong)uVar4 < (longlong)iVar1);
  }
  return 1;
}

