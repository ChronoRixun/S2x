// image offset 0x120610 address 7ff7a32b0610

undefined8 FUN_7ff7a32b0610(longlong param_1)

{
  undefined4 *puVar1;
  char cVar2;
  
  if ((int)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x50) >> 4) != 0) {
    FUN_7ff7a34731a0(param_1,&DAT_7ff7a3cbd562);
  }
  cVar2 = FUN_7ff7a3408400();
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = (uint)(cVar2 != '\0');
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

