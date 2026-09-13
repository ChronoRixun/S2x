// image offset 0xA48B40 address 7ff7a3bd8b40

bool FUN_7ff7a3bd8b40(longlong param_1,longlong *param_2)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  char cVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  byte bVar7;
  bool bVar8;
  undefined4 local_res8 [2];
  longlong *local_res10;
  longlong local_res18;
  
  local_res8[0] = 0;
  local_res10 = param_2;
  cVar4 = FUN_7ff7a3c07030(*param_2,local_res8);
  bVar8 = cVar4 != '\0';
  *(char *)(param_1 + 0x1c) = (char)local_res8[0];
  bVar7 = 0;
  if ((char)local_res8[0] != '\0') {
    do {
      if (bVar8 == false) {
LAB_7ff7a3bd8bc5:
        bVar8 = false;
      }
      else {
        uVar5 = (ulonglong)bVar7;
        if (8 < bVar7) {
          uVar5 = 9;
        }
        puVar6 = (undefined8 *)(param_1 + 0x68 + uVar5 * 0x38);
        pcVar3 = *(code **)*puVar6;
        local_res18 = *param_2;
        if (local_res18 != 0) {
          LOCK();
          *(int *)(local_res18 + 8) = *(int *)(local_res18 + 8) + 1;
          UNLOCK();
        }
        cVar4 = (*pcVar3)(puVar6,&local_res18);
        if (cVar4 == '\0') goto LAB_7ff7a3bd8bc5;
        bVar8 = true;
      }
      bVar7 = bVar7 + 1;
    } while (bVar7 < *(byte *)(param_1 + 0x1c));
  }
  if (*param_2 != 0) {
    LOCK();
    piVar1 = (int *)(*param_2 + 8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 == 1) {
      puVar6 = (undefined8 *)*param_2;
      if (puVar6 != (undefined8 *)0x0) {
        (**(code **)*puVar6)(puVar6,1);
      }
      *param_2 = 0;
    }
  }
  return bVar8;
}

