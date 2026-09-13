// image offset 0x275360 address 7ff7a3405360

void FUN_7ff7a3405360(undefined8 param_1,undefined4 param_2,undefined1 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  char cVar3;
  undefined4 local_18 [4];
  
  cVar3 = FUN_7ff7a3630d90(param_1,local_18);
  if (cVar3 != '\0') {
    cVar3 = FUN_7ff7a324d020(local_18[0],"inventory",DAT_7ff7a4d63d08);
    if (cVar3 != '\0') {
      FUN_7ff7a325c620("inventoryEventType",4,DAT_7ff7a4d63d08);
      FUN_7ff7a325c620("inventoryTaskType",param_2,DAT_7ff7a4d63d08);
      FUN_7ff7a325c3e0("success",param_3,DAT_7ff7a4d63d08);
      uVar2 = DAT_7ff7a4d63d08;
      uVar1 = FUN_7ff7a39c9020(param_4);
      FUN_7ff7a325c810(&DAT_7ff7a3cde9b4,uVar1,uVar2);
      FUN_7ff7a324e7e0(DAT_7ff7a4d63d08);
    }
  }
  return;
}

