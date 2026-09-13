// image offset 0x11DC00 address 7ff7a32adc00

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a32adc00(longlong param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  longlong lVar4;
  undefined4 *puVar5;
  longlong lVar6;
  float fVar7;
  undefined1 auStack_68 [32];
  undefined1 local_48 [16];
  undefined1 local_38 [32];
  ulonglong local_18;
  
  local_18 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_68;
  if ((((int)((longlong)(*(ulonglong *)(param_1 + 0x48) - *(ulonglong *)(param_1 + 0x50)) >> 4) != 2
       ) || (*(ulonglong *)(param_1 + 0x48) <= *(ulonglong *)(param_1 + 0x50))) ||
     (iVar2 = FUN_7ff7a3468d90(param_1), iVar2 == 0)) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  if (*(ulonglong *)(param_1 + 0x50) < *(ulonglong *)(param_1 + 0x48)) {
    fVar7 = (float)FUN_7ff7a3469aa0(param_1);
    iVar2 = (int)fVar7;
  }
  else {
    iVar2 = 0;
  }
  uVar3 = FUN_7ff7a325cb30(param_1,2);
  FUN_7ff7a37e2170(uVar3,local_48);
  cVar1 = FUN_7ff7a3407300(local_48);
  if (cVar1 == '\0') {
    puVar5 = *(undefined4 **)(param_1 + 0x48);
    puVar5[2] = 0;
    *puVar5 = 1;
    puVar5[4] = 0;
    *(undefined4 **)(param_1 + 0x48) = puVar5 + 8;
  }
  else {
    FUN_7ff7a39c90a0(local_38);
    cVar1 = FUN_7ff7a343e580(iVar2,local_48,local_38);
    puVar5 = *(undefined4 **)(param_1 + 0x48);
    puVar5[2] = (uint)(cVar1 != '\0');
    *puVar5 = 1;
    *(undefined4 **)(param_1 + 0x48) = puVar5 + 4;
    if (cVar1 == '\0') {
      puVar5[4] = 0;
      puVar5 = puVar5 + 8;
    }
    else {
      lVar4 = FUN_7ff7a39c9020(local_38);
      if (lVar4 != 0) {
        lVar6 = -1;
        do {
          lVar6 = lVar6 + 1;
        } while (*(char *)(lVar4 + lVar6) != '\0');
        FUN_7ff7a3294620(param_1,lVar4);
        return 2;
      }
      puVar5 = *(undefined4 **)(param_1 + 0x48);
      *puVar5 = 0;
      puVar5 = puVar5 + 4;
    }
    *(undefined4 **)(param_1 + 0x48) = puVar5;
  }
  return 2;
}

