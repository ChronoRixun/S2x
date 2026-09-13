// image offset 0x3722F0 address 7ff7a35022f0

undefined8
FUN_7ff7a35022f0(int param_1,undefined4 param_2,undefined8 param_3,void *param_4,int param_5)

{
  undefined1 uVar1;
  char cVar2;
  uint uVar3;
  longlong lVar4;
  longlong lVar5;
  
  if (*(int *)(DAT_7ff7ad79e9c0 + 0x10) != 0) {
    lVar4 = (longlong)param_1;
    if ((&DAT_7ff7abba4f84)[lVar4 * 0x44] != 0) {
      uVar3 = FUN_7ff7a35023b0(param_2);
      if (uVar3 != 0xffffffff) {
        lVar5 = (ulonglong)uVar3 * 0x1ca0 + (&DAT_7ff7abba5010)[lVar4 * 0x22];
        uVar1 = (&DAT_7ff7abba4f68)[(longlong)(int)uVar3 + lVar4 * 0x110];
        if (*(longlong *)(lVar5 + 0x10) != 0) {
          memset(param_4,0,(longlong)param_5);
          cVar2 = FUN_7ff7a35027c0(lVar5,uVar1,param_4,param_5);
          if (cVar2 != '\0') {
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

