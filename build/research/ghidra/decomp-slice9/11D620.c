// image offset 0x11D620 address 7ff7a32ad620

undefined8 FUN_7ff7a32ad620(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  float fVar9;

  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar2 = FUN_7ff7a3468d90(param_1);
    if (iVar2 != 0) {
      iVar2 = thunk_FUN_7ff7a3294bb0(param_1,2);
      if (iVar2 != 0) goto LAB_7ff7a32ad685;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32ad685:
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar9 = (float)FUN_7ff7a3469aa0(param_1);
    iVar2 = (int)fVar9;
  }
  else {
    iVar2 = 0;
  }
  iVar3 = FUN_7ff7a325cb30(param_1,2);
  if (iVar3 == 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  iVar4 = FUN_7ff7a325f850(iVar2,iVar3,0);
  lVar5 = FUN_7ff7a325f820(iVar4);
  lVar6 = FUN_7ff7a325fad0(iVar2,iVar3,0);
  lVar7 = -1;
  if (lVar5 == 0) {
    puVar1 = *(undefined4 **)(param_1 + 0x48);
    *puVar1 = 0;
    *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  }
  else {
    lVar8 = -1;
    do {
      lVar8 = lVar8 + 1;
    } while (*(char *)(lVar8 + lVar5) != '\0');
    FUN_7ff7a3294620(param_1,lVar5);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  *puVar1 = 3;
  puVar1[2] = (float)iVar4;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  if (lVar6 == 0) {
    puVar1[4] = 0;
    *(undefined4 **)(param_1 + 0x48) = puVar1 + 8;
  }
  else {
    do {
      lVar7 = lVar7 + 1;
    } while (*(char *)(lVar6 + lVar7) != '\0');
    FUN_7ff7a3294620(param_1,lVar6,lVar7);
  }
  return 3;
}
