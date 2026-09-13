// image offset 0x3701F0 address 7ff7a35001f0

undefined8 FUN_7ff7a35001f0(longlong param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  ulonglong uVar6;
  undefined4 *puVar7;
  uint *puVar8;
  ulonglong uVar9;
  undefined4 *puVar10;
  undefined1 uVar11;
  int iVar12;
  int iVar13;
  float fVar14;
  undefined1 local_58 [4];
  undefined4 local_54;
  undefined4 local_50;
  undefined8 local_48;
  undefined8 uStack_40;
  undefined1 local_38 [48];
  
  local_58[0] = 0;
  iVar13 = 0;
  local_50 = 0xffffffff;
  local_54 = 0;
  local_48 = 0;
  uStack_40 = 0;
  cVar1 = FUN_7ff7a3401760();
  if (cVar1 == '\0') {
    return 0;
  }
  cVar1 = FUN_7ff7a36309b0();
  if (cVar1 == '\0') {
    uVar6 = *(ulonglong *)(param_1 + 0x48);
    uVar9 = *(ulonglong *)(param_1 + 0x50);
    if ((int)((longlong)(uVar6 - uVar9) >> 4) != 4) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
      uVar9 = *(ulonglong *)(param_1 + 0x50);
      uVar6 = *(ulonglong *)(param_1 + 0x48);
    }
    if ((uVar6 <= uVar9) || (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    }
    if ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x10U) ||
       (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    }
    if ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x20U) ||
       (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    }
    puVar7 = *(undefined4 **)(param_1 + 0x50);
    puVar10 = *(undefined4 **)(param_1 + 0x48);
    if ((puVar10 <= puVar7 + 0xc) || (((byte)puVar7[0xc] & 0xf) != 1)) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
      puVar7 = *(undefined4 **)(param_1 + 0x50);
      puVar10 = *(undefined4 **)(param_1 + 0x48);
    }
    if (puVar7 < puVar10) {
      fVar14 = (float)FUN_7ff7a3469aa0(param_1,puVar7);
      puVar7 = *(undefined4 **)(param_1 + 0x50);
      puVar10 = *(undefined4 **)(param_1 + 0x48);
    }
    else {
      fVar14 = 0.0;
    }
    iVar2 = (int)fVar14;
    if (puVar7 + 4 < puVar10) {
      fVar14 = (float)FUN_7ff7a3469aa0(param_1,puVar7 + 4);
      puVar7 = *(undefined4 **)(param_1 + 0x50);
      puVar10 = *(undefined4 **)(param_1 + 0x48);
      iVar12 = (int)fVar14;
    }
    else {
      iVar12 = 0;
    }
    if ((puVar10 <= puVar7 + 8) || (iVar3 = FUN_7ff7a3468d90(param_1,puVar7 + 8), iVar3 == 0)) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    }
    if (*(longlong *)(param_1 + 0x50) + 0x20U < *(ulonglong *)(param_1 + 0x48)) {
      fVar14 = (float)FUN_7ff7a3469aa0(param_1);
      iVar13 = (int)fVar14;
    }
    iVar3 = FUN_7ff7a3402950(iVar13);
    if (iVar3 == 0) {
      FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    }
    uVar4 = FUN_7ff7a3402510(iVar13);
    puVar8 = (uint *)(*(longlong *)(param_1 + 0x50) + 0x30);
    if (((puVar8 < *(uint **)(param_1 + 0x48)) && (uVar5 = *puVar8 & 0xf, uVar5 != 0)) &&
       ((uVar5 != 1 || (*(int *)(*(longlong *)(param_1 + 0x50) + 0x38) != 0)))) {
      uVar11 = 1;
    }
    else {
      uVar11 = 0;
    }
    cVar1 = FUN_7ff7a3401c90(iVar2);
    if ((cVar1 != '\0') && (cVar1 = FUN_7ff7a34017e0(iVar2,local_58,local_38,1), cVar1 != '\0')) {
      FUN_7ff7a34022a0(iVar2,uVar4,iVar12,uVar11,local_58,local_38);
    }
    return 0;
  }
  return 0;
}

