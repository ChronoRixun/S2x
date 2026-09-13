// image offset 0x27D510 address 7ff7a340d510

void FUN_7ff7a340d510(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 local_res20 [2];
  
  if ((((DAT_7ff7ab0ff108 == 0) || (*(int *)(DAT_7ff7ab0ff108 + 0x10) != 0)) &&
      (iVar2 = FUN_7ff7a340dc10(), iVar2 != 0)) &&
     ((cVar1 = FUN_7ff7a3630d90(param_1,local_res20), cVar1 != '\0' &&
      (cVar1 = FUN_7ff7a324d020(local_res20[0],"inventory",DAT_7ff7a4d63d08), cVar1 != '\0')))) {
    FUN_7ff7a325c620("inventoryEventType",5,DAT_7ff7a4d63d08);
    FUN_7ff7a325c620("currency",param_2,DAT_7ff7a4d63d08);
    FUN_7ff7a325c620("newBalance",param_3,DAT_7ff7a4d63d08);
    FUN_7ff7a325c620("difference",iVar2,DAT_7ff7a4d63d08);
    FUN_7ff7a324e7e0(DAT_7ff7a4d63d08);
  }
  return;
}

