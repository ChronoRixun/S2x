// image offset 0x1256F0 address 7ff7a32b56f0

undefined8 FUN_7ff7a32b56f0(longlong param_1)

{
  int iVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  float fVar4;
  
  uVar2 = *(ulonglong *)(param_1 + 0x48);
  uVar3 = *(ulonglong *)(param_1 + 0x50);
  if ((int)((longlong)(uVar2 - uVar3) >> 4) != 1) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar3 = *(ulonglong *)(param_1 + 0x50);
    uVar2 = *(ulonglong *)(param_1 + 0x48);
  }
  if (uVar3 < uVar2) {
    iVar1 = FUN_7ff7a3468d90(param_1);
    if (iVar1 != 0) goto LAB_7ff7a32b5747;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32b5747:
  if (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50)) {
    thunk_FUN_7ff7a3502490(0);
    return 0;
  }
  fVar4 = (float)FUN_7ff7a3469aa0(param_1);
  thunk_FUN_7ff7a3502490((int)fVar4);
  return 0;
}

