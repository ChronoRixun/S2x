// image offset 0x2B03B0 address 7ff7a34403b0

void FUN_7ff7a34403b0(longlong param_1)

{
  char cVar1;
  longlong lVar2;
  undefined8 uVar3;
  
  lVar2 = FUN_7ff7a39c9390();
  uVar3 = 0;
  if (*(longlong *)(param_1 + 0x18) != 0) {
    uVar3 = FUN_7ff7a3bcdc30();
  }
  FUN_7ff7a343e7e0(*(undefined8 *)(lVar2 + 200),lVar2 + 0xd0,uVar3,0,0);
  cVar1 = FUN_7ff7a324d020(0,"OpenSupplyPackageSuccess",DAT_7ff7a4d63d08);
  if (cVar1 != '\0') {
    FUN_7ff7a325c810("transactionID",lVar2 + 0xd0,DAT_7ff7a4d63d08);
    FUN_7ff7a324e7e0(DAT_7ff7a4d63d08);
  }
  return;
}

