// image offset 0x27DD30 address 7ff7a340dd30

ulonglong FUN_7ff7a340dd30(int param_1,int *param_2,int param_3,undefined1 param_4,void *param_5,
                          byte param_6)

{
  short sVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  char *pcVar5;
  longlong lVar6;
  uint uVar7;
  short sVar9;
  ulonglong uVar10;
  int *piVar11;
  ulonglong uVar12;
  uint uVar13;
  longlong lVar14;
  char cVar15;
  ulonglong uVar8;

  iVar2 = *param_2;
  lVar4 = (longlong)param_1 * 0xc8438;
  pcVar5 = (char *)FUN_7ff7a38fa3d0(&DAT_7ff7a3cc62d4,iVar2);
  uVar12 = 0;
  uVar13 = 0;
  lVar14 = -1;
  uVar7 = 0;
  if ((pcVar5 != (char *)0x0) && (cVar15 = *pcVar5, cVar15 != '\0')) {
    lVar6 = -1;
    do {
      lVar6 = lVar6 + 1;
    } while (pcVar5[lVar6] != '\0');
    lVar6 = (longlong)((int)lVar6 + 1);
    uVar8 = uVar12;
    uVar10 = uVar12;
    do {
      uVar7 = (uint)uVar8;
      if ((lVar6 != 0) && (lVar6 <= (longlong)uVar10)) break;
      uVar10 = uVar10 + 1;
      iVar3 = (int)cVar15;
      cVar15 = pcVar5[uVar10];
      uVar7 = uVar7 * 0x1f + iVar3;
      uVar8 = (ulonglong)uVar7;
    } while (cVar15 != '\0');
  }
  uVar8 = (ulonglong)(uVar7 & 0x1fff);
  sVar1 = *(short *)(&DAT_7ff7ab104178 + uVar8 * 2 + lVar4);
  while (sVar1 != 0) {
    sVar1 = *(short *)(&DAT_7ff7ab100178 + uVar8 * 2 + lVar4);
    uVar10 = (ulonglong)sVar1;
    piVar11 = (int *)(&DAT_7ff7ab108178 + uVar10 * 0x68 + lVar4);
    if (iVar2 == *piVar11) {
      if (piVar11 == (int *)0x0) goto LAB_7ff7a340de26;
      uVar12 = uVar10;
      if (param_3 == 1) {
        if ((param_2[2] == -1) && (*(longlong *)(param_2 + 4) == 0x7fffffffffffffff)) {
          piVar11[1] = piVar11[1] + param_2[1];
        }
        else {
          *(longlong *)(piVar11 + 4) = *(longlong *)(piVar11 + 4) + *(longlong *)(param_2 + 4);
        }
        *(short *)(piVar11 + 6) = (short)piVar11[6] + 1;
        (&DAT_7ff7ab1c6858)[lVar4 + uVar10] = (&DAT_7ff7ab1c6858)[lVar4 + uVar10] | 2;
      }
      else {
        FUN_7ff7a340ca20(param_1,sVar1,param_2);
      }
      if (param_6 != 0) {
        lVar4 = uVar12 * 0x68 + lVar4;
        (&DAT_7ff7ab1081d8)[lVar4] = param_6;
        memcpy(&DAT_7ff7ab108198 + lVar4,param_5,(ulonglong)param_6);
      }
      FUN_7ff7a340d920(param_1,*param_2,param_4);
      FUN_7ff7a3405be0(param_1,*param_2,param_2[1]);
      goto LAB_7ff7a340e022;
    }
    uVar8 = (ulonglong)((int)uVar8 + 1U & 0x1fff);
    sVar1 = *(short *)(&DAT_7ff7ab104178 + uVar8 * 2 + lVar4);
  }
  uVar10 = 0xffffffff;
LAB_7ff7a340de26:
  uVar7 = *(uint *)(&DAT_7ff7ab1c85a4 + lVar4);
  if (uVar7 < 0x1d4c) {
    FUN_7ff7a340ca20(param_1,uVar7 & 0xffff,param_2);
    iVar2 = *param_2;
    pcVar5 = (char *)FUN_7ff7a38fa3d0(&DAT_7ff7a3cc62d4,iVar2);
    if ((pcVar5 != (char *)0x0) && (cVar15 = *pcVar5, cVar15 != '\0')) {
      do {
        lVar14 = lVar14 + 1;
      } while (pcVar5[lVar14] != '\0');
      iVar3 = (int)lVar14 + 1;
      uVar8 = uVar12;
      do {
        uVar13 = (uint)uVar8;
        if ((iVar3 != 0) && ((longlong)iVar3 <= (longlong)uVar12)) break;
        uVar12 = uVar12 + 1;
        uVar13 = uVar13 * 0x1f + (int)cVar15;
        uVar8 = (ulonglong)uVar13;
        cVar15 = pcVar5[uVar12];
      } while (cVar15 != '\0');
    }
    uVar12 = (ulonglong)(uVar13 & 0x1fff);
    sVar9 = 1;
    sVar1 = *(short *)(&DAT_7ff7ab104178 + uVar12 * 2 + lVar4);
    while (sVar1 != 0) {
      if (iVar2 == *(int *)(&DAT_7ff7ab100178 +
                           (longlong)*(short *)(&DAT_7ff7ab100178 + uVar12 * 2 + lVar4) * 0x68 +
                           0x8000 + lVar4)) goto LAB_7ff7a340def6;
      sVar9 = sVar9 + 1;
      uVar13 = (int)uVar12 + 1U & 0x1fff;
      uVar12 = (ulonglong)uVar13;
      sVar1 = *(short *)(&DAT_7ff7ab104178 + (ulonglong)uVar13 * 2 + lVar4);
    }
    *(short *)(&DAT_7ff7ab100178 + uVar12 * 2 + lVar4) = (short)uVar7;
    *(short *)(&DAT_7ff7ab104178 + uVar12 * 2 + lVar4) = sVar9;
LAB_7ff7a340def6:
    if (param_6 != 0) {
      lVar4 = (longlong)(short)uVar7 * 0x68 + lVar4;
      (&DAT_7ff7ab1081d8)[lVar4] = param_6;
      memcpy(&DAT_7ff7ab108198 + lVar4,param_5,(ulonglong)param_6);
    }
    FUN_7ff7a340d920(param_1,*param_2,param_4);
    FUN_7ff7a3405430(param_1,*param_2,param_2[1]);
    uVar10 = (ulonglong)(uVar7 & 0xffff);
  }
  else {
LAB_7ff7a340e022:
    uVar10 = uVar10 & 0xffff;
  }
  return uVar10;
}
