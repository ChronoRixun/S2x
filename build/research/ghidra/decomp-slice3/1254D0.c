// image offset 0x1254D0 address 7ff7a32b54d0

undefined8 FUN_7ff7a32b54d0(longlong param_1)

{
  int iVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  
  uVar2 = *(ulonglong *)(param_1 + 0x48);
  uVar3 = *(ulonglong *)(param_1 + 0x50);
  if ((int)((longlong)(uVar2 - uVar3) >> 4) != 3) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar3 = *(ulonglong *)(param_1 + 0x50);
    uVar2 = *(ulonglong *)(param_1 + 0x48);
  }
  if (uVar3 < uVar2) {
    iVar1 = FUN_7ff7a3468d90(param_1);
    if (iVar1 == 0) goto LAB_7ff7a32b5526;
  }
  else {
LAB_7ff7a32b5526:
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if (*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48)) {
    iVar1 = FUN_7ff7a3468d90(param_1);
    if (iVar1 == 0) goto LAB_7ff7a32b554f;
  }
  else {
LAB_7ff7a32b554f:
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if (*(longlong *)(param_1 + 0x50) + 0x20U < *(ulonglong *)(param_1 + 0x48)) {
    iVar1 = FUN_7ff7a3468d90(param_1);
    if (iVar1 != 0) goto LAB_7ff7a32b5587;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32b5587:
  uVar2 = *(ulonglong *)(param_1 + 0x50);
  uVar3 = *(ulonglong *)(param_1 + 0x48);
  if (uVar2 < uVar3) {
    fVar5 = (float)FUN_7ff7a3469aa0(param_1,uVar2);
    uVar2 = *(ulonglong *)(param_1 + 0x50);
    uVar3 = *(ulonglong *)(param_1 + 0x48);
  }
  else {
    fVar5 = 0.0;
  }
  iVar1 = 0;
  if (uVar2 + 0x10 < uVar3) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1);
    uVar2 = *(ulonglong *)(param_1 + 0x50);
    uVar3 = *(ulonglong *)(param_1 + 0x48);
    iVar4 = (int)fVar6;
  }
  else {
    iVar4 = 0;
  }
  if (uVar2 + 0x20 < uVar3) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1);
    iVar1 = (int)fVar6;
  }
  FUN_7ff7a35021a0((int)fVar5,iVar4,iVar1);
  return 0;
}

