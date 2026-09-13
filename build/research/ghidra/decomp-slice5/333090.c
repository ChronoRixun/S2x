// image offset 0x333090 address 7ff7a34c3090

undefined8 FUN_7ff7a34c3090(longlong param_1)

{
  undefined4 *puVar1;
  byte bVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  float fVar5;
  
  uVar3 = *(ulonglong *)(param_1 + 0x48);
  uVar4 = *(ulonglong *)(param_1 + 0x50);
  if (1 < (int)((longlong)(uVar3 - uVar4) >> 4)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar3 = *(ulonglong *)(param_1 + 0x48);
    uVar4 = *(ulonglong *)(param_1 + 0x50);
  }
  if ((int)((longlong)(uVar3 - uVar4) >> 4) < 1) {
    bVar2 = FUN_7ff7a360d670();
  }
  else if (uVar4 < uVar3) {
    fVar5 = (float)FUN_7ff7a3469aa0(param_1);
    bVar2 = FUN_7ff7a360d600((int)fVar5);
  }
  else {
    bVar2 = FUN_7ff7a360d600(0);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)bVar2;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

