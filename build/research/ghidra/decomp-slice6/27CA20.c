// image offset 0x27CA20 address 7ff7a340ca20

longlong FUN_7ff7a340ca20(int param_1,short param_2,int *param_3)

{
  int iVar1;
  undefined8 uVar2;
  longlong lVar3;
  longlong lVar4;
  
  lVar3 = (longlong)param_1 * 0xc8438;
  lVar4 = (longlong)param_2 * 0x68 + lVar3;
  iVar1 = *(int *)(&DAT_7ff7ab108178 + lVar4);
  if (iVar1 == 0) {
    *(int *)(&DAT_7ff7ab1c85a4 + lVar3) = *(int *)(&DAT_7ff7ab1c85a4 + lVar3) + 1;
  }
  else if (iVar1 != *param_3) {
    return (ulonglong)(uint3)((uint)iVar1 >> 8) << 8;
  }
  uVar2 = *(undefined8 *)(param_3 + 2);
  lVar3 = lVar3 + param_2;
  *(undefined8 *)(&DAT_7ff7ab108178 + lVar4) = *(undefined8 *)param_3;
  *(undefined8 *)(&DAT_7ff7ab108180 + lVar4) = uVar2;
  uVar2 = *(undefined8 *)(param_3 + 6);
  *(undefined8 *)(&DAT_7ff7ab108188 + lVar4) = *(undefined8 *)(param_3 + 4);
  *(undefined8 *)(&DAT_7ff7ab108190 + lVar4) = uVar2;
  (&DAT_7ff7ab1c6858)[lVar3] = (&DAT_7ff7ab1c6858)[lVar3] | 2;
  return CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
}

