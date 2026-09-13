// image offset 0x11E6B0 address 7ff7a32ae6b0

undefined8 FUN_7ff7a32ae6b0(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  ulonglong uVar5;
  longlong lVar6;
  
  iVar4 = -1;
  uVar5 = *(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4;
  if ((int)uVar5 == 1) {
    iVar2 = thunk_FUN_7ff7a3294bb0(param_1,uVar5 & 0xffffffff);
    if (iVar2 != 0) goto LAB_7ff7a32ae6f2;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32ae6f2:
  iVar2 = FUN_7ff7a325cb30(param_1,1);
  if (iVar2 == 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  lVar6 = FUN_7ff7a3261ba0(iVar2,0x21);
  if (lVar6 != 0) {
    iVar3 = FUN_7ff7a3b94f40(lVar6,&DAT_7ff7a3cc2368);
    if (iVar3 == 0) {
      iVar4 = FUN_7ff7a37e2330(iVar2);
    }
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  *puVar1 = 3;
  puVar1[2] = (float)iVar4;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

