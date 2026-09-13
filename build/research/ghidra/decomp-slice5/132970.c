// image offset 0x132970 address 7ff7a32c2970

undefined8 FUN_7ff7a32c2970(longlong param_1)

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
      if (iVar1 != 0) goto LAB_7ff7a32c29d3;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32c29d3:
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
  FUN_7ff7a39cf550(iVar4,iVar1);
  FUN_7ff7a39cf570(iVar4);
  FUN_7ff7a39da560(iVar4);
  return 0;
}

