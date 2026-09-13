// image offset 0x36FE90 address 7ff7a34ffe90

undefined8 FUN_7ff7a34ffe90(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  undefined1 local_58 [4];
  undefined4 local_54;
  undefined4 local_50;
  undefined8 local_48;
  undefined8 uStack_40;
  undefined1 local_38 [48];
  
  local_58[0] = 0;
  local_48 = 0;
  uStack_40 = 0;
  local_54 = 0;
  local_50 = 0xffffffff;
  iVar8 = 0;
  cVar2 = FUN_7ff7a3401760();
  iVar3 = iVar8;
  if ((cVar2 != '\0') && (cVar2 = FUN_7ff7a36309b0(), iVar3 = 0, cVar2 == '\0')) {
    uVar5 = *(ulonglong *)(param_1 + 0x48);
    uVar6 = *(ulonglong *)(param_1 + 0x50);
    if ((int)((longlong)(uVar5 - uVar6) >> 4) != 2) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
      uVar6 = *(ulonglong *)(param_1 + 0x50);
      uVar5 = *(ulonglong *)(param_1 + 0x48);
    }
    if ((uVar5 <= uVar6) || (iVar3 = FUN_7ff7a3468d90(param_1), iVar3 == 0)) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    }
    if ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x10U) ||
       (iVar3 = FUN_7ff7a3468d90(param_1), iVar3 == 0)) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    }
    uVar5 = *(ulonglong *)(param_1 + 0x50);
    uVar6 = *(ulonglong *)(param_1 + 0x48);
    if (uVar5 < uVar6) {
      fVar9 = (float)FUN_7ff7a3469aa0(param_1,uVar5);
      uVar5 = *(ulonglong *)(param_1 + 0x50);
      uVar6 = *(ulonglong *)(param_1 + 0x48);
    }
    else {
      fVar9 = 0.0;
    }
    iVar7 = (int)fVar9;
    if ((uVar6 <= uVar5 + 0x10) || (iVar3 = FUN_7ff7a3468d90(param_1), iVar3 == 0)) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    }
    if (*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48)) {
      fVar9 = (float)FUN_7ff7a3469aa0(param_1);
      iVar8 = (int)fVar9;
    }
    iVar3 = FUN_7ff7a3402950(iVar8);
    if (iVar3 == 0) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    }
    uVar4 = FUN_7ff7a3402510(iVar8);
    iVar3 = 0;
    cVar2 = FUN_7ff7a3401c90(iVar7);
    if ((cVar2 != '\0') && (cVar2 = FUN_7ff7a34017e0(iVar7,local_58,local_38,0), cVar2 != '\0')) {
      cVar2 = FUN_7ff7a3401910(iVar7,uVar4,local_58,local_38);
      iVar3 = 0;
      if (cVar2 != '\0') {
        iVar3 = 1;
      }
    }
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = iVar3;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

