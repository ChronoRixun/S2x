// image offset 0x11FF90 address 7ff7a32aff90

undefined8 FUN_7ff7a32aff90(longlong param_1)

{
  int iVar1;
  undefined4 uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  uint uVar5;
  ulonglong uVar6;
  longlong local_res8;
  
  uVar3 = *(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4;
  if (((int)uVar3 != 1) || (iVar1 = thunk_FUN_7ff7a3294bb0(param_1,uVar3 & 0xffffffff), iVar1 == 0))
  {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  uVar2 = FUN_7ff7a325cb30(param_1,1);
  uVar3 = 0;
  local_res8 = 0;
  FUN_7ff7a34097e0(uVar2,&local_res8);
  if (local_res8 == 0) {
    FUN_7ff7a324d740("skuData",0,0,param_1);
  }
  else {
    FUN_7ff7a324d740("skuData",1,0,param_1);
    FUN_7ff7a325c870("skuID",uVar2,DAT_7ff7a4d63d08);
    FUN_7ff7a325c620("maxQuantity",*(undefined4 *)(local_res8 + 0xc),DAT_7ff7a4d63d08);
    FUN_7ff7a325c620("remainingQuantity",*(undefined4 *)(local_res8 + 0x248),DAT_7ff7a4d63d08);
    FUN_7ff7a325c3e0("soldOut",*(undefined1 *)(local_res8 + 0x2e0),DAT_7ff7a4d63d08);
    FUN_7ff7a325c870("saleEndTime",*(undefined4 *)(local_res8 + 0x2dc),DAT_7ff7a4d63d08);
    FUN_7ff7a325c810("promotionalText",local_res8 + 0x25c,DAT_7ff7a4d63d08);
    FUN_7ff7a325c810("skuData",local_res8 + 0x29c,DAT_7ff7a4d63d08);
    FUN_7ff7a325c620("numPrices",*(undefined1 *)(local_res8 + 0x2e1),DAT_7ff7a4d63d08);
    FUN_7ff7a324d740("prices",*(undefined1 *)(local_res8 + 0x2e1),0,param_1);
    uVar4 = uVar3;
    uVar6 = uVar3;
    if (*(char *)(local_res8 + 0x2e1) != '\0') {
      do {
        uVar5 = (int)uVar6 + 1;
        FUN_7ff7a324d6e0((ulonglong)uVar5,0,2,DAT_7ff7a4d63d08);
        FUN_7ff7a325c620("currency",*(undefined4 *)(uVar4 + 0x24c + local_res8),DAT_7ff7a4d63d08);
        FUN_7ff7a325c620("value",*(undefined4 *)(uVar4 + 0x250 + local_res8),DAT_7ff7a4d63d08);
        FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
        uVar4 = uVar4 + 8;
        uVar6 = (ulonglong)uVar5;
      } while ((int)uVar5 < (int)(uint)*(byte *)(local_res8 + 0x2e1));
    }
    FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
    FUN_7ff7a325c870("productID",*(undefined4 *)(local_res8 + 0x240),DAT_7ff7a4d63d08);
    FUN_7ff7a325c620("numItems",*(undefined1 *)(local_res8 + 0x244),DAT_7ff7a4d63d08);
    FUN_7ff7a324d740("items",*(undefined1 *)(local_res8 + 0x244),0,param_1);
    uVar4 = uVar3;
    if (*(char *)(local_res8 + 0x244) != '\0') {
      do {
        uVar5 = (int)uVar4 + 1;
        FUN_7ff7a324d6e0((ulonglong)uVar5,0,2,DAT_7ff7a4d63d08);
        FUN_7ff7a325c510(&DAT_7ff7a3cd0848,*(undefined4 *)(uVar3 + 0x30 + local_res8),
                         DAT_7ff7a4d63d08);
        FUN_7ff7a325c620("quantity",*(undefined4 *)(uVar3 + 0x34 + local_res8),DAT_7ff7a4d63d08);
        FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
        uVar3 = uVar3 + 0x38;
        uVar4 = (ulonglong)uVar5;
      } while ((int)uVar5 < (int)(uint)*(byte *)(local_res8 + 0x244));
    }
    FUN_7ff7a324e8a0(DAT_7ff7a4d63d08);
  }
  return 1;
}

