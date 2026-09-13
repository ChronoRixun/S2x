// image offset 0x3726F0 address 7ff7a35026f0

void FUN_7ff7a35026f0(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  longlong lVar2;
  
  if ((((*(int *)(DAT_7ff7ad79e9c0 + 0x10) != 0) &&
       ((&DAT_7ff7abba4f84)[(longlong)param_1 * 0x44] != 0)) &&
      (uVar1 = FUN_7ff7a35023b0(param_2,param_3), uVar1 != 0xffffffff)) &&
     ((lVar2 = (ulonglong)uVar1 * 0x1ca0 + (&DAT_7ff7abba5010)[(longlong)param_1 * 0x22],
      *(longlong *)(lVar2 + 0x10) != 0 && (*(int *)(lVar2 + 0x1c34) != 0)))) {
    if (*(int *)(lVar2 + 0x1c78) != 0) {
      FUN_7ff7a3443590(param_1,lVar2 + 0x1834,lVar2 + 0x1c38);
      return;
    }
    FUN_7ff7a3443420(param_1,lVar2 + 0x1834);
  }
  return;
}

