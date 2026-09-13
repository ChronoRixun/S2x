// image offset 0x11E590 address 7ff7a32ae590

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32ae590(longlong param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint uVar4;
  float fVar5;
  undefined1 auStack_808 [32];
  undefined4 local_7e8 [500];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_808;
  if ((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) != 1
       ) || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) ||
     (iVar1 = FUN_7ff7a3468d90(param_1), iVar1 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar4 = 0;
  uVar2 = uVar4;
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar5 = (float)FUN_7ff7a3469aa0(param_1);
    uVar2 = (int)fVar5;
  }
  uVar2 = FUN_7ff7a3408f30(uVar2,local_7e8,500);
  FUN_7ff7a324d6e0(1,uVar2,0,param_1);
  if (uVar2 != 0) {
    puVar3 = local_7e8;
    do {
      thunk_FUN_7ff7a325af40(param_1,*puVar3);
      uVar4 = uVar4 + 1;
      FUN_7ff7a3469640(param_1,*(longlong *)(param_1 + 0x48) + -0x20,uVar4,
                       *(longlong *)(param_1 + 0x48) + -0x10);
      *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + -0x10;
      puVar3 = puVar3 + 1;
    } while (uVar4 < uVar2);
  }
  return 1;
}

