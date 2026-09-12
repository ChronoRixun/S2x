// image offset 0x13AF60 address 7ff7a32caf60

void FUN_7ff7a32caf60(undefined8 param_1)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  char cVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  longlong lVar7;
  undefined4 local_res10 [2];

  uVar5 = FUN_7ff7a39c9370();
  lVar7 = FUN_7ff7a39c9390(param_1);
  puVar1 = *(undefined4 **)(lVar7 + 0xf0);
  cVar4 = FUN_7ff7a3630d90(uVar5,local_res10);
  if (cVar4 != '\0') {
    cVar4 = FUN_7ff7a324d020(local_res10[0],"achievementEngine",DAT_7ff7a4d63d08);
    if (cVar4 != '\0') {
      uVar5 = FUN_7ff7a39c93d0(param_1);
      FUN_7ff7a325c620("eventType",2,DAT_7ff7a4d63d08);
      FUN_7ff7a325c620(&DAT_7ff7a3cd07e4,*puVar1,DAT_7ff7a4d63d08);
      uVar2 = DAT_7ff7a4d63d08;
      uVar6 = FUN_7ff7a32c9dc0(*puVar1);
      FUN_7ff7a325c620(&DAT_7ff7a3cd03f8,uVar6,uVar2);
      uVar3 = DAT_7ff7a4d63d08;
      uVar2 = FUN_7ff7a39c9020(lVar7 + 0xd0);
      FUN_7ff7a325c810("transactionID",uVar2,uVar3);
      FUN_7ff7a325c3e0("dispatchChildren",1,DAT_7ff7a4d63d08);
      FUN_7ff7a325c3e0("success",0,DAT_7ff7a4d63d08);
      FUN_7ff7a325c620("errorCode",uVar5,DAT_7ff7a4d63d08);
      FUN_7ff7a324e7e0(DAT_7ff7a4d63d08);
    }
  }
  FUN_7ff7a3396000(lVar7);
  return;
}
