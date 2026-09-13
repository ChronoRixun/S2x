// image offset 0x30B750 address 7ff7a349b750

undefined8 FUN_7ff7a349b750(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  
  cVar2 = FUN_7ff7a32f4a40();
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)(cVar2 != '\0');
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

