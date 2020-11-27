
# coding: utf-8

# In[3]:


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
    ipFIRN11 = ol.diff_sq_acc_0
    ipDMAIn0 = ol.axi_dma_in_0
    ipDMAIn1 = ol.axi_dma_in_1
    ipDMAOut0 = ol.axi_dma_out_0
    '''
    fiSamples = open("samples_triangular_wave.txt", "r+")
    numSamples = 0
    line = fiSamples.readline()
    while line:
        numSamples = numSamples + 1
        line = fiSamples.readline()
    '''
    inBuffer0 = allocate(shape=(10,), dtype=np.int32)
    inBuffer1 = allocate(shape=(10,), dtype=np.int32)
    outBuffer0 = allocate(shape=(10,), dtype=np.int32)
    
    '''
    fiSamples.seek(0)
    for i in range(numSamples):
        line = fiSamples.readline()
        inBuffer0[i] = int(line)
    fiSamples.close()
    '''
    '''
    numTaps = 11
    n32Taps = [0, -10, -9, 23, 56, 63, 56, 23, -9, -10, 0]
    #n32Taps = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1]
    n32DCGain = 0
    '''
    a=[11,4,14,3,7,5,1,1,10,12]
    b=[7,0,4,8,4,5,7,1,2,6]
    for i in range(10):
        inBuffer0[i]=a[i]
        inBuffer1[i]=b[i]
    timeKernelStart = time()
    '''
    for i in range(10):
        n32DCGain = n32DCGain + n32Taps[i]
        ipFIRN11.write(0x40 + i * 4, n32Taps[i])
    if n32DCGain < 0:
        n32DCGain = 0 - n32DCGain
    '''
    ipFIRN11.write(0x00, 0x01)
    ipDMAIn0.sendchannel.transfer(inBuffer0)
    ipDMAIn1.sendchannel.transfer(inBuffer1)
    ipDMAOut0.recvchannel.transfer(outBuffer0)
    ipDMAIn0.sendchannel.wait()
    ipDMAIn1.sendchannel.wait()
    ipDMAOut0.recvchannel.wait()
    timeKernelEnd = time()
    print("Kernel execution time: " + str(timeKernelEnd - timeKernelStart) + " s")
    print(outBuffer0)
    '''
    plt.title("FIR Response")
    plt.xlabel("Sample Point") 
    plt.ylabel("Magnitude")
    xSeq = range(len(inBuffer0))
    
    if n32DCGain == 0:
        plt.plot(xSeq, inBuffer0, 'b.', xSeq, outBuffer0, 'r.')
    else:
        plt.plot(xSeq, inBuffer0, 'b.', xSeq, outBuffer0 / n32DCGain, 'r.')
    
    plt.grid(True)
    plt.show() # In Jupyter, press Tab + Shift keys to show plot then redo run
    '''
    print("============================")
    print("Exit process")

