// image offset 0x11F240 address 7ff7a32af240

undefined8 FUN_7ff7a32af240(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  float fVar4;
  
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar2 = FUN_7ff7a3468d90(param_1);
    if (iVar2 != 0) {
      iVar2 = thunk_FUN_7ff7a3294bb0(param_1,2);
      if (iVar2 != 0) goto LAB_7ff7a32af295;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32af295:
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar4 = (float)FUN_7ff7a3469aa0(param_1);
    iVar2 = (int)fVar4;
  }
  else {
    iVar2 = 0;
  }
  uVar3 = FUN_7ff7a325cb30(param_1,2);
  iVar2 = FUN_7ff7a34090f0(iVar2,uVar3);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  *puVar1 = 3;
  puVar1[2] = (float)iVar2;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

