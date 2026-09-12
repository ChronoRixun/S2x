// image offset 0x1222C0 address 7ff7a32b22c0

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_7ff7a32b22c0(longlong param_1)

{
  int *piVar1;
  undefined1 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  bool bVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  longlong lVar11;
  ulonglong uVar12;
  undefined8 uVar13;
  char *pcVar14;
  longlong lVar15;
  undefined4 uVar16;
  ulonglong uVar17;
  undefined8 unaff_RBP;
  undefined8 unaff_RSI;
  undefined8 unaff_RDI;
  longlong lVar18;
  longlong lVar19;
  undefined *puVar20;
  undefined8 unaff_R12;
  undefined8 unaff_R13;
  int iVar21;
  undefined8 unaff_R14;
  undefined8 unaff_R15;
  float fVar22;
  undefined8 auStackX_18 [2];
  undefined *puStack_10;
  
  puStack_10 = &UNK_7ff7a32b22cc;
  lVar11 = FUN_7ff7a3c45ff0();
  lVar11 = -lVar11;
  *(ulonglong *)(&stack0x00001858 + lVar11) =
       _DAT_7ff7a4152aa8 ^ (ulonglong)(&stack0xfffffffffffffff8 + lVar11);
  *(undefined8 *)(&stack0x000018a8 + lVar11) = unaff_RSI;
  uVar12 = *(ulonglong *)(param_1 + 0x48);
  *(undefined8 *)(&stack0x000018b0 + lVar11) = unaff_RDI;
  if (((int)((longlong)(uVar12 - *(ulonglong *)(param_1 + 0x50)) >> 4) == 2) &&
     (*(ulonglong *)(param_1 + 0x50) < uVar12)) {
    *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2318;
    iVar8 = FUN_7ff7a3468d90(param_1);
    if ((iVar8 == 0) || (*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x10U))
    goto code_r0x7ff7a32b2336;
    *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2332;
    iVar8 = FUN_7ff7a3468d90(param_1);
    if (iVar8 == 0) goto code_r0x7ff7a32b2336;
  }
  else {
code_r0x7ff7a32b2336:
    *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2345;
    FUN_7ff7a34731a0(param_1,&UNK_7ff7a3cbd562);
  }
  uVar12 = *(ulonglong *)(param_1 + 0x50);
  uVar17 = *(ulonglong *)(param_1 + 0x48);
  if (uVar12 < uVar17) {
    *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2361;
    fVar22 = (float)FUN_7ff7a3469aa0(param_1,uVar12);
    uVar12 = *(ulonglong *)(param_1 + 0x50);
    uVar17 = *(ulonglong *)(param_1 + 0x48);
    iVar8 = (int)fVar22;
  }
  else {
    iVar8 = 0;
  }
  *(undefined8 *)(&stack0x00001870 + lVar11) = unaff_R14;
  if (uVar12 + 0x10 < uVar17) {
    *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b238b;
    fVar22 = (float)FUN_7ff7a3469aa0(param_1);
    iVar21 = (int)fVar22;
    if (iVar21 == -1) {
      *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b23a5;
      FUN_7ff7a34731a0(param_1,&UNK_7ff7a3cbd562);
    }
  }
  else {
    iVar21 = 0;
  }
  *(undefined8 *)(&stack0x00001878 + lVar11) = unaff_R13;
  *(undefined8 *)(&stack0x00001868 + lVar11) = unaff_R15;
  *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b23bf;
  FUN_7ff7a39c90a0();
  lVar18 = (longlong)iVar8 * 0xf8;
  *(longlong *)(&stack0x00000028 + lVar11) = (longlong)iVar8;
  lVar19 = lVar18 + 0x7ff7a91ca030;
  if (*(int *)(lVar18 + 0x7ff7a91ca0f0) == 0) {
    *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b23f6;
    FUN_7ff7a38f34d0(&UNK_7ff7a3ccfa08,(longlong)auStackX_18 + lVar11);
    *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2405;
    uVar13 = FUN_7ff7a38fa3d0(&UNK_7ff7a3cc2f5c,iVar21);
    *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b241a;
    pcVar14 = (char *)FUN_7ff7a38f3560(*(undefined8 *)((longlong)auStackX_18 + lVar11),0,uVar13,1);
    *(char **)((longlong)auStackX_18 + lVar11 + 8) = pcVar14;
    if ((pcVar14 != (char *)0x0) && (*pcVar14 != '\0')) {
      *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2439;
      iVar9 = FUN_7ff7a32c9dc0(iVar21);
      if ((iVar9 == 4) || (iVar9 == 0xb)) {
        bVar6 = true;
      }
      else {
        bVar6 = false;
      }
      uVar13 = 0x99;
      if (!bVar6) {
        uVar13 = 0x8d;
      }
      *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2469;
      lVar15 = FUN_7ff7a33981b0(0,iVar8,uVar13);
      *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2474;
      cVar7 = func_0x7ff7a39c9650();
      if (cVar7 != '\0') {
        *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2484;
        cVar7 = FUN_7ff7a39c9710();
        if (cVar7 != '\0') {
          *(undefined8 *)(&stack0x000018a0 + lVar11) = unaff_RBP;
          *(undefined8 *)(&stack0x00001880 + lVar11) = unaff_R12;
          *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b24a4;
          FUN_7ff7a3396000(lVar19);
          *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b24b9;
          func_0x7ff7a3c48920(&stack0x00000058 + lVar11,0,0x1800);
          *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b24cd;
          iVar8 = FUN_7ff7a3b94cd0(&stack0x00000058 + lVar11,0x1800,&UNK_7ff7a3cd06cc);
          *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b24ec;
          iVar10 = FUN_7ff7a3b94cd0(&stack0x00000058 + iVar8 + lVar11,0x1800 - iVar8,
                                    &UNK_7ff7a3cd06d0,0);
          iVar8 = iVar8 + iVar10;
          puVar20 = &UNK_7ff7a3cd0b90;
          if (!bVar6) {
            puVar20 = &UNK_7ff7a3cd0ba8;
          }
          *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b251f;
          iVar10 = FUN_7ff7a3b94cd0(&stack0x00000058 + iVar8 + lVar11,0x1800 - iVar8,
                                    &UNK_7ff7a3cd06e0,puVar20);
          iVar8 = iVar8 + iVar10;
          *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2542;
          iVar10 = FUN_7ff7a3b94cd0(&stack0x00000058 + iVar8 + lVar11,0x1800 - iVar8,
                                    &UNK_7ff7a3cd06f0,&stack0x00000030 + lVar11);
          uVar13 = *(undefined8 *)((longlong)auStackX_18 + lVar11 + 8);
          iVar8 = iVar8 + iVar10;
          *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2565;
          iVar10 = FUN_7ff7a3b94cd0(&stack0x00000058 + iVar8 + lVar11,0x1800 - iVar8,
                                    &UNK_7ff7a3cd0bd0,uVar13);
          iVar8 = iVar8 + iVar10;
          if (!bVar6) {
            *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b258b;
            iVar9 = FUN_7ff7a3b94cd0(&stack0x00000058 + iVar8 + lVar11,0x1800 - iVar8,
                                     &UNK_7ff7a3cd0bf0,iVar9);
            iVar8 = iVar8 + iVar9;
          }
          *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b25aa;
          FUN_7ff7a3b94cd0(&stack0x00000058 + iVar8 + lVar11,0x1800 - iVar8,&UNK_7ff7a3cd0704);
          uVar16 = *(undefined4 *)(&stack0x00000034 + lVar11);
          uVar4 = *(undefined4 *)(&stack0x00000038 + lVar11);
          uVar5 = *(undefined4 *)(&stack0x0000003c + lVar11);
          uVar2 = (&stack0x00000048)[lVar11];
          uVar13 = *(undefined8 *)(&stack0x00000040 + lVar11);
          *(undefined4 *)(lVar18 + 0x7ff7a91ca100) = *(undefined4 *)(&stack0x00000030 + lVar11);
          *(undefined4 *)(lVar18 + 0x7ff7a91ca104) = uVar16;
          *(undefined4 *)(lVar18 + 0x7ff7a91ca108) = uVar4;
          *(undefined4 *)(lVar18 + 0x7ff7a91ca10c) = uVar5;
          *(undefined4 *)(lVar18 + 0x7ff7a91ca0f0) = 1;
          *(undefined8 *)(lVar18 + 0x7ff7a91ca110) = uVar13;
          *(undefined1 *)(lVar18 + 0x7ff7a91ca118) = uVar2;
          *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b25e6;
          FUN_7ff7a3bcb8f0(lVar19,&stack0x00000058 + lVar11);
          piVar1 = (int *)(*(longlong *)(&stack0x00000028 + lVar11) * 4 + 0x7ff7a8e27f68);
          *piVar1 = iVar21;
          *(int **)(lVar18 + 0x7ff7a91ca120) = piVar1;
          *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b260b;
          func_0x7ff7a39c9700(lVar15,lVar19);
          *(undefined1 *)(lVar15 + 2) = 1;
          *(code **)(lVar15 + 0x30) = FUN_7ff7a3395a30;
          *(code **)(lVar15 + 0x40) = FUN_7ff7a32caf60;
          *(code **)(lVar15 + 0x38) = FUN_7ff7a32cb0b0;
          *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2638;
          FUN_7ff7a39c97e0(lVar15);
          uVar16 = 1;
          goto code_r0x7ff7a32b2651;
        }
      }
    }
  }
  uVar16 = 0;
code_r0x7ff7a32b2651:
  puVar3 = *(undefined4 **)(param_1 + 0x48);
  puVar3[2] = uVar16;
  *puVar3 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar3 + 4;
  *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b2670;
  lVar18 = func_0x7ff7a39c9020(&stack0x00000030 + lVar11);
  if (lVar18 == 0) {
    puVar3 = *(undefined4 **)(param_1 + 0x48);
    *puVar3 = 0;
    *(undefined4 **)(param_1 + 0x48) = puVar3 + 4;
  }
  else {
    lVar19 = -1;
    do {
      lVar19 = lVar19 + 1;
    } while (*(char *)(lVar18 + lVar19) != '\0');
    *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b26d5;
    FUN_7ff7a3294620(param_1,lVar18);
  }
  *(undefined **)((longlong)&puStack_10 + lVar11) = &UNK_7ff7a32b26ea;
  FUN_7ff7a3c46050(*(ulonglong *)(&stack0x00001858 + lVar11) ^
                   (ulonglong)(&stack0xfffffffffffffff8 + lVar11));
  return;
}

