// image offset 0x1425C0 address 7ff7a32d25c0

void FUN_7ff7a32d25c0(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong lVar7;
  undefined8 *puVar8;
  longlong lVar9;
  uint uVar10;
  longlong lVar11;
  int iVar12;
  longlong *plVar13;
  longlong lVar14;
  char *pcStack_88;
  undefined8 uStack_80;
  undefined8 uStack_78;
  undefined8 uStack_70;
  undefined8 uStack_68;
  int iStack_60;
  undefined4 uStack_5c;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined8 uStack_38;
  undefined8 uStack_30;
  
  cVar2 = FUN_7ff7a340f430(param_2,param_3,&UNK_7ff7a3cd1388,&uStack_78);
  if (cVar2 != '\0') {
    pcStack_88 = (char *)0x0;
    cVar2 = FUN_7ff7a340f430(param_2,param_3,&UNK_7ff7a3cd1398,&uStack_80);
    if ((cVar2 != '\0') && (cVar2 = func_0x7ff7a340fce0(uStack_80), cVar2 == '\0')) {
      FUN_7ff7a340f570(param_2,param_3,&UNK_7ff7a3cd1398,&pcStack_88);
    }
    lVar5 = FUN_7ff7a340efe0(param_2,uStack_78);
    if (lVar5 != 0) {
code_r0x7ff7a32d2690:
      uVar6 = func_0x7ff7a340f220(param_2,lVar5);
      lVar7 = strtoull(uVar6,0,10);
      if (lVar7 != 0) {
        plVar13 = (longlong *)0x7ff7a925b260;
        uVar10 = 0;
        do {
          if (*plVar13 == lVar7) {
            lVar11 = (longlong)(int)uVar10 * 0xb78;
            puVar8 = (undefined8 *)(lVar11 + 0x7ff7a925bdb0);
            lVar7 = lVar11 + 0x7ff7a925b260;
            if ((lVar7 != 0) && (*(int *)(lVar11 + 0x7ff7a925bdd0) == 2)) {
              if (pcStack_88 == (char *)0x0) {
                *puVar8 = 0;
                *(undefined8 *)(lVar11 + 0x7ff7a925bdb8) = 0;
                *(undefined8 *)(lVar11 + 0x7ff7a925bdc0) = 0;
                *(undefined8 *)(lVar11 + 0x7ff7a925bdc8) = 0;
                goto code_r0x7ff7a32d2747;
              }
              iVar12 = 0x20;
              if (*pcStack_88 == '\0') goto code_r0x7ff7a32d2738;
              lVar14 = (longlong)pcStack_88 - (longlong)puVar8;
              goto code_r0x7ff7a32d2721;
            }
            break;
          }
          uVar10 = uVar10 + 1;
          plVar13 = plVar13 + 0x16f;
        } while (uVar10 < 0x30);
      }
      goto code_r0x7ff7a32d2890;
    }
  }
  return;
  while( true ) {
    iVar12 = iVar12 + -1;
    *(undefined1 *)puVar8 = *(undefined1 *)(lVar14 + (longlong)puVar8);
    puVar8 = (undefined8 *)((longlong)puVar8 + 1);
    if (*(char *)(lVar14 + (longlong)puVar8) == '\0') break;
code_r0x7ff7a32d2721:
    if (iVar12 < 2) break;
  }
code_r0x7ff7a32d2738:
  *(undefined1 *)puVar8 = 0;
code_r0x7ff7a32d2747:
  lVar14 = FUN_7ff7a340efe0(param_2,lVar5);
  while ((lVar14 != 0 && (*(uint *)(lVar11 + 0x7ff7a925b268) < 0x1e))) {
    cVar2 = FUN_7ff7a32ca570(param_2,lVar14,&uStack_68,0,0);
    if (cVar2 != '\0') {
      FUN_7ff7a38f34d0(&UNK_7ff7a3ccfa08,&uStack_70);
      uVar4 = uStack_5c;
      uVar6 = FUN_7ff7a38fa3d0(&UNK_7ff7a3cc2f5c,uStack_5c);
      lVar9 = FUN_7ff7a38f3560(uStack_70,0,uVar6);
      if (((lVar9 != 0) && (iVar12 = atoi(lVar9), iVar12 != -1)) &&
         ((iStack_60 == 4 || ((iStack_60 == 0xb || (iVar3 = FUN_7ff7a32c9cb0(iVar12), iVar3 == 1))))
         )) {
        FUN_7ff7a32c9e20(uVar4,(ulonglong)*(uint *)(lVar11 + 0x7ff7a925b268) * 0x60 + 0x14 + lVar7);
        lVar9 = (ulonglong)*(uint *)(lVar11 + 0x7ff7a925b268) * 0x60;
        puVar8 = (undefined8 *)(lVar9 + 0x28 + lVar7);
        *puVar8 = uStack_68;
        puVar8[1] = CONCAT44(uStack_5c,iStack_60);
        puVar8 = (undefined8 *)(lVar9 + 0x38 + lVar7);
        *puVar8 = uStack_58;
        puVar8[1] = uStack_50;
        puVar1 = (undefined4 *)(lVar9 + 0x48 + lVar7);
        *puVar1 = uStack_48;
        puVar1[1] = uStack_44;
        puVar1[2] = uStack_40;
        puVar1[3] = uStack_3c;
        puVar8 = (undefined8 *)(lVar9 + 0x58 + lVar7);
        *puVar8 = uStack_38;
        puVar8[1] = uStack_30;
        *(int *)((ulonglong)*(uint *)(lVar11 + 0x7ff7a925b268) * 0x60 + 0x10 + lVar7) = iVar12;
        *(int *)(lVar11 + 0x7ff7a925b268) = *(int *)(lVar11 + 0x7ff7a925b268) + 1;
      }
    }
    lVar14 = FUN_7ff7a340f240(param_2,lVar14);
  }
  uVar4 = 1;
  if (*(char *)(lVar11 + 0x7ff7a925bdb0) == '\0') {
    uVar4 = 3;
  }
  *(undefined4 *)(lVar11 + 0x7ff7a925bdd0) = uVar4;
code_r0x7ff7a32d2890:
  lVar5 = FUN_7ff7a340f240(param_2,lVar5);
  if (lVar5 == 0) {
    return;
  }
  goto code_r0x7ff7a32d2690;
}

