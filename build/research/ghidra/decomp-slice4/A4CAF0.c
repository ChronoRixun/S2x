// image offset 0xA4CAF0 address 7ff7a3bdcaf0

void FUN_7ff7a3bdcaf0(longlong param_1)

{
  undefined8 *puVar1;
  
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined1 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  FUN_7ff7a3bdca90(param_1 + 0x38);
  puVar1 = (undefined8 *)(param_1 + 0x198);
  FUN_7ff7a3bdc910(puVar1,*puVar1,*(undefined4 *)(param_1 + 0x1a4));
  FUN_7ff7a3c05240(*puVar1);
  *puVar1 = 0;
  *(undefined8 *)(param_1 + 0x1a0) = 0;
  puVar1 = (undefined8 *)(param_1 + 0x1a8);
  FUN_7ff7a3bdca10(puVar1,*puVar1,*(undefined4 *)(param_1 + 0x1b4));
  FUN_7ff7a3c05240(*puVar1);
  *puVar1 = 0;
  *(undefined8 *)(param_1 + 0x1b0) = 0;
  puVar1 = (undefined8 *)(param_1 + 0x1b8);
  FUN_7ff7a3bdc990(puVar1,*puVar1,*(undefined4 *)(param_1 + 0x1c4));
  FUN_7ff7a3c05240(*puVar1);
  *puVar1 = 0;
  *(undefined8 *)(param_1 + 0x1c0) = 0;
  return;
}

