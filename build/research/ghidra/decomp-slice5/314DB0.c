// image offset 0x314DB0 address 7ff7a34a4db0

undefined8 FUN_7ff7a34a4db0(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  int iVar5;
  float fVar6;
  
  uVar3 = *(ulonglong *)(param_1 + 0x48);
  uVar4 = *(ulonglong *)(param_1 + 0x50);
  if ((int)((longlong)(uVar3 - uVar4) >> 4) != 2) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar4 = *(ulonglong *)(param_1 + 0x50);
    uVar3 = *(ulonglong *)(param_1 + 0x48);
  }
  if ((uVar3 <= uVar4) || (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x10U) ||
     (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar3 = *(ulonglong *)(param_1 + 0x50);
  iVar5 = 0;
  uVar4 = *(ulonglong *)(param_1 + 0x48);
  iVar2 = iVar5;
  if (uVar3 < uVar4) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1,uVar3);
    uVar3 = *(ulonglong *)(param_1 + 0x50);
    uVar4 = *(ulonglong *)(param_1 + 0x48);
    iVar2 = (int)fVar6;
  }
  if (uVar3 + 0x10 < uVar4) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1);
    iVar5 = (int)fVar6;
  }
  uVar3 = FUN_7ff7a39cfea0(iVar2);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  *puVar1 = 1;
  puVar1[2] = (uint)((uVar3 & 1L << ((byte)iVar5 & 0x3f)) != 0);
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

