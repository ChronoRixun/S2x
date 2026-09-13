// image offset 0x27BFE0 address 7ff7a340bfe0

undefined8 FUN_7ff7a340bfe0(int param_1,undefined4 *param_2,uint param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char cVar4;
  longlong lVar5;
  undefined4 *puVar6;
  ulonglong uVar7;
  longlong lVar8;
  undefined4 *puVar9;
  uint uVar10;
  uint uVar11;
  undefined4 *puVar12;
  undefined8 *puVar13;
  longlong lVar14;
  ulonglong local_38 [2];
  
  uVar7 = (ulonglong)param_3;
  lVar14 = (longlong)param_1;
  if ((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) {
    uVar10 = 0;
    puVar9 = param_2;
    if (param_3 != 0) {
      do {
        cVar4 = FUN_7ff7a3405270(*puVar9);
        if (cVar4 == '\0') {
          return 0;
        }
        uVar1 = *puVar9;
        cVar4 = thunk_EXT_FUN_7ff7a31804d4(uVar1);
        if (cVar4 == '\0') {
          uVar11 = 0;
          local_38[0] = 0;
          FUN_7ff7a3409300(param_1,uVar1,local_38);
          if (local_38[0] != 0) {
            uVar11 = *(uint *)(local_38[0] + 4);
          }
        }
        else {
          uVar11 = 1;
        }
        if (uVar11 < (uint)puVar9[1]) {
          return 0;
        }
        uVar10 = uVar10 + 1;
        puVar9 = puVar9 + 5;
      } while (uVar10 < param_3);
    }
    lVar5 = FUN_7ff7a33981b0(5,param_1);
    cVar4 = FUN_7ff7a39c9650(lVar5);
    if ((cVar4 != '\0') && (cVar4 = FUN_7ff7a39c9710(lVar5), cVar4 != '\0')) {
      lVar8 = lVar14 * 0x280;
      puVar9 = (undefined4 *)(&DAT_7ff7ab325870 + lVar8);
      FUN_7ff7a339d3b0(puVar9);
      *(uint *)(&DAT_7ff7ab325a70 + lVar8) = param_3;
      uVar1 = param_4[1];
      uVar2 = param_4[2];
      uVar3 = param_4[3];
      *puVar9 = *param_4;
      *(undefined4 *)(lVar8 + 0x7ff7ab325874) = uVar1;
      *(undefined4 *)(lVar8 + 0x7ff7ab325878) = uVar2;
      *(undefined4 *)(lVar8 + 0x7ff7ab32587c) = uVar3;
      *(undefined8 *)(&DAT_7ff7ab325880 + lVar8) = *(undefined8 *)(param_4 + 4);
      (&DAT_7ff7ab325888)[lVar8] = *(undefined1 *)(param_4 + 6);
      if (param_3 != 0) {
        puVar12 = (undefined4 *)(&DAT_7ff7ab3258a4 + lVar8);
        puVar6 = (undefined4 *)((longlong)&DAT_7ff7ab2909ec + lVar14 * 0x2c);
        puVar13 = (undefined8 *)(&DAT_7ff7ab325a74 + lVar8);
        do {
          puVar12[-1] = *param_2;
          *puVar12 = param_2[1];
          puVar12 = puVar12 + 0xc;
          *puVar13 = *(undefined8 *)(param_2 + 2);
          *(undefined4 *)(puVar13 + 1) = param_2[4];
          *puVar6 = *param_2;
          uVar7 = uVar7 - 1;
          puVar6 = puVar6 + 1;
          puVar13 = (undefined8 *)((longlong)puVar13 + 0xc);
          param_2 = param_2 + 5;
        } while (uVar7 != 0);
      }
      FUN_7ff7a39c9700(lVar5,puVar9);
      (&DAT_7ff7ab2909e8)[lVar14 * 0x16] = 0x101;
      *(code **)(lVar5 + 0x30) = thunk_FUN_7ff7b51a545a;
      *(code **)(lVar5 + 0x40) = FUN_7ff7a340b8d0;
      *(code **)(lVar5 + 0x38) = FUN_7ff7a340b980;
      FUN_7ff7a39c97e0(lVar5);
      return 1;
    }
  }
  return 0;
}

