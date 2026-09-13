// image offset 0x2E8830 address 7ff7a3478830

void FUN_7ff7a3478830(longlong param_1)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uStack_5c;
  undefined8 local_38;
  undefined8 uStack_30;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  uVar1 = *(undefined8 *)(param_1 + 0x10);
  uVar2 = FUN_7ff7a3c89b70(uVar1);
  uVar3 = FUN_7ff7a3c89b70(uVar1);
  puVar5 = (undefined4 *)FUN_7ff7a3c89b70(uVar1);
  local_38 = CONCAT44(uVar2,99);
  uStack_30 = CONCAT44(uStack_5c,uVar3);
  local_28 = *puVar5;
  uStack_24 = puVar5[1];
  uStack_20 = puVar5[2];
  uStack_1c = puVar5[3];
  iVar4 = FUN_7ff7a347d3e0(param_1,&local_38);
  if (iVar4 != 0) {
    FUN_7ff7a3c89b70();
  }
  return;
}

