// image offset 0x20D390 address 7ff7a339d390

void FUN_7ff7a339d2f0(void *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  
  uVar2 = 0;
  *(undefined4 *)((longlong)param_1 + 0xc842c) = 0;
  *(undefined1 *)((longlong)param_1 + 0xc8430) = 0;
  memset((void *)((longlong)param_1 + 0xc66e0),0,0x1d4c);
  memset(param_1,-1,0x4000);
  memset((void *)((longlong)param_1 + 0x4000),0,0x4000);
  puVar1 = (undefined4 *)((longlong)param_1 + 0x8008);
  do {
    *(undefined8 *)(puVar1 + -2) = 0;
    *puVar1 = 0xffffffff;
    uVar2 = uVar2 + 1;
    *(undefined8 *)(puVar1 + 2) = 0x7fffffffffffffff;
    *(undefined2 *)(puVar1 + 4) = 0;
    *(undefined1 *)(puVar1 + 0x16) = 0;
    *(undefined8 *)(puVar1 + 6) = 0;
    *(undefined8 *)(puVar1 + 8) = 0;
    *(undefined8 *)(puVar1 + 10) = 0;
    *(undefined8 *)(puVar1 + 0xc) = 0;
    *(undefined8 *)(puVar1 + 0xe) = 0;
    *(undefined8 *)(puVar1 + 0x10) = 0;
    *(undefined8 *)(puVar1 + 0x12) = 0;
    *(undefined8 *)(puVar1 + 0x14) = 0;
    puVar1 = puVar1 + 0x1a;
  } while (uVar2 < 0x1d4c);
  return;
}

