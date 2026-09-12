// image offset 0x13B0B0 address 7ff7a32cb0b0

void FUN_7ff7a32cb0b0(undefined8 param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  char cVar10;
  int iVar11;
  uint uVar12;
  undefined4 uVar13;
  longlong lVar14;
  int *piVar15;
  undefined8 uVar16;
  uint uVar17;
  int *piVar18;
  longlong lVar19;
  longlong lVar20;
  longlong lVar21;
  longlong lVar22;
  undefined4 local_res10 [6];
  undefined4 local_48;
  undefined4 uStack_44;
  uint uStack_40;

  uVar12 = 0;
  uStack_40 = uStack_40 & 0xffff0000;
  iVar11 = FUN_7ff7a39c9370();
  lVar19 = (longlong)iVar11;
  lVar14 = FUN_7ff7a39c9390(param_1);
  lVar20 = lVar19 * 0x1908;
  piVar1 = *(int **)(lVar14 + 0xf0);
  if ((&DAT_7ff7a8e26560)[lVar20] != '\0') {
    piVar15 = (int *)(&DAT_7ff7a8e24c6c + lVar20);
    uVar17 = uVar12;
    do {
      if (*piVar15 == *piVar1) {
        if (uVar17 != 0xffffffff) {
          lVar21 = (longlong)(int)uVar17 * 0x10 + lVar20;
          lVar20 = (longlong)(int)uVar17 * 0x30 + lVar20;
          uVar13 = *(undefined4 *)(&DAT_7ff7a8e24c64 + lVar20);
          uVar3 = *(undefined4 *)(lVar20 + 0x7ff7a8e24c68);
          uVar4 = *(undefined4 *)(&DAT_7ff7a8e24c6c + lVar20);
          *(undefined4 *)(&DAT_7ff7a8e24c88 + lVar20) = 2;
          uVar5 = *(undefined4 *)(&DAT_7ff7a8e24c70 + lVar20);
          uVar6 = *(undefined4 *)(lVar20 + 0x7ff7a8e24c74);
          uVar7 = *(undefined4 *)(lVar20 + 0x7ff7a8e24c78);
          uVar8 = *(undefined4 *)(lVar20 + 0x7ff7a8e24c7c);
          iVar2 = -1;
          if (0 < *(int *)(&DAT_7ff7a8e24c64 + lVar20)) {
            iVar2 = *(int *)(&DAT_7ff7a8e24c64 + lVar20);
          }
          lVar22 = lVar19 * 0x13890;
          piVar18 = (int *)(&DAT_7ff7a923409c + lVar22);
          piVar15 = piVar18;
          uVar17 = uVar12;
          goto LAB_7ff7a32cb1c0;
        }
        break;
      }
      uVar17 = uVar17 + 1;
      piVar15 = piVar15 + 0xc;
    } while (uVar17 < 100);
  }
  goto LAB_7ff7a32cb346;
  while( true ) {
    uVar17 = uVar17 + 1;
    piVar15 = piVar15 + 0x10;
    if (999 < uVar17) break;
LAB_7ff7a32cb1c0:
    if (*piVar15 == *piVar1) {
      if ((uVar17 != 0xffffffff) && ((longlong)(int)uVar17 * 0x40 + lVar22 != -0x7ff7a9234090))
      goto LAB_7ff7a32cb264;
      break;
    }
  }
  do {
    if (*piVar18 == -1) {
      if (uVar12 != 0xffffffff) {
        local_48 = (undefined4)*(undefined8 *)(&DAT_7ff7a8e24c80 + lVar20);
        uStack_44 = (undefined4)((ulonglong)*(undefined8 *)(&DAT_7ff7a8e24c80 + lVar20) >> 0x20);
        lVar22 = (longlong)(int)uVar12 * 0x40 + lVar22;
        *(undefined4 *)(&DAT_7ff7a9234090 + lVar22) = *(undefined4 *)(&DAT_7ff7a8e24c60 + lVar20);
        *(undefined4 *)(&DAT_7ff7a9234094 + lVar22) = uVar13;
        *(undefined4 *)(&DAT_7ff7a9234098 + lVar22) = uVar3;
        *(undefined4 *)(&DAT_7ff7a923409c + lVar22) = uVar4;
        *(undefined4 *)(&DAT_7ff7a92340a0 + lVar22) = uVar5;
        *(undefined4 *)(lVar22 + 0x7ff7a92340a4) = uVar6;
        *(undefined4 *)(&DAT_7ff7a92340a8 + lVar22) = uVar7;
        *(undefined4 *)(lVar22 + 0x7ff7a92340ac) = uVar8;
        *(undefined4 *)(&DAT_7ff7a92340b0 + lVar22) = local_48;
        *(undefined4 *)(lVar22 + 0x7ff7a92340b4) = uStack_44;
        *(uint *)(&DAT_7ff7a92340b8 + lVar22) = uStack_40;
        *(undefined4 *)(&DAT_7ff7a92340bc + lVar22) = 0;
        *(undefined4 *)(&DAT_7ff7a92340c0 + lVar22) = 0;
        *(undefined4 *)(lVar22 + 0x7ff7a92340c4) = 0;
        *(undefined4 *)(&DAT_7ff7a92340c8 + lVar22) = 2;
        *(int *)(&DAT_7ff7a92340cc + lVar22) = iVar2;
        if ((undefined4 *)(&DAT_7ff7a8e25f20 + lVar21) == (undefined4 *)0x0) {
          *(undefined8 *)(&DAT_7ff7a92340b0 + lVar22) = 0;
        }
        else {
          uVar13 = *(undefined4 *)(lVar21 + 0x7ff7a8e25f24);
          uVar3 = *(undefined4 *)(lVar21 + 0x7ff7a8e25f28);
          uVar4 = *(undefined4 *)(lVar21 + 0x7ff7a8e25f2c);
          lVar20 = (lVar19 * 0x1389 + (longlong)(int)uVar12) * 0x10;
          *(undefined4 *)(&DAT_7ff7a9243a90 + lVar20) = *(undefined4 *)(&DAT_7ff7a8e25f20 + lVar21);
          *(undefined4 *)(lVar20 + 0x7ff7a9243a94) = uVar13;
          *(undefined4 *)(lVar20 + 0x7ff7a9243a98) = uVar3;
          *(undefined4 *)(lVar20 + 0x7ff7a9243a9c) = uVar4;
          *(undefined **)(&DAT_7ff7a92340b0 + lVar22) = &DAT_7ff7a9243a90 + lVar20;
        }
      }
      break;
    }
    uVar12 = uVar12 + 1;
    piVar18 = piVar18 + 0x10;
  } while (uVar12 < 1000);
LAB_7ff7a32cb264:
  cVar10 = FUN_7ff7a3630d90(iVar11,local_res10);
  if ((cVar10 != '\0') &&
     (cVar10 = FUN_7ff7a324d020(local_res10[0],"achievementEngine",DAT_7ff7a4d63d08), cVar10 != '\0'
     )) {
    FUN_7ff7a325c620("eventType",2,DAT_7ff7a4d63d08);
    FUN_7ff7a325c620(&DAT_7ff7a3cd07e4,*piVar1,DAT_7ff7a4d63d08);
    uVar9 = DAT_7ff7a4d63d08;
    uVar13 = FUN_7ff7a32c9dc0(*piVar1);
    FUN_7ff7a325c620(&DAT_7ff7a3cd03f8,uVar13,uVar9);
    uVar9 = DAT_7ff7a4d63d08;
    uVar16 = FUN_7ff7a39c9020(lVar14 + 0xd0);
    FUN_7ff7a325c810("transactionID",uVar16,uVar9);
    FUN_7ff7a325c3e0("dispatchChildren",1,DAT_7ff7a4d63d08);
    FUN_7ff7a325c3e0("success",1,DAT_7ff7a4d63d08);
    FUN_7ff7a324e7e0(DAT_7ff7a4d63d08);
  }
LAB_7ff7a32cb346:
  FUN_7ff7a3396000(lVar14);
  return;
}
