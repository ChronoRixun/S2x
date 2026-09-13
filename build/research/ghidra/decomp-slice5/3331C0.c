// image offset 0x3331C0 address 7ff7a34c31c0

undefined8 FUN_7ff7a34c31c0(longlong param_1)

{
  undefined4 uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  float fVar4;
  
  uVar2 = *(ulonglong *)(param_1 + 0x48);
  uVar3 = *(ulonglong *)(param_1 + 0x50);
  if (1 < (int)((longlong)(uVar2 - uVar3) >> 4)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar2 = *(ulonglong *)(param_1 + 0x48);
    uVar3 = *(ulonglong *)(param_1 + 0x50);
  }
  if (0 < (int)((longlong)(uVar2 - uVar3) >> 4)) {
    if (uVar2 <= uVar3) {
      FUN_7ff7a360b6f0(0);
      return 0;
    }
    fVar4 = (float)FUN_7ff7a3469aa0(param_1);
    FUN_7ff7a360b6f0((int)fVar4);
    return 0;
  }
  uVar1 = FUN_7ff7a34a84c0();
  uVar1 = FUN_7ff7a3630b80(uVar1);
  FUN_7ff7a360b6f0(uVar1);
  return 0;
}

