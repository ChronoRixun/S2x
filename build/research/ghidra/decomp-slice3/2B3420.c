// image offset 0x2B3420 address 7ff7a3443420

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a3443420(int param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  longlong lVar15;
  longlong lVar16;
  undefined8 uVar17;
  undefined8 *puVar18;
  longlong lVar19;
  undefined1 auStack_858 [32];
  undefined8 local_838;
  undefined8 uStack_830;
  undefined8 local_828;
  undefined1 local_820;
  undefined8 local_81f [128];
  undefined1 local_41e [1026];
  undefined4 local_1c;
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_858;
  lVar15 = (longlong)param_1;
  lVar19 = lVar15 * 0x30cc;
  if ((uint)(&DAT_7ff7ab97f938)[lVar15 * 0xc33] < 6) {
    local_828 = 0;
    local_820 = 0;
    local_838 = 0;
    uStack_830 = 0;
    memset(local_41e,0,0x401);
    local_1c = 0;
    lVar16 = 8;
    puVar18 = local_81f;
    do {
      puVar1 = puVar18 + 0x10;
      uVar17 = param_2[1];
      uVar12 = param_2[2];
      uVar13 = param_2[3];
      puVar2 = param_2 + 0x10;
      *puVar18 = *param_2;
      puVar18[1] = uVar17;
      uVar17 = param_2[4];
      uVar14 = param_2[5];
      puVar18[2] = uVar12;
      puVar18[3] = uVar13;
      uVar12 = param_2[6];
      uVar13 = param_2[7];
      puVar18[4] = uVar17;
      puVar18[5] = uVar14;
      uVar17 = param_2[8];
      uVar14 = param_2[9];
      puVar18[6] = uVar12;
      puVar18[7] = uVar13;
      uVar12 = param_2[10];
      uVar13 = param_2[0xb];
      puVar18[8] = uVar17;
      puVar18[9] = uVar14;
      uVar4 = *(undefined4 *)(param_2 + 0xc);
      uVar5 = *(undefined4 *)((longlong)param_2 + 100);
      uVar6 = *(undefined4 *)(param_2 + 0xd);
      uVar7 = *(undefined4 *)((longlong)param_2 + 0x6c);
      puVar18[10] = uVar12;
      puVar18[0xb] = uVar13;
      uVar8 = *(undefined4 *)(param_2 + 0xe);
      uVar9 = *(undefined4 *)((longlong)param_2 + 0x74);
      uVar10 = *(undefined4 *)(param_2 + 0xf);
      uVar11 = *(undefined4 *)((longlong)param_2 + 0x7c);
      *(undefined4 *)(puVar18 + 0xc) = uVar4;
      *(undefined4 *)((longlong)puVar18 + 100) = uVar5;
      *(undefined4 *)(puVar18 + 0xd) = uVar6;
      *(undefined4 *)((longlong)puVar18 + 0x6c) = uVar7;
      *(undefined4 *)(puVar18 + 0xe) = uVar8;
      *(undefined4 *)((longlong)puVar18 + 0x74) = uVar9;
      *(undefined4 *)(puVar18 + 0xf) = uVar10;
      *(undefined4 *)((longlong)puVar18 + 0x7c) = uVar11;
      lVar16 = lVar16 + -1;
      puVar18 = puVar1;
      param_2 = puVar2;
    } while (lVar16 != 0);
    *(undefined1 *)puVar1 = *(undefined1 *)puVar2;
    FUN_7ff7a39c90a0(&local_838);
    uVar3 = *(uint *)(&DAT_7ff7ab97f934 + lVar19);
    local_1c = 0;
    *(uint *)(&DAT_7ff7ab97f934 + lVar19) = (uVar3 + 1) % 6;
    memcpy(&DAT_7ff7ab97c870 + (ulonglong)uVar3 * 0x820 + lVar19,&local_838,0x820);
    (&DAT_7ff7ab97f938)[lVar15 * 0xc33] = (&DAT_7ff7ab97f938)[lVar15 * 0xc33] + 1;
    uVar17 = 1;
  }
  else {
    uVar17 = 0;
  }
  return uVar17;
}

