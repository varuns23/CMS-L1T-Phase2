FRAMESPERWORD = 9

def get_hex(number, precision):
    if(precision == 2):
        s = f"0x{number:02x}"
    elif(precision == 4):
        s = f"0x{number:04x}"
    elif(precision == 16):
        s = f"0x{number:016x}"
    else:
        s = "Choose correct precision: 2, 4 or 16"
    return s;


def get_header(nLinks):
    s = "#\n"
    s += "#WordCnt"+" "*16
    for ilink in range(nLinks):
        s += f"Link_{ilink:03d}"+" "*18
    s += "\n#BeginData\n"
    return s

def get_ldata(metadata, data, mFlag=False):
    if(mFlag == True):
        s = get_hex(metadata, 2)+ " " + get_hex(data, 16) + " "*3 
    else:
        s = " "*5 + get_hex(data, 16) + " "*3
    return s


def writeTV(fName, mFlag=False):
   file = open(fName, "w") 
   file.write(get_header(nLinks))
   for iframe in range(nFrames):
       file.write(get_hex(iframe,4) + " "*3)
       for ilink in range(nLinks):
           file.write(get_ldata(0, 0, mFlag))
       file.write("\n")
   file.close()

    
if __name__ == "__main__":
   #Get the number of words for test vector
   #nWords = int(input("Enter the number of words needed for TV: "))
   #nLinks = int(input("\nEnter the number of Input Links: "))
   nWords = 2
   nFrames = nWords * FRAMESPERWORD 
   nLinks = 5

   writeTV("temp_tv.txt", False)
   