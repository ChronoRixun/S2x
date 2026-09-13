// image offset 0x1202C0 address 7ff7a32b02c0

int FUN_7ff7a32b02c0(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  ulonglong uVar4;
  longlong lVar5;
  longlong local_res8 [4];
  
  uVar4 = *(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4;
  if ((int)uVar4 == 1) {
    iVar2 = thunk_FUN_7ff7a3294bb0(param_1,uVar4 & 0xffffffff);
    if (iVar2 != 0) goto LAB_7ff7a32b02f4;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32b02f4:
  uVar3 = FUN_7ff7a325cb30(param_1,1);
  local_res8[0] = 0;
  FUN_7ff7a34097e0(uVar3,local_res8);
  if (local_res8[0] == 0) {
    FUN_7ff7a3294620(param_1,&DAT_7ff7a3cbd562,0);
    return 1;
  }
  if (local_res8[0] + 0x29c == 0) {
    puVar1 = *(undefined4 **)(param_1 + 0x48);
    *puVar1 = 0;
    *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
    return (int)local_res8[0] + 0x29d;
  }
  lVar5 = -1;
  do {
    lVar5 = lVar5 + 1;
  } while (*(char *)(local_res8[0] + 0x29c + lVar5) != '\0');
  FUN_7ff7a3294620(param_1);
  return 1;
}

