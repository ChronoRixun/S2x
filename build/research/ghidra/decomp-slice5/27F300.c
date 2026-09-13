// image offset 0x27F300 address 7ff7a340f300

undefined1
FUN_7ff7a340f300(longlong param_1,undefined8 param_2,undefined8 param_3,undefined4 *param_4)

{
  char cVar1;
  longlong lVar2;
  uint uVar3;
  undefined4 uVar4;
  uint *local_res20;
  
  lVar2 = 0;
  uVar4 = 0;
  *param_4 = 0;
  cVar1 = FUN_7ff7a340f430();
  if (cVar1 != '\0') {
    if ((*local_res20 & 0xe0000000) == 0x80000000) {
      uVar3 = *local_res20 & 0x1fffffff;
      if (uVar3 != 0x1fffffff) {
        lVar2 = (ulonglong)uVar3 + *(longlong *)(param_1 + 0x100);
      }
      lVar2 = FUN_7ff7a34118e0(lVar2);
      if (lVar2 + 0x80000000U < 0x100000000) {
        uVar4 = (undefined4)lVar2;
      }
    }
    *param_4 = uVar4;
    return 1;
  }
  return 0;
}

