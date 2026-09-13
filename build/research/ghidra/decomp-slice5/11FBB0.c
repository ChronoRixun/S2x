// image offset 0x11FBB0 address 7ff7a32afbb0

undefined8 FUN_7ff7a32afbb0(longlong param_1)

{
  int *piVar1;
  int iVar2;
  ulonglong uVar3;
  undefined4 *puVar4;
  ulonglong uVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar2 = FUN_7ff7a3468d90(param_1);
    if ((iVar2 != 0) &&
       ((*(longlong *)(param_1 + 0x50) + 0x10U < *(ulonglong *)(param_1 + 0x48) &&
        (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 != 0)))) goto LAB_7ff7a32afc13;
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32afc13:
  uVar3 = *(ulonglong *)(param_1 + 0x50);
  iVar2 = 0;
  uVar5 = *(ulonglong *)(param_1 + 0x48);
  if (uVar3 < uVar5) {
    fVar8 = (float)FUN_7ff7a3469aa0(param_1,uVar3);
    uVar3 = *(ulonglong *)(param_1 + 0x50);
    uVar5 = *(ulonglong *)(param_1 + 0x48);
    iVar7 = (int)fVar8;
  }
  else {
    iVar7 = 0;
  }
  if (uVar3 + 0x10 < uVar5) {
    fVar8 = (float)FUN_7ff7a3469aa0(param_1);
    iVar6 = (int)fVar8;
  }
  else {
    iVar6 = 0;
  }
  puVar4 = (undefined4 *)FUN_7ff7a3404b90(iVar7,iVar6);
  if (puVar4 == (undefined4 *)0x0) {
    FUN_7ff7a324d6e0(1,0,0,param_1);
    return 1;
  }
  piVar1 = puVar4 + 0x80;
  FUN_7ff7a324d6e0(1,*piVar1,0,param_1);
  if (0 < *piVar1) {
    do {
      thunk_FUN_7ff7a325af40(param_1,*puVar4);
      iVar2 = iVar2 + 1;
      FUN_7ff7a3469640(param_1,*(longlong *)(param_1 + 0x48) + -0x20,iVar2,
                       *(longlong *)(param_1 + 0x48) + -0x10);
      *(longlong *)(param_1 + 0x48) = *(longlong *)(param_1 + 0x48) + -0x10;
      puVar4 = puVar4 + 1;
    } while (iVar2 < *piVar1);
  }
  return 1;
}

