// image offset 0x125020 address 7ff7a32b5020

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32b5020(longlong param_1)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  ulonglong uVar5;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  undefined1 auStack_4b48 [32];
  undefined1 *local_4b28;
  undefined4 local_4b20;
  undefined1 *local_4b18;
  undefined1 local_4b08 [8];
  undefined8 local_4b00;
  undefined1 local_4af8 [8];
  undefined8 local_4af0;
  undefined8 local_4ae8;
  undefined4 local_4ae0;
  undefined1 local_4ad8 [304];
  undefined1 local_49a8 [384];
  undefined1 local_4828 [10240];
  char local_2028 [4096];
  undefined1 local_1028 [4096];
  ulonglong local_28;
  undefined8 local_20;
  ulonglong uVar6;
  
  local_20 = 0x7ff7a32b5040;
  local_28 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_4b48;
  uVar6 = *(ulonglong *)(param_1 + 0x48);
  uVar5 = *(ulonglong *)(param_1 + 0x50);
  if ((int)((longlong)(uVar6 - uVar5) >> 4) != 3) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
    uVar5 = *(ulonglong *)(param_1 + 0x50);
    uVar6 = *(ulonglong *)(param_1 + 0x48);
  }
  if ((uVar6 <= uVar5) || (iVar3 = FUN_7ff7a3468d90(param_1), iVar3 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x10U) ||
     (iVar3 = FUN_7ff7a3468d90(param_1), iVar3 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if ((*(ulonglong *)(param_1 + 0x48) <= *(longlong *)(param_1 + 0x50) + 0x20U) ||
     (iVar3 = FUN_7ff7a3468d90(param_1), iVar3 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar6 = *(ulonglong *)(param_1 + 0x50);
  fVar12 = 0.0;
  uVar5 = *(ulonglong *)(param_1 + 0x48);
  if (uVar6 < uVar5) {
    fVar12 = (float)FUN_7ff7a3469aa0(param_1,uVar6);
    uVar6 = *(ulonglong *)(param_1 + 0x50);
    uVar5 = *(ulonglong *)(param_1 + 0x48);
  }
  iVar11 = 0;
  iVar3 = 0;
  if (uVar6 + 0x10 < uVar5) {
    fVar13 = (float)FUN_7ff7a3469aa0(param_1);
    uVar6 = *(ulonglong *)(param_1 + 0x50);
    uVar5 = *(ulonglong *)(param_1 + 0x48);
    iVar3 = (int)fVar13;
  }
  if (uVar6 + 0x20 < uVar5) {
    fVar13 = (float)FUN_7ff7a3469aa0(param_1);
    iVar11 = (int)fVar13;
  }
  local_4b28._0_4_ = 0x1000;
  cVar1 = FUN_7ff7a35022f0((int)fVar12,iVar3,iVar11,local_2028);
  if (cVar1 != '\0') {
    uVar6 = 0xffffffffffffffff;
    do {
      uVar5 = uVar6 + 1;
      lVar7 = uVar6 + 1;
      uVar6 = uVar5;
    } while (local_2028[lVar7] != '\0');
    if ((int)uVar5 != 0) {
      local_4b28 = (undefined1 *)CONCAT44(local_4b28._4_4_,0x20);
      FUN_7ff7a340f8d0(local_4ad8,local_2028,uVar5 & 0xffffffff,local_49a8);
      iVar3 = FUN_7ff7a340ff40(local_4ad8,&local_4b00);
      if (-1 < iVar3) {
        FUN_7ff7a3473c90(param_1,0,0);
        lVar7 = FUN_7ff7a340efe0(local_4ad8,local_4b00);
        do {
          if (lVar7 == 0) {
            return 1;
          }
          uVar8 = FUN_7ff7a340f220(local_4ad8,lVar7);
          cVar1 = FUN_7ff7a340fd00(lVar7);
          if (cVar1 == '\0') {
            cVar1 = FUN_7ff7a340fcd0(lVar7);
            if (cVar1 == '\0') {
              cVar1 = FUN_7ff7a340fcc0(lVar7);
              if (cVar1 == '\0') {
                cVar1 = FUN_7ff7a340fcb0(lVar7);
                if (cVar1 != '\0') {
                  uVar2 = FUN_7ff7a340efc0(lVar7);
                  FUN_7ff7a325c3e0(uVar8,uVar2,param_1);
                }
              }
              else {
                uVar4 = FUN_7ff7a340f020(local_4ad8,lVar7);
                FUN_7ff7a325c760(uVar8,uVar4,param_1);
              }
            }
            else {
              uVar4 = FUN_7ff7a340f1e0(local_4ad8,lVar7);
              FUN_7ff7a325c620(uVar8,uVar4,param_1);
            }
          }
          else {
            uVar9 = FUN_7ff7a340f710(local_4ad8,lVar7);
            uVar10 = FUN_7ff7a340f220(local_4ad8,lVar7);
            iVar3 = FUN_7ff7a3b94f40("content_long",uVar10);
            if (iVar3 == 0) {
              local_4b18 = local_4b08;
              local_4af0 = 0;
              local_4b28 = local_4828;
              local_4b20 = 0x100;
              local_4ae8 = 0;
              local_4ae0 = 0;
              cVar1 = FUN_7ff7a3400950(uVar9,local_4af8,local_1028,0x1000);
              if (cVar1 == '\0') {
                return 0;
              }
            }
            FUN_7ff7a325c810(uVar8,uVar9,param_1);
          }
          lVar7 = FUN_7ff7a340f240(local_4ad8,lVar7);
        } while( true );
      }
    }
  }
  return 0;
}

