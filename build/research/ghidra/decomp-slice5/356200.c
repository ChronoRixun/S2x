// image offset 0x356200 address 7ff7a34e6200

undefined8 FUN_7ff7a34e6200(longlong param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  longlong lVar6;
  undefined8 *puVar7;
  longlong lVar8;
  
  lVar6 = FUN_7ff7a325ca00(param_1,1);
  FUN_7ff7a325b280(lVar6,param_1);
  puVar7 = (undefined8 *)thunk_FUN_7ff7a346d100(param_1,0x10);
  *puVar7 = 0;
  puVar7[1] = 0;
  if (*(ulonglong *)(param_1 + 0x58) < *(longlong *)(param_1 + 0x48) + 0x20U) {
    FUN_7ff7a3466cd0(param_1 + 0x18,param_1,2,0);
  }
  FUN_7ff7a3294620(param_1,"_vendorOverhead",0xf);
  lVar8 = *(longlong *)(param_1 + 0x48);
  uVar1 = *(undefined4 *)(lVar8 + -0x10);
  uVar2 = *(undefined4 *)(lVar8 + -0xc);
  uVar3 = *(undefined4 *)(lVar8 + -8);
  uVar4 = *(undefined4 *)(lVar8 + -4);
  *(undefined4 *)(lVar8 + -0x10) = *(undefined4 *)(lVar8 + -0x20);
  *(undefined4 *)(lVar8 + -0xc) = *(undefined4 *)(lVar8 + -0x1c);
  *(undefined4 *)(lVar8 + -8) = *(undefined4 *)(lVar8 + -0x18);
  *(undefined4 *)(lVar8 + -4) = *(undefined4 *)(lVar8 + -0x14);
  *(undefined4 *)(lVar8 + -0x20) = uVar1;
  *(undefined4 *)(lVar8 + -0x1c) = uVar2;
  *(undefined4 *)(lVar8 + -0x18) = uVar3;
  *(undefined4 *)(lVar8 + -0x14) = uVar4;
  *(longlong *)(param_1 + 0x48) = lVar8;
  FUN_7ff7a34696b0(param_1,lVar8 + -0x30);
  lVar8 = *(longlong *)(param_1 + 0x48) + -0x20;
  iVar5 = (int)(lVar8 - *(longlong *)(param_1 + 0x50) >> 4);
  if (0 < iVar5) {
    iVar5 = 1;
  }
  *(longlong *)(param_1 + 0x48) = lVar8 + (longlong)iVar5 * -0x10;
  *(code **)(lVar6 + 0xe0) = FUN_7ff7a34e5000;
  return 0;
}

