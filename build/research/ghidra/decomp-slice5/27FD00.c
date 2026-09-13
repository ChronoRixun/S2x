// image offset 0x27FD00 address 7ff7a340fd00

undefined4 FUN_7ff7a340fd00(uint *param_1)

{
  return CONCAT31((int3)((*param_1 & 0xe0000000) >> 8),(*param_1 & 0xe0000000) == 0x40000000);
}

