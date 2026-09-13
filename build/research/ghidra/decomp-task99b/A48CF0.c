// image offset 0xA48CF0 address 7ff7a3bd8cf0

undefined8 FUN_7ff7a3bd8cf0(longlong *param_1,undefined8 param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  longlong *plVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  
  cVar2 = FUN_7ff7a3c07870(param_2,(int)param_1[2]);
  if (cVar2 == '\0') {
LAB_7ff7a3bd8d90:
    bVar1 = false;
  }
  else {
    cVar2 = FUN_7ff7a3c07250(param_2,&DAT_7ff7a3cbd562,0);
    if (cVar2 == '\0') goto LAB_7ff7a3bd8d90;
    cVar2 = FUN_7ff7a3c07250(param_2,&DAT_7ff7a3cbd562,0);
    if (cVar2 == '\0') goto LAB_7ff7a3bd8d90;
    cVar2 = FUN_7ff7a3c07250(param_2,&DAT_7ff7a3cbd562,0);
    if (cVar2 == '\0') goto LAB_7ff7a3bd8d90;
    cVar2 = FUN_7ff7a3c07810(param_2,*(undefined2 *)((longlong)param_1 + 0x14));
    if (cVar2 == '\0') goto LAB_7ff7a3bd8d90;
    cVar2 = FUN_7ff7a3c07870(param_2,(int)param_1[3]);
    if (cVar2 == '\0') goto LAB_7ff7a3bd8d90;
    cVar2 = (**(code **)(*param_1 + 0x18))(param_1,param_2);
    if (cVar2 == '\0') goto LAB_7ff7a3bd8d90;
    bVar1 = true;
  }
  uVar3 = 4;
  if (*(byte *)((longlong)param_1 + 0x1d) < 4) {
    uVar5 = (ulonglong)*(byte *)((longlong)param_1 + 0x1d);
  }
  else {
    uVar5 = 4;
  }
  if (bVar1) {
    cVar2 = FUN_7ff7a3c07870(param_2,uVar5);
    if (cVar2 == '\0') goto LAB_7ff7a3bd8dc0;
    bVar1 = true;
  }
  else {
LAB_7ff7a3bd8dc0:
    bVar1 = false;
  }
  if ((int)uVar5 != 0) {
    plVar6 = param_1 + 4;
    uVar4 = uVar5;
    do {
      FUN_7ff7a3c07870(param_2,(int)*plVar6);
      plVar6 = (longlong *)((longlong)plVar6 + 4);
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
    plVar6 = param_1 + 6;
    do {
      FUN_7ff7a3c07870(param_2,(int)*plVar6);
      plVar6 = (longlong *)((longlong)plVar6 + 4);
      uVar5 = uVar5 - 1;
    } while (uVar5 != 0);
  }
  if (*(byte *)(param_1 + 8) < 4) {
    uVar3 = (uint)*(byte *)(param_1 + 8);
  }
  if (bVar1) {
    cVar2 = FUN_7ff7a3c07870(param_2,uVar3);
    if (cVar2 != '\0') {
      uVar8 = 1;
      goto LAB_7ff7a3bd8e3d;
    }
  }
  uVar8 = 0;
LAB_7ff7a3bd8e3d:
  if (uVar3 != 0) {
    puVar7 = (undefined4 *)((longlong)param_1 + 0x44);
    uVar4 = (ulonglong)uVar3;
    uVar5 = (ulonglong)uVar3;
    do {
      FUN_7ff7a3c07870(param_2,*puVar7);
      puVar7 = puVar7 + 1;
      uVar5 = uVar5 - 1;
    } while (uVar5 != 0);
    puVar7 = (undefined4 *)((longlong)param_1 + 0x54);
    do {
      FUN_7ff7a3c07870(param_2,*puVar7);
      puVar7 = puVar7 + 1;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
  return uVar8;
}

