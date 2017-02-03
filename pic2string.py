from PIL import Image, ImageFilter
filename = "polymon_images/logo.bmp"
print("File name: " + filename)

try:
    im = Image.open(filename)
except:
    print("Cannot load image for some unfathomable reason.")
    
im.load()

rgb_im = im.convert('RGB')
#print(rgb_im.getpixel((1,1)))

[dimx, dimy] = rgb_im.size

heximage = []

for xpix in range(0, dimx):
    thisrow = []
    onebyte = ""
    for ypix in range(dimy-1, 1, -1):
        rgb_tuple = rgb_im.getpixel((xpix, ypix))
        if rgb_tuple[0]==0:
            #is black
            onebyte = onebyte + "1"
        elif rgb_tuple[0]==255:
            #is white
            onebyte = onebyte + "0"
        else:
            print("Error: There is only black and white morality, foolish mortal.")
            
        if len(onebyte) == 8:
            newbyte = hex(int(onebyte,2)).upper()
            if len(newbyte) == 3: newbyte = newbyte[0:2] + "0" + newbyte[2:3]
            thisrow.append(newbyte)
            onebyte = ""
    heximage.append(thisrow)
    
fstr = "{"

for row in heximage:
    fstr += "{" + str(row)[1:-1] + "}\n"
    
fstr += "}"

print(fstr)
    



'''
imstring = str(im.tobytes()).replace('x', '0x').split('\\')
imstring = imstring[1:len(imstring)-2]


newstring = ""
for i in range(len(imstring)):
    newstring = newstring + imstring[i] + ', '
    if(i%7 == 6):
        newstring = newstring[0:len(newstring)-2] + '},\n{'
newstring = '{{' + newstring[0:len(newstring)-2] +'}'
newstring = newstring.replace('a', 'A').replace('b', 'B').replace('c', 'C').replace('d', 'D').replace('e', 'E').replace('f', 'F')
print(newstring)
'''