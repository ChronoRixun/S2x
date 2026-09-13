// image offset 0xA486F0 address 7ff7a3bd86f0

undefined8 FUN_7ff7a3bd86f0(longlong param_1,longlong *param_2)

{
  int *piVar1;
  int iVar2;
  undefined8 *puVar3;
  char cVar4;
  undefined8 uVar5;
  
  cVar4 = FUN_7ff7a3c07030(*param_2,param_1 + 0x20);
  if (cVar4 != '\0') {
    cVar4 = FUN_7ff7a3c07030(*param_2,param_1 + 0x24);
    if (cVar4 != '\0') {
      uVar5 = 1;
      goto LAB_7ff7a3bd872b;
    }
  }
  uVar5 = 0;
LAB_7ff7a3bd872b:
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

