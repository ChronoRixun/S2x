// image offset 0xCE780 address 7ff7a325e780

undefined8 FUN_7ff7a325e780(int param_1)

{
  undefined8 uVar1;
  undefined8 local_res10 [3];

  if (param_1 != 0) {
    FUN_7ff7a38f34d0("mp/statstable.csv",local_res10);
    uVar1 = FUN_7ff7a37e2610(param_1);
    uVar1 = FUN_7ff7a38f3560(local_res10[0],0x12,uVar1);
    return uVar1;
  }
  return 0;
}
