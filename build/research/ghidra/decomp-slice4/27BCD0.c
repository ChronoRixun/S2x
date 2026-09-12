// image offset 0x27BCD0 address 7ff7a340bcd0

void FUN_7ff7a340bcd0(undefined8 param_1)

{
  short sVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  longlong lVar9;
  longlong lVar10;
  byte *pbVar11;
  longlong lVar12;
  int *piVar13;
  short *psVar14;
  longlong lVar15;
  char cVar16;
  bool bVar17;
  longlong local_res10;
  longlong local_res18;
  ulonglong uVar8;
  
  bVar17 = false;
  iVar4 = FUN_7ff7a39c9370();
  lVar15 = (longlong)iVar4;
  FUN_7ff7a39c9400(&local_res10,param_1);
  if (local_res10 != 0) {
    iVar4 = FUN_7ff7a3bcdb50();
    bVar17 = iVar4 == 0x1f44;
  }
  iVar4 = 0;
  if (0 < *(int *)(&DAT_7ff7ab2dd9cc + lVar15 * 0x16a0)) {
    lVar9 = lVar15 * 0xc8438;
    psVar14 = (short *)(&DAT_7ff7ab2dc3de + lVar15 * 0x16a0);
    local_res18 = lVar9;
    do {
      iVar2 = *(int *)(psVar14 + -0x23);
      pcVar7 = (char *)FUN_7ff7a38fa3d0(&DAT_7ff7a3cc62d4);
      lVar10 = -1;
      do {
        lVar10 = lVar10 + 1;
      } while (pcVar7[lVar10] != '\0');
      uVar5 = 0;
      uVar6 = uVar5;
      if (pcVar7 != (char *)0x0) {
        lVar12 = 0;
        cVar16 = *pcVar7;
        uVar6 = 0;
        if (cVar16 != '\0') {
          lVar10 = (longlong)((int)lVar10 + 1);
          do {
            if ((lVar10 != 0) && (uVar6 = uVar5, lVar10 <= lVar12)) break;
            uVar5 = uVar5 * 0x1f + (int)cVar16;
            lVar12 = lVar12 + 1;
            cVar16 = pcVar7[lVar12];
            uVar6 = uVar5;
          } while (cVar16 != '\0');
        }
      }
      uVar6 = uVar6 & 0x1fff;
      uVar8 = (ulonglong)uVar6;
      sVar1 = *(short *)(&DAT_7ff7ab104178 + uVar8 * 2 + lVar9);
      while (sVar1 != 0) {
        sVar1 = *(short *)(&DAT_7ff7ab100178 + (ulonglong)uVar6 * 2 + lVar9);
        piVar13 = (int *)(&DAT_7ff7ab108178 + (longlong)sVar1 * 0x68 + lVar9);
        if (iVar2 == *piVar13) {
          if (sVar1 != -1) {
            pbVar11 = &DAT_7ff7ab1c6858 + local_res18 + sVar1;
            bVar3 = *pbVar11;
            if ((bVar3 & 4) == 0) {
              bVar3 = bVar3 | 4;
              *pbVar11 = bVar3;
              (&DAT_7ff7ab32b568)[lVar15] = (&DAT_7ff7ab32b568)[lVar15] + 1;
            }
            if ((bVar3 & 8) != 0) {
              *pbVar11 = bVar3 & 0xf7;
            }
            if (((piVar13 != (int *)0x0) && (bVar17)) && (*psVar14 == (short)piVar13[6])) {
              *(short *)(piVar13 + 6) = (short)piVar13[6] + 1;
            }
          }
          break;
        }
        uVar6 = (int)uVar8 + 1U & 0x1fff;
        uVar8 = (ulonglong)uVar6;
        sVar1 = *(short *)(&DAT_7ff7ab104178 + uVar8 * 2 + lVar9);
      }
      iVar4 = iVar4 + 1;
      psVar14 = psVar14 + 0x60;
    } while (iVar4 < *(int *)(&DAT_7ff7ab2dd9cc + lVar15 * 0x16a0));
  }
  if (local_res10 != 0) {
    LOCK();
    piVar13 = (int *)(local_res10 + 8);
    iVar4 = *piVar13;
    *piVar13 = *piVar13 + -1;
    UNLOCK();
    if ((iVar4 == 1) && (local_res10 != 0)) {
      FUN_7ff7a3c89b70(local_res10,1);
    }
  }
  return;
}

