// image offset 0x278480 address 7ff7a3408480

undefined8 FUN_7ff7a3408480(int param_1,longlong param_2,uint param_3,undefined4 *param_4)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char cVar6;
  uint uVar7;
  char *pcVar8;
  ulonglong uVar9;
  int iVar10;
  longlong lVar11;
  int *piVar12;
  longlong lVar13;
  uint uVar14;
  longlong lVar15;
  undefined *puVar16;
  longlong lVar17;
  longlong lVar18;
  longlong lVar19;
  
  if ((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) {
    lVar18 = (longlong)param_1;
    lVar15 = lVar18 * 0x6c;
    puVar16 = &DAT_7ff7ab2fa608 + lVar15;
    FUN_7ff7a339cb20(puVar16);
    uVar14 = 0;
    if (param_3 != 0) {
      lVar13 = lVar18 * 0xc8438;
      lVar19 = 0;
      do {
        iVar2 = *(int *)(param_2 + lVar19 * 8);
        pcVar8 = (char *)FUN_7ff7a38fa3d0(&DAT_7ff7a3cc62d4,iVar2);
        uVar7 = 0;
        if (pcVar8 != (char *)0x0) {
          cVar6 = *pcVar8;
          uVar7 = 0;
          lVar17 = 0;
          if (cVar6 != '\0') {
            lVar11 = -1;
            do {
              lVar11 = lVar11 + 1;
            } while (pcVar8[lVar11] != '\0');
            lVar11 = (longlong)((int)lVar11 + 1);
            do {
              if ((lVar11 != 0) && (lVar11 <= lVar17)) break;
              lVar17 = lVar17 + 1;
              iVar10 = (int)cVar6;
              cVar6 = pcVar8[lVar17];
              uVar7 = uVar7 * 0x1f + iVar10;
            } while (cVar6 != '\0');
          }
        }
        uVar7 = uVar7 & 0x1fff;
        uVar9 = (ulonglong)uVar7;
        sVar1 = *(short *)(&DAT_7ff7ab104178 + uVar9 * 2 + lVar13);
        while( true ) {
          if (sVar1 == 0) {
            return 0;
          }
          piVar12 = (int *)(&DAT_7ff7ab108178 +
                           (longlong)*(short *)(&DAT_7ff7ab100178 + (ulonglong)uVar7 * 2 + lVar13) *
                           0x68 + lVar13);
          if (iVar2 == *piVar12) break;
          uVar7 = (int)uVar9 + 1U & 0x1fff;
          uVar9 = (ulonglong)uVar7;
          sVar1 = *(short *)(&DAT_7ff7ab104178 + uVar9 * 2 + lVar13);
        }
        if (piVar12 == (int *)0x0) {
          return 0;
        }
        if ((uint)piVar12[1] < *(uint *)(param_2 + 4 + lVar19 * 8)) {
          return 0;
        }
        uVar14 = uVar14 + 1;
        *(undefined4 *)(puVar16 + (ulonglong)*(ushort *)(&DAT_7ff7ab2fa672 + lVar15) * 4) =
             *(undefined4 *)(param_2 + lVar19 * 8);
        *(undefined4 *)
         (lVar15 + 0x7ff7ab2fa630 + (ulonglong)*(ushort *)(&DAT_7ff7ab2fa672 + lVar15) * 4) =
             *(undefined4 *)(param_2 + 4 + lVar19 * 8);
        *(short *)(&DAT_7ff7ab2fa672 + lVar15) = *(short *)(&DAT_7ff7ab2fa672 + lVar15) + 1;
        lVar11 = lVar19 + lVar18 * 10;
        lVar17 = lVar19 * 8;
        lVar19 = lVar19 + 1;
        *(undefined4 *)((longlong)&DAT_7ff7ab290a40 + lVar11 * 4) =
             *(undefined4 *)(param_2 + lVar17);
      } while (uVar14 < param_3);
    }
    uVar3 = param_4[1];
    uVar4 = param_4[2];
    uVar5 = param_4[3];
    *(undefined4 *)(&DAT_7ff7ab2fa658 + lVar15) = *param_4;
    *(undefined4 *)(lVar15 + 0x7ff7ab2fa65c) = uVar3;
    *(undefined4 *)(lVar15 + 0x7ff7ab2fa660) = uVar4;
    *(undefined4 *)(lVar15 + 0x7ff7ab2fa664) = uVar5;
    *(undefined8 *)(&DAT_7ff7ab2fa668 + lVar15) = *(undefined8 *)(param_4 + 4);
    (&DAT_7ff7ab2fa670)[lVar15] = *(undefined1 *)(param_4 + 6);
    lVar15 = FUN_7ff7a33981b0(5,param_1);
    cVar6 = FUN_7ff7a39c9650(lVar15);
    if ((cVar6 != '\0') && (cVar6 = FUN_7ff7a39c9710(lVar15), cVar6 != '\0')) {
      FUN_7ff7a39c9700(lVar15,puVar16);
      *(undefined1 *)(lVar15 + 2) = 1;
      *(code **)(lVar15 + 0x30) = thunk_FUN_7ff7a33522e6;
      *(code **)(lVar15 + 0x40) = FUN_7ff7a340a640;
      *(code **)(lVar15 + 0x38) = FUN_7ff7a340a6b0;
      FUN_7ff7a39c97e0(lVar15);
      return 1;
    }
  }
  return 0;
}

