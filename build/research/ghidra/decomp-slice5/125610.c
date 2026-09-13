// image offset 0x125610 address 7ff7a32b5610

undefined8 FUN_7ff7a32b5610(longlong param_1)

{
  int iVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  float fVar4;
  float fVar5;
  
  uVar2 = *(ulonglong *)(param_1 + 0x48);
  uVar3 = *(ulonglong *)(param_1 + 0x50);
  if ((int)((longlong)(uVar2 - uVar3) >> 4) != 2) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar3 = *(ulonglong *)(param_1 + 0x50);
    uVar2 = *(ulonglong *)(param_1 + 0x48);
  }
  if (uVar3 < uVar2) {
    iVar1 = FUN_7ff7a3468d90(param_1);
    if (iVar1 == 0) goto LAB_7ff7a32b565c;
  }
  else {
LAB_7ff7a32b565c:
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if (*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48)) {
    iVar1 = FUN_7ff7a3468d90(param_1);
    if (iVar1 != 0) goto LAB_7ff7a32b5694;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32b5694:
  uVar2 = *(ulonglong *)(param_1 + 0x50);
  uVar3 = *(ulonglong *)(param_1 + 0x48);
  if (uVar2 < uVar3) {
    fVar4 = (float)FUN_7ff7a3469aa0(param_1,uVar2);
    uVar2 = *(ulonglong *)(param_1 + 0x50);
    uVar3 = *(ulonglong *)(param_1 + 0x48);
  }
  else {
    fVar4 = 0.0;
  }
  if (uVar2 + 0x10 < uVar3) {
    fVar5 = (float)FUN_7ff7a3469aa0(param_1);
    iVar1 = (int)fVar5;
  }
  else {
    iVar1 = 0;
  }
  FUN_7ff7a35020c0((int)fVar4,iVar1);
  return 0;
}

