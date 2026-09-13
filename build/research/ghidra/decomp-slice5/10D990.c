// image offset 0x10D990 address 7ff7a329d990

undefined8 FUN_7ff7a329d990(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  float fVar9;
  
  uVar7 = *(ulonglong *)(param_1 + 0x48);
  uVar8 = *(ulonglong *)(param_1 + 0x50);
  if ((int)((longlong)(uVar7 - uVar8) >> 4) != 1) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar8 = *(ulonglong *)(param_1 + 0x50);
    uVar7 = *(ulonglong *)(param_1 + 0x48);
  }
  if (uVar8 < uVar7) {
    iVar3 = FUN_7ff7a3468d90(param_1);
    if (iVar3 != 0) goto LAB_7ff7a329d9f5;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a329d9f5:
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar9 = (float)FUN_7ff7a3469aa0(param_1);
  }
  else {
    fVar9 = 0.0;
  }
  uVar4 = FUN_7ff7a39e6580();
  uVar5 = FUN_7ff7a39e6640((int)fVar9);
  cVar2 = FUN_7ff7a38d0260(0,"menu_resetstats_warning");
  if (((uVar5 & uVar4) == 0) && (cVar2 == '\0')) {
    uVar6 = 1;
  }
  else {
    uVar6 = 0;
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = uVar6;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

