import os

vBusMax = 32.0
vShuntMax = 0.32

rShunt = float(input("Enter the vlaue of R-Shunt in ohm: "))

maxExpCurr = float(input("Enter Maximum Expected current: "))

currLSB = round(maxExpCurr/pow(2,15),4)
powLSB = 20*currLSB
calVal = round(0.04096/(currLSB*rShunt))

print(maxExpCurr, rShunt, currLSB,powLSB,calVal)

with open(os.path.join(os.path.dirname(os.path.abspath(__file__)),'src','enumDef.txt'),'r') as firstfile, open(os.path.join(os.path.dirname(os.path.abspath(__file__)),'..','include','INA219.hpp'),'w') as secondFile:
    for line in firstfile:
        secondFile.write(line)
    firstfile.close()
    secondFile.close()

_data1 = ['\n',
          '#define VBUS_MAX ',
          '#define VSHUNT_MAX ',
          '#define RSHUNT ',
          '#define MaxExpected_I ',
          '',
          '#define CALVAL ',
          '#define Current_LSB ',
          '#define Power_LSB ']
_data2 = ['',str(vBusMax),str(vShuntMax),str(rShunt),str(maxExpCurr),'',str(calVal),str(currLSB),str(powLSB)]

f = open(os.path.join(os.path.dirname(os.path.abspath(__file__)),'..','include','INA219.hpp'),'a')
data = []
for dp in range(len(_data1)):
    data.append(_data1[dp] + _data2[dp]+'\n')
    f.write(data[dp])
f.close()

with open(os.path.join(os.path.dirname(os.path.abspath(__file__)),'src','class.txt'),'r') as firstfile, open(os.path.join(os.path.dirname(os.path.abspath(__file__)),'..','include','INA219.hpp'),'a') as secondFile:
    for line in firstfile:
        secondFile.write(line)
    firstfile.close()
    secondFile.close()