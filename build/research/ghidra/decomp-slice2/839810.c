// image offset 0x839810 address 7ff7a39c9810

void FUN_7ff7a39c9810(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  int iVar3;
  longlong lVar4;
  undefined4 uVar5;
  int iVar6;
  longlong local_res8;
  longlong local_res10;
  
  *(undefined4 *)(param_1 + 8) = 3;
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  uVar5 = FUN_7ff7a3941290();
  *(undefined4 *)(param_1 + 0x14) = uVar5;
  FUN_7ff7a3c89b70(&local_res8,param_1);
  if (local_res8 != 0) {
    plVar1 = (longlong *)(param_1 + 0x18);
    if (&local_res8 != plVar1) {
      if (*plVar1 != 0) {
        LOCK();
        piVar2 = (int *)(*plVar1 + 8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if ((iVar6 == 1) && (*plVar1 != 0)) {
          FUN_7ff7a3c89b70(*plVar1,1);
        }
      }
      *plVar1 = local_res8;
      if (local_res8 != 0) {
        LOCK();
        *(int *)(local_res8 + 8) = *(int *)(local_res8 + 8) + 1;
        UNLOCK();
      }
    }
    iVar6 = 2;
    lVar4 = *plVar1;
    local_res10 = lVar4;
    if (lVar4 != 0) {
      LOCK();
      *(int *)(lVar4 + 8) = *(int *)(lVar4 + 8) + 1;
      UNLOCK();
      uVar5 = FUN_7ff7a3c89b70(lVar4);
      iVar6 = FUN_7ff7a39cd330(uVar5,0);
      LOCK();
      piVar2 = (int *)(lVar4 + 8);
      iVar3 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar3 == 1) {
        FUN_7ff7a3c89b70(local_res10,1);
      }
    }
    if (iVar6 == 0) {
      if (*(char *)(param_1 + 3) == '\0') {
        lVar4 = *plVar1;
        uVar5 = FUN_7ff7a3397870(*(undefined4 *)(param_1 + 0xc));
        FUN_7ff7a3bcde40(lVar4,uVar5);
      }
      goto LAB_7ff7a39c9930;
    }
  }
  *(undefined4 *)(param_1 + 8) = 5;
LAB_7ff7a39c9930:
  if (local_res8 != 0) {
    LOCK();
    piVar2 = (int *)(local_res8 + 8);
    iVar6 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if ((iVar6 == 1) && (local_res8 != 0)) {
      FUN_7ff7a3c89b70(local_res8,1);
    }
  }
  return;
}

