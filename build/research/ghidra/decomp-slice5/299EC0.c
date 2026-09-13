// image offset 0x299EC0 address 7ff7a3429ec0

undefined8 FUN_7ff7a3429ec0(longlong param_1)

{
  undefined4 *puVar1;
  byte bVar2;
  undefined8 uVar3;
  int iVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  float fVar7;
  
  uVar5 = *(ulonglong *)(param_1 + 0x48);
  uVar6 = *(ulonglong *)(param_1 + 0x50);
  if ((int)((longlong)(uVar5 - uVar6) >> 4) != 1) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar6 = *(ulonglong *)(param_1 + 0x50);
    uVar5 = *(ulonglong *)(param_1 + 0x48);
  }
  if (uVar6 < uVar5) {
    fVar7 = (float)FUN_7ff7a3469aa0(param_1);
    iVar4 = (int)fVar7;
  }
  else {
    iVar4 = 0;
  }
  uVar3 = FUN_7ff7a342a780(iVar4);
  uVar3 = FUN_7ff7a342a890(uVar3);
  bVar2 = FUN_7ff7a341d7c0(uVar3);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)bVar2;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

