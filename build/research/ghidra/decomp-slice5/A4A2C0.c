// image offset 0xA4A2C0 address 7ff7a3bda2c0

char FUN_7ff7a3bda2c0(longlong param_1,longlong *param_2)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  char cVar4;
  char cVar5;
  ulonglong uVar6;
  undefined8 *puVar7;
  byte bVar8;
  undefined4 local_res8 [2];
  longlong *local_res10;
  undefined4 local_res18 [2];
  undefined4 local_res20 [2];
  longlong local_38 [3];
  
  local_res10 = param_2;
  cVar4 = FUN_7ff7a3c07030(*param_2,param_1 + 0x20);
  if (((cVar4 == '\0') || (cVar4 = FUN_7ff7a3c07030(*param_2,param_1 + 0x24), cVar4 == '\0')) ||
     (cVar4 = FUN_7ff7a3c06f70(*param_2,param_1 + 0x28), cVar4 == '\0')) {
    local_res8[0]._0_1_ = 0x40;
    local_res8[0] = 0x40;
LAB_7ff7a3bda447:
    *(undefined1 *)(param_1 + 0x69) = (undefined1)local_res8[0];
LAB_7ff7a3bda44a:
    local_res18[0] = 0x87;
LAB_7ff7a3bda453:
    *(undefined4 *)(param_1 + 0x108) = local_res18[0];
LAB_7ff7a3bda459:
    local_res20[0] = 0;
  }
  else {
    local_res8[0] = 0x40;
    cVar4 = FUN_7ff7a3c06950(*param_2,param_1 + 0x29,local_res8);
    if (cVar4 == '\0') goto LAB_7ff7a3bda447;
    *(undefined1 *)(param_1 + 0x69) = (undefined1)local_res8[0];
    cVar4 = FUN_7ff7a3c06f70(*param_2,param_1 + 0x6a);
    if (((cVar4 == '\0') || (cVar4 = FUN_7ff7a3c07030(*param_2,param_1 + 0x6c), cVar4 == '\0')) ||
       ((cVar4 = FUN_7ff7a3c07030(*param_2,param_1 + 0x70), cVar4 == '\0' ||
        ((cVar4 = FUN_7ff7a3c07030(*param_2,param_1 + 0x74), cVar4 == '\0' ||
         (cVar4 = FUN_7ff7a3c06f70(*param_2,param_1 + 0x78), cVar4 == '\0'))))))
    goto LAB_7ff7a3bda44a;
    local_res18[0] = 0x87;
    cVar4 = FUN_7ff7a3c06950(*param_2,param_1 + 0x80,local_res18);
    if (cVar4 == '\0') goto LAB_7ff7a3bda453;
    *(undefined4 *)(param_1 + 0x108) = local_res18[0];
    cVar4 = FUN_7ff7a3c07030(*param_2,param_1 + 0x10c);
    if ((((cVar4 == '\0') || (cVar4 = FUN_7ff7a3c06fd0(*param_2,param_1 + 0x110), cVar4 == '\0')) ||
        (cVar4 = FUN_7ff7a3c07030(*param_2,param_1 + 0x114), cVar4 == '\0')) ||
       (cVar4 = FUN_7ff7a3c06f70(*param_2,param_1 + 0x6b), cVar4 == '\0')) goto LAB_7ff7a3bda459;
    local_res20[0] = 0;
    cVar5 = FUN_7ff7a3c07030(*param_2,local_res20);
    cVar4 = (char)local_res20[0];
    if (cVar5 != '\0') {
      cVar5 = '\x01';
      goto LAB_7ff7a3bda462;
    }
  }
  cVar4 = (char)local_res20[0];
  cVar5 = '\0';
LAB_7ff7a3bda462:
  *(char *)(param_1 + 0x118) = cVar4;
  bVar8 = 0;
  if (cVar4 != '\0') {
    do {
      if (cVar5 == '\0') {
LAB_7ff7a3bda4ba:
        cVar5 = '\0';
      }
      else {
        uVar6 = (ulonglong)bVar8;
        if (8 < bVar8) {
          uVar6 = 9;
        }
        puVar7 = (undefined8 *)(param_1 + 0x120 + uVar6 * 0x38);
        pcVar3 = *(code **)*puVar7;
        local_38[0] = *param_2;
        if (local_38[0] != 0) {
          LOCK();
          *(int *)(local_38[0] + 8) = *(int *)(local_38[0] + 8) + 1;
          UNLOCK();
        }
        cVar4 = (*pcVar3)(puVar7,local_38);
        if (cVar4 == '\0') goto LAB_7ff7a3bda4ba;
        cVar5 = '\x01';
      }
      bVar8 = bVar8 + 1;
    } while (bVar8 < *(byte *)(param_1 + 0x118));
  }
  if (*param_2 != 0) {
    LOCK();
    piVar1 = (int *)(*param_2 + 8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 == 1) {
      puVar7 = (undefined8 *)*param_2;
      if (puVar7 != (undefined8 *)0x0) {
        (**(code **)*puVar7)(puVar7,1);
      }
      *param_2 = 0;
    }
  }
  return cVar5;
}

