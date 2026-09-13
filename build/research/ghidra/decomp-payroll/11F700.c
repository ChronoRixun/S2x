// image offset 0x11F700 address 7ff7a32af700

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32af6a0(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  float fVar8;
  undefined1 auStack_58 [32];
  undefined1 local_38 [32];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_58;
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar4 = FUN_7ff7a3468d90(param_1);
    if (iVar4 != 0) {
      iVar4 = thunk_FUN_7ff7a3294bb0(param_1,2);
      if (iVar4 != 0) goto LAB_7ff7a32af70a;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32af70a:
  bVar3 = 0;
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar8 = (float)FUN_7ff7a3469aa0(param_1);
    iVar4 = (int)fVar8;
  }
  else {
    iVar4 = 0;
  }
  iVar5 = FUN_7ff7a325cb30(param_1,2);
  if (iVar5 == 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  cVar2 = FUN_7ff7a34052b0(iVar5);
  if (cVar2 == '\0') {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if (iVar5 != 0) {
    FUN_7ff7a39c90a0(local_38);
    bVar3 = FUN_7ff7a34068b0(iVar4,iVar5,local_38);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)bVar3;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  lVar6 = FUN_7ff7a39c9020(local_38);
  if (lVar6 == 0) {
    puVar1 = *(undefined4 **)(param_1 + 0x48);
    *puVar1 = 0;
    *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  }
  else {
    lVar7 = -1;
    do {
      lVar7 = lVar7 + 1;
    } while (*(char *)(lVar6 + lVar7) != '\0');
    FUN_7ff7a3294620(param_1,lVar6);
  }
  return 2;
}

