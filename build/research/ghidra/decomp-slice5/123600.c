// image offset 0x123600 address 7ff7a32b3600

undefined8 FUN_7ff7a32b3600(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  ulonglong uVar6;
  uint *puVar7;
  uint *puVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  float fVar11;
  
  if ((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2
       ) && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) &&
     (iVar4 = FUN_7ff7a3468d90(param_1), iVar4 != 0)) {
    puVar8 = *(uint **)(param_1 + 0x50);
    puVar7 = *(uint **)(param_1 + 0x48);
    if ((puVar7 <= puVar8 + 4) || (1 < (puVar8[4] & 0xf) - 3)) goto LAB_7ff7a32b3658;
  }
  else {
LAB_7ff7a32b3658:
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    puVar8 = *(uint **)(param_1 + 0x50);
    puVar7 = *(uint **)(param_1 + 0x48);
  }
  uVar6 = 0;
  uVar10 = uVar6;
  if (puVar8 < puVar7) {
    fVar11 = (float)FUN_7ff7a3469aa0(param_1);
    uVar10 = (ulonglong)(uint)(int)fVar11;
    if ((int)fVar11 == 0xffffffff) goto LAB_7ff7a32b36a2;
  }
  cVar2 = FUN_7ff7a391a170(uVar10);
  if (cVar2 != '\0') {
    uVar5 = FUN_7ff7a3631610();
    uVar10 = (ulonglong)uVar5;
  }
LAB_7ff7a32b36a2:
  bVar3 = 0;
  uVar9 = *(longlong *)(param_1 + 0x50) + 0x10;
  if (uVar9 < *(ulonglong *)(param_1 + 0x48)) {
    uVar6 = FUN_7ff7a3469740(param_1,uVar9,0);
  }
  iVar4 = FUN_7ff7a37e24c0(uVar6);
  if (iVar4 != 0) {
    bVar3 = FUN_7ff7a340a310(uVar10,iVar4);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)bVar3;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

