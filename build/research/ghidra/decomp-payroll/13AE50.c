// image offset 0x13AE50 address 7ff7a32cae50

ulonglong FUN_7ff7a32cae50(int param_1)

{
  ulonglong in_RAX;
  uint uVar1;
  
  uVar1 = param_1 - 1;
  if (uVar1 < 0xd) {
    in_RAX = (ulonglong)(int)uVar1;
    switch(uVar1) {
    default:
      return CONCAT71((int7)(int3)(uVar1 >> 8),1);
    case 4:
    case 5:
    case 0xc:
      break;
    }
  }
  return in_RAX & 0xffffffffffffff00;
}

