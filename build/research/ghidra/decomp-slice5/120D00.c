// image offset 0x120D00 address 7ff7a32b0d00

undefined8 FUN_7ff7a32b0d00(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  int iVar5;
  float fVar6;
  
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar2 = FUN_7ff7a3468d90(param_1);
    if ((iVar2 != 0) && (*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48))) {
      iVar2 = FUN_7ff7a3468d90(param_1);
      if (iVar2 != 0) goto LAB_7ff7a32b0d63;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32b0d63:
  uVar3 = *(ulonglong *)(param_1 + 0x50);
  iVar2 = 0;
  uVar4 = *(ulonglong *)(param_1 + 0x48);
  if (uVar3 < uVar4) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1,uVar3);
    uVar3 = *(ulonglong *)(param_1 + 0x50);
    uVar4 = *(ulonglong *)(param_1 + 0x48);
    iVar5 = (int)fVar6;
  }
  else {
    iVar5 = 0;
  }
  if (uVar3 + 0x10 < uVar4) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1);
    iVar2 = (int)fVar6;
  }
  iVar2 = FUN_7ff7a343edb0(iVar5,iVar2);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  *puVar1 = 3;
  puVar1[2] = (float)iVar2;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

