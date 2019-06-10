from PIL import Image

name = 'monkey'
ftype = '.jpg'

source = Image.open(name+ftype)
base = source
base.convert('RGB')
base.save(name+'-base.bmp')

bw = base
bw = bw.convert('L')
bw = bw.convert('RGB')
bw.save(name+'-bw.bmp')

dither = base
dither = dither.convert('1')
dither = dither.convert('RGB')
dither.save(name+'-dither.bmp')