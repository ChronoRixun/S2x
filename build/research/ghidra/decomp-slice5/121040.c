// image offset 0x121040 address 7ff7a32b1040

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32b1040(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  ulonglong uVar4;
  longlong lVar5;
  ulonglong uVar6;
  int iVar7;
  longlong lVar8;
  float fVar9;
  undefined1 auStack_58 [32];
  undefined1 local_38 [32];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_58;
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar3 = FUN_7ff7a3468d90(param_1);
    if ((iVar3 != 0) && (*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48))) {
      iVar3 = FUN_7ff7a3468d90(param_1);
      if (iVar3 != 0) goto LAB_7ff7a32b10b2;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32b10b2:
  uVar4 = *(ulonglong *)(param_1 + 0x50);
  uVar6 = *(ulonglong *)(param_1 + 0x48);
  if (uVar4 < uVar6) {
    fVar9 = (float)FUN_7ff7a3469aa0(param_1,uVar4);
    uVar4 = *(ulonglong *)(param_1 + 0x50);
    uVar6 = *(ulonglong *)(param_1 + 0x48);
    iVar3 = (int)fVar9;
  }
  else {
    iVar3 = 0;
  }
  if (uVar4 + 0x10 < uVar6) {
    fVar9 = (float)FUN_7ff7a3469aa0(param_1);
    iVar7 = (int)fVar9;
  }
  else {
    iVar7 = 0;
  }
  FUN_7ff7a39c90a0(local_38);
  cVar2 = FUN_7ff7a3406780(iVar3,iVar7,local_38);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)(cVar2 != '\0');
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  lVar5 = FUN_7ff7a39c9020(local_38);
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
  return 2;
}

