// image offset 0x13E910 address 7ff7a32ce910

bool FUN_7ff7a32ce910(undefined4 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  longlong lVar2;

  lVar2 = FUN_7ff7a3398270(0,param_1,0x9e);
  if (lVar2 != 0) {
    lVar2 = FUN_7ff7a39c9390(lVar2);
    iVar1 = func_0x7ff7a3c48940(lVar2 + 0xd0,param_4,0x19);
    return iVar1 == 0;
  }
  return false;
}
