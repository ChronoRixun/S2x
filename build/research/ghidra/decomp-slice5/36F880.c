// image offset 0x36F880 address 7ff7a34ff880

undefined8 FUN_7ff7a34ff880(longlong param_1)

{
  ulonglong uVar1;
  ulonglong uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  
  uVar2 = *(ulonglong *)(param_1 + 0x48);
  uVar1 = *(ulonglong *)(param_1 + 0x50);
  if ((int)((longlong)(uVar2 - uVar1) >> 4) != 3) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar1 = *(ulonglong *)(param_1 + 0x50);
    uVar2 = *(ulonglong *)(param_1 + 0x48);
  }
  iVar5 = 0;
  if (uVar1 < uVar2) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1,uVar1);
    uVar1 = *(ulonglong *)(param_1 + 0x50);
    uVar2 = *(ulonglong *)(param_1 + 0x48);
    iVar3 = (int)fVar6;
  }
  else {
    iVar3 = 0;
  }
  if (uVar1 + 0x10 < uVar2) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1,uVar1 + 0x10);
    uVar1 = *(ulonglong *)(param_1 + 0x50);
    uVar2 = *(ulonglong *)(param_1 + 0x48);
    iVar4 = (int)fVar6;
  }
  else {
    iVar4 = 0;
  }
  if (uVar1 + 0x20 < uVar2) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1,uVar1 + 0x20);
    iVar5 = (int)fVar6;
  }
  FUN_7ff7a3403f40(iVar3,iVar4,iVar5);
  return 0;
}

