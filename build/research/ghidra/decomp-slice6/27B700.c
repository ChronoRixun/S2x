// image offset 0x27B700 address 7ff7a340b700

void FUN_7ff7a340b700(undefined8 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  longlong lVar4;
  undefined8 *puVar5;
  ulonglong uVar6;
  int *piVar7;
  int iVar8;
  uint uVar9;
  ulonglong uVar10;
  longlong lVar11;
  longlong local_res10;
  
  uVar1 = FUN_7ff7a39c9370();
  lVar4 = FUN_7ff7a39c9390(param_1);
  puVar5 = (undefined8 *)FUN_7ff7a39c9400(&local_res10,param_1);
  uVar2 = FUN_7ff7a3bcdb60(*puVar5);
  *(undefined4 *)(lVar4 + 0x15950) = uVar2;
  if (local_res10 != 0) {
    LOCK();
    piVar7 = (int *)(local_res10 + 8);
    iVar8 = *piVar7;
    *piVar7 = *piVar7 + -1;
    UNLOCK();
    if ((iVar8 == 1) && (local_res10 != 0)) {
      FUN_7ff7a3c89b70(local_res10,1);
    }
  }
  *(undefined1 *)(lVar4 + 0x15964) = 0;
  uVar10 = 0;
  uVar3 = 0;
  if (*(int *)(lVar4 + 0x15950) != 0) {
    do {
      lVar11 = uVar10 * 0x370 + lVar4;
      uVar6 = 0;
      piVar7 = &DAT_7ff7ab2938b0;
      do {
        if (*(int *)(lVar11 + 0x20) == *piVar7) {
          if (uVar6 * 0x2e8 != -0x7ff7ab2938b0) goto LAB_7ff7a340b837;
          break;
        }
        uVar3 = (int)uVar6 + 1;
        uVar6 = (ulonglong)uVar3;
        piVar7 = piVar7 + 0xba;
      } while (uVar3 < 400);
      uVar3 = 0;
      piVar7 = &DAT_7ff7ab2938b0;
      do {
        if (*piVar7 == 0) {
          if (uVar3 != 0xffffffff) {
            FUN_7ff7a339c250(lVar11,&DAT_7ff7ab2938b0 + (longlong)(int)uVar3 * 0xba);
            FUN_7ff7a339d440(&DAT_7ff7ab2938c0 + (longlong)(int)uVar3 * 0x2e8);
          }
          break;
        }
        uVar3 = uVar3 + 1;
        piVar7 = piVar7 + 0xba;
      } while (uVar3 < 400);
LAB_7ff7a340b837:
      uVar9 = (int)uVar10 + 1;
      uVar10 = (ulonglong)uVar9;
      uVar3 = *(uint *)(lVar4 + 0x15950);
    } while (uVar9 < uVar3);
  }
  if (uVar3 < *(uint *)(lVar4 + 0x1595c)) {
    DAT_7ff7ab2938a8 = 1;
  }
  else {
    uVar2 = *(undefined4 *)(lVar4 + 0x15960);
    iVar8 = *(int *)(lVar4 + 0x15958) + 1;
    if (iVar8 == 1) {
      FUN_7ff7a339d680(&DAT_7ff7ab2938a8);
      DAT_7ff7ab2938ac = uVar2;
    }
    FUN_7ff7a3408d30(uVar1,iVar8,uVar2,FUN_7ff7a340b700,FUN_7ff7a340b6c0);
  }
  return;
}

