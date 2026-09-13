// image offset 0x276330 address 7ff7a3406330

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a3406330(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  ulonglong uVar7;
  undefined *puVar8;
  uint *puVar9;
  longlong lVar10;
  uint *puVar11;
  undefined1 auStack_1328 [32];
  int local_1308;
  uint local_12f8 [1200];
  ulonglong local_38;
  undefined8 local_30;
  
  local_30 = 0x7ff7a3406352;
  local_38 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_1328;
  iVar4 = 0;
  do {
    iVar3 = FUN_7ff7a34094f0(param_1,local_12f8,300,iVar4);
    lVar10 = 0;
    local_1308 = iVar4 + iVar3;
    if (0 < iVar3) {
      puVar11 = local_12f8 + 1;
      do {
        uVar1 = puVar11[-1];
        pcVar6 = (char *)FUN_7ff7a3261ba0(uVar1,0x18);
        if (((((pcVar6 == (char *)0x0) || (iVar4 = atoi(pcVar6), iVar4 < 1)) && (*puVar11 == 1)) &&
            ((1 < puVar11[1] &&
             (pcVar6 = (char *)FUN_7ff7a3261ba0(uVar1,0x1e), pcVar6 != (char *)0x0)))) &&
           (iVar4 = atoi(pcVar6), 0 < iVar4)) {
          iVar4 = FUN_7ff7a37e2250(uVar1);
          puVar8 = &DAT_7ff7ab0f6de0;
          if (iVar4 != 0) {
            puVar8 = &DAT_7ff7ab0f6bc0;
          }
          uVar7 = 0;
          puVar9 = (uint *)(puVar8 + (longlong)param_1 * 0x110);
          uVar2 = *puVar9;
          if (uVar2 != 0) {
            do {
              if ((puVar9[uVar7 * 2 + 2] == 1) && (puVar9[uVar7 * 2 + 1] == uVar1))
              goto LAB_7ff7a340644d;
              uVar5 = (int)uVar7 + 1;
              uVar7 = (ulonglong)uVar5;
            } while (uVar5 < uVar2);
          }
          if (0x1d < uVar2) break;
          puVar9[(ulonglong)uVar2 * 2 + 1] = uVar1;
          puVar9[(ulonglong)*puVar9 * 2 + 2] = 1;
          *puVar9 = *puVar9 + 1;
        }
LAB_7ff7a340644d:
        lVar10 = lVar10 + 1;
        puVar11 = puVar11 + 4;
      } while (lVar10 < iVar3);
    }
    iVar4 = local_1308;
    if (iVar3 != 300) {
      return;
    }
  } while( true );
}

