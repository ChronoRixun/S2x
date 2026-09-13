// image offset 0x11E9E0 address 7ff7a32ae9e0

undefined8 FUN_7ff7a32ae9e0(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  
  uVar3 = *(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4;
  if ((int)uVar3 == 1) {
    iVar2 = thunk_FUN_7ff7a3294bb0(param_1,uVar3 & 0xffffffff);
    if (iVar2 != 0) goto LAB_7ff7a32aea18;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32aea18:
  iVar2 = FUN_7ff7a325cb30(param_1,1);
  if (iVar2 == 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar4 = FUN_7ff7a3404cf0(iVar2);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  *puVar1 = 3;
  puVar1[2] = (float)(int)uVar4;
  puVar1[4] = 3;
  puVar1[6] = (float)(int)((ulonglong)uVar4 >> 0x20);
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 8;
  return 2;
}

