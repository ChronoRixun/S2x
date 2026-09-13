// image offset 0x11F470 address 7ff7a32af470

undefined8 FUN_7ff7a32af470(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  longlong lVar4;
  longlong lVar5;
  float fVar6;
  
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar2 = FUN_7ff7a3468d90(param_1);
    if (iVar2 != 0) {
      iVar2 = thunk_FUN_7ff7a3294bb0(param_1,2);
      if (iVar2 != 0) goto LAB_7ff7a32af4c5;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32af4c5:
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar6 = (float)FUN_7ff7a3469aa0(param_1);
    iVar2 = (int)fVar6;
  }
  else {
    iVar2 = 0;
  }
  uVar3 = FUN_7ff7a325cb30(param_1,2);
  uVar3 = FUN_7ff7a3409010(iVar2,uVar3);
  lVar4 = FUN_7ff7a38fa3d0(&DAT_7ff7a3ccb10c,uVar3);
  if (lVar4 == 0) {
    puVar1 = *(undefined4 **)(param_1 + 0x48);
    *puVar1 = 0;
    *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
    return 1;
  }
  lVar5 = -1;
  do {
    lVar5 = lVar5 + 1;
  } while (*(char *)(lVar4 + lVar5) != '\0');
  FUN_7ff7a3294620(param_1,lVar4);
  return 1;
}

