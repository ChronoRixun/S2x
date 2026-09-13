// image offset 0x372A70 address 7ff7a3502a70

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_7ff7a3502a70(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined8 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  longlong lVar6;
  void *_Dst;
  ulonglong uVar7;
  longlong lVar8;
  undefined8 uVar9;
  int iVar10;
  uint uVar11;
  longlong lVar12;
  undefined1 auStack_b8 [32];
  undefined8 local_98;
  undefined8 uStack_90;
  undefined8 local_88;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined8 local_78;
  undefined8 uStack_70;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  ulonglong local_48;
  
  local_48 = DAT_7ff7a4152aa8 ^ (ulonglong)auStack_b8;
  FUN_7ff7a3be0580(&local_98,1);
  if (*(int *)(DAT_7ff7ad79e9c0 + 0x10) != 0) {
    lVar12 = (longlong)param_1 * 0x110;
    uVar5 = FUN_7ff7a35023b0(param_2,param_3);
    if ((uVar5 != 0xffffffff) && ((&DAT_7ff7abba4f60)[(longlong)(int)uVar5 + 8 + lVar12] != '\x01'))
    {
      lVar6 = FUN_7ff7a33981b0(4,param_1,0x24);
      cVar4 = FUN_7ff7a39c9650(lVar6);
      if (cVar4 != '\0') {
        cVar4 = FUN_7ff7a39c9710(lVar6);
        if ((cVar4 != '\0') && ((int)uVar5 < *(int *)(&DAT_7ff7abba501c + lVar12))) {
          lVar8 = (ulonglong)uVar5 * 0x1ca0 + (&DAT_7ff7abba5010)[(longlong)param_1 * 0x22];
          FUN_7ff7a3be0670(&local_98);
          FUN_7ff7a38fc8e0(&uStack_70,lVar8 + 0x18,0x14);
          local_88 = *(undefined8 *)(lVar8 + 0x10);
          uStack_80 = *(undefined4 *)(lVar8 + 0x1c88);
          local_78 = *(undefined8 *)(lVar8 + 0x1c80);
          FUN_7ff7a3be0860(lVar12 + 0x7ff7abba5030);
          iVar3 = *(int *)(&DAT_7ff7abba5058 + lVar12);
          if (*(int *)(&DAT_7ff7abba505c + lVar12) == iVar3) {
            iVar10 = iVar3;
            if (iVar3 == 0) {
              iVar10 = 1;
            }
            _Dst = (void *)0x0;
            uVar11 = iVar10 + iVar3;
            if (uVar11 != 0) {
              _Dst = (void *)FUN_7ff7a3c05210((ulonglong)uVar11 * 0x50);
              if (*(uint *)(&DAT_7ff7abba505c + lVar12) != 0) {
                memcpy(_Dst,*(void **)(&DAT_7ff7abba5050 + lVar12),
                       (ulonglong)*(uint *)(&DAT_7ff7abba505c + lVar12) * 0x50);
              }
            }
            FUN_7ff7a3c05240(*(undefined8 *)(&DAT_7ff7abba5050 + lVar12));
            *(void **)(&DAT_7ff7abba5050 + lVar12) = _Dst;
            *(uint *)(&DAT_7ff7abba5058 + lVar12) = uVar11;
          }
          else {
            _Dst = *(void **)(&DAT_7ff7abba5050 + lVar12);
          }
          uVar7 = (ulonglong)*(uint *)(&DAT_7ff7abba505c + lVar12);
          puVar1 = (undefined8 *)((longlong)_Dst + uVar7 * 0x50);
          *puVar1 = local_98;
          puVar1[1] = uStack_90;
          puVar1 = (undefined8 *)((longlong)_Dst + uVar7 * 0x50 + 0x10);
          *puVar1 = local_88;
          puVar1[1] = CONCAT44(uStack_7c,uStack_80);
          puVar1 = (undefined8 *)((longlong)_Dst + uVar7 * 0x50 + 0x20);
          *puVar1 = local_78;
          puVar1[1] = uStack_70;
          puVar2 = (undefined4 *)((longlong)_Dst + uVar7 * 0x50 + 0x30);
          *puVar2 = local_68;
          puVar2[1] = uStack_64;
          puVar2[2] = uStack_60;
          puVar2[3] = uStack_5c;
          puVar2 = (undefined4 *)((longlong)_Dst + uVar7 * 0x50 + 0x40);
          *puVar2 = local_58;
          puVar2[1] = uStack_54;
          puVar2[2] = uStack_50;
          puVar2[3] = uStack_4c;
          *(int *)(&DAT_7ff7abba505c + lVar12) = *(int *)(&DAT_7ff7abba505c + lVar12) + 1;
          *(longlong *)(&DAT_7ff7abba4fa0 + lVar12) = lVar12 + 0x7ff7abba5030;
          FUN_7ff7a39c9700(lVar6);
          *(undefined1 *)(lVar6 + 1) = 0;
          *(code **)(lVar6 + 0x30) = thunk_FUN_7ff7b5062370;
          *(undefined **)(lVar6 + 0x40) = &DAT_7ff7a35026d0;
          *(undefined **)(lVar6 + 0x38) = &DAT_7ff7a35026e0;
          (&DAT_7ff7abba4f60)[(longlong)(int)uVar5 + 8 + lVar12] = 1;
          FUN_7ff7a39c97e0(lVar6);
          uVar9 = 1;
          goto LAB_7ff7a3502c8d;
        }
      }
    }
  }
  uVar9 = 0;
LAB_7ff7a3502c8d:
  FUN_7ff7a3bcb470(&local_88);
  FUN_7ff7a3c04d10(&local_58);
  return uVar9;
}

