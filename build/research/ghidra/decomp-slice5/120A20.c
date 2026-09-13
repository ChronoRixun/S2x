// image offset 0x120A20 address 7ff7a32b0a20

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32b0a20(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  ulonglong uVar3;
  int *piVar4;
  uint uVar5;
  ulonglong uVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  undefined1 auStack_a8 [32];
  int local_88 [28];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_a8;
  iVar8 = 0;
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar2 = FUN_7ff7a3468d90(param_1);
    if ((iVar2 != 0) && (*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48))) {
      iVar2 = FUN_7ff7a3468d90(param_1);
      if (iVar2 != 0) goto LAB_7ff7a32b0a9f;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32b0a9f:
  uVar3 = *(ulonglong *)(param_1 + 0x50);
  uVar6 = *(ulonglong *)(param_1 + 0x48);
  if (uVar3 < uVar6) {
    fVar9 = (float)FUN_7ff7a3469aa0(param_1,uVar3);
    uVar3 = *(ulonglong *)(param_1 + 0x50);
    uVar6 = *(ulonglong *)(param_1 + 0x48);
    iVar2 = (int)fVar9;
  }
  else {
    iVar2 = 0;
  }
  if (uVar3 + 0x10 < uVar6) {
    fVar9 = (float)FUN_7ff7a3469aa0(param_1);
    iVar7 = (int)fVar9;
  }
  else {
    iVar7 = 0;
  }
  FUN_7ff7a343ed60(iVar2,local_88,0xd);
  uVar5 = 0;
  piVar4 = local_88 + 1;
  do {
    if (iVar7 == piVar4[-1]) {
      iVar8 = *piVar4;
    }
    uVar5 = uVar5 + 1;
    piVar4 = piVar4 + 2;
  } while (uVar5 < 0xd);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  *puVar1 = 3;
  puVar1[2] = (float)iVar8;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

