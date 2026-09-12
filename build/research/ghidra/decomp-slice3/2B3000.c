// image offset 0x2B3000 address 7ff7a3443000

void FUN_7ff7a3442fa0(void)

{
  int *piVar1;
  int iVar2;
  void *_Dst;
  longlong local_res10 [3];
  
  _Dst = (void *)FUN_7ff7a39c9390();
  FUN_7ff7a39c9400(local_res10);
  if (local_res10[0] != 0) {
    FUN_7ff7a3bcdb50();
  }
  memset(_Dst,0,0x81b);
  FUN_7ff7a3be01b0((longlong)_Dst + 0x820);
  if (local_res10[0] != 0) {
    LOCK();
    piVar1 = (int *)(local_res10[0] + 8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if ((iVar2 == 1) && (local_res10[0] != 0)) {
      FUN_7ff7a3c89b70(local_res10[0],1);
    }
  }
  return;
}

