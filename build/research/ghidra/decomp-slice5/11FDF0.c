// image offset 0x11FDF0 address 7ff7a32afdf0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32afdf0(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  longlong lVar5;
  ulonglong uVar6;
  int iVar7;
  longlong lVar8;
  float fVar9;
  undefined1 auStack_78 [32];
  int local_58;
  undefined1 local_48 [32];
  ulonglong local_28;
  
  local_28 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_78;
  iVar4 = 0;
  if ((2 < (int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4))
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar2 = FUN_7ff7a3468d90(param_1);
    if (iVar2 != 0) {
      iVar2 = thunk_FUN_7ff7a3294bb0(param_1,2);
      if ((iVar2 != 0) && (*(longlong *)(param_1 + 0x50) + 0x20U < *(ulonglong *)(param_1 + 0x48)))
      {
        iVar2 = FUN_7ff7a3468d90(param_1);
        if (iVar2 != 0) goto LAB_7ff7a32afe76;
      }
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32afe76:
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar9 = (float)FUN_7ff7a3469aa0(param_1);
    iVar2 = (int)fVar9;
  }
  else {
    iVar2 = 0;
  }
  uVar3 = FUN_7ff7a325cb30(param_1,2);
  lVar5 = *(longlong *)(param_1 + 0x50);
  uVar6 = *(ulonglong *)(param_1 + 0x48);
  if (lVar5 + 0x20U < uVar6) {
    fVar9 = (float)FUN_7ff7a3469aa0(param_1,lVar5 + 0x20U);
    uVar6 = *(ulonglong *)(param_1 + 0x48);
    lVar5 = *(longlong *)(param_1 + 0x50);
    iVar7 = (int)fVar9;
  }
  else {
    iVar7 = 0;
  }
  local_58 = 0;
  if (((int)((longlong)(uVar6 - lVar5) >> 4) == 4) && (local_58 = iVar4, lVar5 + 0x30U < uVar6)) {
    iVar4 = FUN_7ff7a3468d90(param_1);
    if ((iVar4 != 0) && (*(longlong *)(param_1 + 0x50) + 0x30U < *(ulonglong *)(param_1 + 0x48))) {
      fVar9 = (float)FUN_7ff7a3469aa0(param_1);
      local_58 = (int)fVar9;
    }
  }
  FUN_7ff7a3406580(iVar2,uVar3,iVar7,local_48);
  lVar5 = FUN_7ff7a39c9020(local_48);
  if (lVar5 == 0) {
    puVar1 = *(undefined4 **)(param_1 + 0x48);
    *puVar1 = 0;
    *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  }
  else {
    lVar8 = -1;
    do {
      lVar8 = lVar8 + 1;
    } while (*(char *)(lVar5 + lVar8) != '\0');
    FUN_7ff7a3294620(param_1,lVar5);
  }
  return 1;
}

