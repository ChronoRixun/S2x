// image offset 0x2B3590 address 7ff7a3443590

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a3443590(int param_1,undefined8 *param_2,undefined8 *param_3)

{
  uint uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  longlong lVar5;
  undefined8 *puVar6;
  undefined8 uVar7;
  longlong lVar8;
  longlong lVar9;
  undefined1 auStack_868 [32];
  undefined8 local_848;
  undefined8 uStack_840;
  undefined8 local_838;
  undefined1 local_830;
  undefined8 local_82f [128];
  undefined1 local_42f;
  undefined8 local_42e;
  undefined8 uStack_426;
  undefined8 local_41e;
  undefined8 uStack_416;
  undefined4 local_40e;
  undefined4 uStack_40a;
  undefined4 uStack_406;
  undefined4 uStack_402;
  undefined4 local_3fe;
  undefined4 uStack_3fa;
  undefined4 uStack_3f6;
  undefined4 uStack_3f2;
  undefined1 local_3ee;
  undefined1 local_3ed [961];
  undefined4 local_2c;
  ulonglong local_28;
  
  local_28 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_868;
  lVar5 = (longlong)param_1;
  lVar9 = lVar5 * 0x30cc;
  if ((uint)(&DAT_7ff7ab97f938)[lVar5 * 0xc33] < 6) {
    local_838 = 0;
    local_830 = 0;
    local_848 = 0;
    uStack_840 = 0;
    memset(local_3ed,0,0x3c0);
    local_2c = 0;
    lVar8 = 8;
    puVar6 = local_82f;
    do {
      uVar7 = param_2[1];
      uVar2 = param_2[2];
      uVar3 = param_2[3];
      *puVar6 = *param_2;
      puVar6[1] = uVar7;
      uVar7 = param_2[4];
      uVar4 = param_2[5];
      puVar6[2] = uVar2;
      puVar6[3] = uVar3;
      uVar2 = param_2[6];
      uVar3 = param_2[7];
      puVar6[4] = uVar7;
      puVar6[5] = uVar4;
      uVar7 = param_2[8];
      uVar4 = param_2[9];
      puVar6[6] = uVar2;
      puVar6[7] = uVar3;
      uVar2 = param_2[10];
      uVar3 = param_2[0xb];
      puVar6[8] = uVar7;
      puVar6[9] = uVar4;
      uVar7 = param_2[0xc];
      uVar4 = param_2[0xd];
      puVar6[10] = uVar2;
      puVar6[0xb] = uVar3;
      uVar2 = param_2[0xe];
      uVar3 = param_2[0xf];
      puVar6[0xc] = uVar7;
      puVar6[0xd] = uVar4;
      puVar6[0xe] = uVar2;
      puVar6[0xf] = uVar3;
      lVar8 = lVar8 + -1;
      puVar6 = puVar6 + 0x10;
      param_2 = param_2 + 0x10;
    } while (lVar8 != 0);
    local_42e = *param_3;
    uStack_426 = param_3[1];
    local_42f = 0;
    local_41e = param_3[2];
    uStack_416 = param_3[3];
    local_3ee = 0;
    local_40e = *(undefined4 *)(param_3 + 4);
    uStack_40a = *(undefined4 *)((longlong)param_3 + 0x24);
    uStack_406 = *(undefined4 *)(param_3 + 5);
    uStack_402 = *(undefined4 *)((longlong)param_3 + 0x2c);
    local_3fe = *(undefined4 *)(param_3 + 6);
    uStack_3fa = *(undefined4 *)((longlong)param_3 + 0x34);
    uStack_3f6 = *(undefined4 *)(param_3 + 7);
    uStack_3f2 = *(undefined4 *)((longlong)param_3 + 0x3c);
    FUN_7ff7a39c90a0(&local_848);
    uVar1 = *(uint *)(&DAT_7ff7ab97f934 + lVar9);
    local_2c = 1;
    *(uint *)(&DAT_7ff7ab97f934 + lVar9) = (uVar1 + 1) % 6;
    memcpy(&DAT_7ff7ab97c870 + (ulonglong)uVar1 * 0x820 + lVar9,&local_848,0x820);
    (&DAT_7ff7ab97f938)[lVar5 * 0xc33] = (&DAT_7ff7ab97f938)[lVar5 * 0xc33] + 1;
    uVar7 = 1;
  }
  else {
    uVar7 = 0;
  }
  return uVar7;
}

