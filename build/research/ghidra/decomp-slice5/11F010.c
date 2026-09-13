// image offset 0x11F010 address 7ff7a32af010

undefined8 FUN_7ff7a32af010(longlong param_1)

{
  int iVar1;
  float fVar2;
  
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 1)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar1 = FUN_7ff7a3468d90(param_1);
    if (iVar1 != 0) goto LAB_7ff7a32af050;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32af050:
  if (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50)) {
    FUN_7ff7a3406330(0);
    return 0;
  }
  fVar2 = (float)FUN_7ff7a3469aa0(param_1);
  FUN_7ff7a3406330((int)fVar2);
  return 0;
}

