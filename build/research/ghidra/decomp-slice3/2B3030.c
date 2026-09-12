// image offset 0x2B3030 address 7ff7a3443030

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_7ff7a3443030(longlong param_1)

{
  undefined1 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  void *_Dst;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  uint uVar11;
  undefined1 auStack_3b8 [32];
  undefined4 local_398;
  longlong local_390;
  undefined1 local_388;
  undefined4 local_380;
  undefined8 local_378;
  undefined2 local_370;
  undefined4 local_368;
  undefined4 local_360;
  undefined4 local_358;
  uint local_348;
  undefined4 local_344;
  longlong local_340;
  longlong local_338;
  void *local_330;
  undefined1 local_328 [8];
  longlong local_320;
  undefined1 local_318 [8];
  longlong local_310;
  undefined1 local_308 [4];
  undefined4 local_304;
  undefined1 local_300 [24];
  undefined1 local_2e8 [16];
  undefined1 local_2d8 [16];
  undefined1 local_2c8 [8];
  undefined1 local_2c0 [16];
  undefined1 local_2b0 [24];
  undefined1 local_298 [56];
  undefined1 local_260 [24];
  undefined1 local_248 [56];
  undefined1 local_210 [24];
  undefined1 local_1f8 [16];
  undefined1 local_1e8 [16];
  undefined1 local_1d8 [56];
  undefined1 local_1a0 [120];
  undefined1 local_128 [16];
  undefined1 local_118 [16];
  undefined1 local_108 [16];
  undefined1 local_f8 [56];
  undefined1 local_c0 [120];
  undefined1 local_48 [16];
  ulonglong local_38;
  
  local_38 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_3b8;
  local_338 = param_1;
  FUN_7ff7a3bd9140(local_1f8,1);
  FUN_7ff7a3bd97f0(local_328,1);
  FUN_7ff7a3bbc650(local_298,1);
  _Dst = (void *)FUN_7ff7a39c9390(param_1);
  local_330 = _Dst;
  lVar7 = FUN_7ff7a38b5500(local_248,*(undefined4 *)(param_1 + 4));
  FUN_7ff7a3bbc490(local_2e8,lVar7 + 0x30,1);
  FUN_7ff7a3bbc740(local_298);
  FUN_7ff7a3bbc6f0(local_2b0);
  FUN_7ff7a3c04d10(local_2b0);
  FUN_7ff7a3bbc6f0(local_210);
  FUN_7ff7a3c04d10(local_210);
  uVar10 = 0;
  local_348 = 0;
  if (*(int *)((longlong)_Dst + 0x83c) != 0) {
    do {
      local_340 = uVar10 * 0x3b0 + *(longlong *)((longlong)_Dst + 0x830);
      uVar3 = *(undefined4 *)(local_340 + 0x388);
      uVar2 = *(undefined2 *)(local_340 + 0x374);
      uVar9 = *(undefined8 *)(local_340 + 0x380);
      uVar4 = *(undefined4 *)(local_340 + 0x378);
      uVar1 = *(undefined1 *)(local_340 + 0x368);
      uVar5 = *(undefined4 *)(local_340 + 0x370);
      uVar6 = *(undefined4 *)(local_340 + 0x36c);
      local_344 = *(undefined4 *)(local_340 + 0x10);
      uVar8 = FUN_7ff7a3bbc3a0(local_248,local_298,1);
      local_390 = local_340 + 0x326;
      local_358 = 1;
      local_360 = 0;
      local_398 = uVar5;
      local_388 = uVar1;
      local_380 = uVar4;
      local_378 = uVar9;
      local_370 = uVar2;
      local_368 = uVar3;
      uVar9 = FUN_7ff7a3bd8f90(local_118,uVar8,local_344,uVar6);
      FUN_7ff7a3442920(local_1f8,uVar9);
      FUN_7ff7a3bbc6f0(local_c0);
      FUN_7ff7a3c04d10(local_c0);
      FUN_7ff7a3bcb570(local_f8);
      FUN_7ff7a3bbc060(local_108);
      FUN_7ff7a3c04d10(local_48);
      param_1 = local_338;
      FUN_7ff7a3409840(*(undefined4 *)(local_338 + 4),local_1f8,1);
      local_348 = local_348 + 1;
      uVar10 = (ulonglong)local_348;
      _Dst = local_330;
    } while (local_348 < *(uint *)((longlong)local_330 + 0x83c));
  }
  uVar10 = 0;
  if (*(int *)((longlong)_Dst + 0x84c) != 0) {
    do {
      lVar7 = uVar10 * 0x30 + *(longlong *)((longlong)_Dst + 0x840);
      lVar7 = FUN_7ff7a3bd9740(local_2e8,*(undefined1 *)(lVar7 + 0x10),
                               *(int *)(lVar7 + 0x18) + *(int *)(lVar7 + 0x14),1);
      FUN_7ff7a3c04d20(local_318 + (longlong)*(int *)(local_320 + 4) + -8,
                       (longlong)*(int *)(*(longlong *)(lVar7 + 8) + 4) + lVar7 + 8);
      FUN_7ff7a3c04d20(local_308 + (longlong)*(int *)(local_310 + 4) + -8,
                       (longlong)*(int *)(*(longlong *)(lVar7 + 0x18) + 4) + 0x18 + lVar7);
      local_308[0] = *(undefined1 *)(lVar7 + 0x20);
      local_304 = *(undefined4 *)(lVar7 + 0x24);
      FUN_7ff7a3bcb570(local_2c8);
      FUN_7ff7a3bbc060(local_2d8);
      FUN_7ff7a3c04d10(local_2c0);
      FUN_7ff7a3409830(*(undefined4 *)(param_1 + 4),local_328,1);
      uVar11 = (int)uVar10 + 1;
      uVar10 = (ulonglong)uVar11;
    } while (uVar11 < *(uint *)((longlong)_Dst + 0x84c));
    if (*(uint *)((longlong)_Dst + 0x84c) != 0) {
      FUN_7ff7a3265f30(*(undefined4 *)(param_1 + 4));
    }
  }
  memset(_Dst,0,0x81b);
  FUN_7ff7a3be01b0((longlong)_Dst + 0x820);
  FUN_7ff7a3bbc6f0(local_260);
  FUN_7ff7a3c04d10(local_260);
  FUN_7ff7a3bcb570(local_308);
  FUN_7ff7a3bbc060(local_318);
  FUN_7ff7a3c04d10(local_300);
  FUN_7ff7a3bbc6f0(local_1a0);
  FUN_7ff7a3c04d10(local_1a0);
  FUN_7ff7a3bcb570(local_1d8);
  FUN_7ff7a3bbc060(local_1e8);
  FUN_7ff7a3c04d10(local_128);
  return;
}

