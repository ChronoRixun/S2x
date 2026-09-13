// image offset 0x27A260 address 7ff7a340a260

bool FUN_7ff7a340a260(int param_1,short param_2)

{
  longlong lVar1;
  uint uVar2;
  longlong lVar3;
  
  lVar3 = (longlong)param_1 * 0xc8438 + (longlong)param_2 * 0x68;
  lVar1 = *(longlong *)(lVar3 + 0x7ff7ab108188);
  if (*(int *)(lVar3 + 0x7ff7ab108180) != -1) {
    if (lVar1 == 0x7fffffffffffffff) {
      uVar2 = _time64(0);
    }
    else {
      uVar2 = _time64(0);
      if (*(longlong *)(lVar3 + 0x7ff7ab108188) < 1) {
        return true;
      }
    }
    return *(uint *)(lVar3 + 0x7ff7ab108180) <= uVar2;
  }
  if (lVar1 == 0x7fffffffffffffff) {
    return false;
  }
  return lVar1 < 1;
}

