// image offset 0x9F1090 address 7ff7a3b81090

int FUN_7ff7a3b81090(longlong param_1,char *param_2,char *param_3)

{
  longlong lVar1;
  undefined8 *puVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  longlong *plVar6;
  undefined8 uVar7;
  ulonglong *puVar8;
  ulonglong uVar9;
  undefined **ppuVar10;
  int local_res20 [2];
  undefined8 uVar11;
  
  uVar7 = *(undefined8 *)(param_1 + 0x440b8);
  local_res20[0] = 0;
  plVar6 = (longlong *)FUN_7ff7a3b32550(param_2,*(undefined8 *)(param_1 + 0xa8));
  if (plVar6 == (longlong *)0x0) {
    puVar8 = (ulonglong *)FUN_7ff7a3b32550(param_2,param_1 + 0x440d0);
    if (puVar8 == (ulonglong *)0x0) {
      local_res20[0] = FUN_7ff7a3b836d0(param_2,1,param_1);
      if (local_res20[0] != 0) {
        return local_res20[0];
      }
      puVar8 = (ulonglong *)FUN_7ff7a3b32550(param_2,param_1 + 0x440d0);
    }
    iVar5 = *(int *)(param_1 + 0x58);
    if (*(int *)(param_1 + 0x5c) == iVar5) {
      if (iVar5 == 0) {
        uVar11 = 0;
      }
      else {
        uVar11 = *(undefined8 *)(param_1 + 0x60);
      }
      uVar11 = FUN_7ff7a3b32a90(uVar7,0x18,iVar5,iVar5 + 1,uVar11,local_res20);
      *(undefined8 *)(param_1 + 0x60) = uVar11;
      if (local_res20[0] != 0) {
        return local_res20[0];
      }
      uVar9 = (ulonglong)*(uint *)(param_1 + 0x58);
      lVar1 = *(longlong *)(param_1 + 0x60);
      *(undefined8 *)(lVar1 + uVar9 * 0x18) = 0;
      *(undefined8 *)(lVar1 + 8 + uVar9 * 0x18) = 0;
      *(undefined8 *)(lVar1 + 0x10 + uVar9 * 0x18) = 0;
      *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + 1;
    }
    uVar9 = *puVar8;
    if (uVar9 < 0x53) {
      ppuVar10 = &PTR_s_ADD_STYLE_NAME_7ff7a3d808a0 + uVar9 * 3;
    }
    else {
      ppuVar10 = (undefined **)(*(longlong *)(param_1 + 0x440c0) + (uVar9 - 0x53) * 0x18);
    }
    puVar2 = (undefined8 *)
             (*(longlong *)(param_1 + 0x60) + (ulonglong)*(uint *)(param_1 + 0x5c) * 0x18);
    *puVar2 = *ppuVar10;
    *(undefined4 *)(puVar2 + 1) = *(undefined4 *)(ppuVar10 + 1);
    *(undefined4 *)((longlong)puVar2 + 0xc) = *(undefined4 *)((longlong)ppuVar10 + 0xc);
    iVar5 = *(int *)(ppuVar10 + 1);
    if (iVar5 == 1) {
      puVar2[2] = 0;
      if ((param_3 != (char *)0x0) && (*param_3 != '\0')) {
        uVar11 = FUN_7ff7a3b32bb0(uVar7,param_3,local_res20);
        puVar2[2] = uVar11;
        if (local_res20[0] != 0) {
          return local_res20[0];
        }
      }
    }
    else if (iVar5 == 2) {
      uVar4 = FUN_7ff7a3b81460(param_3);
      *(undefined4 *)(puVar2 + 2) = uVar4;
    }
    else if (iVar5 == 3) {
      uVar4 = FUN_7ff7a3b815d0(param_3);
      *(undefined4 *)(puVar2 + 2) = uVar4;
    }
    iVar5 = strncmp(param_2,"COMMENT",7);
    if ((((iVar5 == 0) && ((byte)param_2[7] < 0x21)) &&
        ((0x100002601U >> ((longlong)param_2[7] & 0x3fU) & 1) != 0)) ||
       (local_res20[0] =
             thunk_FUN_7ff7a3b33630
                       (*puVar2,*(undefined4 *)(param_1 + 0x5c),*(undefined8 *)(param_1 + 0xa8),
                        uVar7), local_res20[0] == 0)) {
      *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + 1;
      iVar5 = strncmp(param_2,"DEFAULT_CHAR",0xc);
      if (((iVar5 == 0) && ((byte)param_2[0xc] < 0x21)) &&
         ((0x100002601U >> ((longlong)param_2[0xc] & 0x3fU) & 1) != 0)) {
        *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(puVar2 + 2);
      }
      else {
        iVar5 = strncmp(param_2,"FONT_ASCENT",0xb);
        if (((iVar5 == 0) && ((byte)param_2[0xb] < 0x21)) &&
           ((0x100002601U >> ((longlong)param_2[0xb] & 0x3fU) & 1) != 0)) {
          *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(puVar2 + 2);
        }
        else {
          iVar5 = strncmp(param_2,"FONT_DESCENT",0xc);
          if (((iVar5 == 0) && ((byte)param_2[0xc] < 0x21)) &&
             ((0x100002601U >> ((longlong)param_2[0xc] & 0x3fU) & 1) != 0)) {
            *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(puVar2 + 2);
          }
          else {
            iVar5 = strncmp(param_2,"SPACING",7);
            if (((iVar5 == 0) && ((byte)param_2[7] < 0x21)) &&
               ((0x100002601U >> ((longlong)param_2[7] & 0x3fU) & 1) != 0)) {
              if ((char *)puVar2[2] == (char *)0x0) {
                local_res20[0] = 3;
              }
              else {
                cVar3 = *(char *)puVar2[2];
                if ((cVar3 + 0xb0U & 0xdf) == 0) {
                  *(undefined4 *)(param_1 + 0x20) = 8;
                }
                else if ((cVar3 + 0xb3U & 0xdf) == 0) {
                  *(undefined4 *)(param_1 + 0x20) = 0x10;
                }
                else if ((cVar3 + 0xbdU & 0xdf) == 0) {
                  *(undefined4 *)(param_1 + 0x20) = 0x20;
                }
              }
            }
          }
        }
      }
    }
  }
  else {
    iVar5 = *(int *)(*(longlong *)(param_1 + 0x60) + 8 + *plVar6 * 0x18);
    lVar1 = *(longlong *)(param_1 + 0x60) + *plVar6 * 0x18;
    if (iVar5 == 1) {
      FUN_7ff7a3b32970(uVar7,*(undefined8 *)(lVar1 + 0x10));
      *(undefined8 *)(lVar1 + 0x10) = 0;
      if ((param_3 != (char *)0x0) && (*param_3 != '\0')) {
        uVar7 = FUN_7ff7a3b32bb0(uVar7,param_3,local_res20);
        *(undefined8 *)(lVar1 + 0x10) = uVar7;
        return local_res20[0];
      }
    }
    else {
      if (iVar5 == 2) {
        uVar4 = FUN_7ff7a3b81460(param_3);
        *(undefined4 *)(lVar1 + 0x10) = uVar4;
        return local_res20[0];
      }
      if (iVar5 == 3) {
        uVar4 = FUN_7ff7a3b815d0(param_3);
        *(undefined4 *)(lVar1 + 0x10) = uVar4;
        return local_res20[0];
      }
    }
  }
  return local_res20[0];
}

