// image offset 0x27A0A0 address 7ff7a340a0a0

void FUN_7ff7a340a080(longlong param_1,undefined8 param_2,undefined8 param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined1 extraout_AL;
  undefined1 extraout_AL_00;
  undefined1 extraout_AL_01;
  undefined1 extraout_AL_02;
  undefined1 extraout_AL_03;
  undefined1 uVar4;
  undefined1 extraout_AL_04;
  char cVar5;
  undefined1 extraout_AL_05;
  undefined1 extraout_AL_06;
  undefined1 extraout_AL_07;
  undefined1 extraout_AL_08;
  undefined1 extraout_AL_09;
  undefined1 extraout_AL_10;
  undefined1 extraout_AH;
  undefined1 extraout_AH_00;
  undefined1 extraout_AH_01;
  undefined1 extraout_AH_02;
  undefined1 extraout_AH_03;
  undefined1 extraout_AH_04;
  undefined1 extraout_AH_05;
  undefined1 extraout_AH_06;
  undefined1 extraout_AH_07;
  undefined1 extraout_AH_08;
  undefined1 extraout_AH_09;
  undefined1 extraout_AH_10;
  undefined1 extraout_AH_11;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  undefined2 extraout_var_04;
  undefined2 extraout_var_05;
  undefined2 extraout_var_06;
  undefined2 extraout_var_07;
  undefined2 extraout_var_08;
  undefined2 extraout_var_09;
  undefined2 extraout_var_10;
  undefined4 extraout_var_11;
  undefined4 extraout_var_12;
  undefined4 extraout_var_13;
  undefined4 extraout_var_14;
  
  FUN_7ff7a340efe0(param_2,param_3);
  uVar2 = CONCAT44(extraout_var_11,CONCAT22(extraout_var,CONCAT11(extraout_AH,extraout_AL)));
  uVar1 = CONCAT44(extraout_var_11,CONCAT22(extraout_var,CONCAT11(extraout_AH,extraout_AL))) &
          CONCAT44(extraout_var_11,CONCAT22(extraout_var,CONCAT11(extraout_AH,extraout_AL)));
  while (uVar1 != 0) {
    FUN_7ff7a340f220(param_2,uVar2);
    uVar3 = CONCAT44(extraout_var_12,
                     CONCAT22(extraout_var_00,CONCAT11(extraout_AH_00,extraout_AL_00)));
    FUN_7ff7a3b94f40(CONCAT44(extraout_var_12,
                              CONCAT22(extraout_var_00,CONCAT11(extraout_AH_00,extraout_AL_00))),
                     "item_id");
    if ((CONCAT22(extraout_var_01,CONCAT11(extraout_AH_01,extraout_AL_01)) &
        CONCAT22(extraout_var_01,CONCAT11(extraout_AH_01,extraout_AL_01))) == 0) {
      FUN_7ff7a340f750(param_2,uVar2);
      *(uint *)(param_1 + 0x68) = CONCAT22(extraout_var_02,CONCAT11(extraout_AH_02,extraout_AL_02));
    }
    else {
      FUN_7ff7a3b94f40(uVar3,"collision_field");
      if ((CONCAT22(extraout_var_03,CONCAT11(extraout_AH_03,extraout_AL_03)) &
          CONCAT22(extraout_var_03,CONCAT11(extraout_AH_03,extraout_AL_03))) == 0) {
        uVar4 = FUN_7ff7a340f750(param_2,uVar2);
        *(ushort *)(param_1 + 0xc0) = CONCAT11(extraout_AH_04,uVar4);
      }
      else {
        FUN_7ff7a3b94f40(uVar3,"expiry_duration");
        if ((CONCAT22(extraout_var_04,CONCAT11(extraout_AH_05,extraout_AL_04)) &
            CONCAT22(extraout_var_04,CONCAT11(extraout_AH_05,extraout_AL_04))) == 0) {
          cVar5 = FUN_7ff7a340fce0(uVar2);
          if (cVar5 == '\0') {
            FUN_7ff7a340f1e0(param_2,uVar2);
            *(ulonglong *)(param_1 + 0xb8) =
                 CONCAT44(extraout_var_13,
                          CONCAT22(extraout_var_05,CONCAT11(extraout_AH_06,extraout_AL_05)));
          }
        }
        else {
          FUN_7ff7a3b94f40(uVar3,"item_quantity");
          if ((CONCAT22(extraout_var_06,CONCAT11(extraout_AH_07,extraout_AL_06)) &
              CONCAT22(extraout_var_06,CONCAT11(extraout_AH_07,extraout_AL_06))) == 0) {
            FUN_7ff7a340f750(param_2,uVar2);
            *(uint *)(param_1 + 0x6c) =
                 CONCAT22(extraout_var_07,CONCAT11(extraout_AH_08,extraout_AL_07));
          }
          else {
            FUN_7ff7a3b94f40(uVar3,"mod_date_time");
            if ((CONCAT22(extraout_var_08,CONCAT11(extraout_AH_09,extraout_AL_08)) &
                CONCAT22(extraout_var_08,CONCAT11(extraout_AH_09,extraout_AL_08))) == 0) {
              FUN_7ff7a340f750(param_2,uVar2);
              *(uint *)(param_1 + 0xc4) =
                   CONCAT22(extraout_var_09,CONCAT11(extraout_AH_10,extraout_AL_09));
            }
          }
        }
      }
    }
    FUN_7ff7a340f240(param_2,uVar2);
    uVar2 = CONCAT44(extraout_var_14,
                     CONCAT22(extraout_var_10,CONCAT11(extraout_AH_11,extraout_AL_10)));
    uVar1 = CONCAT44(extraout_var_14,
                     CONCAT22(extraout_var_10,CONCAT11(extraout_AH_11,extraout_AL_10))) &
            CONCAT44(extraout_var_14,
                     CONCAT22(extraout_var_10,CONCAT11(extraout_AH_11,extraout_AL_10)));
  }
  return;
}

