// image offset 0x11E920 address 7ff7a32ae920

undefined8 FUN_7ff7a32ae920(longlong param_1)

{
  int iVar1;
  ulonglong uVar2;
  undefined4 uStackX_c;
  
  uVar2 = *(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4;
  if ((int)uVar2 == 1) {
    iVar1 = thunk_FUN_7ff7a3294bb0(param_1,uVar2 & 0xffffffff);
    if (iVar1 != 0) goto LAB_7ff7a32ae958;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32ae958:
  iVar1 = FUN_7ff7a325cb30(param_1,1);
  if (iVar1 == 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar2 = FUN_7ff7a3404970(iVar1);
  FUN_7ff7a324d6e0(1,1,0,param_1);
  FUN_7ff7a325c620("currency",uVar2 & 0xffffffff,DAT_7ff7a4d63d08);
  uStackX_c = (undefined4)(uVar2 >> 0x20);
  FUN_7ff7a325c620("price",uStackX_c,DAT_7ff7a4d63d08);
  return 1;
}

