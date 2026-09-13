// image offset 0x270950 address 7ff7a3400950

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Type propagation algorithm not settling */

undefined8
FUN_7ff7a3400950(char *param_1,int *param_2,undefined1 *param_3,int param_4,undefined8 *param_5,
                int param_6,uint *param_7)

{
  int iVar1;
  int iVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  undefined8 uVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  longlong lVar9;
  char cVar10;
  uint uVar11;
  char *pcVar12;
  int iVar13;
  int *piVar14;
  undefined1 *puVar15;
  int *piVar16;
  ulonglong uVar17;
  undefined1 auStack_5f8 [32];
  char **local_5d8;
  uint local_5c8;
  undefined8 *local_5c0;
  char *local_5b8;
  undefined1 *local_5b0;
  int local_5a8;
  int local_5a4;
  int local_5a0;
  int iStack_59c;
  int iStack_598;
  int iStack_594;
  ulonglong local_590;
  ulonglong uStack_588;
  undefined8 local_580;
  undefined8 local_578;
  ulonglong uStack_570;
  ulonglong local_568;
  int local_560 [6];
  ulonglong auStack_548 [158];
  ulonglong local_58;
  
  local_58 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_5f8;
  local_5a0 = *param_2;
  iStack_59c = param_2[1];
  iStack_598 = param_2[2];
  iStack_594 = param_2[3];
  local_590 = *(ulonglong *)(param_2 + 4);
  uStack_588 = *(ulonglong *)(param_2 + 6);
  local_578 = param_7;
  local_5b8 = param_1;
  FUN_7ff7a34005f0(&DAT_7ff7a3cd6168,&local_5a0);
  FUN_7ff7a38f34d0("ui/htmlBoldFontMapping.csv");
  if (local_5c0 != (undefined8 *)0x0) {
    iVar6 = FUN_7ff7a38f3550();
    iVar13 = 0;
    if (0 < iVar6) {
      do {
        uVar8 = FUN_7ff7a38f3510(local_5c0,iVar13,1);
        iVar7 = FUN_7ff7a3b94f40(uVar8);
        if (iVar7 == 0) {
          local_590 = CONCAT44(local_590._4_4_,1);
          break;
        }
        iVar13 = iVar13 + 1;
      } while (iVar13 < iVar6);
    }
  }
  memset(&local_568,0,0x508);
  lVar9 = (longlong)(int)local_568;
  puVar15 = param_3 + param_4;
  *param_3 = 0;
  local_560[lVar9 * 10 + 2] = local_5a0;
  local_560[lVar9 * 10 + 3] = iStack_59c;
  local_560[lVar9 * 10 + 4] = iStack_598;
  local_560[lVar9 * 10 + 5] = iStack_594;
  auStack_548[lVar9 * 5] = local_590;
  auStack_548[lVar9 * 5 + 1] = uStack_588;
  iVar6 = (int)local_568 + 1;
  local_568._0_4_ = iVar6;
  if (0 < param_6) {
    *param_5 = param_3;
    *(int *)(param_5 + 1) = local_5a0;
    *(int *)((longlong)param_5 + 0xc) = iStack_59c;
    *(int *)(param_5 + 2) = iStack_598;
    *(int *)((longlong)param_5 + 0x14) = iStack_594;
    param_5[3] = local_590;
    param_5[4] = uStack_588;
  }
  local_5c8 = (uint)(0 < param_6);
  cVar10 = *param_1;
  uVar11 = (uint)(0 < param_6);
  if (cVar10 != '\0') {
    local_580 = (longlong)param_6;
    uVar17 = (ulonglong)(uint)(0 < param_6);
    param_5 = param_5 + uVar17 * 5;
    local_5c0 = param_5 + -5;
    piVar16 = (int *)(param_5 + 1);
    local_5b0 = puVar15;
    do {
      uVar11 = local_5c8;
      if (puVar15 <= param_3) break;
      if ((byte)(cVar10 - 1U) < 0x1f) {
        local_5b8 = param_1 + 1;
      }
      else {
        iVar13 = (int)param_3;
        if (cVar10 == '<') {
          piVar14 = (int *)0x0;
          local_5a4 = 0;
          local_5a8 = 0;
          if (0 < iVar6) {
            lVar9 = (longlong)iVar6;
            if (&uStack_588 + lVar9 * 5 != (ulonglong *)0x0) {
              local_590 = (&uStack_570)[lVar9 * 5];
              local_5a0 = *(int *)(&local_580 + lVar9 * 5);
              iStack_59c = *(int *)((longlong)&local_580 + lVar9 * 0x28 + 4);
              iStack_598 = *(int *)(&local_578 + lVar9 * 5);
              iStack_594 = *(int *)((longlong)&local_578 + lVar9 * 0x28 + 4);
              uStack_588 = (&local_568)[lVar9 * 5] & 0xffffffff00000000;
            }
          }
          local_5d8 = &local_5b8;
          FUN_7ff7a34011b0(param_1,&local_5a8,&local_5a4,&local_5a0);
          puVar15 = local_5b0;
          if (local_5a8 != 0) {
            if (local_5a8 == 1) {
              if (iVar6 < 0x20) {
                local_560[(longlong)iVar6 * 10] = local_5a4;
                lVar9 = (longlong)(int)local_568;
                local_560[lVar9 * 10 + 2] = local_5a0;
                local_560[lVar9 * 10 + 3] = iStack_59c;
                local_560[lVar9 * 10 + 4] = iStack_598;
                local_560[lVar9 * 10 + 5] = iStack_594;
                auStack_548[lVar9 * 5] = local_590;
                auStack_548[lVar9 * 5 + 1] = uStack_588;
                iVar6 = (int)local_568 + 1;
LAB_7ff7a3400bb7:
                local_568._0_4_ = iVar6;
              }
            }
            else if ((local_5a8 == 2) && (0 < iVar6)) {
              iVar7 = iVar6 + -1;
              iVar6 = iVar6 + -1;
              piVar14 = local_560 + (longlong)iVar7 * 10;
              goto LAB_7ff7a3400bb7;
            }
            if ((longlong)uVar17 < local_580) {
              if ((0 < (longlong)uVar17) && ((undefined1 *)*local_5c0 == param_3)) {
                local_5c8 = local_5c8 - 1;
                local_5c0 = local_5c0 + -5;
                uVar17 = uVar17 - 1;
                param_5 = param_5 + -5;
                piVar16 = piVar16 + -10;
              }
              *param_5 = param_3;
              if (0 < iVar6) {
                lVar9 = (longlong)iVar6;
                if (&uStack_588 + lVar9 * 5 != (ulonglong *)0x0) {
                  iVar7 = *(int *)((longlong)&local_580 + lVar9 * 0x28 + 4);
                  iVar1 = *(int *)(&local_578 + lVar9 * 5);
                  iVar2 = *(int *)((longlong)&local_578 + lVar9 * 0x28 + 4);
                  local_5c8 = local_5c8 + 1;
                  local_5c0 = local_5c0 + 5;
                  uVar3 = (&uStack_570)[lVar9 * 5];
                  uVar4 = (&local_568)[lVar9 * 5];
                  uVar17 = uVar17 + 1;
                  *piVar16 = *(int *)(&local_580 + lVar9 * 5);
                  piVar16[1] = iVar7;
                  piVar16[2] = iVar1;
                  piVar16[3] = iVar2;
                  *(ulonglong *)(piVar16 + 4) = uVar3;
                  *(ulonglong *)(piVar16 + 6) = uVar4;
                  *(undefined4 *)(param_5 + 4) = 0;
                  param_5 = param_5 + 5;
                  piVar16 = piVar16 + 10;
                }
              }
            }
            if (local_5a8 == 3) {
              if (local_5a4 == 3) {
LAB_7ff7a3400c72:
                if ((int)local_5b0 - iVar13 < 2) {
                  return 0;
                }
                if (((local_5a8 == 2) && (piVar14 != (int *)0x0)) && (0.0 < (float)piVar14[8])) {
                  iVar13 = piVar14[2];
                  iVar7 = piVar14[3];
                  iVar1 = piVar14[4];
                  iVar2 = piVar14[5];
                  local_5c0 = local_5c0 + 5;
                  local_5c8 = local_5c8 + 1;
                  uVar8 = *(undefined8 *)(piVar14 + 6);
                  uVar5 = *(undefined8 *)(piVar14 + 8);
                  *param_5 = param_3;
                  uVar17 = uVar17 + 1;
                  *piVar16 = iVar13;
                  piVar16[1] = iVar7;
                  piVar16[2] = iVar1;
                  piVar16[3] = iVar2;
                  param_5 = param_5 + 5;
                  *(undefined8 *)(piVar16 + 4) = uVar8;
                  *(undefined8 *)(piVar16 + 6) = uVar5;
                  piVar16 = piVar16 + 10;
                }
                FUN_7ff7a38fc8e0(param_3,&DAT_7ff7a3cc356c,2);
                param_3 = param_3 + 1;
                puVar15 = local_5b0;
              }
            }
            else if (local_5a8 == 2) {
              if ((local_5a4 - 6U < 7) || (local_5a4 == 2)) goto LAB_7ff7a3400c72;
            }
            else if (local_5a8 == 1) {
              if ((local_5a4 == 6) || (local_5a4 == 1)) goto LAB_7ff7a3400c72;
              if (local_5a4 == 2) {
                if ((int)local_5b0 - iVar13 < 6) {
                  return 0;
                }
                FUN_7ff7a38fc8e0(param_3,&DAT_7ff7a3cde698,6);
                param_3 = param_3 + 5;
                puVar15 = local_5b0;
              }
            }
          }
        }
        else {
          iVar7 = FUN_7ff7a3b95000(param_1,&DAT_7ff7a3cde688,4);
          if (iVar7 == 0) {
            pcVar12 = param_1 + 4;
            param_1 = "<";
          }
          else {
            iVar7 = FUN_7ff7a3b95000(param_1,&DAT_7ff7a3cde690,4);
            if (iVar7 == 0) {
              pcVar12 = param_1 + 4;
              param_1 = ">";
            }
            else {
              pcVar12 = param_1 + 1;
            }
          }
          if ((int)puVar15 - iVar13 < 2) {
            return 0;
          }
          FUN_7ff7a38fc8e0(param_3,param_1,2);
          param_3 = param_3 + 1;
          puVar15 = local_5b0;
          local_5b8 = pcVar12;
        }
      }
      cVar10 = *local_5b8;
      param_1 = local_5b8;
      uVar11 = local_5c8;
    } while (cVar10 != '\0');
  }
  *local_578 = uVar11;
  return 1;
}

