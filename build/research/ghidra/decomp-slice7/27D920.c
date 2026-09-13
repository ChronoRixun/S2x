// image offset 0x27D920 address 7ff7a340d920

void FUN_7ff7a340d920(int param_1,int param_2,char param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  longlong lVar4;
  int *piVar5;
  uint uVar6;
  ulonglong uVar7;
  longlong lVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  
  cVar1 = FUN_7ff7a34047a0(param_2);
  if ((cVar1 == '\0') && (cVar1 = FUN_7ff7a3405230(param_2), cVar1 == '\0')) {
    if (param_3 == '\0') {
      return;
    }
    lVar8 = (longlong)param_1 * 0xc8438;
    pcVar3 = (char *)FUN_7ff7a38fa3d0(&UNK_7ff7a3cc62d4);
    uVar7 = 0;
    uVar6 = 0;
    if ((pcVar3 != (char *)0x0) && (cVar1 = *pcVar3, cVar1 != '\0')) {
      lVar4 = -1;
      do {
        lVar4 = lVar4 + 1;
      } while (pcVar3[lVar4] != '\0');
      lVar4 = (longlong)((int)lVar4 + 1);
      uVar9 = uVar7;
      do {
        uVar6 = (uint)uVar7;
        if ((lVar4 != 0) && (lVar4 <= (longlong)uVar9)) break;
        uVar9 = uVar9 + 1;
        iVar2 = (int)cVar1;
        cVar1 = pcVar3[uVar9];
        uVar6 = uVar6 * 0x1f + iVar2;
        uVar7 = (ulonglong)uVar6;
      } while (cVar1 != '\0');
    }
    uVar7 = (ulonglong)(uVar6 & 0x1fff);
    if (*(short *)(lVar8 + 0x7ff7ab104178 + uVar7 * 2) == 0) {
      return;
    }
    while( true ) {
      uVar9 = (ulonglong)*(short *)(lVar8 + 0x7ff7ab100178 + uVar7 * 2);
      piVar5 = (int *)(lVar8 + 0x7ff7ab108178 + uVar9 * 0x68);
      if (param_2 == *piVar5) break;
      uVar6 = (int)uVar7 + 1U & 0x1fff;
      uVar7 = (ulonglong)uVar6;
      if (*(short *)(lVar8 + 0x7ff7ab104178 + (ulonglong)uVar6 * 2) == 0) {
        return;
      }
    }
    if (piVar5 == (int *)0x0) {
      return;
    }
    uVar10 = 0;
  }
  else {
    lVar8 = (longlong)param_1 * 0xc8438;
    pcVar3 = (char *)FUN_7ff7a38fa3d0(&UNK_7ff7a3cc62d4);
    uVar7 = 0;
    uVar6 = 0;
    if ((pcVar3 != (char *)0x0) && (cVar1 = *pcVar3, cVar1 != '\0')) {
      lVar4 = -1;
      do {
        lVar4 = lVar4 + 1;
      } while (pcVar3[lVar4] != '\0');
      lVar4 = (longlong)((int)lVar4 + 1);
      uVar9 = uVar7;
      do {
        uVar6 = (uint)uVar7;
        if ((lVar4 != 0) && (lVar4 <= (longlong)uVar9)) break;
        uVar9 = uVar9 + 1;
        iVar2 = (int)cVar1;
        cVar1 = pcVar3[uVar9];
        uVar6 = uVar6 * 0x1f + iVar2;
        uVar7 = (ulonglong)uVar6;
      } while (cVar1 != '\0');
    }
    uVar7 = (ulonglong)(uVar6 & 0x1fff);
    if (*(short *)(lVar8 + 0x7ff7ab104178 + uVar7 * 2) == 0) {
      return;
    }
    while( true ) {
      uVar9 = (ulonglong)*(short *)(lVar8 + 0x7ff7ab100178 + uVar7 * 2);
      piVar5 = (int *)(lVar8 + 0x7ff7ab108178 + uVar9 * 0x68);
      if (param_2 == *piVar5) break;
      uVar6 = (int)uVar7 + 1U & 0x1fff;
      uVar7 = (ulonglong)uVar6;
      if (*(short *)(lVar8 + 0x7ff7ab104178 + (ulonglong)uVar6 * 2) == 0) {
        return;
      }
    }
    if (piVar5 == (int *)0x0) {
      return;
    }
    uVar10 = 1;
  }
  FUN_7ff7a340a3a0(param_1,uVar9 & 0xffff,1,uVar10);
  return;
}

