// image offset 0xA488C0 address 7ff7a3bd88c0

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char FUN_7ff7a3bd88c0(longlong *param_1,longlong *param_2)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  undefined8 *puVar4;
  bool bVar5;
  char cVar6;
  char cVar7;
  ulonglong uVar8;
  byte bVar9;
  undefined1 auStack_238 [32];
  undefined4 local_218;
  undefined4 local_214;
  undefined4 local_210;
  undefined4 local_20c;
  undefined4 local_208 [2];
  longlong local_200;
  longlong *local_1f8;
  undefined1 local_1e8 [64];
  undefined1 local_1a8 [144];
  undefined1 local_118 [240];
  ulonglong local_28;
  
  local_28 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_238;
  local_1f8 = param_2;
  cVar6 = FUN_7ff7a3c07030(*param_2,param_1 + 2);
  local_208[0] = 0x87;
  if (cVar6 == '\0') {
LAB_7ff7a3bd89d5:
    local_210 = 0xf0;
LAB_7ff7a3bd89dd:
    local_20c = 0x40;
LAB_7ff7a3bd89e5:
    local_218 = 0;
LAB_7ff7a3bd89eb:
    bVar5 = false;
  }
  else {
    cVar6 = FUN_7ff7a3c06950(*param_2,local_1a8,local_208);
    if (cVar6 == '\0') goto LAB_7ff7a3bd89d5;
    local_210 = 0xf0;
    cVar6 = FUN_7ff7a3c06950(*param_2,local_118,&local_210);
    if (cVar6 == '\0') goto LAB_7ff7a3bd89dd;
    local_20c = 0x40;
    cVar6 = FUN_7ff7a3c06950(*param_2,local_1e8,&local_20c);
    if (cVar6 == '\0') goto LAB_7ff7a3bd89e5;
    cVar6 = FUN_7ff7a3c06fd0(*param_2,(longlong)param_1 + 0x14);
    if (cVar6 == '\0') goto LAB_7ff7a3bd89e5;
    cVar6 = FUN_7ff7a3c07030(*param_2,param_1 + 3);
    if (cVar6 == '\0') goto LAB_7ff7a3bd89e5;
    pcVar3 = *(code **)(*param_1 + 0x20);
    local_200 = *param_2;
    if (local_200 != 0) {
      LOCK();
      *(int *)(local_200 + 8) = *(int *)(local_200 + 8) + 1;
      UNLOCK();
    }
    cVar6 = (*pcVar3)(param_1,&local_200);
    if (cVar6 == '\0') goto LAB_7ff7a3bd89e5;
    local_218 = 0;
    cVar6 = FUN_7ff7a3c07030(*param_2,&local_218);
    if (cVar6 == '\0') goto LAB_7ff7a3bd89eb;
    bVar5 = true;
  }
  *(char *)((longlong)param_1 + 0x1d) = (char)local_218;
  bVar9 = 0;
  if ((char)local_218 != '\0') {
    do {
      if (bVar5) {
        uVar8 = (ulonglong)bVar9;
        if (2 < bVar9) {
          uVar8 = 3;
        }
        cVar6 = FUN_7ff7a3c07030(*param_2,(longlong)param_1 + (uVar8 + 8) * 4);
        if (cVar6 == '\0') goto LAB_7ff7a3bd8a40;
        uVar8 = 3;
        if (bVar9 < 3) {
          uVar8 = (ulonglong)bVar9;
        }
        cVar6 = FUN_7ff7a3c07030(*param_2,(longlong)param_1 + (uVar8 + 0xc) * 4);
        if (cVar6 == '\0') goto LAB_7ff7a3bd8a40;
        bVar5 = true;
      }
      else {
LAB_7ff7a3bd8a40:
        bVar5 = false;
      }
      bVar9 = bVar9 + 1;
    } while (bVar9 < *(byte *)((longlong)param_1 + 0x1d));
  }
  local_214 = 0;
  if (bVar5) {
    cVar7 = FUN_7ff7a3c07030(*param_2,&local_214);
    cVar6 = (char)local_214;
    if (cVar7 != '\0') {
      cVar7 = '\x01';
      goto LAB_7ff7a3bd8a70;
    }
  }
  cVar6 = (char)local_214;
  cVar7 = '\0';
LAB_7ff7a3bd8a70:
  *(char *)(param_1 + 8) = cVar6;
  bVar9 = 0;
  if (cVar6 != '\0') {
    do {
      if (cVar7 == '\0') {
LAB_7ff7a3bd8acc:
        cVar7 = '\0';
      }
      else {
        uVar8 = (ulonglong)bVar9;
        if (2 < bVar9) {
          uVar8 = 3;
        }
        cVar6 = FUN_7ff7a3c07030(*param_2,(longlong)param_1 + (uVar8 + 0x11) * 4);
        if (cVar6 == '\0') goto LAB_7ff7a3bd8acc;
        uVar8 = 3;
        if (bVar9 < 3) {
          uVar8 = (ulonglong)bVar9;
        }
        cVar6 = FUN_7ff7a3c07030(*param_2,(longlong)param_1 + (uVar8 + 0x15) * 4);
        if (cVar6 == '\0') goto LAB_7ff7a3bd8acc;
        cVar7 = '\x01';
      }
      bVar9 = bVar9 + 1;
    } while (bVar9 < *(byte *)(param_1 + 8));
  }
  if (*param_2 != 0) {
    LOCK();
    piVar1 = (int *)(*param_2 + 8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 == 1) {
      puVar4 = (undefined8 *)*param_2;
      if (puVar4 != (undefined8 *)0x0) {
        (**(code **)*puVar4)(puVar4,1);
      }
      *param_2 = 0;
    }
  }
  return cVar7;
}

