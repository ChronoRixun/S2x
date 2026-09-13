// image offset 0x20BCC0 address 7ff7a339bcc0

longlong FUN_7ff7a339bcc0(longlong param_1,uint param_2)

{
  _eh_vector_destructor_iterator_((void *)(param_1 + -0x230),0x38,10,FUN_7ff7a339bc20);
  FUN_7ff7a3bbc060(param_1 + -0x288);
  FUN_7ff7a3c04d10(param_1);
  if ((param_2 & 1) != 0) {
    if ((param_2 & 4) == 0) {
      FUN_7ff7a3c05240(param_1 + -0x298);
    }
    else {
      FUN_7ff7a31a2b10(param_1 + -0x298,0x2a8);
    }
  }
  return param_1 + -0x298;
}

