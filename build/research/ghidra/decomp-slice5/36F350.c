// image offset 0x36F350 address 7ff7a34ff350

undefined8 FUN_7ff7a34ff350(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  ulonglong uVar4;
  longlong lVar5;
  ulonglong uVar6;
  char cVar7;
  int iVar8;
  float fVar9;
  float fVar10;
  
  uVar4 = *(ulonglong *)(param_1 + 0x48);
  uVar6 = *(ulonglong *)(param_1 + 0x50);
  if ((int)((longlong)(uVar4 - uVar6) >> 4) != 3) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar6 = *(ulonglong *)(param_1 + 0x50);
    uVar4 = *(ulonglong *)(param_1 + 0x48);
  }
  if ((uVar4 <= uVar6) || (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)) {
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
  uVar4 = *(ulonglong *)(param_1 + 0x50);
  uVar6 = *(ulonglong *)(param_1 + 0x48);
  if (uVar4 < uVar6) {
    fVar9 = (float)FUN_7ff7a3469aa0(param_1,uVar4);
    uVar4 = *(ulonglong *)(param_1 + 0x50);
    uVar6 = *(ulonglong *)(param_1 + 0x48);
  }
  else {
    fVar9 = 0.0;
  }
  if ((uVar6 <= uVar4 + 0x10) || (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  iVar8 = 0;
  iVar2 = iVar8;
  if (*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48)) {
    fVar10 = (float)FUN_7ff7a3469aa0(param_1);
    iVar2 = (int)fVar10;
  }
  iVar3 = FUN_7ff7a3402950(iVar2);
  if (iVar3 == 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x20U) ||
     (iVar3 = FUN_7ff7a3468d90(param_1), iVar3 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if (*(longlong *)(param_1 + 0x50) + 0x20U < *(ulonglong *)(param_1 + 0x48)) {
    fVar10 = (float)FUN_7ff7a3469aa0(param_1);
    iVar8 = (int)fVar10;
  }
  lVar5 = FUN_7ff7a3403cf0((int)fVar9,iVar2,iVar8);
  cVar7 = '\0';
  if (lVar5 != 0) {
    cVar7 = *(char *)(*(longlong *)(lVar5 + 8) + 0x1348);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)(cVar7 != '\0');
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

