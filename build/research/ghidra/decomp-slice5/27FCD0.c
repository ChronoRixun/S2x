// image offset 0x27FCD0 address 7ff7a340fcd0

undefined4 FUN_7ff7a340fcd0(uint *param_1)

{
  return CONCAT31((int3)((*param_1 & 0xe0000000) >> 8),(*param_1 & 0xe0000000) == 0x80000000);
}

