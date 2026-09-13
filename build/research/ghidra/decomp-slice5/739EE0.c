// image offset 0x739EE0 address 7ff7a38c9ee0

undefined8 FUN_7ff7a38c9ee0(longlong param_1)

{
  undefined4 *puVar1;
  byte bVar2;
  int iVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  ulonglong uVar6;
  int iVar7;
  uint uVar8;
  float fVar9;
  
  uVar8 = 0;
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar3 = FUN_7ff7a3468d90(param_1);
    if ((iVar3 != 0) && (*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48))) {
      iVar3 = FUN_7ff7a3468d90(param_1);
      if (iVar3 != 0) goto LAB_7ff7a38c9f41;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a38c9f41:
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar3 = FUN_7ff7a3468d90(param_1);
    if ((iVar3 != 0) && (*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48))) {
      iVar3 = FUN_7ff7a3468d90(param_1);
      if (iVar3 != 0) {
        uVar4 = *(ulonglong *)(param_1 + 0x50);
        iVar3 = 0;
        uVar6 = *(ulonglong *)(param_1 + 0x48);
        if (uVar4 < uVar6) {
          fVar9 = (float)FUN_7ff7a3469aa0(param_1,uVar4);
          uVar4 = *(ulonglong *)(param_1 + 0x50);
          uVar6 = *(ulonglong *)(param_1 + 0x48);
          iVar7 = (int)fVar9;
        }
        else {
          iVar7 = 0;
        }
        if (uVar4 + 0x10 < uVar6) {
          fVar9 = (float)FUN_7ff7a3469aa0(param_1);
          iVar3 = (int)fVar9;
        }
        uVar5 = FUN_7ff7a3919870(iVar7);
        bVar2 = FUN_7ff7a3340350(uVar5,iVar3,0);
        uVar8 = (uint)bVar2;
      }
    }
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = uVar8;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

