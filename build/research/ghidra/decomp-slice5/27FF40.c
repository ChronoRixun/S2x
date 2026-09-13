// image offset 0x27FF40 address 7ff7a340ff40

ulonglong FUN_7ff7a340ff40(_JBTYPE *param_1,undefined8 *param_2)

{
  int *piVar1;
  int iVar2;
  ulonglong uVar3;
  undefined8 *puVar4;
  int iVar5;
  undefined1 auStack_28 [32];
  
  uVar3 = __intrinsic_setjmp(param_1,auStack_28);
  if ((int)uVar3 == 0) {
    puVar4 = (undefined8 *)0x0;
    uVar3 = param_1[0x11].Part[1];
    if (uVar3 == 0) {
      piVar1 = (int *)((longlong)param_1[0x12].Part + 4);
      *piVar1 = *piVar1 + 1;
    }
    else {
      iVar2 = *(int *)((longlong)param_1[0x12].Part + 4);
      iVar5 = iVar2 + 1;
      if ((int)param_1[0x12].Part[0] < iVar5) {
                    /* WARNING: Subroutine does not return */
        longjmp(param_1,-2);
      }
      *(int *)((longlong)param_1[0x12].Part + 4) = iVar5;
      puVar4 = (undefined8 *)(uVar3 + (longlong)iVar2 * 0xc);
      *puVar4 = 0xffffffffffffffff;
      *(undefined4 *)(puVar4 + 1) = 0xffffffff;
    }
    FUN_7ff7a3410510(param_1,puVar4);
    if (param_2 != (undefined8 *)0x0) {
      *param_2 = puVar4;
    }
    uVar3 = (ulonglong)*(uint *)((longlong)param_1[0x12].Part + 4);
  }
  return uVar3;
}

