// image offset 0x27F1E0 address 7ff7a340f1e0

undefined8 FUN_7ff7a340f1e0(longlong param_1,uint *param_2)

{
  undefined8 uVar1;
  uint uVar2;
  
  if ((*param_2 & 0xe0000000) != 0x80000000) {
    return 0;
  }
  uVar2 = *param_2 & 0x1fffffff;
  if (uVar2 == 0x1fffffff) {
    uVar1 = FUN_7ff7a34118e0(0);
    return uVar1;
  }
  uVar1 = FUN_7ff7a34118e0((ulonglong)uVar2 + *(longlong *)(param_1 + 0x100));
  return uVar1;
}

