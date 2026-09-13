// image offset 0x33AEF0 address 7ff7a34caef0

undefined8 FUN_7ff7a34caef0(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  longlong lVar5;
  
  uVar4 = FUN_7ff7a3600d30(0);
  lVar5 = FUN_7ff7a3600f20(uVar4);
  cVar2 = FUN_7ff7a3601200(uVar4);
  if ((cVar2 == '\0') || (((byte)*(undefined4 *)(lVar5 + 0x186490) & 0xfc) != 0x20)) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = uVar3;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

