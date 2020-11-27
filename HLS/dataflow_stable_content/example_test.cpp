// 67d7842dbbe25473c3c32b93c0da8047785f30d78e8a024de1b57352245f9689
#include <iostream>
#include <stdlib.h>
#include "example.h"

void example(strm_t &in1, strm_t &in2, strm_t &out);

int validation(int* in1, int*in2){
	int ans=0;
	for(int i=0;i<10;i++){
		  if ((in2[i]!=0) && (in1[in2[i]]<10)){
			  ans+=in1[in2[i]];
		  }
	}
	return ans;
}
int main()
{
  // Declare streams
  strm_t in1, in2, out;
  int tempa[10];
  int tempb[10];

  // Write data into a and b
  value_t valDataCtrl;
  valDataCtrl.data = 0;
  valDataCtrl.keep = 0xF;
  valDataCtrl.strb = 0;
  valDataCtrl.user = 0;
  valDataCtrl.last = 0;
  valDataCtrl.id = 0;
  valDataCtrl.dest = 0;
  for (int i = 0; i < 10; i++)
  {
    int a = rand() % 15;
    int b = rand() % 10;
    if (i==9) {valDataCtrl.last = 1;}
    valDataCtrl.data=a;
    in1.write(valDataCtrl);
    tempa[i]=a;
    valDataCtrl.data=b;
    in2.write(valDataCtrl);
    tempb[i]=b;
  }

  example(in1, in2, out);
  int sum;
  int ans= validation(tempa,tempb);

  sum = out.read().data;
  std::cout << "sum: " << sum << std::endl;

  for (int i=0;i<10;i++){
  	  std::cout <<"a: "<< tempa[i]<<", b: "<<tempb[i]<<" a[b]: "<<tempa[tempb[i]]<<std::endl;
  }
  if (sum==ans){
	  std::cout << std::endl;
	  std::cout << "------------PASS--------------------" << std::endl;
	  std::cout << std::endl;
	  return 0;
  }

  std::cout << sum << std::endl;
  std::cout << ans << std::endl;
  return 1;
}
