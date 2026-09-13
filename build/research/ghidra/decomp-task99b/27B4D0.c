// image offset 0x27B4D0 address 7ff7a340b4d0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_7ff7a340b4d0(undefined8 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  longlong lVar4;
  undefined8 *puVar5;
  int *piVar6;
  uint uVar7;
  longlong lVar8;
  uint uVar9;
  ulonglong uVar10;
  uint uVar11;
  longlong local_res18 [2];
  
  uVar2 = FUN_7ff7a39c9370();
  lVar4 = FUN_7ff7a39c9390(param_1);
  puVar5 = (undefined8 *)FUN_7ff7a39c9400(local_res18,param_1);
  uVar3 = FUN_7ff7a3bcdb60(*puVar5);
  *(undefined4 *)(lVar4 + 0x10b30) = uVar3;
  if (local_res18[0] != 0) {
    LOCK();
    piVar6 = (int *)(local_res18[0] + 8);
    iVar1 = *piVar6;
    *piVar6 = *piVar6 + -1;
    UNLOCK();
    if ((iVar1 == 1) && (local_res18[0] != 0)) {
      FUN_7ff7a3c89b70(local_res18[0],1);
    }
  }
  if (*(int *)(lVar4 + 0x10b30) != 0) {
    uVar7 = 0;
    uVar11 = 0;
    do {
      lVar8 = (ulonglong)uVar11 * 0x2a8 + lVar4;
      if (*(char *)(lVar4 + 0x10b34) == '\0') {
        uVar9 = 0;
        piVar6 = &DAT_7ff7ab290e70;
        do {
          if (*(int *)(lVar8 + 0x10) == *piVar6) {
            if ((ulonglong)uVar9 * 0x238 != -0x7ff7ab290c40) goto LAB_7ff7a340b633;
            break;
          }
          uVar9 = uVar9 + 1;
          piVar6 = piVar6 + 0x8e;
        } while (uVar9 < 0x14);
        uVar9 = 0;
        piVar6 = &DAT_7ff7ab290e70;
        do {
          if (*piVar6 == 0) {
            if (uVar9 != 0xffffffff) {
              FUN_7ff7a339c1a0(lVar8,&DAT_7ff7ab290c40 + (longlong)(int)uVar9 * 0x238);
              _DAT_7ff7ab2938a0 = _DAT_7ff7ab2938a0 + 1;
            }
            break;
          }
          uVar9 = uVar9 + 1;
          piVar6 = piVar6 + 0x8e;
        } while (uVar9 < 0x14);
      }
      else {
        uVar10 = 0;
        piVar6 = &DAT_7ff7ab2938b8;
        do {
          if ((piVar6[-2] != 0) && (*piVar6 == *(int *)(lVar8 + 0x10))) {
            FUN_7ff7a339c1a0(lVar8,&DAT_7ff7ab2938c0 + uVar10 * 0x2e8);
          }
          uVar9 = (int)uVar10 + 1;
          uVar10 = (ulonglong)uVar9;
          piVar6 = piVar6 + 0xba;
        } while (uVar9 < 400);
      }
LAB_7ff7a340b633:
      uVar11 = uVar11 + 1;
    } while (uVar11 < *(uint *)(lVar4 + 0x10b30));
    if (*(char *)(lVar4 + 0x10b34) == '\0') {
      FUN_7ff7a34052e0(uVar2,3);
    }
    else if (DAT_7ff7ab2938a8 != '\0') {
      piVar6 = &DAT_7ff7ab293af0;
      do {
        if ((piVar6[-0x90] != 0) && (piVar6[-0x8e] != *piVar6)) {
          return;
        }
        uVar7 = uVar7 + 1;
        piVar6 = piVar6 + 0xba;
      } while (uVar7 < 400);
      FUN_7ff7a3405360(uVar2,0x17,1);
    }
  }
  return;
}

