// image offset 0x27B400 address 7ff7a340b400

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a340b360(undefined8 param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined8 *puVar4;
  longlong lVar5;
  uint uVar6;
  uint uVar7;
  ulonglong uVar8;
  longlong lVar9;
  undefined1 auStack_68 [32];
  undefined *local_48;
  undefined1 local_40;
  longlong local_38;
  undefined1 local_30 [32];
  ulonglong local_10;
  
  local_10 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_68;
  iVar3 = FUN_7ff7a39c9370();
  puVar4 = (undefined8 *)FUN_7ff7a39c9400(&local_38,param_1);
  DAT_7ff7ab2fa5fc = FUN_7ff7a3bcdb60(*puVar4);
  if (local_38 != 0) {
    LOCK();
    piVar1 = (int *)(local_38 + 8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if ((iVar2 == 1) && (local_38 != 0)) {
      FUN_7ff7a3c89b70(local_38,1);
    }
  }
  DAT_7ff7ab2fa600 = 0;
  uVar8 = 0;
  lVar5 = DAT_7ff7ab0ff108;
  uVar6 = DAT_7ff7ab2fa5fc;
  if (DAT_7ff7ab2fa5fc != 0) {
    do {
      lVar9 = uVar8 * 0xe0;
      if ((lVar5 == 0) || (*(int *)(lVar5 + 0x10) != 0)) {
        FUN_7ff7a339c850(local_30,&DAT_7ff7ab2df070 + lVar9);
        local_48 = &DAT_7ff7ab2df0e0 + lVar9;
        local_40 = (&DAT_7ff7ab2df120)[lVar9];
        FUN_7ff7a340dd30(iVar3,local_30,0,0);
        lVar5 = DAT_7ff7ab0ff108;
        uVar6 = DAT_7ff7ab2fa5fc;
      }
      uVar7 = (int)uVar8 + 1;
      uVar8 = (ulonglong)uVar7;
    } while (uVar7 < uVar6);
  }
  if (uVar6 < DAT_7ff7ab2fa5f8) {
    (&DAT_7ff7ab1c85a8)[(longlong)iVar3 * 0xc8438] = 1;
    FUN_7ff7a3405470(iVar3);
  }
  else {
    FUN_7ff7a3408b30(iVar3,DAT_7ff7ab2fa5f0 + 1);
  }
  return;
}

