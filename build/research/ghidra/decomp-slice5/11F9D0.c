// image offset 0x11F9D0 address 7ff7a32af9d0

undefined8 FUN_7ff7a32af9d0(longlong param_1)

{
  int iVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  int iVar4;
  float fVar5;
  
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar1 = FUN_7ff7a3468d90(param_1);
    if ((iVar1 != 0) && (*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48))) {
      iVar1 = FUN_7ff7a3468d90(param_1);
      if (iVar1 != 0) goto LAB_7ff7a32afa33;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32afa33:
  uVar2 = *(ulonglong *)(param_1 + 0x50);
  iVar1 = 0;
  uVar3 = *(ulonglong *)(param_1 + 0x48);
  if (uVar2 < uVar3) {
    fVar5 = (float)FUN_7ff7a3469aa0(param_1,uVar2);
    uVar2 = *(ulonglong *)(param_1 + 0x50);
    uVar3 = *(ulonglong *)(param_1 + 0x48);
    iVar4 = (int)fVar5;
  }
  else {
    iVar4 = 0;
  }
  if (uVar2 + 0x10 < uVar3) {
    fVar5 = (float)FUN_7ff7a3469aa0(param_1);
    iVar1 = (int)fVar5;
  }
  FUN_7ff7a34059c0(iVar4,iVar1);
  return 0;
}

