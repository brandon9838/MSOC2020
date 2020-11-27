
# coding: utf-8

# In[ ]:


from __future__ import print_function

import sys
import numpy as np
from time import time
import matplotlib.pyplot as plt 

sys.path.append('/home/xilinx')
from pynq import Overlay
from pynq import allocate

if __name__ == "__main__":
    print("Entry:", sys.argv[0])
    print("System argument(s):", len(sys.argv))

    print("Start of \"" + sys.argv[0] + "\"")

    ol = Overlay("/home/xilinx/IPBitFile_temp/design_1.bit")
    ipFIRN11 = ol.matrixmul_0

    

    inBuffer0 = allocate(shape=(4,4), dtype=np.int16)
    inBuffer1 = allocate(shape=(4,4), dtype=np.int16)
    outBuffer0 = allocate(shape=(4,4), dtype=np.int16)
    a=[[0,0,0,1],
       [0,0,1,0],
       [0,1,0,0],
       [1,0,0,0]]
    b=[[0,0,0,1],
       [0,0,1,1],
       [0,1,1,1],
       [1,1,1,1]]
    for i in range(4):
        for j in range(4):
            inBuffer0[i][j] = a[i][j]
            inBuffer1[i][j] = b[i][j]
    
    timeKernelStart = time()
    
    ipFIRN11.write(0x10, inBuffer0.device_address)
    ipFIRN11.write(0x18, inBuffer1.device_address)
    ipFIRN11.write(0x20, outBuffer0.device_address)
    ipFIRN11.write(0x00, 0x01)
    while (ipFIRN11.read(0x00) & 0x4) == 0x0:
        continue
    timeKernelEnd = time()
    print("Kernel execution time: " + str(timeKernelEnd - timeKernelStart) + " s")
      
    print(outBuffer0)

    print("============================")
    print("Exit process")

