// image offset 0x297880 address 7ff7a3427880

undefined8 FUN_7ff7a3427880(longlong param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  longlong lVar4;
  int iVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  float fVar8;
  
  uVar6 = *(ulonglong *)(param_1 + 0x48);
  uVar7 = *(ulonglong *)(param_1 + 0x50);
  if ((int)((longlong)(uVar6 - uVar7) >> 4) != 1) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar7 = *(ulonglong *)(param_1 + 0x50);
    uVar6 = *(ulonglong *)(param_1 + 0x48);
  }
  iVar5 = 0;
  if (uVar7 < uVar6) {
    fVar8 = (float)FUN_7ff7a3469aa0(param_1);
    iVar5 = (int)fVar8;
  }
  uVar3 = FUN_7ff7a342a780(iVar5);
  lVar4 = FUN_7ff7a342a890(uVar3);
  puVar2 = *(undefined4 **)(param_1 + 0x48);
  uVar1 = *(undefined4 *)(lVar4 + 0x186490);
  *puVar2 = 1;
  puVar2[2] = (uint)(((byte)uVar1 & 0xfc) == 0x20);
  *(undefined4 **)(param_1 + 0x48) = puVar2 + 4;
  return 1;
}

