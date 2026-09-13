// image offset 0xA4A5A0 address 7ff7a3bda5a0

undefined8 FUN_7ff7a3bda5a0(longlong param_1,longlong *param_2)

{
  int *piVar1;
  int iVar2;
  undefined8 *puVar3;
  char cVar4;
  undefined8 uVar5;
  longlong local_res18 [2];
  
  local_res18[0] = *param_2;
  if (local_res18[0] != 0) {
    LOCK();
    *(int *)(local_res18[0] + 8) = *(int *)(local_res18[0] + 8) + 1;
    UNLOCK();
  }
  cVar4 = FUN_7ff7a3bda510(param_1,local_res18);
  if (cVar4 != '\0') {
    cVar4 = FUN_7ff7a3c07030(*param_2,param_1 + 0x358);
    if (cVar4 != '\0') {
      cVar4 = FUN_7ff7a3c069e0(*param_2,param_1 + 0x35c);
      if (cVar4 != '\0') {
        uVar5 = 1;
        goto LAB_7ff7a3bda600;
      }
    }
  }
  uVar5 = 0;
LAB_7ff7a3bda600:
  if (*param_2 != 0) {
    LOCK();
    piVar1 = (int *)(*param_2 + 8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 == 1) {
      puVar3 = (undefined8 *)*param_2;
      if (puVar3 != (undefined8 *)0x0) {
        (**(code **)*puVar3)(puVar3,1);
      }
      *param_2 = 0;
    }
  }
  return uVar5;
}

