// image offset 0x27B230 address 7ff7a340b230

void FUN_7ff7a340b230(undefined8 param_1)

{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined8 *puVar6;
  int *piVar7;
  longlong lVar8;
  longlong local_res10;
  
  iVar3 = FUN_7ff7a39c9370();
  lVar8 = (longlong)iVar3 * 0x2e0;
  (&DAT_7ff7ab0ffe94)[lVar8] = 1;
  puVar6 = (undefined8 *)FUN_7ff7a39c9400(&local_res10,param_1);
  uVar4 = FUN_7ff7a3bcdb60(*puVar6);
  *(undefined4 *)(&DAT_7ff7ab0ffe90 + lVar8) = uVar4;
  if (local_res10 != 0) {
    LOCK();
    piVar7 = (int *)(local_res10 + 8);
    iVar1 = *piVar7;
    *piVar7 = *piVar7 + -1;
    UNLOCK();
    if ((iVar1 == 1) && (local_res10 != 0)) {
      FUN_7ff7a3c89b70(local_res10,1);
    }
  }
  piVar7 = (int *)(&DAT_7ff7ab0ffbdc + lVar8);
  lVar8 = 0xd;
  do {
    cVar2 = FUN_7ff7a325ece0(iVar3);
    if ((cVar2 != '\0') && ((char)piVar7[-1] == '\x01')) {
      iVar1 = *piVar7;
      uVar4 = FUN_7ff7a3819900(DAT_7ff7ad7912d4);
      FUN_7ff7a331e9e0(iVar3,uVar4,iVar1,0);
      uVar4 = FUN_7ff7a3819900(DAT_7ff7ad790fbc);
      iVar5 = FUN_7ff7a331de50(iVar3,uVar4,0);
      if (iVar1 < iVar5) {
        uVar4 = FUN_7ff7a3819900(DAT_7ff7ad790fbc);
        FUN_7ff7a331e9e0(iVar3,uVar4,iVar1,0);
      }
    }
    piVar7 = piVar7 + 0xe;
    lVar8 = lVar8 + -1;
  } while (lVar8 != 0);
  return;
}

