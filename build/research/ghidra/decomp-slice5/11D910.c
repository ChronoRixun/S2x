// image offset 0x11D910 address 7ff7a32ad910

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32ad910(longlong param_1)

{
  int iVar1;
  undefined4 uVar2;
  longlong lVar3;
  undefined1 auStack_48 [32];
  undefined4 local_28 [4];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_48;
  if ((int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4) != 1) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  iVar1 = thunk_FUN_7ff7a3294bb0(param_1,1);
  if (iVar1 == 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar2 = FUN_7ff7a325cb30(param_1,1);
  FUN_7ff7a37e2170(uVar2,local_28);
  FUN_7ff7a324d6e0(1,3,0,param_1);
  lVar3 = 0;
  iVar1 = 0;
  do {
    iVar1 = iVar1 + 1;
    thunk_FUN_7ff7a325af40(param_1,local_28[lVar3]);
    FUN_7ff7a3469640(param_1,*(longlong *)(param_1 + 0x48) + -0x20,iVar1,
                     *(longlong *)(param_1 + 0x48) + -0x10);
    *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + -0x10;
    lVar3 = lVar3 + 1;
  } while (lVar3 < 3);
  return 1;
}

