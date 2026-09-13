// image offset 0x13C480 address 7ff7a32cc480

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a32cc480(undefined8 param_1,undefined8 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  ulonglong uVar7;
  int *piVar8;
  ulonglong uVar9;
  uint uVar10;
  undefined4 *puVar11;
  uint uVar12;
  ulonglong uVar13;
  uint uVar14;
  longlong lVar15;
  uint *puVar16;
  longlong lVar17;
  ulonglong uVar18;
  undefined8 uVar19;
  ulonglong uVar20;
  bool bVar21;
  undefined1 auStack_6498 [32];
  undefined4 *local_6478;
  char local_6468;
  undefined1 local_6467;
  undefined4 local_6460;
  undefined4 uStack_645c;
  undefined8 local_6458;
  undefined4 local_6450;
  uint local_644c;
  undefined4 local_6448 [2];
  undefined8 local_6440;
  ulonglong local_6438;
  undefined8 local_6428;
  undefined8 uStack_6420;
  undefined4 local_6418;
  undefined4 uStack_6414;
  undefined8 uStack_6410;
  undefined4 local_6408;
  undefined4 uStack_6404;
  undefined4 uStack_6400;
  undefined4 uStack_63fc;
  undefined8 local_63f8;
  undefined4 uStack_63f0;
  undefined4 uStack_63ec;
  undefined8 local_63e8;
  undefined8 local_63e0;
  undefined8 local_63d8;
  undefined8 local_63d0;
  undefined8 local_63c8;
  undefined8 local_63c0;
  undefined8 local_63b8;
  undefined8 local_63b0;
  undefined8 local_63a8;
  undefined4 local_63a0;
  undefined4 uStack_639c;
  undefined4 uStack_6398;
  undefined4 uStack_6394;
  undefined4 local_6390;
  undefined4 uStack_638c;
  undefined4 uStack_6388;
  undefined4 uStack_6384;
  undefined1 local_6378 [304];
  uint local_6248 [28];
  undefined4 local_61d8 [100];
  undefined1 local_6048 [24576];
  ulonglong local_48;
  undefined8 uStack_40;
  
  uStack_40 = 0x7ff7a32cc49d;
  local_48 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_6498;
  uVar13 = 0;
  local_6467 = 1;
  uVar12 = 0;
  local_644c = 0;
  local_6438 = 0xffffffffffffffff;
  local_6468 = '\0';
  iVar2 = FUN_7ff7a39197a0();
  lVar15 = (longlong)iVar2;
  lVar6 = FUN_7ff7a3bcb850(param_2);
  lVar17 = -1;
  do {
    lVar17 = lVar17 + 1;
  } while (*(char *)(lVar6 + lVar17) != '\0');
  local_6478 = (undefined4 *)CONCAT44(local_6478._4_4_,0x800);
  FUN_7ff7a340f8d0(local_6378,lVar6,lVar17,local_6048);
  iVar3 = FUN_7ff7a340ff40(local_6378,&local_6458);
  if (iVar3 < 0) {
    return;
  }
  cVar1 = FUN_7ff7a340f570(local_6378,local_6458,&DAT_7ff7a3cc4b48,&local_63d8);
  if (cVar1 == '\0') {
    return;
  }
  iVar3 = FUN_7ff7a32c9d50(local_63d8);
  if (iVar3 == -1) {
    return;
  }
  cVar1 = FUN_7ff7a340f300(local_6378,local_6458,&DAT_7ff7a3cd03f8,&local_6450);
  if (cVar1 == '\0') {
    return;
  }
  cVar1 = FUN_7ff7a340f570(local_6378,local_6458,"reason",&local_6440);
  if (cVar1 == '\0') {
    return;
  }
  iVar4 = FUN_7ff7a3b94f40(local_6440,"inProgress");
  if (iVar4 == 0) {
    local_6438 = CONCAT44(local_6438._4_4_,1);
  }
  else {
    iVar4 = FUN_7ff7a3b94f40(local_6440,"claimable");
    if (iVar4 == 0) {
      local_6438 = CONCAT44(local_6438._4_4_,6);
    }
    else {
      iVar4 = FUN_7ff7a3b94f40(local_6440,"completed");
      if (iVar4 == 0) {
        local_6438 = 0;
      }
      else {
        iVar4 = FUN_7ff7a3b94f40(local_6440,"expired");
        if (iVar4 == 0) {
          local_6467 = 0;
          local_6438 = 0;
          uVar10 = (&DAT_7ff7a8e27fe8)[lVar15 * 0x1f];
          uVar7 = uVar13;
          if (uVar10 != 0) {
            do {
              if (*(int *)(&DAT_7ff7a8e27f70 + uVar7 * 4 + lVar15 * 0x7c) == iVar3)
              goto LAB_7ff7a32cc661;
              uVar14 = (int)uVar7 + 1;
              uVar7 = (ulonglong)uVar14;
            } while (uVar14 < uVar10);
          }
          if (uVar10 < 0x1e) {
            *(int *)(&DAT_7ff7a8e27f70 + (ulonglong)uVar10 * 4 + lVar15 * 0x7c) = iVar3;
            (&DAT_7ff7a8e27fe8)[lVar15 * 0x1f] = (&DAT_7ff7a8e27fe8)[lVar15 * 0x1f] + 1;
          }
        }
      }
    }
  }
LAB_7ff7a32cc661:
  cVar1 = FUN_7ff7a340f570(local_6378,local_6458,"status",&local_63d0);
  if (cVar1 == '\0') {
    return;
  }
  iVar4 = FUN_7ff7a32c9c10(local_63d0);
  local_6448[0] = 0;
  cVar1 = FUN_7ff7a340f300(local_6378,local_6458,"progress",local_6448);
  if (cVar1 == '\0') {
    return;
  }
  cVar1 = FUN_7ff7a340f570(local_6378,local_6458,&DAT_7ff7a3cd07fc,&local_63e8);
  if (cVar1 == '\0') {
    return;
  }
  iVar5 = FUN_7ff7a3b94f40(local_63e8,"ACHIEVEMENT");
  if ((iVar5 != 0) && (iVar5 = FUN_7ff7a3b94f40(local_63e8,"CHALLENGE"), iVar5 != 0)) {
    return;
  }
  if (iVar4 - 2U < 2) {
    uVar7 = FUN_7ff7a32ca230(iVar2,iVar3);
    if (uVar7 == 0) {
      cVar1 = FUN_7ff7a32cae50(local_6450);
      if (cVar1 != '\0') goto LAB_7ff7a32ccb80;
      local_6478 = &local_63a0;
      cVar1 = FUN_7ff7a32ca570(local_6378,local_6458,&local_6428,0);
      if (cVar1 != '\0') {
        lVar6 = FUN_7ff7a32ca280(iVar2,iVar3);
        if (lVar6 != 0) {
          uStack_6410 = *(undefined8 *)(lVar6 + 0x18);
          local_6418 = *(undefined4 *)(lVar6 + 0x10);
          puVar11 = *(undefined4 **)(lVar6 + 0x20);
          if (puVar11 != (undefined4 *)0x0) {
            local_63a0 = *puVar11;
            uStack_639c = puVar11[1];
            uStack_6398 = puVar11[2];
            uStack_6394 = puVar11[3];
          }
        }
        piVar8 = (int *)(&DAT_7ff7a923409c + lVar15 * 0x13890);
        uVar7 = uVar13;
        do {
          iVar5 = (int)uVar7;
          if (*piVar8 == -1) {
            if (iVar5 != -1) {
              lVar17 = lVar15 * 0x13890 + (longlong)iVar5 * 0x40;
              *(undefined8 *)(&DAT_7ff7a9234090 + lVar17) = local_6428;
              *(undefined8 *)(&DAT_7ff7a9234098 + lVar17) = uStack_6420;
              *(ulonglong *)(&DAT_7ff7a92340a0 + lVar17) = CONCAT44(uStack_6414,local_6418);
              *(undefined8 *)(&DAT_7ff7a92340a8 + lVar17) = uStack_6410;
              *(undefined4 *)(&DAT_7ff7a92340b0 + lVar17) = local_6408;
              *(undefined4 *)(lVar17 + 0x7ff7a92340b4) = uStack_6404;
              *(undefined4 *)(&DAT_7ff7a92340b8 + lVar17) = uStack_6400;
              *(undefined4 *)(&DAT_7ff7a92340bc + lVar17) = uStack_63fc;
              lVar6 = (lVar15 * 0x1389 + (longlong)iVar5) * 0x10;
              *(undefined8 *)(&DAT_7ff7a92340c0 + lVar17) = local_63f8;
              *(ulonglong *)(&DAT_7ff7a92340c8 + lVar17) = CONCAT44(uStack_63ec,uStack_63f0);
              *(undefined4 *)(&DAT_7ff7a9243a90 + lVar6) = local_63a0;
              *(undefined4 *)(lVar6 + 0x7ff7a9243a94) = uStack_639c;
              *(undefined4 *)(lVar6 + 0x7ff7a9243a98) = uStack_6398;
              *(undefined4 *)(lVar6 + 0x7ff7a9243a9c) = uStack_6394;
              *(undefined **)(&DAT_7ff7a92340b0 + lVar17) = &DAT_7ff7a9243a90 + lVar6;
            }
            break;
          }
          uVar7 = (ulonglong)(iVar5 + 1U);
          piVar8 = piVar8 + 0x10;
        } while (iVar5 + 1U < 1000);
        local_6468 = '\x01';
        uVar7 = FUN_7ff7a32ca230(iVar2,iVar3);
      }
      bVar21 = iVar4 == 3;
      goto LAB_7ff7a32ccb74;
    }
    cVar1 = FUN_7ff7a32cae50(local_6450);
    if ((cVar1 == '\0') && (iVar5 = FUN_7ff7a3b94f40(local_6440,"completed"), iVar5 == 0)) {
      local_6478 = &local_63a0;
      cVar1 = FUN_7ff7a32ca570(local_6378,local_6458,&local_6428,0);
      if (cVar1 == '\0') {
LAB_7ff7a32cca20:
        FUN_7ff7a32c91b0(iVar2,iVar3);
      }
      else {
        FUN_7ff7a32cd100(iVar2,iVar3);
        piVar8 = (int *)(&DAT_7ff7a923409c + lVar15 * 0x13890);
        uVar9 = uVar13;
        do {
          iVar5 = (int)uVar9;
          if (*piVar8 == -1) {
            if (iVar5 != -1) {
              lVar17 = lVar15 * 0x13890 + (longlong)iVar5 * 0x40;
              *(undefined8 *)(&DAT_7ff7a9234090 + lVar17) = local_6428;
              *(undefined8 *)(&DAT_7ff7a9234098 + lVar17) = uStack_6420;
              *(ulonglong *)(&DAT_7ff7a92340a0 + lVar17) = CONCAT44(uStack_6414,local_6418);
              *(undefined8 *)(&DAT_7ff7a92340a8 + lVar17) = uStack_6410;
              *(ulonglong *)(&DAT_7ff7a92340b0 + lVar17) = CONCAT44(uStack_6404,local_6408);
              *(ulonglong *)(&DAT_7ff7a92340b8 + lVar17) = CONCAT44(uStack_63fc,uStack_6400);
              lVar6 = (lVar15 * 0x1389 + (longlong)iVar5) * 0x10;
              *(undefined8 *)(&DAT_7ff7a92340c0 + lVar17) = local_63f8;
              *(ulonglong *)(&DAT_7ff7a92340c8 + lVar17) = CONCAT44(uStack_63ec,uStack_63f0);
              *(undefined4 *)(&DAT_7ff7a9243a90 + lVar6) = local_63a0;
              *(undefined4 *)(lVar6 + 0x7ff7a9243a94) = uStack_639c;
              *(undefined4 *)(lVar6 + 0x7ff7a9243a98) = uStack_6398;
              *(undefined4 *)(lVar6 + 0x7ff7a9243a9c) = uStack_6394;
              *(undefined **)(&DAT_7ff7a92340b0 + lVar17) = &DAT_7ff7a9243a90 + lVar6;
            }
            goto LAB_7ff7a32cca20;
          }
          uVar9 = (ulonglong)(iVar5 + 1U);
          piVar8 = piVar8 + 0x10;
        } while (iVar5 + 1U < 1000);
        FUN_7ff7a32c91b0(iVar2,iVar3);
      }
    }
    else if (*(ushort *)(uVar7 + 0x28) < (ushort)local_6448[0]) {
      *(ushort *)(uVar7 + 0x28) = (ushort)local_6448[0];
      local_6468 = '\x01';
    }
    else {
      local_6468 = '\0';
    }
    if (iVar4 != 3) goto LAB_7ff7a32ccb80;
    *(undefined4 *)(uVar7 + 0x38) = 3;
    lVar6 = FUN_7ff7a32ca280(iVar2,iVar3);
    if (lVar6 != 0) {
      *(undefined4 *)(lVar6 + 0x28) = 3;
    }
  }
  else {
    cVar1 = FUN_7ff7a32cae50(local_6450);
    uVar7 = uVar13;
    if (cVar1 == '\0') {
      if (iVar4 != 4) goto LAB_7ff7a32ccb80;
      uVar7 = FUN_7ff7a32ca230(iVar2,iVar3);
      local_6478 = &local_63a0;
      if (uVar7 == 0) {
        cVar1 = FUN_7ff7a32ca570(local_6378,local_6458,&local_6428,1);
        if (cVar1 != '\0') {
          lVar6 = FUN_7ff7a32ca280(iVar2,iVar3);
          if (lVar6 != 0) {
            uStack_6410 = *(undefined8 *)(lVar6 + 0x18);
            local_6418 = *(undefined4 *)(lVar6 + 0x10);
            puVar11 = *(undefined4 **)(lVar6 + 0x20);
            if (puVar11 != (undefined4 *)0x0) {
              local_63a0 = *puVar11;
              uStack_639c = puVar11[1];
              uStack_6398 = puVar11[2];
              uStack_6394 = puVar11[3];
            }
          }
          piVar8 = (int *)(&DAT_7ff7a923409c + lVar15 * 0x13890);
          uVar7 = uVar13;
          do {
            iVar4 = (int)uVar7;
            if (*piVar8 == -1) {
              if (iVar4 != -1) {
                lVar17 = lVar15 * 0x13890 + (longlong)iVar4 * 0x40;
                *(undefined8 *)(&DAT_7ff7a9234090 + lVar17) = local_6428;
                *(undefined8 *)(&DAT_7ff7a9234098 + lVar17) = uStack_6420;
                *(ulonglong *)(&DAT_7ff7a92340a0 + lVar17) = CONCAT44(uStack_6414,local_6418);
                *(undefined8 *)(&DAT_7ff7a92340a8 + lVar17) = uStack_6410;
                *(undefined4 *)(&DAT_7ff7a92340b0 + lVar17) = local_6408;
                *(undefined4 *)(lVar17 + 0x7ff7a92340b4) = uStack_6404;
                *(undefined4 *)(&DAT_7ff7a92340b8 + lVar17) = uStack_6400;
                *(undefined4 *)(&DAT_7ff7a92340bc + lVar17) = uStack_63fc;
                lVar6 = (lVar15 * 0x1389 + (longlong)iVar4) * 0x10;
                *(undefined8 *)(&DAT_7ff7a92340c0 + lVar17) = local_63f8;
                *(ulonglong *)(&DAT_7ff7a92340c8 + lVar17) = CONCAT44(uStack_63ec,uStack_63f0);
                *(undefined4 *)(&DAT_7ff7a9243a90 + lVar6) = local_63a0;
                *(undefined4 *)(lVar6 + 0x7ff7a9243a94) = uStack_639c;
                *(undefined4 *)(lVar6 + 0x7ff7a9243a98) = uStack_6398;
                *(undefined4 *)(lVar6 + 0x7ff7a9243a9c) = uStack_6394;
                *(undefined **)(&DAT_7ff7a92340b0 + lVar17) = &DAT_7ff7a9243a90 + lVar6;
              }
              uVar7 = FUN_7ff7a32ca230(iVar2,iVar3);
              goto LAB_7ff7a32ccb79;
            }
            uVar7 = (ulonglong)(iVar4 + 1U);
            piVar8 = piVar8 + 0x10;
          } while (iVar4 + 1U < 1000);
          uVar7 = FUN_7ff7a32ca230(iVar2,iVar3);
        }
      }
      else {
        cVar1 = FUN_7ff7a32ca570(local_6378,local_6458,&local_6428,1);
        if (cVar1 != '\0') {
          FUN_7ff7a32cd100(iVar2,iVar3);
          piVar8 = (int *)(&DAT_7ff7a923409c + lVar15 * 0x13890);
          uVar9 = uVar13;
          do {
            iVar4 = (int)uVar9;
            if (*piVar8 == -1) {
              if (iVar4 != -1) {
                lVar17 = (longlong)iVar4 * 0x40 + lVar15 * 0x13890;
                *(undefined8 *)(&DAT_7ff7a9234090 + lVar17) = local_6428;
                *(undefined8 *)(&DAT_7ff7a9234098 + lVar17) = uStack_6420;
                *(ulonglong *)(&DAT_7ff7a92340a0 + lVar17) = CONCAT44(uStack_6414,local_6418);
                *(undefined8 *)(&DAT_7ff7a92340a8 + lVar17) = uStack_6410;
                *(ulonglong *)(&DAT_7ff7a92340b0 + lVar17) = CONCAT44(uStack_6404,local_6408);
                *(ulonglong *)(&DAT_7ff7a92340b8 + lVar17) = CONCAT44(uStack_63fc,uStack_6400);
                lVar6 = (lVar15 * 0x1389 + (longlong)iVar4) * 0x10;
                *(undefined8 *)(&DAT_7ff7a92340c0 + lVar17) = local_63f8;
                *(ulonglong *)(&DAT_7ff7a92340c8 + lVar17) = CONCAT44(uStack_63ec,uStack_63f0);
                *(undefined4 *)(&DAT_7ff7a9243a90 + lVar6) = local_63a0;
                *(undefined4 *)(lVar6 + 0x7ff7a9243a94) = uStack_639c;
                *(undefined4 *)(lVar6 + 0x7ff7a9243a98) = uStack_6398;
                *(undefined4 *)(lVar6 + 0x7ff7a9243a9c) = uStack_6394;
                *(undefined **)(&DAT_7ff7a92340b0 + lVar17) = &DAT_7ff7a9243a90 + lVar6;
              }
              break;
            }
            uVar9 = (ulonglong)(iVar4 + 1U);
            piVar8 = piVar8 + 0x10;
          } while (iVar4 + 1U < 1000);
        }
      }
    }
    else {
      FUN_7ff7a32cd100(iVar2,iVar3);
      bVar21 = iVar4 == 4;
LAB_7ff7a32ccb74:
      if (!bVar21) goto LAB_7ff7a32ccb80;
    }
  }
LAB_7ff7a32ccb79:
  FUN_7ff7a32c91b0(iVar2);
LAB_7ff7a32ccb80:
  cVar1 = FUN_7ff7a340f430(local_6378,local_6458,"triggers",&local_63c8);
  if (cVar1 != '\0') {
    lVar6 = FUN_7ff7a340efe0(local_6378,local_63c8);
    uVar9 = uVar13;
    uVar18 = local_6438;
    while (local_6438 = uVar18, lVar6 != 0) {
      cVar1 = FUN_7ff7a340f570(local_6378,lVar6,&DAT_7ff7a3cd07fc,&local_6460);
      if (cVar1 == '\0') {
        return;
      }
      iVar4 = FUN_7ff7a3b94f40(CONCAT44(uStack_645c,local_6460),"GRANT_PRODUCT");
      if (((iVar4 != 0) &&
          (iVar4 = FUN_7ff7a3b94f40(CONCAT44(uStack_645c,local_6460),"ACTIVATE_ACHIEVEMENT"),
          iVar4 != 0)) &&
         (iVar4 = FUN_7ff7a3b94f40(CONCAT44(uStack_645c,local_6460),"GRANT_CURRENCY"), iVar4 != 0))
      {
        FUN_7ff7a3b94f40(CONCAT44(uStack_645c,local_6460),"SET_CURRENCY_BALANCE");
      }
      iVar4 = FUN_7ff7a3b94f40(CONCAT44(uStack_645c,local_6460),"GRANT_PRODUCT");
      if (iVar4 == 0) {
        cVar1 = FUN_7ff7a340f430(local_6378,lVar6,"inventory",&local_63e0);
        if (cVar1 == '\0') {
          return;
        }
        cVar1 = FUN_7ff7a340f430(local_6378,local_63e0,"detailed_inventory",&local_63c0);
        if (cVar1 == '\0') {
          return;
        }
        local_6478 = (undefined4 *)CONCAT44(local_6478._4_4_,0x32 - local_644c);
        iVar4 = FUN_7ff7a340c1d0(iVar2,local_6378,local_63c0,local_61d8 + (ulonglong)local_644c * 2)
        ;
        local_644c = local_644c + iVar4;
        cVar1 = FUN_7ff7a340f430(local_6378,local_63e0,"currencies",&local_63b8);
        uVar19 = local_63b8;
        if (cVar1 == '\0') {
          return;
        }
LAB_7ff7a32cce4e:
        local_6478 = (undefined4 *)CONCAT44(local_6478._4_4_,0xd - (int)uVar9);
        iVar4 = FUN_7ff7a340c480(iVar2,local_6378,uVar19,local_6248 + uVar9 * 2);
        uVar9 = (ulonglong)(uint)((int)uVar9 + iVar4);
      }
      else {
        iVar4 = FUN_7ff7a3b94f40(CONCAT44(uStack_645c,local_6460),"GRANT_CURRENCY");
        if ((iVar4 == 0) ||
           (iVar4 = FUN_7ff7a3b94f40(CONCAT44(uStack_645c,local_6460),"SET_CURRENCY_BALANCE"),
           iVar4 == 0)) {
          cVar1 = FUN_7ff7a340f430(local_6378,lVar6,"inventory",&local_63b0);
          if (cVar1 == '\0') {
            return;
          }
          cVar1 = FUN_7ff7a340f430(local_6378,local_63b0,"currencies",&local_63a8);
          uVar19 = local_63a8;
          if (cVar1 == '\0') {
            return;
          }
          goto LAB_7ff7a32cce4e;
        }
        iVar4 = FUN_7ff7a3b94f40(CONCAT44(uStack_645c,local_6460),"ACTIVATE_ACHIEVEMENT");
        if (iVar4 == 0) {
          local_6478 = &local_6390;
          cVar1 = FUN_7ff7a32ca570(local_6378,lVar6,&local_6428,0);
          if (cVar1 != '\0') {
            uStack_63f0 = 2;
            piVar8 = (int *)(&DAT_7ff7a923409c + lVar15 * 0x13890);
            uVar18 = uVar13;
            uVar20 = uVar13;
            do {
              iVar4 = (int)uVar18;
              if (*piVar8 == -1) {
                if (iVar4 != -1) {
                  lVar17 = lVar15 * 0x13890 + uVar20 * 0x40;
                  *(undefined8 *)(&DAT_7ff7a9234090 + lVar17) = local_6428;
                  *(undefined8 *)(&DAT_7ff7a9234098 + lVar17) = uStack_6420;
                  *(ulonglong *)(&DAT_7ff7a92340a0 + lVar17) = CONCAT44(uStack_6414,local_6418);
                  *(undefined8 *)(&DAT_7ff7a92340a8 + lVar17) = uStack_6410;
                  *(ulonglong *)(&DAT_7ff7a92340b0 + lVar17) = CONCAT44(uStack_6404,local_6408);
                  *(ulonglong *)(&DAT_7ff7a92340b8 + lVar17) = CONCAT44(uStack_63fc,uStack_6400);
                  *(undefined8 *)(&DAT_7ff7a92340c0 + lVar17) = local_63f8;
                  *(ulonglong *)(&DAT_7ff7a92340c8 + lVar17) = CONCAT44(uStack_63ec,2);
                  lVar17 = (uVar20 + lVar15 * 0x1389) * 0x10;
                  *(undefined4 *)(&DAT_7ff7a9243a90 + lVar17) = local_6390;
                  *(undefined4 *)(lVar17 + 0x7ff7a9243a94) = uStack_638c;
                  *(undefined4 *)(lVar17 + 0x7ff7a9243a98) = uStack_6388;
                  *(undefined4 *)(lVar17 + 0x7ff7a9243a9c) = uStack_6384;
                  *(undefined **)(&DAT_7ff7a92340b0 + lVar15 * 0x13890 + uVar20 * 0x40) =
                       &DAT_7ff7a9243a90 + ((longlong)iVar4 + lVar15 * 0x1389) * 0x10;
                }
                break;
              }
              uVar18 = (ulonglong)(iVar4 + 1U);
              uVar20 = uVar20 + 1;
              piVar8 = piVar8 + 0x10;
            } while (iVar4 + 1U < 1000);
          }
        }
      }
      uVar12 = (uint)uVar9;
      lVar6 = FUN_7ff7a340f240(local_6378,lVar6);
      uVar18 = local_6438;
    }
    if (((int)uVar18 != -1) && (cVar1 = FUN_7ff7a3630d90(iVar2,&local_6460), cVar1 != '\0')) {
      if ((int)uVar18 == 1) {
        if ((local_6468 != '\0') && (uVar7 != 0)) {
          FUN_7ff7a32cdae0(local_6460,uVar7);
        }
      }
      else {
        cVar1 = FUN_7ff7a324d020(local_6460,"achievementEngine",DAT_7ff7a4d63d08);
        if (cVar1 != '\0') {
          FUN_7ff7a325c620("eventType",uVar18 & 0xffffffff,DAT_7ff7a4d63d08);
          FUN_7ff7a325c3e0("success",local_6467,DAT_7ff7a4d63d08);
          FUN_7ff7a325c810("challengeName",local_63d8,DAT_7ff7a4d63d08);
          FUN_7ff7a325c620(&DAT_7ff7a3cd07e4,iVar3,DAT_7ff7a4d63d08);
          FUN_7ff7a325c620(&DAT_7ff7a3cd03f8,local_6450,DAT_7ff7a4d63d08);
          FUN_7ff7a324d7b0("itemsReceived",DAT_7ff7a4d63d08);
          uVar10 = local_644c;
          if (local_644c != 0) {
            puVar11 = local_61d8;
            uVar7 = uVar13;
            do {
              uVar14 = (int)uVar7 + 1;
              uVar7 = (ulonglong)uVar14;
              FUN_7ff7a324d710(uVar7,DAT_7ff7a4d63d08);
              FUN_7ff7a325c510(&DAT_7ff7a3cd0848,*puVar11,DAT_7ff7a4d63d08);
              FUN_7ff7a325c620("quantity",puVar11[1],DAT_7ff7a4d63d08);
              FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
              puVar11 = puVar11 + 2;
            } while (uVar14 < uVar10);
          }
          FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
          FUN_7ff7a324d7b0("currenciesReceived",DAT_7ff7a4d63d08);
          if (uVar12 != 0) {
            puVar16 = local_6248 + 1;
            do {
              uVar10 = (int)uVar13 + 1;
              FUN_7ff7a324d710(uVar10,DAT_7ff7a4d63d08);
              FUN_7ff7a325c620("currencyID",puVar16[-1],DAT_7ff7a4d63d08);
              FUN_7ff7a325c620("amount",*puVar16,DAT_7ff7a4d63d08);
              FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
              puVar16 = puVar16 + 2;
              uVar13 = (ulonglong)uVar10;
            } while (uVar10 < uVar12);
          }
          FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
          FUN_7ff7a325c3e0("dispatchChildren",1,DAT_7ff7a4d63d08);
          FUN_7ff7a324e7e0(DAT_7ff7a4d63d08);
        }
      }
    }
  }
  return;
}

