// image offset 0x27C480 address 7ff7a340c480

ulonglong FUN_7ff7a340c480(undefined4 param_1,undefined8 param_2,undefined8 param_3,longlong param_4
                          ,uint param_5)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  longlong lVar6;
  undefined8 uVar7;
  uint uVar8;
  ulonglong uVar9;
  undefined1 local_68 [16];
  undefined1 local_58 [16];
  byte local_48 [4];
  int local_44;
  undefined1 local_40 [24];

  uVar9 = 0;
  lVar5 = FUN_7ff7a340efe0(param_2,param_3);
  if (lVar5 != 0) {
    do {
      FUN_7ff7a3bd97f0(local_68,1);
      iVar3 = 0;
      iVar4 = 0;
      for (lVar6 = FUN_7ff7a340efe0(param_2,lVar5); lVar6 != 0;
          lVar6 = FUN_7ff7a340f240(param_2,lVar6)) {
        uVar7 = FUN_7ff7a340f220(param_2,lVar6);
        iVar2 = FUN_7ff7a3b94f40(uVar7,"currency_id");
        if (iVar2 == 0) {
          local_48[0] = FUN_7ff7a340f750(param_2,lVar6);
        }
        else {
          iVar2 = FUN_7ff7a3b94f40(uVar7,"balance_delta");
          if (iVar2 == 0) {
            iVar3 = FUN_7ff7a340f170(param_2,lVar6);
          }
          else {
            iVar2 = FUN_7ff7a3b94f40(uVar7,"balance_before");
            if (iVar2 == 0) {
              iVar4 = FUN_7ff7a340f750(param_2,lVar6);
            }
          }
        }
      }
      local_44 = iVar4 + iVar3;
      FUN_7ff7a340d510(param_1,local_48[0]);
      if ((uint)uVar9 < param_5) {
        puVar1 = (uint *)(param_4 + uVar9 * 8);
        *puVar1 = (uint)local_48[0];
        puVar1[1] = local_44 - iVar4;
      }
      uVar8 = (uint)uVar9 + 1;
      uVar9 = (ulonglong)uVar8;
      FUN_7ff7a3bcb570(local_48);
      FUN_7ff7a3bbc060(local_58);
      FUN_7ff7a3c04d10(local_40);
      lVar5 = FUN_7ff7a340f240(param_2,lVar5);
    } while (lVar5 != 0);
    if (uVar8 != 0) {
      FUN_7ff7a3265f30(param_1);
    }
  }
  FUN_7ff7a34052e0(param_1,2);
  return uVar9;
}
