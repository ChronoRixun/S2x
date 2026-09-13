// image offset 0x11E810 address 7ff7a32ae810

undefined8 FUN_7ff7a32ae810(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  ulonglong uVar3;
  
  uVar3 = *(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4;
  if ((int)uVar3 == 1) {
    iVar2 = thunk_FUN_7ff7a3294bb0(param_1,uVar3 & 0xffffffff);
    if (iVar2 != 0) goto LAB_7ff7a32ae848;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32ae848:
  iVar2 = FUN_7ff7a325cb30(param_1,1);
  if (iVar2 == 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  iVar2 = FUN_7ff7a37e2280(iVar2);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  *puVar1 = 3;
  puVar1[2] = (float)iVar2;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

