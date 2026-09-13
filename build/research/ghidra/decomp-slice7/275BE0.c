// image offset 0x275BE0 address 7ff7a3405be0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_7ff7a3405be0(int param_1,int param_2,int param_3)

{
  longlong lVar1;
  uint uVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int *piVar7;
  longlong lVar8;
  uint *puVar9;
  int iVar10;
  int iVar11;
  undefined8 *puVar12;
  int iVar13;
  undefined8 *puVar14;
  longlong lVar15;
  longlong lVar16;
  undefined1 auStack_8a8 [32];
  undefined1 auStack_888 [64];
  int aiStack_848 [256];
  undefined1 auStack_448 [1024];
  ulonglong uStack_48;
  
  uStack_48 = _DAT_7ff7a4152aa8 ^ (ulonglong)auStack_8a8;
  cVar3 = func_0x7ff7a340a1f0();
  if (cVar3 != '\0') {
    pcVar6 = (char *)FUN_7ff7a3261ba0(param_2,6);
    if ((pcVar6 != (char *)0x0) && (*pcVar6 != '\0')) {
      FUN_7ff7a32638e0(param_1,param_2);
    }
    cVar3 = func_0x7ff7a37e2440(param_2);
    iVar13 = 0;
    if ((cVar3 != '\0') &&
       (iVar4 = FUN_7ff7a36321d0(param_1), 8 < *(int *)((longlong)iVar4 * 0x7b8 + 0x7ff7a4d3f4e4)))
    {
      func_0x7ff7a326c720(auStack_888,auStack_448,0x3fc);
      func_0x7ff7a326dad0(auStack_888,0x62);
      func_0x7ff7a3c48920(aiStack_848,0,0x400);
      iVar10 = 0;
      piVar7 = aiStack_848;
      iVar11 = 0;
      do {
        iVar5 = FUN_7ff7a343eea0(param_1,iVar11);
        if (0 < iVar5) {
          *piVar7 = iVar5;
          iVar10 = iVar10 + 1;
        }
        iVar11 = iVar11 + 1;
        piVar7 = piVar7 + 1;
      } while (iVar11 < 0x100);
      func_0x7ff7a326dd60(auStack_888,iVar10);
      iVar10 = 0;
      piVar7 = aiStack_848;
      do {
        iVar11 = *piVar7;
        if (0 < iVar11) {
          func_0x7ff7a326dd60(auStack_888,iVar10);
          func_0x7ff7a326dd60(auStack_888,iVar11);
        }
        iVar10 = iVar10 + 1;
        piVar7 = piVar7 + 1;
      } while (iVar10 < 0x100);
      FUN_7ff7a31f0740(iVar4,auStack_888);
    }
    pcVar6 = (char *)FUN_7ff7a3261ba0(param_2,0x15);
    if ((pcVar6 != (char *)0x0) && (*pcVar6 == '1')) {
      lVar8 = (longlong)param_1 * 0x194;
      puVar9 = (uint *)(lVar8 + 0x7ff7ab0f6890);
      uVar2 = *puVar9;
      if (0 < (int)uVar2) {
        piVar7 = (int *)(lVar8 + 0x7ff7ab0f6894);
        do {
          if (*piVar7 == param_2) goto code_r0x7ff7a3405db8;
          iVar13 = iVar13 + 1;
          piVar7 = piVar7 + 2;
        } while (iVar13 < (int)uVar2);
      }
      iVar13 = -1;
code_r0x7ff7a3405db8:
      if (param_3 == 0) {
        if (iVar13 != -1) {
          lVar16 = (longlong)iVar13;
          lVar15 = (longlong)(int)(uVar2 - 1);
          if (lVar16 < lVar15) {
            lVar1 = lVar8 + lVar16 * 8;
            puVar12 = (undefined8 *)(lVar1 + 0x7ff7ab0f689c);
            puVar14 = (undefined8 *)(lVar1 + 0x7ff7ab0f6894);
            for (lVar16 = lVar15 - lVar16; lVar16 != 0; lVar16 = lVar16 + -1) {
              *puVar14 = *puVar12;
              puVar12 = puVar12 + 1;
              puVar14 = puVar14 + 1;
            }
          }
          func_0x7ff7a340c980(lVar8 + lVar15 * 8 + 0x7ff7ab0f6894);
          *puVar9 = *puVar9 - 1;
        }
      }
      else if (iVar13 == -1) {
        if (uVar2 < 0x32) {
          *(int *)(lVar8 + (longlong)(int)uVar2 * 8 + 0x7ff7ab0f6894) = param_2;
          *(int *)(lVar8 + (longlong)(int)*puVar9 * 8 + 0x7ff7ab0f6898) = param_3;
          *puVar9 = *puVar9 + 1;
        }
      }
      else {
        *(int *)(lVar8 + (longlong)iVar13 * 8 + 0x7ff7ab0f6898) = param_3;
      }
    }
  }
  FUN_7ff7a3c46050(uStack_48 ^ (ulonglong)auStack_8a8);
  return;
}

