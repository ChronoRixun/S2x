// image offset 0x1237F0 address 7ff7a32b37f0

undefined8 FUN_7ff7a32b37f0(longlong param_1)

{
  undefined4 *puVar1;
  byte bVar2;
  int iVar3;
  ulonglong uVar4;
  
  uVar4 = *(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4;
  if ((int)uVar4 == 1) {
    iVar3 = thunk_FUN_7ff7a3294bb0(param_1,uVar4 & 0xffffffff);
    if (iVar3 != 0) goto LAB_7ff7a32b3828;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32b3828:
  bVar2 = 0;
  iVar3 = FUN_7ff7a325cb30(param_1,1);
  if (iVar3 != 0) {
    bVar2 = FUN_7ff7a37e2490(iVar3);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)bVar2;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

