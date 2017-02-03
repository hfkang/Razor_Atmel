from PIL import Image

im = Image.open("picture.bmp")

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