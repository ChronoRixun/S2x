// image offset 0x11EC10 address 7ff7a32aec10

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32aec10(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  int iVar6;
  longlong lVar7;
  float fVar8;
  undefined1 auStack_58 [32];
  undefined1 local_38 [32];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_58;
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 3)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar3 = FUN_7ff7a3468d90(param_1);
    if (iVar3 == 0) goto LAB_7ff7a32aec89;
    iVar3 = thunk_FUN_7ff7a3294bb0(param_1,2);
    if ((iVar3 == 0) || (*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x20U))
    goto LAB_7ff7a32aec89;
    iVar3 = FUN_7ff7a3468d90(param_1);
    if (iVar3 == 0) goto LAB_7ff7a32aec89;
  }
  else {
LAB_7ff7a32aec89:
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar8 = (float)FUN_7ff7a3469aa0(param_1);
    iVar3 = (int)fVar8;
  }
  else {
    iVar3 = 0;
  }
  iVar4 = FUN_7ff7a325cb30(param_1,2);
  if (iVar4 == 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if (*(longlong *)(param_1 + 0x50) + 0x20U < *(ulonglong *)(param_1 + 0x48)) {
    fVar8 = (float)FUN_7ff7a3469aa0(param_1);
    iVar6 = (int)fVar8;
    if (iVar6 != 0) goto LAB_7ff7a32aed05;
  }
  else {
    iVar6 = 0;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32aed05:
  FUN_7ff7a39c90a0(local_38);
  cVar2 = FUN_7ff7a3406540(iVar3,iVar4,iVar6,local_38);
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)(cVar2 != '\0');
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  lVar5 = FUN_7ff7a39c9020(local_38);
  if (lVar5 == 0) {
    puVar1 = *(undefined4 **)(param_1 + 0x48);
    *puVar1 = 0;
    *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  }
  else {
    lVar7 = -1;
    do {
      lVar7 = lVar7 + 1;
    } while (*(char *)(lVar5 + lVar7) != '\0');
    FUN_7ff7a3294620(param_1,lVar5);
  }
  return 2;
}

