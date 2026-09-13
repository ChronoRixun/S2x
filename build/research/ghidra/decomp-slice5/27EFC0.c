// image offset 0x27EFC0 address 7ff7a340efc0

int FUN_7ff7a340efc0(uint *param_1)

{
  uint uVar1;
  uint3 uVar2;
  
  uVar1 = (*param_1 >> 0x1d) - 5;
  uVar2 = (uint3)(uVar1 >> 8);
  if (1 < uVar1) {
    return (uint)uVar2 << 8;
  }
  return CONCAT31(uVar2,*param_1 >> 0x1d == 5);
}

