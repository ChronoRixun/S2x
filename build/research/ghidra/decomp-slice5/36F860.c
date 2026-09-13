// image offset 0x36F860 address 7ff7a34ff860

undefined8 FUN_7ff7a34ff860(longlong param_1)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 0x48);
  puVar1[2] = 0;
  *puVar1 = 1;
  *(undefined4 **)(param_1 + 0x48) = puVar1 + 4;
  return 1;
}

