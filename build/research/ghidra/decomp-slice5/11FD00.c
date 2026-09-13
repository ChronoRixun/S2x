// image offset 0x11FD00 address 7ff7a32afd00

undefined8 FUN_7ff7a32afd00(longlong param_1)

{
  undefined4 *puVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  ulonglong uVar5;
  
  uVar5 = *(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4;
  if ((int)uVar5 == 1) {
    iVar3 = thunk_FUN_7ff7a3294bb0(param_1,uVar5 & 0xffffffff);
    if (iVar3 != 0) goto LAB_7ff7a32afd34;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32afd34:
  uVar4 = FUN_7ff7a325cb30(param_1,1);
  bVar2 = FUN_7ff7a37e2440(uVar4);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)bVar2;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

