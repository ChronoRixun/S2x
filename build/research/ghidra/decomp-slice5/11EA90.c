// image offset 0x11EA90 address 7ff7a32aea90

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32aea90(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  float fVar6;
  undefined1 auStack_68 [32];
  undefined4 local_48;
  int local_44;
  undefined4 local_40;
  undefined8 local_3c;
  undefined1 local_30 [32];
  ulonglong local_10;
  
  local_10 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_68;
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 3)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar3 = FUN_7ff7a3468d90(param_1);
    if (iVar3 != 0) {
      iVar3 = thunk_FUN_7ff7a3294bb0(param_1,2);
      if ((iVar3 != 0) && (*(longlong *)(param_1 + 0x50) + 0x20U < *(ulonglong *)(param_1 + 0x48)))
      {
        iVar3 = FUN_7ff7a3468d90(param_1);
        if (iVar3 != 0) goto LAB_7ff7a32aeb13;
      }
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32aeb13:
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1);
    iVar3 = (int)fVar6;
  }
  else {
    iVar3 = 0;
  }
  local_48 = FUN_7ff7a325cb30(param_1,2);
  if (*(longlong *)(param_1 + 0x50) + 0x20U < *(ulonglong *)(param_1 + 0x48)) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1);
    local_44 = (int)fVar6;
  }
  else {
    local_44 = 0;
  }
  local_40 = 2;
  local_3c = 1;
  FUN_7ff7a39c90a0(local_30);
  cVar2 = FUN_7ff7a340bfe0(iVar3,&local_48,1,local_30);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)(cVar2 != '\0');
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  lVar4 = FUN_7ff7a39c9020(local_30);
  if (lVar4 == 0) {
    puVar1 = *(undefined4 **)(param_1 + 0x48);
    *puVar1 = 0;
    *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  }
  else {
    lVar5 = -1;
    do {
      lVar5 = lVar5 + 1;
    } while (*(char *)(lVar4 + lVar5) != '\0');
    FUN_7ff7a3294620(param_1,lVar4);
  }
  return 2;
}

