// image offset 0x11DAF0 address 7ff7a32adaf0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32adaf0(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  float fVar6;
  undefined1 auStack_48 [32];
  undefined4 local_28 [4];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_48;
  if ((int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4) != 2) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  iVar3 = thunk_FUN_7ff7a3294bb0(param_1,2);
  if (iVar3 == 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1);
    iVar3 = (int)fVar6;
  }
  else {
    iVar3 = 0;
  }
  uVar4 = FUN_7ff7a325cb30(param_1,2);
  FUN_7ff7a37e2170(uVar4,local_28);
  lVar5 = 0;
  do {
    cVar2 = FUN_7ff7a340a310(iVar3,local_28[lVar5]);
    if (cVar2 == '\0') {
      puVar1 = *(undefined4 **)(param_1 + 0x48);
      puVar1[2] = 0;
      *puVar1 = 1;
      *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
      return 1;
    }
    lVar5 = lVar5 + 1;
  } while (lVar5 < 3);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = 1;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

