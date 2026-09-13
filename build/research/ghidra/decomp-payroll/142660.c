// image offset 0x142660 address 7ff7a32d2660

void FUN_7ff7a32d25c0(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 *puVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong lVar7;
  undefined8 *puVar8;
  char *_Str;
  ulonglong uVar9;
  uint uVar10;
  longlong lVar11;
  int iVar12;
  longlong *plVar13;
  longlong lVar14;
  char *local_88;
  undefined8 local_80;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  int iStack_60;
  undefined4 uStack_5c;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined8 local_38;
  undefined8 uStack_30;
  
  cVar2 = FUN_7ff7a340f430(param_2,param_3,"Achievements",&local_78);
  if (cVar2 != '\0') {
    local_88 = (char *)0x0;
    cVar2 = FUN_7ff7a340f430(param_2,param_3,"NextPageToken",&local_80);
    if ((cVar2 != '\0') && (cVar2 = FUN_7ff7a340fce0(local_80), cVar2 == '\0')) {
      FUN_7ff7a340f570(param_2,param_3,"NextPageToken",&local_88);
    }
    lVar5 = FUN_7ff7a340efe0(param_2,local_78);
    if (lVar5 != 0) {
LAB_7ff7a32d2690:
      uVar6 = FUN_7ff7a340f220(param_2,lVar5);
      lVar7 = strtoull(uVar6,0,10);
      if (lVar7 != 0) {
        plVar13 = &DAT_7ff7a925b260;
        uVar10 = 0;
        do {
          if (*plVar13 == lVar7) {
            lVar7 = (longlong)(int)uVar10;
            lVar11 = lVar7 * 0xb78;
            puVar8 = (undefined8 *)(&DAT_7ff7a925bdb0 + lVar11);
            puVar1 = &DAT_7ff7a925b260 + lVar7 * 0x16f;
            if ((puVar1 != (undefined8 *)0x0) && ((&DAT_7ff7a925bdd0)[lVar7 * 0x2de] == 2)) {
              if (local_88 == (char *)0x0) {
                *puVar8 = 0;
                *(undefined8 *)(lVar11 + 0x7ff7a925bdb8) = 0;
                *(undefined8 *)(&DAT_7ff7a925bdc0 + lVar11) = 0;
                *(undefined8 *)(lVar11 + 0x7ff7a925bdc8) = 0;
                goto LAB_7ff7a32d2747;
              }
              iVar12 = 0x20;
              if (*local_88 == '\0') goto LAB_7ff7a32d2738;
              lVar14 = (longlong)local_88 - (longlong)puVar8;
              goto LAB_7ff7a32d2721;
            }
            break;
          }
          uVar10 = uVar10 + 1;
          plVar13 = plVar13 + 0x16f;
        } while (uVar10 < 0x30);
      }
      goto LAB_7ff7a32d2890;
    }
  }
  return;
  while( true ) {
    iVar12 = iVar12 + -1;
    *(undefined1 *)puVar8 = *(undefined1 *)(lVar14 + (longlong)puVar8);
    puVar8 = (undefined8 *)((longlong)puVar8 + 1);
    if (*(char *)(lVar14 + (longlong)puVar8) == '\0') break;
LAB_7ff7a32d2721:
    if (iVar12 < 2) break;
  }
LAB_7ff7a32d2738:
  *(undefined1 *)puVar8 = 0;
LAB_7ff7a32d2747:
  lVar14 = FUN_7ff7a340efe0(param_2,lVar5);
  while ((lVar14 != 0 && ((uint)(&DAT_7ff7a925b268)[lVar7 * 0x2de] < 0x1e))) {
    cVar2 = FUN_7ff7a32ca570(param_2,lVar14,&local_68,0,0);
    if (cVar2 != '\0') {
      FUN_7ff7a38f34d0("dw/dwGameChallenges.csv",&local_70);
      uVar4 = uStack_5c;
      uVar6 = FUN_7ff7a38fa3d0(&DAT_7ff7a3cc2f5c,uStack_5c);
      _Str = (char *)FUN_7ff7a38f3560(local_70,0,uVar6);
      if (((_Str != (char *)0x0) && (iVar12 = atoi(_Str), iVar12 != -1)) &&
         ((iStack_60 == 4 || ((iStack_60 == 0xb || (iVar3 = FUN_7ff7a32c9cb0(iVar12), iVar3 == 1))))
         )) {
        FUN_7ff7a32c9e20(uVar4,(ulonglong)(uint)(&DAT_7ff7a925b268)[lVar7 * 0x2de] * 0x60 + 0x14 +
                               (longlong)puVar1);
        uVar9 = (ulonglong)(uint)(&DAT_7ff7a925b268)[lVar7 * 0x2de];
        puVar1[uVar9 * 0xc + 5] = local_68;
        (puVar1 + uVar9 * 0xc + 5)[1] = CONCAT44(uStack_5c,iStack_60);
        puVar1[uVar9 * 0xc + 7] = local_58;
        (puVar1 + uVar9 * 0xc + 7)[1] = uStack_50;
        puVar8 = puVar1 + uVar9 * 0xc + 9;
        *(undefined4 *)puVar8 = local_48;
        *(undefined4 *)((longlong)puVar8 + 4) = uStack_44;
        *(undefined4 *)(puVar8 + 1) = uStack_40;
        *(undefined4 *)((longlong)puVar8 + 0xc) = uStack_3c;
        puVar1[uVar9 * 0xc + 0xb] = local_38;
        (puVar1 + uVar9 * 0xc + 0xb)[1] = uStack_30;
        *(int *)(puVar1 + (ulonglong)(uint)(&DAT_7ff7a925b268)[lVar7 * 0x2de] * 0xc + 2) = iVar12;
        (&DAT_7ff7a925b268)[lVar7 * 0x2de] = (&DAT_7ff7a925b268)[lVar7 * 0x2de] + 1;
      }
    }
    lVar14 = FUN_7ff7a340f240(param_2,lVar14);
  }
  uVar4 = 1;
  if ((&DAT_7ff7a925bdb0)[lVar11] == '\0') {
    uVar4 = 3;
  }
  (&DAT_7ff7a925bdd0)[lVar7 * 0x2de] = uVar4;
LAB_7ff7a32d2890:
  lVar5 = FUN_7ff7a340f240(param_2,lVar5);
  if (lVar5 == 0) {
    return;
  }
  goto LAB_7ff7a32d2690;
}

