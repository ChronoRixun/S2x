// image offset 0x11E4F0 address 7ff7a32ae4f0

undefined8 FUN_7ff7a32ae4f0(longlong param_1)

{
  int iVar1;
  undefined4 uVar2;
  float fVar3;
  
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar1 = FUN_7ff7a3468d90(param_1);
    if (iVar1 != 0) {
      iVar1 = thunk_FUN_7ff7a3294bb0(param_1,2);
      if (iVar1 != 0) goto LAB_7ff7a32ae545;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32ae545:
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar3 = (float)FUN_7ff7a3469aa0(param_1);
    iVar1 = (int)fVar3;
  }
  else {
    iVar1 = 0;
  }
  uVar2 = FUN_7ff7a325cb30(param_1,2);
  FUN_7ff7a340ca90(iVar1,uVar2);
  return 0;
}

