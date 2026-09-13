// image offset 0x276C40 address 7ff7a3406c40

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a3406c20(void)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  longlong lVar4;
  undefined8 uVar5;
  ulonglong uVar6;
  longlong lVar7;
  undefined4 *puVar8;
  longlong lVar9;
  uint uVar10;
  ulonglong uVar11;
  int iVar12;
  uint *puVar13;
  int *piVar14;
  undefined2 *puVar15;
  longlong lVar16;
  longlong lVar17;
  char *pcVar18;
  int iVar19;
  longlong lVar20;
  undefined1 auStack_1c8 [32];
  code *local_1a8;
  longlong local_198;
  longlong local_190;
  longlong local_188;
  longlong local_180;
  undefined4 local_178;
  undefined4 local_174;
  longlong local_170;
  undefined *local_168;
  longlong local_160;
  undefined1 local_158 [56];
  undefined1 local_120 [24];
  uint local_108 [52];
  ulonglong local_38;
  
  local_38 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_1c8;
  cVar2 = FUN_7ff7a340a1f0();
  if (cVar2 != '\0') {
    iVar19 = 0;
    local_198 = 0;
    local_188 = 0;
    local_170 = 0;
    pcVar18 = &DAT_7ff7ab0f4814;
    local_190 = 0;
    local_180 = 0;
    do {
      lVar17 = local_170;
      lVar20 = local_180;
      lVar9 = local_188;
      lVar16 = local_190;
      lVar7 = local_198;
      cVar2 = FUN_7ff7a3630d90(iVar19,&local_178);
      if (cVar2 != '\0') {
        if ((*pcVar18 != '\0') && (cVar2 = FUN_7ff7a3398650(5,iVar19,0x89), cVar2 == '\0')) {
          lVar4 = FUN_7ff7a33981b0(5,iVar19,0x89);
          local_160 = lVar4;
          cVar2 = FUN_7ff7a39c9650(lVar4);
          lVar7 = local_198;
          if ((cVar2 != '\0') && (cVar2 = FUN_7ff7a39c9710(lVar4), lVar7 = local_198, cVar2 != '\0')
             ) {
            local_168 = &DAT_7ff7ab0f2dc0 + lVar16;
            FUN_7ff7a339cca0(local_168);
            FUN_7ff7a39c90a0(&DAT_7ff7ab0f3444 + lVar16);
            lVar16 = local_188;
            lVar7 = local_190;
            iVar12 = 0;
            piVar14 = (int *)(pcVar18 + -0x34);
            do {
              iVar1 = *piVar14;
              if (0 < iVar1) {
                (&DAT_7ff7ab0f2e28)
                [(ulonglong)*(uint *)(&DAT_7ff7ab0f3440 + lVar16) * 0x80 + lVar16] = (char)iVar12;
                *(int *)(&DAT_7ff7ab0f2e2c +
                        (ulonglong)*(uint *)(&DAT_7ff7ab0f3440 + lVar16) * 0x80 + lVar16) = iVar1;
                uVar5 = FUN_7ff7a38b5500(local_158,iVar19);
                FUN_7ff7a3bbc740(&DAT_7ff7ab0f2de0 +
                                 (ulonglong)*(uint *)(&DAT_7ff7ab0f3440 + lVar16) * 0x80 + lVar7,
                                 uVar5);
                FUN_7ff7a3bbc6f0(local_120);
                FUN_7ff7a3c04d10(local_120);
                *(int *)(&DAT_7ff7ab0f3440 + lVar16) = *(int *)(&DAT_7ff7ab0f3440 + lVar16) + 1;
              }
              lVar9 = local_160;
              iVar12 = iVar12 + 1;
              piVar14 = piVar14 + 1;
            } while (iVar12 < 0xd);
            *pcVar18 = '\0';
            FUN_7ff7a39c9700(local_160,local_168);
            *(code **)(lVar9 + 0x40) = FUN_7ff7a3405710;
            *(code **)(lVar9 + 0x38) = FUN_7ff7a3405730;
            *(code **)(lVar9 + 0x30) = FUN_7ff7a339bfb0;
            FUN_7ff7a39c97e0(lVar9);
            lVar9 = local_188;
            lVar7 = local_198;
            lVar16 = local_190;
            lVar17 = local_170;
            lVar20 = local_180;
          }
        }
        iVar12 = FUN_7ff7a320dfd0(local_178);
        if ((iVar12 == 0) || (DAT_7ff7a4d636f8 != '\0')) {
          puVar13 = (uint *)(&DAT_7ff7ab0f6bc0 + lVar20);
          if (*puVar13 != 0) {
            cVar2 = FUN_7ff7a3398650(5,iVar19);
            uVar11 = 0;
            if ((cVar2 == '\0') && (uVar3 = *puVar13, uVar6 = uVar11, uVar3 != 0)) {
              do {
                uVar10 = (uint)uVar6;
                if (puVar13[uVar11 * 2 + 2] == 1) {
                  uVar3 = FUN_7ff7a3409480(iVar19,puVar13[uVar11 * 2 + 1]);
                  if (1 < uVar3) {
                    if (uVar10 < 10) {
                      puVar13[uVar11 * 2 + 2] = 2;
                      local_108[uVar6 * 5] = puVar13[uVar11 * 2 + 1];
                      local_108[uVar6 * 5 + 1] = uVar3 - 1;
                      local_108[uVar6 * 5 + 3] = 6;
                      local_108[uVar6 * 5 + 2] = 2;
                      local_108[uVar6 * 5 + 4] = 0;
                      uVar6 = (ulonglong)(uVar10 + 1);
                      uVar3 = *puVar13;
                      goto LAB_7ff7a3406ef9;
                    }
                    break;
                  }
                  uVar3 = *puVar13 - 1;
                  if ((uint)uVar11 != uVar3) {
                    *(undefined8 *)(puVar13 + uVar11 * 2 + 1) =
                         *(undefined8 *)(&DAT_7ff7ab0f6bc4 + (ulonglong)uVar3 * 8 + lVar20);
                  }
                  *(undefined8 *)(&DAT_7ff7ab0f6bc4 + (ulonglong)uVar3 * 8 + lVar20) = 0;
                  *puVar13 = *puVar13 - 1;
                  uVar3 = *puVar13;
                }
                else {
LAB_7ff7a3406ef9:
                  uVar11 = (ulonglong)((uint)uVar11 + 1);
                }
                uVar10 = (uint)uVar6;
              } while ((uint)uVar11 < uVar3);
              lVar17 = local_170;
              if (uVar10 != 0) {
                FUN_7ff7a39c90a0(&DAT_7ff7ab0f6cb4 + lVar20);
                cVar2 = FUN_7ff7a340bfe0(iVar19,local_108,uVar10,&DAT_7ff7ab0f6cb4 + lVar20);
                uVar11 = 0;
                if ((cVar2 == '\0') && (*puVar13 != 0)) {
                  do {
                    if (*(int *)(&DAT_7ff7ab0f6bc8 + uVar11 * 8 + lVar20) == 2) {
                      *(undefined4 *)(&DAT_7ff7ab0f6bc8 + uVar11 * 8 + lVar20) = 1;
                    }
                    uVar3 = (int)uVar11 + 1;
                    uVar11 = (ulonglong)uVar3;
                  } while (uVar3 < *puVar13);
                }
              }
            }
          }
          uVar11 = 0;
          piVar14 = (int *)(&DAT_7ff7ab0f6de0 + lVar20);
          if ((*piVar14 != 0) && (cVar2 = FUN_7ff7a3398650(5,iVar19), cVar2 == '\0')) {
            uVar3 = FUN_7ff7a3409480(iVar19,*(undefined4 *)(&DAT_7ff7ab0f6de4 + lVar20));
            if (uVar3 < 2) {
              uVar3 = *piVar14 - 1;
              uVar6 = uVar11;
              if (uVar3 != 0) {
                *(undefined8 *)(&DAT_7ff7ab0f6de4 + lVar20) =
                     *(undefined8 *)(&DAT_7ff7ab0f6de4 + (ulonglong)uVar3 * 8 + lVar20);
                uVar6 = (ulonglong)uVar3;
              }
              *(undefined8 *)(&DAT_7ff7ab0f6de4 + uVar6 * 8 + lVar20) = 0;
              *piVar14 = *piVar14 + -1;
            }
            else {
              FUN_7ff7a39c90a0(&DAT_7ff7ab0f6ed4 + lVar20);
              uVar5 = FUN_7ff7a38fa3d0("Pawnable_Uniform_%X",
                                       *(undefined4 *)(&DAT_7ff7ab0f6de4 + lVar20));
              cVar2 = FUN_7ff7a3408180(iVar19,uVar5,&DAT_7ff7ab0f6ed4 + lVar20,uVar3 - 1);
              if (cVar2 != '\0') {
                *(undefined4 *)(&DAT_7ff7ab0f6de8 + lVar20) = 2;
              }
            }
          }
          cVar2 = FUN_7ff7a340a1f0();
          if (((((cVar2 != '\0') && (cVar2 = FUN_7ff7a3398650(5,iVar19), cVar2 == '\0')) &&
               (cVar2 = FUN_7ff7a3630d90(iVar19,&local_174), cVar2 != '\0')) &&
              ((iVar12 = FUN_7ff7a320dfd0(local_174), lVar7 = local_198, iVar12 == 0 ||
               (DAT_7ff7a4d636f8 != '\0')))) &&
             (puVar8 = (undefined4 *)(&DAT_7ff7ab0f3da0 + local_198), uVar6 = uVar11,
             *(longlong *)((longlong)&DAT_7ff7ab0f41b8 + local_198) != 0)) {
            do {
              if (puVar8[1] == 2) {
                local_1a8 = FUN_7ff7a34058c0;
                cVar2 = FUN_7ff7a34086b0(iVar19,uVar6,
                                         &DAT_7ff7ab0f3ba0 + (longlong)(int)uVar6 * 0x208 + lVar17,
                                         *puVar8);
                if (cVar2 != '\0') {
                  *(undefined4 *)(&DAT_7ff7ab0f3da4 + uVar11 * 0x208 + lVar7) = 3;
                  break;
                }
              }
              uVar3 = (int)uVar6 + 1;
              uVar6 = (ulonglong)uVar3;
              uVar11 = uVar11 + 1;
              puVar8 = puVar8 + 0x82;
            } while (uVar3 < 3);
          }
          lVar9 = local_188;
          lVar7 = local_198;
          lVar16 = local_190;
          if (((DAT_7ff7ab0f4880 == '\0') &&
              (cVar2 = FUN_7ff7a39c4640(iVar19), lVar9 = local_188, lVar7 = local_198,
              lVar16 = local_190, cVar2 != '\0')) &&
             ((cVar2 = FUN_7ff7a33978b0(), lVar9 = local_188, lVar7 = local_198, lVar16 = local_190,
              cVar2 != '\0' &&
              (cVar2 = FUN_7ff7a33986d0(5), lVar9 = local_188, lVar7 = local_198, lVar16 = local_190
              , cVar2 == '\0')))) {
            DAT_7ff7ab0f4884 = 0;
            DAT_7ff7ab0f4880 = cVar2;
            memset(&DAT_7ff7ab0f4890,0,0x2000);
            puVar15 = &DAT_7ff7a3f98840;
            for (lVar7 = 0x800; lVar7 != 0; lVar7 = lVar7 + -1) {
              *puVar15 = 0xffff;
              puVar15 = puVar15 + 1;
            }
            local_1a8 = FUN_7ff7a3405a30;
            FUN_7ff7a3408d30(iVar19,1,0x96,FUN_7ff7a3405a50);
            lVar9 = local_188;
            lVar7 = local_198;
            lVar16 = local_190;
          }
        }
      }
      iVar19 = iVar19 + 1;
      local_190 = lVar16 + 0x6f0;
      local_170 = lVar17 + 0x620;
      local_188 = lVar9 + 0x6f0;
      pcVar18 = pcVar18 + 0x38;
      local_180 = lVar20 + 0x110;
      local_198 = lVar7 + 0x620;
    } while (iVar19 < 2);
    cVar2 = FUN_7ff7a3408430();
    if ((cVar2 != '\0') && (DAT_7ff7ab0f487c == 1)) {
      cVar2 = FUN_7ff7a340e3c0(DAT_7ff7ab0f4850);
      if (cVar2 == '\0') {
        cVar2 = FUN_7ff7a3398650(5,DAT_7ff7ab0f4878);
        if (cVar2 == '\0') {
          local_180 = 0;
          FUN_7ff7a34097e0(DAT_7ff7ab0f4850,&local_180);
          FUN_7ff7a3408c30(DAT_7ff7ab0f4878,local_180 + 8,1,1);
        }
      }
      else {
        local_1a8 = (code *)CONCAT44(local_1a8._4_4_,DAT_7ff7ab0f4858);
        cVar2 = FUN_7ff7a340c640(DAT_7ff7ab0f4878,DAT_7ff7ab0f4850,DAT_7ff7ab0f4854,
                                 &DAT_7ff7ab0f485c);
        if (cVar2 != '\0') {
          DAT_7ff7ab0f487c = 2;
        }
      }
    }
  }
  return;
}

