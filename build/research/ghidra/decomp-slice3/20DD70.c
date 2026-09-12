// image offset 0x20DD70 address 7ff7a339dd70

longlong * FUN_7ff7a339dd70(longlong *param_1,undefined8 param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  longlong lVar4;
  longlong lVar5;
  longlong local_res18 [2];
  
  uVar3 = FUN_7ff7a39c9370(param_2);
  lVar4 = FUN_7ff7a39cab50(uVar3);
  if (lVar4 == 0) {
    *param_1 = 0;
  }
  else {
    lVar5 = FUN_7ff7a39c9390(param_2);
    thunk_FUN_7ff7b4acb014(lVar4,local_res18,lVar5,lVar5 + 0x19,lVar5 + 0x41a,lVar5 + 0x820);
    *param_1 = local_res18[0];
    if (local_res18[0] != 0) {
      LOCK();
      *(int *)(local_res18[0] + 8) = *(int *)(local_res18[0] + 8) + 1;
      UNLOCK();
      if (local_res18[0] != 0) {
        LOCK();
        piVar1 = (int *)(local_res18[0] + 8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if ((iVar2 == 1) && (local_res18[0] != 0)) {
          FUN_7ff7a3c89b70(local_res18[0],1);
          return param_1;
        }
      }
    }
  }
  return param_1;
}

