// image offset 0x11F380 address 7ff7a32af380

undefined8 FUN_7ff7a32af380(longlong param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  longlong lVar5;
  longlong lVar6;
  float fVar7;
  
  if (((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2)
     && (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48))) {
    iVar2 = FUN_7ff7a3468d90(param_1);
    if (iVar2 != 0) {
      iVar2 = thunk_FUN_7ff7a3294bb0(param_1,2);
      if (iVar2 != 0) goto LAB_7ff7a32af3d5;
    }
  }
  FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
LAB_7ff7a32af3d5:
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar7 = (float)FUN_7ff7a3469aa0(param_1);
    iVar2 = (int)fVar7;
  }
  else {
    iVar2 = 0;
  }
  uVar3 = FUN_7ff7a325cb30(param_1,2);
  uVar4 = FUN_7ff7a3409220(iVar2,uVar3);
  lVar5 = FUN_7ff7a38fa3d0(&DAT_7ff7a3ccb10c,uVar4);
  if (lVar5 == 0) {
    puVar1 = *(undefined4 **)(param_1 + 0x48);
    *puVar1 = 0;
    *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
    return 1;
  }
  lVar6 = -1;
  do {
    lVar6 = lVar6 + 1;
  } while (*(char *)(lVar5 + lVar6) != '\0');
  FUN_7ff7a3294620(param_1,lVar5);
  return 1;
}

